/**
* Function already complete:
* 2013/12/10  DS18b20 : temprature measurement
* 2013/12/11  nRF24L01: wireless communication
* 2013/12/23  combainn server & client node in sigle project
* tusion@163.com 
**/

/* The two liabrary should download to .../arduino/library/ */
//Ds18b20 use one wire bus connect Arduino GPIO
#include <OneWire.h>  
//wrap some founction of Ds18b20
#include <DallasTemperature.h>
/*wireless communication chip nRF24L01 connect on SPI */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//#include <RF24Network.h>
#include <EEPROM.h>
#include "MyCommon.h"


/********************************************************************/
// config all 
/********************************************************************/
#define CONFIG_NODE_NO
#define WRITE_NODE_NO    3 //server 1, client 2-6

//#define DS18B20_ENABLE    
#define PIR_ENABLE      

// temperature sensor Ds18b20 data pin connect to pin 7
#define DS18B20_DATA_PIN   7
// numbers of Ds18b20 connected
#define NUM_TMERATURE_SENSORS     3
//Ds18b20 usual precision 9,10,11,12
#define TEMPERATURE_PRECISION       12

// nRF24L01 connect on SPI bus
#define CE_PIN             9
#define CSN_PIN            10

//serial port baudrate 9600(default)/ 19200 / 115200
#define SERIAL_BAUDRATE             9600
/********************************************************************/

/********************************************************************
/*  DallasTemperature liabrary initial something */
/*******************************************************************/

// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire( DS18B20_DATA_PIN );
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature TempSensors( &oneWire );
// usually we use mutiple Ds18b20 one one wire bus.
int numOfFindTempSensors;
//arrays to hold device address 
DeviceAddress TempSensorsAddress[NUM_TMERATURE_SENSORS];
//TempSensorsAddress[0] = {0x28, 0x17, 0x69, ox45, 0x05, ox00, 0x00, 0x76};
//TempSensorsAddress[1] = {0x28, 0x6F, 0x07, 0x45, ox05, 0x00, 0x00, 0xFC};

/********************************************************************/
// nRF24L01 Wireless communication initial something 
/********************************************************************/
//setup nRF23L01 radio on SPI bus plus pins 9 & 10.
RF24 radio( CE_PIN, CSN_PIN );

// server <-- nodes
const uint64_t node_to_server_pipes[5] = {  0xF0F0F0F0D2LL,
                                            0xF0F0F0F0C3LL,
                                            0xF0F0F0F0B4LL,
                                            0xF0F0F0F0A5LL,
                                            0xF0F0F0F096LL };
// server --> nodes                                    
const uint64_t server_to_node_pipes[5]={   0x3A3A3A3AD2LL,
                                           0x3A3A3A3AC3LL,
                                           0x3A3A3A3AB4LL,
                                           0x3A3A3A3AA5LL,
                                           0x3A3A3A3A96LL };

//role store in EEOPROM, 1:server, 2-6:nodes.
typedef enum { role_invalid = 0, role_server, role_node } role_e;
role_e  role;


// function to print a device address
void printAddress(DeviceAddress deviceAddress);
// function to print the temperature for a device
void printTempraturues(DeviceAddress deviceAddress);
// setup DS18b20
void setupTemperatureSensors( void );
void clearMonitorMesg( payload_monitor monitor_mesg);
void printMonitorMesg( payload_monitor monitor_mesg );

payload_control     commander_mesg;
payload_monitor monitor_mesg;
// role define at EEPROM addr 0
const uint8_t address_at_eeprom = 0;
//sensor node no.
uint8_t node_NO;
//how many messages we send
unsigned long num_of_mesg = 0;
//when did client node send last message
unsigned long client_last_sent = 0;


void setup( void )
{
  
  //start serial port
  Serial.begin( SERIAL_BAUDRATE );
  
  //------------- Node role detect -------------------------
  //config node number in the EEPROM at address 0
  #ifdef CONFIG_NODE_NO
    Serial.println("1. Config node number ." );
    if( EEPROM.read( address_at_eeprom) != WRITE_NODE_NO  )
    {
      Serial.println(" write node number in EEPROM...");
      EEPROM.write( address_at_eeprom, WRITE_NODE_NO );
      Serial.print(" Now, write node NO. is: ");
      Serial.println( EEPROM.read( address_at_eeprom) );
      delay(2000);
    }
    else
    {
      Serial.print(" Node number is already: ");
      Serial.print( EEPROM.read( address_at_eeprom) );
      Serial.println(", do not need reconfigure.");
    }
  #endif 
 
  uint8_t reading = EEPROM.read( address_at_eeprom);
  if( reading == 1 )
  {
     //sensor server
    role = role_server;
    node_NO = reading;
  }
  else if( reading >= 2 && reading <= 6 )
  {
    //sensor node
    role = role_node;
    node_NO = reading;
  }
  else 
  {
    node_NO = 0;
    role = role_invalid;
  }
  Serial.print(" Node NO: ");
  Serial.print( node_NO );
  Serial.println(" , (role store in EEOPROM, 1:server, 2-6:nodes.)");

  //--------------------- initial RF chip ------------------
  Serial.print("2. Initial RF24 ...");
  // setup and config rf radio
  radio.begin();
 
  if( role == role_server )
  { 
    Serial.println(" This is server node ." );
    for( uint8_t i=0; i<5; i++ )
    {
      radio.openReadingPipe( i+1, node_to_server_pipes[i] );
      radio.openWritingPipe( server_to_node_pipes[i] );
    }
    //radio.openReadingPipe( 1, talking_pipes[0] );
  }

  if( role == role_node )
  {
    //sensor node at NO 2-6
    Serial.println(" This is sensor node ." );
    radio.openWritingPipe( node_to_server_pipes[ node_NO-2 ] );
    radio.openReadingPipe(1, server_to_node_pipes[ node_NO-2 ] );
  }
  
  radio.startListening();
  // Dump the configuration of the rf unit for debugging
  //radio.printDetails();
  Serial.println(" RF ok !!!");
  
  // Initail all DS18b20 on the 1-wire bus, print infomations.
  //if( node_NO == 2 || node_NO == 4 )
  Serial.println("3. Initial DS18b20 sensors...");
  setupTemperatureSensors();

  Serial.println("============ Finish setup =================");

  
}

void loop( void ) 
{
    // sensor client node.
   if( role == role_node )
   {
    //client always wait for server send heart beat at 1s interval.
    if( radio.available() )
    {      
      //got a message at 1s interval
      unsigned long receive_time = millis();
      client_last_sent = receive_time;
       unsigned long got_time;
      bool done = false;
  
      // step1; receive server's hear beat signal
       while( !done )
       {
         // get the message from serveR
         done = radio.read(  &commander_mesg, sizeof(commander_mesg) );
       }
       // stop listening so we can talk.
       radio.stopListening();
   
       // step2: do something in loop: such as ds18b20
       clearMonitorMesg( monitor_mesg );
       monitor_mesg.Counter = commander_mesg.Counter;
       monitor_mesg.FromNode = node_NO;
       monitor_mesg.PIR = 0;
       for( uint8_t j=0; j<8; j++ )
        {
          monitor_mesg.SwitchState[j] = commander_mesg.SwitchControl[j];
          monitor_mesg.AlarmState[j] = commander_mesg.AlarmControl[j];
        }
       
       // scan all 3 ds18b20 time cost:
       // precesion  9: 140ms;   12: 800ms.
       TempSensors.requestTemperatures();
       for(uint8_t i=0; i<numOfFindTempSensors; i++ ) 
       {
         monitor_mesg.TempC[i] = TempSensors.getTempC(TempSensorsAddress[i]);
       }
      monitor_mesg.CostTime = millis()- receive_time;
      //Serial.print(", sensor cost time(ms): ");
      //Serial.print(monitor_mesg.CostTime );
  
      // step3: send response back to server.
       bool write_status = radio.write( &monitor_mesg, sizeof(monitor_mesg));
       if( write_status )
       {
        printMonitorMesg( monitor_mesg ); 
       }
       else
       {
        Serial.println(" send back failed. ");
       } 
       radio.startListening();
     }
   }
   else if(  role == role_server )
   {
     ;//
   }
   else
   {
     Serial.println("this node role is not invalid, pls check.");
     delay(500);
   }

  
}





void printMonitorMesg( payload_monitor monitor_mesg )
{
  Serial.print("{\"name\": \"monitor\"");
  Serial.print(", \"Counter\": ");
  Serial.print( monitor_mesg.Counter );
  Serial.print(", \"CostTime\": ");
  Serial.print( monitor_mesg.CostTime );
  Serial.print(", \"FromNode\": ");
  Serial.print( monitor_mesg.FromNode );
  Serial.print(", \"TempC\":[");
  Serial.print( monitor_mesg.TempC[0] );
  Serial.print(", ");
  Serial.print( monitor_mesg.TempC[1] );
  Serial.print(",");
  Serial.print( monitor_mesg.TempC[2] );
  Serial.print("], \"Humd\": ");
  Serial.print( monitor_mesg.Humd );
  Serial.print(", \"PIR\": ");
  Serial.print( monitor_mesg.PIR );
  Serial.print(", \"SwitchState\": [");
  for( uint8_t t=0; t<8; t++ )
  {
    if( monitor_mesg.SwitchState[t] == true )
      Serial.print( 1 );
    else
      Serial.print( 0 );
    if( t<7 )
      Serial.print(",");
  }
  Serial.print("], \"AlarState\": [");
  for( uint8_t t=0; t<8; t++ )
  {
    if( monitor_mesg.AlarmState[t] == true )
      Serial.print( 1 );
    else
      Serial.print( 0 );
    if( t<7 )
      Serial.print(",");
  }
  Serial.println("] } ");
}

void clearMonitorMesg( payload_monitor monitor_mesg )
{
  monitor_mesg.Counter  = 0;
  monitor_mesg.CostTime = 0;
  monitor_mesg.FromNode = 0;
  monitor_mesg.TempC[0] = 0;
  monitor_mesg.TempC[1] = 0;
  monitor_mesg.TempC[2] = 0;
  monitor_mesg.Humd     = 0;
  monitor_mesg.PIR      = false;
  for( uint8_t x=0; x<8; x++ )
  {
    monitor_mesg.SwitchState[x] == false;
    monitor_mesg.AlarmState[x] == false;
  }
}


// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// function to print the temperature for a device
void printTempraturues(DeviceAddress deviceAddress)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  //printTemperature(deviceAddress);
  float tempC = TempSensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.println(tempC);
  //Serial.println();
}

//
void setupTemperatureSensors( void )
{
  numOfFindTempSensors = 0;
  
  Serial.println("------------Inital temperature sensors --------");
  //start up DallasTemperature library
  TempSensors.begin();
  
  //get count of temperature sensor 
  Serial.println("Scan connect 1-wire devices ...");
  numOfFindTempSensors = TempSensors.getDeviceCount();
  Serial.print("Found devices number:         ");
  Serial.println( numOfFindTempSensors,DEC );
  Serial.print("Actual connect device number: ");
  Serial.println( NUM_TMERATURE_SENSORS,DEC );
  if( numOfFindTempSensors < NUM_TMERATURE_SENSORS )
  {
    Serial.print("Warn: lost 1-wire devices number: ");
    Serial.println((NUM_TMERATURE_SENSORS-numOfFindTempSensors), DEC);
  }
  else
  {
    Serial.println("OK,all 1-wire device are found !");
  }
  
  Serial.println("Congfigure devices ... ");
  // scan all temperature sensors, print address and resolution
  for(uint8_t i=0; i<numOfFindTempSensors; i++ ) 
  {
    if(!TempSensors.getAddress( TempSensorsAddress[i], i) )
    {
      Serial.print("Unable to find address for 1-wire device number: ");
      Serial.println( i, DEC );
      //break;
    }
    //print address of ds18b20.
    Serial.print("Address of temprature sensor " );
    Serial.print( i, DEC);
    Serial.print(" : ");
    printAddress( TempSensorsAddress[i] );
    Serial.println();
    
    //set resolution of ds18b20
    TempSensors.setResolution(TempSensorsAddress[i],TEMPERATURE_PRECISION );
    //print resolution of ds18b20.
    Serial.print("Resolution of temprature sensor " );
    Serial.print( i, DEC);
    Serial.print(" : ");
    Serial.println( TempSensors.getResolution(TempSensorsAddress[i]) );
  }         
  Serial.println("");
  Serial.println("------------------------------------------------");               
}


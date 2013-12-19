/**
* Function already complete:
* 2013/12/10  DS18b20 : temprature measurement
* 2013/12/11  nRF24L01: wireless communication
*
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


//#define DS18B20_ENABLE    
#define PIR_ENABLE      

// nRF24L01 connect on SPI bus
#define CE_PIN             9
#define CSN_PIN            10

//serial port baudrate 9600(default)/ 19200 / 115200
#define SERIAL_BAUDRATE             9600


/* Pin connect assgiment */
// Toggle LED 
//#define LED_PIN            0

/********************************************************************
/*  DallasTemperature liabrary initial something */
/*******************************************************************/
// temperature sensor Ds18b20 data pin connect to pin 7
#define DS18B20_DATA_PIN   8
// numbers of Ds18b20 connected
#define NUM_TMERATURE_SENSORS     3
//Ds18b20 usual precision 9,10,11,12
#define TEMPERATURE_PRECISION       9
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
//NO.1 = 2817694505000076
//NO.2 = 286F0745050000FC
// function to print a device address
void printAddress(DeviceAddress deviceAddress);
// function to print the temperature for a device
void printTempraturues(DeviceAddress deviceAddress);
// setup 
void setupTemperatureSensors( void );

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

// role define at EEPROM addr 0
const uint8_t address_at_eeprom = 0;

//sensor node no.
uint8_t node_NO;

//every message interval time
//const unsigned long interval = 1000; //ms

//how many messages we send
unsigned long num_of_mesg = 0;

//when did client node send last message
unsigned long last_sent = 0;



//Struct of our payload
struct payload_com
{
  unsigned long counter;    // Heat beat counter.
  unsigned long timestamp;  // server start heart beat request time.
  uint8_t       DesNode;    // destination to node's NO
  bool          SwitchControl[8]; // every bit control a delay switch
  bool          AlarmControl[8];  //every bit control a beep. 
};

struct payload_monitor
{
  unsigned long counter;    // Heat beat counter.
  unsigned long CostTime;    // complete all sensors cost at nods time.
  uint8_t       FromNode;    // message from node's NO
  float         TempC[3];   // temperature sensor  less than 3.
  float         humd;       // humandity sensor data
  bool          PIR;        // human move singal data   
  bool          SwitchState[8]; // state of switch.  
  bool          AlarmState[8];  //every bit control a beep. 
};



// print payload data from RF24 communication
//void printMessage( payload_t payload );

void setup( void )
{
  //initialize digitak pin as output for led
  //pinMode(LED_PIN, OUTPUT );
  //digitalWrite( LED_PIN, HIGH );
  
  //start serial port
  Serial.begin( SERIAL_BAUDRATE );
  
  uint8_t reading = EEPROM.read( address_at_eeprom);
  if( reading == 1 )
  {
     //sensor node
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
  Serial.print("Node NO: ");
  Serial.print( node_NO );
  Serial.println(" , (role store in EEOPROM, 1:server, 2-6:nodes.)");

  //initial RF chip
  Serial.print("Initial RF24 ...");
  
  //SPI.begin();
  // setup and config rf radio
  radio.begin();
  /*
  // open pipe 0 to write,  server <--- client.
  // open pipe 1 to read.   server ---> client.
  //we can have up to 5 pipes open for reading)
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  */
  
  //is not valid at there
  if( role == role_server )
  { 
    Serial.println("This is server node ." );
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
    Serial.println("This is sensor node ." );
    radio.openWritingPipe( node_to_server_pipes[ node_NO-2 ] );
    radio.openReadingPipe(1, server_to_node_pipes[ node_NO-2 ] );
  }
  
  radio.startListening();
  // Dump the configuration of the rf unit for debugging
  //radio.printDetails();
  Serial.println("RF ok !!!");
  

  
  // Initail all DS18b20 on the 1-wire bus, print infomations.
  if( node_NO == 2 || node_NO == 4 )
  {
    Serial.println("Initial DS18b20 sensors...");
    setupTemperatureSensors();
  }

  
  Serial.println("============ Finish setup =================");

  
}

void loop( void ) 
{
  //client always wait for server send heart beat at 1s interval.
  if( radio.available() )
  {      
    //got a message at 1s interval
    unsigned long receive_time = millis();
    last_sent = receive_time;
     unsigned long got_time;
    bool done = false;
    payload_com     commander_mesg;
    payload_monitor monitor_mesg;
    
    // step1; receive server's hear beat signal
     while( !done )
     {
       // get the message from serveR
       done = radio.read(  &commander_mesg, sizeof(commander_mesg) );
     }
     Serial.print("got heartbeat: ");
     Serial.print( commander_mesg.counter );
     
     // stop listening so we can talk.
     radio.stopListening();
 
     // step2: do something in loop: such as ds18b20
     monitor_mesg.counter = commander_mesg.counter;
     monitor_mesg.FromNode = node_NO;
     monitor_mesg.PIR = 0;
     for( uint8_t j=0; j<8; j++ )
      {
        monitor_mesg.SwitchState[j] = false;
        monitor_mesg.AlarmState[j] = false;
      }
     
     // scan all 3 ds18b20 time cost:
     // precesion  9: 140ms
     // precesion 12: 800ms.
     if( node_NO == 2 || node_NO == 4 )
     {
       TempSensors.requestTemperatures();
       for(uint8_t i=0; i<numOfFindTempSensors; i++ ) 
       {
         monitor_mesg.TempC[i] = TempSensors.getTempC(TempSensorsAddress[i]);
       }
     }

     
     if( node_NO == 3 || node_NO == 5 )
     {
        if( (commander_mesg.counter % 2 ) == 1 )
          monitor_mesg.TempC[0] = 1;
        else
          monitor_mesg.TempC[0] = 2; 
        delay(100);
     }
    monitor_mesg.CostTime = millis()- receive_time;
    Serial.print(", sensor cost time(ms): ");
    Serial.print(monitor_mesg.CostTime );

    
    // step3: send response back to server.
     bool write_status = radio.write( &monitor_mesg, sizeof(monitor_mesg));
     if( write_status )
     {
       Serial.println(", send back to server ok. ");
       //Serial.println("send back ok. ");
       
       
          Serial.print("monitor { ");
          Serial.print("counter: ");
          Serial.print( monitor_mesg.counter );
          Serial.print(", CostTime: ");
          Serial.print( monitor_mesg.CostTime );
          Serial.print(", FromNode: ");
          Serial.print( monitor_mesg.FromNode );
          Serial.print(", TempC1:");
          Serial.print( monitor_mesg.TempC[0] );
          Serial.print(", TempC2:");
          Serial.print( monitor_mesg.TempC[1] );
          Serial.print(", TempC3:");
          Serial.print( monitor_mesg.TempC[2] );
          Serial.print(", humd: ");
          Serial.print( monitor_mesg.humd );
          Serial.print(", PIR: ");
          Serial.print( monitor_mesg.PIR );
          Serial.print(", SwitchState: ");
          for( uint8_t t=0; t<8; t++ )
            Serial.print( monitor_mesg.SwitchState[t],BIN );
          Serial.print(", AlarState: ");
          for( uint8_t t=0; t<8; t++ )
            Serial.print( monitor_mesg.AlarmState[t],BIN );
          Serial.println(" } ");
     }
     else
     {
      Serial.println(", send back failed. ");
     } 
     //printMessage();
     
     //Serial.println();
     //
     radio.startListening();
   }



/*

  //mannually write node no to eeprom.
  if( Serial.available() )
  {
    char c = Serial.read();
    if( c>='1' && c<='6' )
    {
      EEPROM.write( address_at_eeprom, c-'0' );
      
      Serial.print("manually write node noe to eeprom, node no:");
      Serial.println(EEPROM.read( address_at_eeprom ) );
      
      Serial.println("Press reset to continue." );
      
      while(1) 
      {
        ;
      }
    }
  }
  
  */
  
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
 /*
// print payload data from RF24 communication
void printMessage( void)
{
 Serial.print("data{ ");

 Serial.print(payload.counter);
 Serial.print("; ");
 Serial.print(payload.send_ms);
 Serial.print("; "); 
 Serial.print(payload.last_delay_ms);
 Serial.print("; ");
 Serial.print(payload.Node_NO);
 Serial.print("; ");
 Serial.print(payload.switch_state);
 Serial.print("; ");
 Serial.print(payload.tempC[0]);
 Serial.print("; ");
 Serial.print(payload.tempC[1]);
 Serial.print("; ");
 Serial.print(payload.tempC[2]);
 Serial.print("; ");
 Serial.print(payload.humd);
 Serial.print("; ");
 Serial.print(payload.PIR);
 Serial.print("; ");
 Serial.print(payload.switch_control);
 Serial.print("; ");
 Serial.print(payload.alrm);
 Serial.print("} ");

}
 */

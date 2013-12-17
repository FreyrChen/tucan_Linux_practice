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

//sensor node no.
#define NODE_NO             1
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
#define TEMPERATURE_PRECISION       12
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
RF24 radio( CE_PIN, CSN_PIN );

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL,
                            0xF0F0F0F0D2LL  };

//every message interval time
const unsigned long interval = 1000; //ms

//how many messages we send
unsigned long num_of_mesg = 0;

//when did client node send last message
unsigned long last_sent = 0;

//Struct of our payload
struct payload_t
{
  unsigned long counter;    // Heat beat counter.
  unsigned long send_ms;    // server start heart beat request time.
  unsigned long last_delay_ms; //last message delay time.
  uint8_t       Node_NO;    // message from node's NO
  
  uint8_t       switch_state;// state of switch.  
  float         tempC[3];   // temperature sensor  less than 3.
  float         humd;       // humandity sensor data
  float         PIR;        // human move singal data   
  
  uint8_t        switch_control; //command to control switch
  bool          alrm;          // control arlm beep.
  
};
payload_t payload;

// print payload data from RF24 communication
void printMessage( payload_t payload );

void setup( void )
{
  //initialize digitak pin as output for led
  //pinMode(LED_PIN, OUTPUT );
  //digitalWrite( LED_PIN, HIGH );
  
  //start serial port
  Serial.begin( SERIAL_BAUDRATE );
  
  //initial RF chip
  Serial.println("----------- initial RF24 -----------------");
  Serial.println("This is client, waitting to receive ...");
  
  SPI.begin();
  // setup and config rf radio
  radio.begin();
  // open pipe 0 to write,  server <--- client.
  // open pipe 1 to read.   server ---> client.
  //we can have up to 5 pipes open for reading)
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  radio.startListening();
  // Dump the configuration of the rf unit for debugging
  //radio.printDetails();
  Serial.println("network ok");
  
  #ifdef DS18B20_ENABLE
  // Initail all DS18b20 on the 1-wire bus, print infomations.
  setupTemperatureSensors();
  #endif
  
  Serial.println("============ Finish setup =================");

  
}

void loop( void ) 
{
  //client always wait for server send heart beat at 1s interval.
  if( radio.available() )
  {      
    //got a message at 1s interval
    unsigned long now = millis();
    last_sent = now;
     unsigned long got_time;
    bool done = false;


    
    // step1; receive server's hear beat signal
     while( !done )
     {
       // get the message from serveR
       done = radio.read(  &payload, sizeof(payload) );
     }
     
     if( payload.Node_NO != NODE_NO )
     {;
     /*
       Serial.print("Got a mesg to node: ");
       Serial.print( payload.Node_NO  );
       Serial.println(",Ignore!");
       */
     }
     else
     {
       // stop listening so we can talk.
       radio.stopListening();
   
       // step2: do something in loop: such as ds18b20
       #ifdef DS18B20_ENABLE
         TempSensors.requestTemperatures();
         for(uint8_t i=0; i<numOfFindTempSensors; i++ ) 
         {
           payload.tempC[i] = TempSensors.getTempC(TempSensorsAddress[i]);
         }
       #endif
       
       #ifdef PIR_ENABLE  
          payload.switch_state = 99;
          payload.humd = 11;
          payload.PIR = 22;
         for(uint8_t i=0; i<numOfFindTempSensors; i++ ) 
         {
           payload.tempC[i] = 0;
         }
       #endif

      // step3: send response back to server.
       delay(20);//waitting for server.
       bool write_status = radio.write( &payload, sizeof(payload));
       if( write_status )
       {
         ;
         //Serial.println("send back ok. ");
       }
       else
       {
        Serial.println("send back failed. ");
        // if failed, this delay can display slow.
        delay(100);
       } 
       printMessage();
       Serial.println();
       //
       radio.startListening();
     }
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
    TempSensors.setResolution(TempSensorsAddress[i],
                               TEMPERATURE_PRECISION );
    //print resolution of ds18b20.
    Serial.print("Resolution of temprature sensor " );
    Serial.print( i, DEC);
    Serial.print(" : ");
    Serial.println( TempSensors.getResolution(TempSensorsAddress[i]) );
  }         
  Serial.println("");
  Serial.println("------------------------------------------------");               
}

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

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
#include "nRF24L01.h"
#include "RF24.h"


/* Pin connect assgiment */
#define DS18B20_DATA_PIN   2
#define LED_PIN            8
//for nRF24L01 SPI
#define CE_PIN             9
#define CSN_PIN            10


/* Some funtion varaibles */
// numbers of Ds18b20 connected
#define NUM_TMERATURE_SENSORS 3
//Ds18b20 usual precision 9,10,11,12
#define TEMPERATURE_PRECISION 12
//serial port baudrate 9600(default)/ 19200 / 115200
#define SERIAL_BAUDRATE 9600

/*  DallasTemperature liabrary initial something */
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire( DS18B20_DATA_PIN );
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature TempSensors( &oneWire );
// usually we use mutiple Ds18b20 one one wire bus.
int numberOfTempSensors;
//arrays to hold device address 
DeviceAddress TempSensorsAddress[NUM_TMERATURE_SENSORS];

/* nRF24L01 Wireless communication initial something */
RF24 radio( CE_PIN, CSN_PIN );
//define transmit pipe, 
//'LL' at the end is 'long long' type 
const uint64_t pipe = 0xE8E8F0F0E1LL; 

void setup( void )
{
  //initialize digitak pin as output for led
  pinMode(LED_PIN, OUTPUT );
  //start serial port
  Serial.begin( SERIAL_BAUDRATE );
  
  // Initail all DS18b20 on the 1-wire bus, print infomations.
  setupTemperatureSensors();
  
  //initial RF chip
  radio.begin();
  radio.openWritingPipe(pipe);
  
}


void loop( void ) 
{
  byte i;
  
  digitalWrite( LED_PIN, ~digitalRead(LED_PIN) );
  Serial.println("Requeset temperatures ...");
  
  // sends command for all devices on the bus to perform
  // a temperature conversion
  TempSensors.requestTemperatures();
  for( i=0; i<numberOfTempSensors; i++ ) 
  {
    printTempraturues( TempSensorsAddress[i] );
  }
 
 
   /* transmit data through RF */
   
   float tempC = TempSensors.getTempC(TempSensorsAddress[0]);
   radio.write( &tempC, sizeof( float) );
 
   //delay(1000); 
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

void setupTemperatureSensors( void )
{
  byte i;
  numberOfTempSensors = 0;
  
  Serial.println("=== Inital temperature sensors ===");
  //start up DallasTemperature library
  TempSensors.begin();
  
  //get count of temperature sensor 
  Serial.println("Scan connect 1-wire devices ...");
  numberOfTempSensors = TempSensors.getDeviceCount();
  Serial.print("Found devices number:         ");
  Serial.println( numberOfTempSensors,DEC );
  Serial.print("Actual connect device number: ");
  Serial.println( NUM_TMERATURE_SENSORS,DEC );
  if( numberOfTempSensors < NUM_TMERATURE_SENSORS )
  {
    //lostTempSensors = NUM_TMERATURE_SENSORS-numberOfTempSensors;
    Serial.print("Warn: lost 1 wire devices number");
    Serial.println((NUM_TMERATURE_SENSORS-numberOfTempSensors), DEC);
  }
  else
  {
    Serial.println("OK,all 1-wire device are found !");
  }
  Serial.println();
  
  // scan all temperature sensors, print address and resolution
  for( i=0; i<numberOfTempSensors; i++ ) 
  {
    if(!TempSensors.getAddress( TempSensorsAddress[i], i) )
    {
      Serial.print("Unable to find address for 1-wire device number: ");
      Serial.println( i, DEC );
      break;
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
  Serial.println();
  Serial.println("------------------------------------------------");               
}

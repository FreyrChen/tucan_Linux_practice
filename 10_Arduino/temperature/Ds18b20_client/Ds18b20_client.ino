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
#include <RF24Network.h>


/* Pin connect assgiment */

// Toggle LED 
//#define LED_PIN            0

// temperature sensor Ds18b20 data pin connect to pin 7
#define DS18B20_DATA_PIN   8

// nRF24L01 connect on SPI bus
#define CE_PIN             9
#define CSN_PIN            10


/* Some funtion varaibles */
// numbers of Ds18b20 connected
#define NUM_TMERATURE_SENSORS       1
//Ds18b20 usual precision 9,10,11,12
#define TEMPERATURE_PRECISION       12
//serial port baudrate 9600(default)/ 19200 / 115200
#define SERIAL_BAUDRATE             9600
//RF24 channel
#define NETWORK_CHANNEL              90


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
//TempSensorsAddress[0] = {0x28, 0x17, 0x69, ox45, 0x05, ox00, 0x00, 0x76};
//TempSensorsAddress[1] = {0x28, 0x6F, 0x07, 0x45, ox05, 0x00, 0x00, 0xFC};
//NO.1 = 2817694505000076
//NO.2 = 286F0745050000FC
/* nRF24L01 Wireless communication initial something */
RF24 radio( CE_PIN, CSN_PIN );

// network use the radio
RF24Network network( radio );

//address of our node (server node)
const uint16_t server_node = 0;

//address of ohter node( client node )
const uint16_t client_1_node = 1;

//every message interval time
const unsigned long interval = 1000; //ms

//how many messages we send
unsigned long num_of_mesg = 0;

//when did client node send last message
unsigned long last_sent = 0;


//Struct of our payload
struct payload_t
{
  unsigned long send_ms;
  unsigned long back_ms;  
  unsigned long counter;
  float tempC;      //store temperature data.
};

void setup( void )
{
  //initialize digitak pin as output for led
  //pinMode(LED_PIN, OUTPUT );
  //digitalWrite( LED_PIN, HIGH );
  
  //start serial port
  Serial.begin( SERIAL_BAUDRATE );

 
  //initial RF chip
  Serial.println("=== nrf24l01 TEST ===");
  Serial.println("this is client, waitting to receive ...");
  
  SPI.begin();
  radio.begin();
  radio.printDetails();
  network.begin( NETWORK_CHANNEL, client_1_node );
  Serial.println("network ok");
  
  
  // Initail all DS18b20 on the 1-wire bus, print infomations.
  //setupTemperatureSensors();
  //start up DallasTemperature library
//  TempSensors.begin();
  //TempSensors.setResolution(  TempSensorsAddress[1], 12 ); 
  Serial.println("Finish setup");
  
}

bool done = false;
float temp = 0;
payload_t payload;

void loop( void ) 
{
  
 /* --------------- RF ------------------------------------*/  
   //pump the network regularly
  network.update();
  //send a message at 1s interval
  unsigned long now = millis();
  
  // if it's time to send message.
  //if( now - last_sent >interval )
  //client always wait for server send heart beat at 1s interval.
  while( network.available() )
  {
    last_sent = now;
     unsigned long got_time;
      //send to server node
     RF24NetworkHeader rx_header;
     
     // get the message from server
     network.read( rx_header, &payload, sizeof(payload) );
     Serial.print("got message: " );
     //Serial.print( (uint16_t)rx_header );
     Serial.print("server time: " );
     Serial.print( payload.send_ms );
     Serial.print("ms, num_of_mesg: ");
     Serial.print( num_of_mesg);

    
     //do something,...
     //now just delay
     delay(20);

     payload.counter = num_of_mesg ++;
     Serial.print( ", send back ... ");
     RF24NetworkHeader tx_header( server_node );
     bool write_status = network.write( tx_header, 
                                 &payload, sizeof(payload));
     if( write_status )
       Serial.println(" ok. ");
     else
      {
      Serial.println(" failed. ");
      // if failed, this delay can display slow.
      delay(100);
      } 
  }
  
    
  /* ----------------- DS18b20 ---------------------------*/
  /*
  Serial.print("Requeset temperatures ...");
  // sends command for all devices on the bus to perform
  // a temperature conversion
  TempSensors.requestTemperatures();
  //temp  = TempSensors.getTempC(TempSensorsAddress[0]);
  temp  = TempSensors.getTempCByIndex(0);
  Serial.println( temp );
   //delay(1000);
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
  numberOfTempSensors = 0;
  
  Serial.println("=== Inital temperature sensors ===");
  //start up DallasTemperature library
  //TempSensors.begin();
  
  //get count of temperature sensor 
  Serial.println("Scan connect 1-wire devices ...");
  numberOfTempSensors = TempSensors.getDeviceCount();
  Serial.print("Found devices number:         ");
  Serial.println( numberOfTempSensors,DEC );
  Serial.print("Actual connect device number: ");
  Serial.println( NUM_TMERATURE_SENSORS,DEC );
  if( numberOfTempSensors < NUM_TMERATURE_SENSORS )
  {
    Serial.print("Warn: lost 1-wire devices number: ");
    Serial.println((NUM_TMERATURE_SENSORS-numberOfTempSensors), DEC);
  }
  else
  {
    Serial.println("OK,all 1-wire device are found !");
  }
  Serial.println("");
  
  // scan all temperature sensors, print address and resolution
  for(uint8_t i=0; i<numberOfTempSensors; i++ ) 
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

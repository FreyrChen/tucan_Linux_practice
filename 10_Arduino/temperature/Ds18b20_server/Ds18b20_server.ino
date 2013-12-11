/**
* Function already complete:
* 2013/12/10  DS18b20 : temprature measurement
* 2013/12/11  nRF24L01: wireless communication
*
* tusion@163.com 
**/


/*wireless communication chip nRF24L01 connect on SPI */
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define SERIAL_BAUDRATE    9600
#define LED_PIN            8
//for nRF24L01 SPI
#define CE_PIN             9
#define CSN_PIN            10


/* nRF24L01 Wireless communication initial something */
RF24 radio( CE_PIN, CSN_PIN );
//define transmit pipe, 
//'LL' at the end is 'long long' type 
const uint64_t pipe = 0xE8E8F0F0E1LL; 
float tempC;

void setup( void )
{
  //initialize digitak pin as output for led
  pinMode(LED_PIN, OUTPUT );
  //start serial port
  Serial.begin( SERIAL_BAUDRATE );
  Serial.println("=== nrf24l01 test ===");
  Serial.println(" this is server, waitting to receive ...");
  
  //initial RF chip
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  
}


void loop( void ) 
{
  if( radio.available() )
  {
    bool done = false;
    while( !done )
    {
      done = radio.read( &tempC, sizeof( float ) );
      Serial.print("received temprature: " );
      Serial.println( tempC );
      
      digitalWrite( LED_PIN, ~digitalRead(LED_PIN) );
    }
  }
  /*
  else
  {
    Serial.println("No radio available.");
  }
  */
 
}
  
 

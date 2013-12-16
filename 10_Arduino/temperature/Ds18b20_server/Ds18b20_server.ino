/**
* Function already complete:
* 2013/12/10  DS18b20 : temprature measurement
* 2013/12/11  nRF24L01: wireless communication
*
* tusion@163.com 
**/


/*wireless communication chip nRF24L01 connect on SPI */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Network.h>

#define SERIAL_BAUDRATE    9600
#define LED_PIN            8


//for nRF24L01 SPI
#define CE_PIN             9
#define CSN_PIN            10
#define NETWORK_CHANNEL    90


/* nRF24L01 Wireless on SPI bus */
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
unsigned long num_of_miss = 0;

//when did client node send last message
unsigned long last_sent;

//Struct of our payload
struct payload_t
{
  unsigned long send_ms;
  unsigned long back_ms;  
  unsigned long counter;  //add by client
  float tempC;      //store temperature data.
};
payload_t payload;

void setup( void )
{
  //initialize digitak pin as output for led
  pinMode(LED_PIN, OUTPUT );
  //start serial port
  Serial.begin( SERIAL_BAUDRATE );

  
  //initial RF chip
  last_sent = 0;
  num_of_mesg = 0;
  SPI.begin();
  radio.begin();
  network.begin( NETWORK_CHANNEL, server_node );
  Serial.println("=== nrf24l01 TEST ===");
  Serial.println(" this is server, waitting to receive ...");
  Serial.println();
}



void loop( void ) 
{

  //pump the network regularly
  network.update();
  unsigned long now = millis();
  // heart beat at 1s interveal
  if( now - last_sent > interval )
  {
    last_sent = now;
    num_of_mesg ++;

    payload = { millis(), 0, num_of_mesg, 23.55 };
    // send heart beat to client 1 .
    Serial.print("send ...");
    RF24NetworkHeader header( client_1_node );
    bool write_status = network.write( header, 
                                       &payload, sizeof(payload));
    if( write_status )
    {
     Serial.print(" ok. ");
    }
    else
    {
    Serial.print(" failed. ");
    // if failed, this delay can display slow.
    delay(100);
    } 
    
    bool timeout = false;
    //wait for client backk message.
    while( !network.available()  && !timeout)
    {
      network.update();
      // received back message time out less than 200ms
      if( (millis() - payload.send_ms) > 200 )
        timeout = true;
    }
    if( timeout )
    {
      Serial.println();
      Serial.println("Failed, reponse time out. ");
    }
    else
    {
      
      network.read( header, &payload, sizeof(payload) );
      //Serial.print( "received msg:  ");
      //Serial.print( header );
      payload.back_ms = millis();
     
      num_of_miss = num_of_mesg -payload.counter;
      Serial.print("Recevied: NO.");
      Serial.print(num_of_mesg);
      Serial.print(", counter: ");
      Serial.print( payload.counter );
      Serial.print(" send@ ");
      Serial.print(payload.send_ms);
      Serial.print("ms. back@ ");
      Serial.print(payload.back_ms);
      Serial.print("ms. cost: ");
      Serial.print( payload.back_ms - payload.send_ms );
      Serial.println(" ms");

    }
    
    
  }
    
    
/*
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
      
*/ 
 
}
  
 

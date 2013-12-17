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
//#include <RF24Network.h>

#define NODE_NUM           2

#define SERIAL_BAUDRATE    9600
#define LED_PIN            8


//for nRF24L01 SPI
#define CE_PIN             9
#define CSN_PIN            10
//#define NETWORK_CHANNEL    90

/********************************************************************/
// nRF24L01 Wireless communication initial something 
/********************************************************************/
/* nRF24L01 Wireless on SPI bus */
RF24 radio( CE_PIN, CSN_PIN );
// open pipe 0 to read,  server <--- client.
// open pipe 1 to write.   server ---> client.
//we can have up to 5 pipes open for reading)
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL,
                            0xF0F0F0F0D2LL  };
//every message interval time
const unsigned long interval = 1000; //ms
const unsigned long timeout = 1000; //ms

//how many messages we send
unsigned long num_of_mesg = 0;
//evry node missed response message no.
unsigned long num_of_miss[8];

//when did client node send last message
unsigned long last_sent;

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
void printMessage( void );

void setup( void )
{
  //initialize digitak pin as output for led
  //pinMode(LED_PIN, OUTPUT );
  //start serial port
  Serial.begin( SERIAL_BAUDRATE );
  Serial.println("=== nrf24l01 TEST ===");
  Serial.println(" this is server, waitting to receive ...");
  
  //initial RF chip
  last_sent = 0;
  num_of_mesg = 0;
  payload.counter = 0;
  
  SPI.begin();
  radio.begin();
  // open pipe 0 to read,  server <--- client.
  // open pipe 1 to write. server ---> client.
  //we can have up to 5 pipes open for reading)
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  
  radio.startListening();
  // Dump the configuration of the rf unit for debugging
  //radio.printDetails();
  //network.begin( NETWORK_CHANNEL, client_1_node );
  Serial.println("network ok, finish setup");
  Serial.println();
  
  
}


void loop( void ) 
{
    //step 1: send heart beat signal to all nodes every 1s.
  unsigned long now = millis();
  // heart beat at 1s interveal
  if( now - last_sent > interval )
  {
    last_sent = now;
    num_of_mesg ++;
    payload.counter += 1;
  
    //scan all nodes
    for( payload.Node_NO=0; payload.Node_NO<NODE_NUM; payload.Node_NO++)
    {
      radio.stopListening();
      Serial.print("check node:");
      Serial.print(payload.Node_NO);
      Serial.print(", " );


      // assamble message packet
      payload.send_ms = millis();
      payload.switch_control = 0;
      payload.alrm = 0;

      
      bool write_status = radio.write(  &payload, sizeof(payload));
      if( write_status )
      {
        ;
       //Serial.print(", ");
      }
      else
      {
        Serial.println(" send heart beat failed. ");
        // if failed, this delay can display slow.
        //delay(100);
      } 
      
      //step 2: wait for nodes response.
      radio.startListening();
      bool is_timeout = false;
      //wait for client backk message. 
      while( !radio.available()  && !is_timeout)
      {
        // received back message time out less than 200ms
        if( (millis() - payload.send_ms) > timeout )
          is_timeout = true;
      }
      if( is_timeout )
      {
        //Serial.println();
        Serial.println("wait reponse time out, failed! ");
      }
      else
      {
        bool done = false;
        while (!done)
        {
          done = radio.read( &payload, sizeof(payload) );
          payload.last_delay_ms = millis() - payload.send_ms;   
          // print payload data from RF24 communication
          printMessage(  );
          Serial.println();
          //digitalWrite( LED_PIN, ~digitalRead(LED_PIN) );
        }
  
      }
    } 
  }
}
  
  
// print payload data from RF24 communication
void printMessage( void )
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
 

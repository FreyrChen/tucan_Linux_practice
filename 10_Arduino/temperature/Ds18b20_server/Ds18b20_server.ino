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
#include "MyCommon.h"


#define  DEBUG
//1-server, 2-UNO, 3-millis(),
#define SUM_SENSOR_NODES  2

#define SERIAL_BAUDRATE    9600
#define LED_PIN            8

//for nRF24L01 SPI
#define CE_PIN             9
#define CSN_PIN            10

/********************************************************************/
// nRF24L01 Wireless communication initial something 
/********************************************************************/
/* nRF24L01 Wireless on SPI bus */
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
const unsigned long interval = 1000; //ms
const unsigned long timeout = 100; //ms

//how many messages we send
unsigned long server_num_of_mesg = 0;
//evry node missed response message no.
unsigned long num_of_miss[8];

//when did client node send last message
unsigned long server_last_sent;

// serial commader to server
struct commder_t
{
  uint8_t     DesNode;  
};

payload_control     control_mesg;
payload_monitor     monitor_mesg;

void clearMonitorMesg( payload_monitor monitor_mesg);
void clearControlMesg( payload_control control_mesg );
void printMonitorMesg( payload_monitor monitor_mesg );
void printControlMesg( payload_control control_mesg );

void setup( void )
{
  //initialize digitak pin as output for led
  //pinMode(LED_PIN, OUTPUT );
  //start serial port
  Serial.begin( SERIAL_BAUDRATE );
  Serial.println("*************************************************");
  Serial.println(" Initial and setup " );
  
  //read node no from eeprom
  Serial.println(" read node no from eeprom to determin role. ");
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
  Serial.println(" initial RF24 ...");
  //SPI.begin();
  radio.begin();
  if( role == role_server )
  {
    Serial.println("This is server node ." );
    for( uint8_t node_num =0; node_num <5; node_num++ )
    {
      radio.openReadingPipe((node_num+1),node_to_server_pipes[node_num] );
      radio.openWritingPipe(server_to_node_pipes[node_num] );
    }
    //radio.openReadingPipe( 1, talking_pipes[0] );
  }
  
  if( role == role_node )
  {
    //sensor node at NO 2-6
     Serial.println("This is sensor node ." );
    radio.openWritingPipe( node_to_server_pipes[ node_NO-2 ]);
    radio.openReadingPipe(1, server_to_node_pipes[ node_NO-2 ] );
  }
 
  radio.startListening();
  Serial.println(" RF OK");
  
  server_last_sent = 0;
  server_num_of_mesg = 0;

  
  Serial.println("============ Finish setup =================");
}



void loop( void ) 
{
 
  
   //step 1: send heart beat signal to all nodes every 1s.
  unsigned long start_scan = millis();
  // heart beat send to all sensor nodes at 1s interveal
  if( start_scan - server_last_sent > interval )
  {
    server_last_sent = start_scan;
    server_num_of_mesg ++;
 
    radio.stopListening();
    //scan all nodes
    for( uint8_t to_node=2; to_node<(2+SUM_SENSOR_NODES); to_node++ )
    {
      clearControlMesg( control_mesg );
      radio.openWritingPipe( server_to_node_pipes[to_node-2 ] );
     
      // assamble message packet
      control_mesg.Timestamp = start_scan;
      control_mesg.Counter = server_num_of_mesg;
      control_mesg.DesNode = to_node;
      for( uint8_t j=0; j<8; j++ )
      {
        control_mesg.SwitchControl[j] = false;
        control_mesg.AlarmControl[j] = false;
      }
      
      bool write_status = radio.write(  &control_mesg,
                                      sizeof(control_mesg));
                                      
      if( write_status == true )
        printControlMesg( control_mesg );
      else
      {
        Serial.print("Send heartbeat to node: " );
        Serial.print(to_node);
        Serial.println(", falied.");
        
      }
 
      
    }  
    

    //step 2: wait for nodes response.
    //scan all nodes
    radio.startListening();
    //wait for the busy node to measure the sensors.
    delay(interval);
   
    for( uint8_t pipe_num=1; pipe_num<(SUM_SENSOR_NODES+1); pipe_num++ )
    {

      clearMonitorMesg( monitor_mesg );
      bool is_timeout = false;
      unsigned long start_time = millis();
      //wait for client backk message. 
      while( !radio.available(&pipe_num)  && !is_timeout)
      {
        // received back message time out less than 200ms
        if( (millis() - start_time) > timeout )
          is_timeout = true;
      }
      if( is_timeout )
      {
        
        Serial.print("Wait reponse from node: " );
        Serial.print( pipe_num+1);
        Serial.println(" time out, failed! ");
        is_timeout = false;
        continue;
      }
      else
      {
        bool done = false;
        while (!done)
        {
          done = radio.read( &monitor_mesg, sizeof(monitor_mesg) );
          unsigned long delay_ms = millis() - start_scan;   
          
          printMonitorMesg(monitor_mesg);
          //digitalWrite( LED_PIN, ~digitalRead(LED_PIN) );
        }
      }
    }
  }

 

}
 

void printControlMesg( payload_control control_mesg )
{
  Serial.print("{\"name\": \"control\"  ");
  Serial.print(",\"Counter\": ");
  Serial.print( control_mesg.Counter );
  Serial.print(", \"Timestamp\": ");
  Serial.print( control_mesg.Timestamp );
  Serial.print(", \"DestinationNode\": ");
  Serial.print( control_mesg.DesNode );
  Serial.print(", \"SwitchControl\": ");
  
  for( uint8_t t=0; t<8; t++ )
  {
    if( control_mesg.SwitchControl[t] == true )
      Serial.print( 1 );
    else
      Serial.print( 0 );
    if( t<7 )
      Serial.print(",");
  }
  Serial.print("], \"AlarControl\": [");
  for( uint8_t t=0; t<8; t++ )
  {
    if( control_mesg.AlarmControl[t] == true )
      Serial.print( 1 );
    else
      Serial.print( 0 );
    if( t<7 )
      Serial.print(",");
  }
  Serial.println("] } ");
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
  Serial.print("], \"AlarmState\": [");
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

void clearControlMesg( payload_control control_mesg )
{
  control_mesg.Counter  = 0;
  control_mesg.Timestamp = 0;
  control_mesg.DesNode = 0;
  for( uint8_t x=0; x<8; x++ )
  {
    control_mesg.SwitchControl[x] == false;
    control_mesg.AlarmControl[x] == false;
  }
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

/**
* Function already complete:
* 2013/12/10  DS18b20 : temprature measurement
* 2013/12/11  nRF24L01: wireless communication
*
* tusion@163.com 
**/

#include <EEPROM.h>

/*wireless communication chip nRF24L01 connect on SPI */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//#include <RF24Network.h>

#define  DEBUG
//1-server, 2-UNO, 3-millis(),
#define NUM_SENSOR_NODES  2

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
const unsigned long timeout = 200; //ms

//how many messages we send
unsigned long num_of_mesg = 0;
//evry node missed response message no.
unsigned long num_of_miss[8];

//when did client node send last message
unsigned long last_sent;

//Struct of our payload
struct payload_control
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
  SPI.begin();
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
  
  last_sent = 0;
  num_of_mesg = 0;
  //payload.counter = 0;
  
  Serial.println("============ Finish setup =================");
}



void loop( void ) 
{
 
  
    //step 1: send heart beat signal to all nodes every 1s.
  unsigned long start_scan = millis();
  // heart beat send to all sensor nodes at 1s interveal
  if( start_scan - last_sent > interval )
  {
     //Serial.println("-------------------------------------------");
    last_sent = start_scan;
    num_of_mesg ++;
 

    radio.stopListening();
    //scan all nodes
    for( uint8_t to_node=2; to_node<(2+NUM_SENSOR_NODES); to_node++ )
    {
      payload_control     commander_mesg;
      radio.openWritingPipe( server_to_node_pipes[to_node-2 ] );
     
      // assamble message packet
      commander_mesg.timestamp = start_scan;
      commander_mesg.counter = num_of_mesg;
      commander_mesg.DesNode = to_node;
      for( uint8_t j=0; j<8; j++ )
      {
        commander_mesg.SwitchControl[j] = false;
        commander_mesg.AlarmControl[j] = false;
      }
      
      /*
      Serial.print("scan node:");
      Serial.print(commander_mesg.DesNode);
      Serial.print(", " );
      */
      
      bool write_status = radio.write(  &commander_mesg,
      
                                      sizeof(commander_mesg));
      /*  
      if( write_status )
      {
       Serial.println("ok. ");
      }
      else
      {
        Serial.println(" send heart beat failed. ");
      } 
      */
      
      
      /*
      Serial.print("control { ");
      Serial.print("counter: ");
      Serial.print( commander_mesg.counter );
      Serial.print(", timestamp: ");
      Serial.print( commander_mesg.timestamp );
      Serial.print(", DestinationNode: ");
      Serial.print( commander_mesg.DesNode );
      Serial.print(", SwitchControl: ");
      for( uint8_t t=0; t<8; t++ )
        Serial.print( commander_mesg.SwitchControl[t] );
      Serial.print(", AlarControl: ");
      for( uint8_t t=0; t<8; t++ )
        Serial.print( commander_mesg.AlarmControl[t] );
      Serial.println(" } ");
      */
      
      
      
    }  
    

    //step 2: wait for nodes response.
    //scan all nodes
    radio.startListening();
    //wait for the busy node to measure the sensors.
    //Serial.println("wait for sensors ... " );
    //Serial.println(" .............. ");
    delay(1000);
   
    for( uint8_t pipe_num=1; pipe_num<(NUM_SENSOR_NODES+1); pipe_num++ )
    {
      payload_monitor monitor_mesg;
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

      }
      else
      {
        bool done = false;
        while (!done)
        {
          done = radio.read( &monitor_mesg, sizeof(monitor_mesg) );
          unsigned long delay_ms = millis() - start_scan;   
          // print payload data from RF24 communication
          //printMessage(  );
          /*
          Serial.print(" response form node: ");
          Serial.print( monitor_mesg.FromNode );
          Serial.print(" node cost time(ms):");
          Serial.print( monitor_mesg.CostTime );
          Serial.print(", delay(ms): ");
          Serial.println(delay_ms );
          */
          
          
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
            Serial.print( monitor_mesg.AlarmState[t], BIN );
          Serial.println(" } ");
          
          
          //digitalWrite( LED_PIN, ~digitalRead(LED_PIN) );
        }
  
      }
      //sdelay(1000);
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
}
 
/* 
void printControlMesg( payload_control mesg )
{
  Serial.print("control { ");
  Serial.print("counter: ");
  Serial.print( mesg.counter );
  Serial.print(", timestamp: ");
  Serial.print( mesg.timestamp );
  Serial.print(", DestinationNode: ");
  Serial.print( mesg.DesNode );
  Serial.print(", SwitchControl: ");
  for( uint8_t t=0; t<8; t++ )
    Serial.print( mesg.SwitchControl[t] );
  Serial.print(", AlarControl: ");
  for( uint8_t t=0; t<8; t++ )
    Serial.print( mesg.AlarmControl[t] );
  Serial.println(" } ");
}

void printMonitorMesg( payload_monitor mesg )
{
  Serial.print("monitor { ");
  Serial.print("counter: ");
  Serial.print( mesg.counter );
  Serial.print(", CostTime: ");
  Serial.print( mesg.CostTime );
  Serial.print(", FromNode: ");
  Serial.print( mesg.FromNode );
  Serial.print(", TempC1:");
  Serial.print( mesg.TempC[0] );
  Serial.print(", TempC2:");
  Serial.print( mesg.TempC[1] );
  Serial.print(", TempC3:");
  Serial.print( mesg.TempC[2] );
  Serial.print(", humd: ");
  Serial.print( mesg.humd );
  Serial.print(", PIR: ");
  Serial.print( mesg.PIR );
  Serial.print(", SwitchState: ");
  for( uint8_t t=0; t<8; t++ )
    Serial.print( mesg.SwitchControl[t] );
  Serial.print(", AlarState: ");
  for( uint8_t t=0; t<8; t++ )
    Serial.print( mesg.AlarmControl[t] );
  Serial.println(" } ");
}
   */

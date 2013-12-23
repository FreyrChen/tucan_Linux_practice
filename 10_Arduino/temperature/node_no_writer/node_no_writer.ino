#include <EEPROM.h>

const int addr = 0;

// Toggle LED 
#define LED_PIN           13

#define EEPROM_WRITE

void setup()
{
  
  pinMode( LED_PIN, OUTPUT );
  digitalWrite( LED_PIN, HIGH );
  
  Serial.begin(9600);
  
  #ifdef EEPROM_WRITE
  Serial.print("write node address in EEPROM, ");
  // server no = 1
  // node no = 2,3,4,5,6.
  int NodeNO = 3;
  EEPROM.write( addr, NodeNO );
  #endif

  
}

void ToggleLed( uint8_t pin);
void loop()
{
  ToggleLed( LED_PIN );
   //digitalWrite( LED_PIN, HIGH);
  Serial.print("This board's NO.: ");
  Serial.println(EEPROM.read( addr ) );
  delay(1000);
}
  
void ToggleLed( uint8_t pin)
{
  digitalWrite( pin,!(digitalRead( pin)) );
}
  
  
  
  

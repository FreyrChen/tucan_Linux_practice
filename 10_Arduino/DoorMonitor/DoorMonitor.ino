/*
*
*
*/
const int ButtonPin = 2;  //push buttion pin to input signal
const int BuzzerPin = 3;  //alarm beeper
const int AnalogInPin = A5; //analog input pin
const int DigitalInPin = 13; // digital input pin
const int LEDPin = 8;  //LED output pin

void BuzzerBeep( int BuzzerPin, int volume,  int delay_ms );
void BuzzerTest( void );

int ButtonState = LOW;
int ButtonISRState = LOW;
int analog_value = 0;
int digital_value = 0;

void setup()
{
  pinMode( ButtonPin, INPUT );
  pinMode( BuzzerPin, OUTPUT );
  pinMode( DigitalInPin, INPUT );
  pinMode( LEDPin, OUTPUT );
  
  Serial.begin(9600);
  
  //once button been pushed, function ButtonISR() will be executed
  // INT0 => PIN2; INT1 => PIN3; 
  attachInterrupt(0,ButtonISR, RISING );
}

void loop()
{
  /*
  ButtonState = digitalRead( ButtonPin );

    
  Serial.print("Buttion State: ");
  Serial.println( ButtonState );
  */
  //BuzzerTest( );
  analog_value = analogRead( AnalogInPin );
  Serial.print("analog value: ");
  Serial.print( analog_value );
  
  digital_value = digitalRead( DigitalInPin );
  Serial.print(",  digital_value: " );
  Serial.println( digital_value ); 
  
  digitalWrite( LEDPin, digital_value );
  digitalWrite( BuzzerPin, digital_value );
   
  
  delay(100);

}

// volume 0-255  volume of buzzering
// delay time: 200ms is DI..DI..DI...
void BuzzerBeep( int BuzzerPin, int volume,  int delay_ms )
{
  analogWrite( BuzzerPin, volume );
  delay( delay_ms );
}

void BuzzerTest( void )
{
    //make some Di Di Di Di sound
  for(int i = 0; i < 10; i++)
  {
    BuzzerBeep(BuzzerPin, 100, 100);
    BuzzerBeep(BuzzerPin, 0, 100);

  }
}

void ButtonISR(  )
{
     ButtonISRState = !ButtonISRState;
    Serial.print("ButtonISRState = ");
    Serial.println( ButtonISRState );
    
    if( ButtonISRState == HIGH)
      BuzzerBeep( BuzzerPin, 100, 0 );
    else
      BuzzerBeep( BuzzerPin, 0, 0 );
      

}
     


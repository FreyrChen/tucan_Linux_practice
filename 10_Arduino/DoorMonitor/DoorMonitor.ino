  /*
*
*
*/
const int ButtonPin = 2;  //push buttion pin to input signal
const int BuzzerPin = 3;  //alarm beeper
const int AnalogInPinA0 = A0; //analog input pin
const int AnalogInPinA1 = A1; //analog input pin
const int DigitalInPin = 13; // digital input pin
const int LEDPin = 13;  //LED output pin

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
//  attachInterrupt(0,ButtonISR, RISING );
}

void loop()
{
 
  //BuzzerTest( );
 
  analog_value = analogRead( AnalogInPinA0  );
  Serial.print( analog_value );
  Serial.print(", " );
  
  analog_value = analogRead( AnalogInPinA1  );
  Serial.println( analog_value );
  
  
  //analogWrite( BuzzerPin, 1023-analog_value ); 
  //delay( 1023 - analog_value );
  //BuzzerTest();
  
  if( analog_value < 900 )
    BuzzerAlarm( analog_value / 2 );
   else
     BuzzerHeatBeat();
     
  
  /*
  digital_value = digitalRead( DigitalInPin );
  Serial.print(", digital_value: " );
  Serial.println( digital_value ); 
  
  digitalWrite( LEDPin, digital_value );
  digitalWrite( BuzzerPin, digital_value );
  */
   
   
  //delay(100);
  //Serial.println("blink.");

}

// volume 0-255  volume of buzzering
// delay time: 200ms is DI..DI..DI...
void BuzzerBeep( int BuzzerPin, int volume,  int delay_ms )
{
  analogWrite( BuzzerPin, volume );
  delay( delay_ms );
}

void BuzzerHeatBeat( void )
{
    //make some Di Di Di Di sound
    BuzzerBeep(BuzzerPin, 255, 100);
    BuzzerBeep(BuzzerPin, 0, 100);
    delay(1000);
}

void BuzzerAlarm( int delay_ms )
{
      //make some Di Di Di Di sound
    BuzzerBeep(BuzzerPin, 255, delay_ms);
    BuzzerBeep(BuzzerPin, 0, delay_ms);

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
     


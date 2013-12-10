/* 
 //==============================================
 Arduino Electronic Bricks Advanced Kit example
 Project 10 - HumAndTempSensor
 Get the humidity and temperature value from DHT11,
 and display it on the Serial Monitor.
 
 //==============================================
 Arduino Electronic Bricks Advanced Kit example
 Project 14 - PIRMotionSensor
 Output the state when detecting people move nearby. 
 
 
 */

#include <Arduino.h>
#include <Wire.h>
#include <DHT11.h>




//initial humdity and temprature sensor DHT11
dht11 DHT11;
#define DHT11PIN 2

// initial PIR Motion sensor
const int PIRSensorPin = 1;     // the number of the Sensor pin
int PIRSensorState = 0;         // variable for reading the Sensor status
int flag = 0; //use the flag to prevent continuous outputing when no moving people

//connet RGBLed to pin 9,10,11
const int  pinR = 9;
const int  pinG = 10;
const int  pinB = 11;


//input button
volatile int ButtonState = LOW;

void setup()
{
  Serial.begin(9600);
  
  // initialize the Sensor pin as an input:
  pinMode(PIRSensorPin, INPUT);
  digitalWrite(PIRSensorPin, LOW);
  
  //once push button ,then tigger a interrupt.
  attachInterrupt( 1, pushButtonFun, RISING );
  //attachInterrupt( 1, pushButtonFun, CHANGE);
  
  pinMode( pinR, OUTPUT );
  pinMode( pinG, OUTPUT );
  pinMode( pinB, OUTPUT );
  digitalWrite( pinR, HIGH );
  digitalWrite( pinG, HIGH );
  digitalWrite( pinB, HIGH );  
}

void loop()
{
    
  //digitalWrite( LEDPin, ButtonState );

  
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Read sensor: ");
  switch (chk)
  {
  case DHTLIB_OK: 
    Serial.print("OK; "); 
    break;
  case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error; "); 
    break;
  case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error; "); 
    break;
  default: 
    Serial.print("Unknown error; "); 
    break;
  }
  Serial.print("Humidity (%): ");
  Serial.print((float)DHT11.humidity, 2);

  Serial.print("; Tempe (oC): ");
  Serial.println((float)DHT11.temperature, 2);
  
  delay(1000);
  
  while( Serial.available() > 0 )
  {
    int red = Serial.parseInt();
    int green = Serial.parseInt();
    int blue = Serial.parseInt();
  
    if( Serial.read() == '\n' ) 
    {
      red = 255 - constrain( red, 0, 255 );
      green = 255 - constrain( green, 0, 255 );
      blue = 255 - constrain( blue, 0, 255 );
      
      analogWrite( pinG, red );
      analogWrite( pinR, green );
      analogWrite( pinB, blue );
    }
  }
  /*
  //---------------PRI Motion sensor --------------------
  // read the state of the Sensor value:
  PIRSensorState = digitalRead(PIRSensorPin);
  // check if the moving people sensed.
  // if it is, the sensorState is HIGH:
  if ( PIRSensorState == HIGH ) {       
 
    Serial.println("Moving people detected");
    flag = 0; 
  } 
  else {
    if(flag == 0){
      Serial.println("PRI:No moving people");
      flag = 1;
    }
  }
  */
}


void pushButtonFun()
{
  ButtonState = !ButtonState;
  Serial.print("Button State: " );
  Serial.println( ButtonState );
}

/*
void LedBlink()
{
  digitalWrite( LEDPin, HIGH );
  delay(500);
  digitalWrite( LEDPin, LOW );
  delay(500);
}
*/

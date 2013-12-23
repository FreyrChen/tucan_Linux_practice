//Struct of our payload
struct payload_control
{
  unsigned long Counter;    // Heat beat Counter.
  unsigned long Timestamp;  // server start heart beat request time.
  uint8_t       DesNode;    // destination to node's NO
  bool          SwitchControl[8]; // every bit control a delay switch
  bool          AlarmControl[8];  //every bit control a beep. 
};

typedef struct
{
  unsigned long Counter;    // Heat beat Counter.
  unsigned long CostTime;    // complete all sensors cost at nods time.
  uint8_t       FromNode;    // message from node's NO
  float         TempC[3];   // temperature sensor  less than 3.
  float         Humd;       // humandity sensor data
  bool          PIR;        // human move singal data   
  bool          SwitchState[8]; // state of switch.  
  bool          AlarmState[8];  //every bit control a beep. 
}payload_monitor;



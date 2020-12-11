/**
 * Function List:
 *    1. bool TKTouchSensor::touched()
 *    2. void TKTouchSensor::SetTogMode(uint8_t TogMode)
 */
#include "TKOrion.h"

// Touch sensor must connect with  the port 2,3,5,6,7,8:
// Resulted is YES: if you conneted with this module, else NO
TKTouchSensor TKTouchSensor(PORT_6);

void setup()
{
  Serial.begin(9600);
  Serial.println("Start.");
  TKTouchSensor.SetTogMode(0);
}

void loop()
{
  if(TKTouchSensor.touched() )    
  {
    Serial.println("State: DOWN.");
    
  }
  else {
     Serial.println("State: UP.");
  } 
  delay(2); 
}

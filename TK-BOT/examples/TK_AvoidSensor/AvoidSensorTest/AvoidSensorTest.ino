/**

 * Function List:
 *    1. bool TKAvoidSensor::Avoidtested()
 *    2. void TKAvoidSensor::SetTogMode(uint8_t TogMode)

 */
#include "TKOrion.h"

// Me_LimitSwitch module can only be connected to PORT_3, PORT_4, PORT_6,PORT_7,PORT_8 of base shield
// or from PORT_3 to PORT_8 of baseboard.
TKAvoidSensor TKAvoidSensor(PORT_6);

void setup()
{
  Serial.begin(9600);
  Serial.println("Start.");
  TKAvoidSensor.SetTogMode(0);
}

void loop()
{
  if(TKAvoidSensor.Avoidtested() )      // If the limit switch is Avoidtested, the  return value is true.
  {
    Serial.println("State: YES");
  }
  if(!TKAvoidSensor.Avoidtested() )
  {
    Serial.println("State: NO");
  }
  delay(2);
}

/**
 * Function List:
 * 1. double TKUltrasonicSensor::distanceCm(uint16_t MAXcm)
 */
#include "TKOrion.h"

TKUltrasonicSensor TKUltrasonicSensor(PORT_7); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Distance : ");
  Serial.print(TKUltrasonicSensor.distanceCm() );
  Serial.println(" cm");
  delay(100); /* the minimal measure interval is 100 milliseconds */
}

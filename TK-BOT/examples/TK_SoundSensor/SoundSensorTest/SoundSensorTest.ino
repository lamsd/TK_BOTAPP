/**
 * Function List:
 * 1. int16_t TKSoundSensor::strength()
 */
#include "TKOrion.h"

TKSoundSensor mySound(PORT_6);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("value=");
  Serial.println(mySound.strength() );
  delay(100);
}

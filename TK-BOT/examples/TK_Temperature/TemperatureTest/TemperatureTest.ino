/**
 * Function List:
 *    1. bool TKTemperature::temperature()
 */
#include "TKOrion.h"

TKTemperature myTemp(PORT_8, SLOT2);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Temperature=");
  Serial.println(myTemp.temperature() );
  delay(1000);
}

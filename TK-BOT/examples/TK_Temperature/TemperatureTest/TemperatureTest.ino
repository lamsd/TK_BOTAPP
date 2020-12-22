/**
 * Function List:
 *    1. bool TKTemperature::temperature()
 */
#include "TKOrion.h"

TKTemperature myTemp(PORT_2, SLOT2);

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

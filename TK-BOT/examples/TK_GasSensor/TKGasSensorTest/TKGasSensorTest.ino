/**
 * Function List:
 *    1. uint8_t TKGasSensor::readDigital(void)
 *    2. TKGasSensor::readAnalog(void)
 */
#include "TKOrion.h"

TKGasSensor GasSensor1(PORT_6);

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  Serial.print("Analog Value is: ");
  Serial.print(GasSensor1.readAnalog());
  Serial.print("----Status: ");
  if(GasSensor1.readDigital() == Gas_Exceeded)
  {
    Serial.println("The concentration exceeds");
  }
  else if(GasSensor1.readDigital() == Gas_not_Exceeded)
  {
    Serial.println("The concentration of the gas in the range");
  }
  delay(200);
}

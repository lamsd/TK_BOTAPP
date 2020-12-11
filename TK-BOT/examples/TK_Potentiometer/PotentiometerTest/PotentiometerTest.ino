/**
 * Function List:
 * 1. uint16_t MePotentiometer::read(); 
 */

/* Includes ------------------------------------------------------------------*/
#include "TKOrion.h"

/* Private variables ---------------------------------------------------------*/
TKPotentiometer myPotentiometer(PORT_6);

/* Private functions ---------------------------------------------------------*/
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("value=");
  Serial.println(myPotentiometer.read() );
  delay(100);
}

/**

 * Function List:
 * 1. bool TKRGBLed::dWrite1(bool value)
 * 2. bool TKRGBLed::dRead2()
 */

#include "TKOrion.h"

TKPort output(PORT_4);


TKPort input(PORT_3);


int val;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  output.dWrite1(HIGH);   /* SLOT1 HIGH */
  delay(500);
  output.dWrite1(LOW);    /* SLOT1 LOW */
  delay(500);

  val = input.dRead1();   /* read SLOT1 level */
  Serial.print("val=");
  Serial.println(val);
}

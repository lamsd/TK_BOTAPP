/**

 * Function List:
 * 1. void tone(frequency, duration)
 * 2. void noTone()
 
 */

#include "TKOrion.h"
TKBuzzer TKMusic(PORT_6,SLOT1);

void setup() 
{
  Serial.begin(9600);
}

void loop()
{
  int durationT = 100;
  TKMusic.tone(1000,durationT);
  delay(1000);
  TKMusic.noTone();
  delay(1000);
}
/**
 * Function List:
 * 1. void TKSerial::begin(long baudrate)
 * 2. void TKSerial::printf(char *fmt,...)
 */
#include "TKOrion.h"
#include <SoftwareSerial.h>

TKSerial mySerial(PORT_8);

void setup()
{
  mySerial.begin(9600);
}

void loop()
{
  mySerial.println("just for test");
  mySerial.printf("%d,0x%x \r\n",123,0x123);
  delay(100);
}

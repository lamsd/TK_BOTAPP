/**

 * Function List:
 * 1. void TKBluetooth::begin()
 * 2. int16_t TKBluetooth::available()
 * 3. size_t TKSerial::write(uint8_t byte)
 * 4. int16_t TKSerial::read(void)

 */
 
#include "TKOrion.h"
#include <SoftwareSerial.h>

TKBluetooth bluetooth(PORT_3);

unsigned char table[128] = {0};

void setup()
{
  Serial.begin(115200);
  bluetooth.begin(115200);    //The factory default baud rate is 115200
  Serial.println("Bluetooth Start!");
}

void loop()
{ 
  int readdata = 0,i = 0,count = 0;
  char outDat;
  if (bluetooth.available())
  {
    while((readdata = bluetooth.read()) != (int)-1)
    {
      table[count] = readdata;
      count++;
      delay(1);
    }
    for(i = 0;i<count;i++)
    {
      Serial.write(table[i]);
    }
  }
  if(Serial.available() )
  {
    outDat = Serial.read();
    bluetooth.write(outDat);
  }
}

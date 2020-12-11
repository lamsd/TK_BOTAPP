#include "TKOrion.h"
#include <Wire.h>


TKColorSensor colorsensor(PORT_4);

uint8_t colorresult;
uint16_t redvalue=0,greenvalue=0,bluevalue=0,colorvalue=0,hue;
uint8_t grayscale = 0;
long systime = 0,colorcode=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  colorsensor.SensorInit();//
  systime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis()-systime>100)
  {
    systime = millis();
    colorresult = colorsensor.Returnresult();
    redvalue   = colorsensor.ReturnRedData();
    greenvalue = colorsensor.ReturnGreenData();
    bluevalue  = colorsensor.ReturnBlueData();
    colorvalue = colorsensor.ReturnColorData();
    colorcode = colorsensor.ReturnColorCode();//RGB24code
    grayscale  = colorsensor.ReturnGrayscale();

    Serial.print("R:");
    Serial.print(redvalue);
    Serial.print("\t");
    Serial.print("G:");
    Serial.print(greenvalue);
    Serial.print("\t");
    Serial.print("B:");
    Serial.print(bluevalue);
    Serial.print("\t");
    Serial.print("C:");
    Serial.print(colorvalue);
    Serial.print("\t");
    Serial.print("color:");
    switch(colorresult)
    {
       case BLACK:
      Serial.print("BLACK");
      break;
      case BLUE:
      Serial.print("BLUE");
      break;
      case YELLOW:
      Serial.print("YELLOW");
      break;
      case GREEN:
      Serial.print("GREEN");
      break;
      case RED:
      Serial.print("RED");
      break;
      case WHITE:
      Serial.print("WHITE");
      break;
      default:
      break;    
     }
     
    Serial.print("\t");
    Serial.print("code:");
    Serial.print(colorcode,HEX); 
    Serial.print("\t");
    Serial.print("grayscale:");
    Serial.println(grayscale);
  }
}

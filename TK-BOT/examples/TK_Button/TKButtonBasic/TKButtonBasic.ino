/**
 * Function List:
 * 1. uint8_t TKButton::pressed()
 */

/* Includes ------------------------------------------------------------------*/
#include <TKOrion.h>

/* Private variables ---------------------------------------------------------*/

/**
 * TKButton module can only be connected to PORT_6, PORT_7, PORT_8 on base 
 * shield and Orion board.
 */
TKButton btn(PORT_2);

void setup()
{
  Serial.begin(9600);
}

void loop()
{ 
  int keyPressed = btn.tkpressed();
  if (keyPressed == 1)
  {  
      Serial.println("Button: YES");
    }
  else{
    Serial.println("Button: NO");
  }   
}

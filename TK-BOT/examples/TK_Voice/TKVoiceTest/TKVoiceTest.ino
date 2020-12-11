#include "TKOrion.h"
#include <SoftwareSerial.h>
#include "TKVoice.h"

TKVoice myVoice(PORT_4);
TK7SegmentDisplay disp(PORT_6);

void setup()
{
  myVoice.begin(9600);
  Serial.begin(9600);
  Serial.println("Voice Start!");
}

uint8_t pre_receive_data;

void loop()
{
  uint8_t receive_data;
  myVoice.loop();
  receive_data =  myVoice.getCode();
  if(pre_receive_data != receive_data)
  {
    pre_receive_data = receive_data;
    if(receive_data != 0)
    {
      Serial.print("Receive_data: ");
      Serial.println(receive_data);
    }
    switch(receive_data)
    {
      case CMD_FORWARD:
        disp.display(receive_data);
        break;
      case CMD_BACK:
        disp.display(receive_data);
        break;
      case CMD_LEFT:
        disp.display(receive_data);
        break;
      case CMD_RIGHT:
        disp.display(receive_data);
        break;
      case CMD_DIS_ON:
        disp.display(receive_data);
        break;
      case CMD_DIS_OFF:
        disp.clearDisplay();
        break;
      default:
        break;
    }
  }
}

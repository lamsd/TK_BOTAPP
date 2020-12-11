/**
 * Function List:
 *    1. void TKDCMotor::run(int16_t speed)
 *    2. void TKDCMotor::stop(void)
*/
#include "TKOrion.h"

TKDCMotor motor1(M1);

TKDCMotor motor2(M2);

// Speed is from[0, 250];
uint8_t motorSpeed = 150;

void setup()
{
  
}

void loop()
{
  motor1.run(motorSpeed); 
  motor2.run(motorSpeed);
  delay(2000);
  motor1.stop();
  motor2.stop();
  delay(1000);
  motor1.run(-motorSpeed);
  motor2.run(-motorSpeed);
  delay(2000);
  motor1.stop();
  motor2.stop();
  delay(2000);
}

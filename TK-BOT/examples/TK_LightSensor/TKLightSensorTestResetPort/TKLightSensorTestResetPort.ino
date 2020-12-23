/**
 * Function List:
 *    1. int16_t TKLightSensor::read();
 *    2. void  TKLightSensor::reset(uint8_t port);
 */

/* Includes ------------------------------------------------------------------*/
#include "TKOrion.h"

/* Private variables ---------------------------------------------------------*/
//Instantiate class TKLightSensor
TKLightSensor lightSensor(PORT_6);
//TK Light Sensor can only be connected to PORT_6, PORT_7, PORT_8 on Orion Board of TITKUL.
// lightSensor's value
int value = 0;

/* Private functions ---------------------------------------------------------*/
/**
 * \par Function
 *    setup
 * \par Description
 *    Run once, initialize serial port and reset port.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \return
 *    None.
 * \par Others
 *    None
 */
void setup()
{
  // Initialize serial communication using 9600 bps
  Serial.begin(9600);
  // Reset the port of instance lightSensor to PORT_8
  lightSensor.reset(PORT_8);
  // Reset lightSensor's port to PORT_8.
}

/**
 * \par Function
 *    loop
 * \par Description
 *    Run continuously, print light sensor's DAC value.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \return
 *    None.
 * \par Others
 *    None
 */
void loop()
{
  // Read the lightSensor's value
  value = lightSensor.read();

  // Print results to serial monitor
  Serial.print("value = ");
  Serial.println(value);
  // Wait 100 milliseconds before next loop
  delay(100);
}

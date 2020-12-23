/**

 * Function List:
 *    1. int16_t TKLightSensor::read();
 */

/* Includes ------------------------------------------------------------------*/
#include "TKOrion.h"

/* Private variables ---------------------------------------------------------*/
TKLightSensor lightSensor(PORT_6);
int value = 0;      /* a variable for the lightSensor's value */

/* Private functions ---------------------------------------------------------*/
/**
 * \par Function
 *    setup
 * \par Description
 *    Run once, initialize serial port.
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
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
}

/**
 * \par Function
 *    loop
 * \par Description
 *    Run continuously, print if light sensor's DAC value.
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
  // read the lightSensor value:
  value = lightSensor.read();

  // print the results to the serial monitor
  Serial.print("value = ");
  Serial.println(value);
  // wait 100 milliseconds before the next loop
  delay(100);
}


/**
 *
 * \par Method List:
 *
 *    1. void    TKLightSensor::setpin(uint8_t ledPin, uint8_t sensorPin)
 *    2. int16_t TKLightSensor::read()
 *    3. void    TKLightSensor::lightOn()
 *    4. void    TKLightSensor::lightOff()
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TKLightSensor_H
#define TKLightSensor_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "TKConfig.h"

#ifdef TK_PORT_DEFINED
#include "TKPort.h"
#endif // TK_PORT_DEFINED

/**
 * Class: TKLightSensor
 * \par Description
 * Declaration of Class TKLightSensor.
 */
#ifndef TK_PORT_DEFINED
class TKLightSensor
#else // !TK_PORT_DEFINED
class TKLightSensor : public TKPort
#endif // !TK_PORT_DEFINED
{
public:
#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the light sensor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
  TKLightSensor(void);

/**
 * Alternate Constructor which can call your own function to map the light sensor to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  TKLightSensor(uint8_t port);
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the light sensor to arduino port
 * \param[in]
 *   ledPin - arduino port for led input
 * \param[in]
 *   sensorPin - arduino port for sensor data read
 */
  TKLightSensor(uint8_t ledPin, uint8_t sensorPin);
#endif  // TK_PORT_DEFINED
/**
 * \par Function
 *    setpin
 * \par Description
 *    Set I2C data pin, clock pin and clear display. \n
 *    dataPin - the DATA pin for Seven-Segment LED module. \n
 *    clkPin  - the CLK pin for Seven-Segment LED module.
 * \param[in]
 *    ledPin - Which pin on board that LEDpin is connecting to.
 * \param[in]
 *    sensorPin - Which pin on board that sensorPin is connecting to.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    Set global variable _KeyPin and s2
 */
  void setpin(uint8_t ledPin, uint8_t sensorPin);

/**
 * \par Function
 *    read
 * \par Description
 *    Read analog value of light sensor.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    TKPort::aRead2() - DAC value of current light sensor's output.
 * \par Others
 */
  int16_t read(void);

/**
 * \par Function
 *    lightOn
 * \par Description
 *    Turn on the LED on the light sensor.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 */
  void lightOn(void);

/**
 * \par Function
 *    lightOff
 * \par Description
 *    Turn off the LED on the light sensor.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 */
  void lightOff(void);
private:
  uint8_t _ledPin;
  uint8_t _sensorPin;
};

#endif // TKLightSensor_H

/**
 * \par Method List:
 *
 *    1. void    TKLightSensor::setpin(uint8_t ledPin, uint8_t sensorPin)
 *    2. int16_t TKLightSensor::read()
 *    3. void    TKLightSensor::lightOn()
 *    4. void    TKLightSensor::lightOff()
 * 
 * 
 * @example TLLightSensorTestResetPort.ino \n
 * @example TKLightSensorTest.ino \n
 * @example TKLightSensorTestWithLEDon.ino
 */

/* Private define ------------------------------------------------------------*/
#include "TKLightSensor.h"

/* Private functions ---------------------------------------------------------*/
#ifdef TK_PORT_DEFINED

/**
 * Alternate Constructor which can call your own function to map the light sensor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   NoneS
 */
TKLightSensor::TKLightSensor(void) : TKPort(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the light sensor to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
TKLightSensor::TKLightSensor(uint8_t port) : TKPort(port)
{

}
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the light sensor to arduino port
 * \param[in]
 *   ledPin - arduino port for led input
 * \param[in]
 *   sensorPin - arduino port for sensor data read
 */
TKLightSensor::TKLightSensor(uint8_t ledPin, uint8_t sensorPin)
{
  _ledPin = ledPin;
  _sensorPin = sensorPin;

  pinMode(_ledPin, OUTPUT);
  pinMode(_sensorPin, INPUT);

  digitalWrite(_ledPin,LOW);
}
#endif //TK_PORT_DEFINED

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
void TKLightSensor::setpin(uint8_t ledPin, uint8_t sensorPin)
{
  _ledPin = ledPin;
  _sensorPin = sensorPin;

  pinMode(_ledPin, OUTPUT);
  pinMode(_sensorPin, INPUT);

#ifdef TK_PORT_DEFINED
  s1 = _ledPin;
  s2 = _sensorPin;
#endif // TK_PORT_DEFINED
}

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
 *    MPort::aRead2() - DAC value of current light sensor's output.
 * \par Others
 */
int16_t TKLightSensor::read(void)
{
#ifdef TK_PORT_DEFINED
  return(TKPort::aRead1());
#else //TK_PORT_DEFINED
  return(analogRead(_sensorPin));
#endif //TK_PORT_DEFINED

}

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
void TKLightSensor::lightOn(void)
{
#ifdef TK_PORT_DEFINED
  TKPort::dWrite1(HIGH);
#else //TK_PORT_DEFINED
  digitalWrite(_ledPin,HIGH);
#endif //TK_PORT_DEFINED
}

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
void TKLightSensor::lightOff(void)
{
#ifdef TK_PORT_DEFINED
  TKPort::dWrite1(LOW);
#else //TK_PORT_DEFINED
  digitalWrite(_ledPin,LOW);
#endif //TK_PORT_DEFINED

}

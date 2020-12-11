
#include "TKGasSensor.h"

#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the gas snesor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
TKGasSensor::TKGasSensor(void) : TKPort(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the gas snesor to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
TKGasSensor::TKGasSensor(uint8_t port) : TKPort(port)
{

}
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the gas snesor to arduino port,
 * it will assigned the input pin for gas snesor.
 * \param[in]
 *   digital_pin - arduino port for digital signal input
 * \param[in]
 *   analog_pin - arduino port for analog signal input
 */
TKGasSensor::TKGasSensor(uint8_t digital_pin,uint8_t analog_pin)
{
  _digital_pin = digital_pin;
  _analog_pin = analog_pin;
  pinMode(_digital_pin, INPUT);
}
#endif /* TK_PORT_DEFINED */

/**
 * \par Function
 *   setpin
 * \par Description
 *   Reset the gas snesor available PIN by its arduino port.
 * \param[in]
 *   digital_pin - arduino port for digital signal input
 * \param[in]
 *   analog_pin - arduino port for analog signal input
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void TKGasSensor::setpin(uint8_t digital_pin,uint8_t analog_pin)
{
  _digital_pin = digital_pin;
  _analog_pin = analog_pin;
  pinMode(_digital_pin, INPUT);
#ifdef TK_PORT_DEFINED
  s1 = _analog_pin;
  s2 = _digital_pin;
#endif // TK_PORT_DEFINED
}

/**
 * \par Function
 *   readDigital
 * \par Description
 *   Read the digital signal of gas snesor, It is the result of comparison between the threshold
 *   value and the analog output. The threshold value can be adjusted using a rheostat
 * \par Output
 *   None
 * \return
 *   true - The gas concentration exceeds \n
 *   false - The concentration of the gas in the range
 * \par Others
 *   None
 */
uint8_t TKGasSensor::readDigital(void)
{
#ifdef TK_PORT_DEFINED
  return( TKPort::dRead2() );
#else //TK_PORT_DEFINED
  return digitalRead(_digital_pin);
#endif //TK_PORT_DEFINED
}

/**
 * \par Function
 *   readAnalog
 * \par Description
 *   Read the analog signal of gas snesor.
 * \par Output
 *   None
 * \return
 *   The vlaue from gas snesor's analog output
 * \par Others
 *   None
 */
int16_t TKGasSensor::readAnalog(void)
{
#ifdef TK_PORT_DEFINED
  return( TKPort::aRead1() );
#else //TK_PORT_DEFINED
  return analogRead(_analog_pin);
#endif //TK_PORT_DEFINED
}


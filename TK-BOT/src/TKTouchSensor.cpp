

#include "TKTouchSensor.h"

#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the touch Sensor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
TKTouchSensor::TKTouchSensor(void) : TKPort(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the touch Sensor to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
TKTouchSensor::TKTouchSensor(uint8_t port) : TKPort(port)
{

}
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the touch Sensor to arduino port,
 * it will assigned the TogPin PIN and OutputPin pin.
 * \param[in]
 *   TogPin - arduino port for output type option pin(should digital pin)
 * \param[in]
 *   OutputPin - arduino port for output pin(should digital pin)
 */
TKTouchSensor::TKTouchSensor(uint8_t TogPin, uint8_t OutputPin)
{
  _TogPin = TogPin;
  _OutputPin = OutputPin;
  pinMode(_TogPin,OUTPUT);
  pinMode(_OutputPin,INPUT);
  digitalWrite(_TogPin,LOW);
}
#endif // TK_PORT_DEFINED

/**
 * \par Function
 *   setpin
 * \par Description
 *   Reset the touch Sensor available PIN by its arduino port.
 * \param[in]
 *   TogPin - arduino port for output type option pin(should digital pin)
 * \param[in]
 *   OutputPin - arduino port for output pin(should digital pin)
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void TKTouchSensor::setpin(uint8_t TogPin, uint8_t OutputPin)
{
  _TogPin = TogPin;
  _OutputPin = OutputPin;
  pinMode(_TogPin,OUTPUT);
  pinMode(_OutputPin,INPUT);
#ifdef TK_PORT_DEFINED
  s1 = _TogPin;
  s2 = _OutputPin;
#endif // TK_PORT_DEFINED
}

/**
 * \par Function
 *   touched
 * \par Description
 *   Read and return the output signal.
 * \par Output
 *   None
 * \return
 *   The output signal of touch sensor
 * \par Others
 *   None
 */
bool TKTouchSensor::touched(void)
{
#ifdef TK_PORT_DEFINED
  return(TKPort::dRead2());
#else // TK_PORT_DEFINED
  return(digitalRead(_OutputPin))
#endif // TK_PORT_DEFINED
}

/**
 * \par Function
 *   SetTogMode
 * \par Description
 *   Set the output type.
 * \param[in]
 *   TogMode - 1=> Toggle mode; 0(default)=>Direct mode
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void TKTouchSensor::SetTogMode(uint8_t TogMode)
{
#ifdef TK_PORT_DEFINED
  TKPort::dWrite1(TogMode);
#else // TK_PORT_DEFINED
  digitalWrite(_TogPin,TogMode);
#endif // TK_PORT_DEFINED
}



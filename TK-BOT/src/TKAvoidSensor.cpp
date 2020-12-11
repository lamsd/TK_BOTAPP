

#include "TKAvoidSensor.h"

#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the obtecle dectection Sensor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
TKAvoidSensor::TKAvoidSensor(void) : TKPort(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the obtecle dectection Sensor to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
TKAvoidSensor::TKAvoidSensor(uint8_t port) : TKPort(port)
{

}
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the obtecle dectection Sensor to arduino port,
 * it will assigned the TogPin PIN and OutputPin pin.
 * \param[in]
 *   TogPin - arduino port for output type option pin(should digital pin)
 * \param[in]
 *   OutputPin - arduino port for output pin(should digital pin)
 */
TKAvoidSensor::TKAvoidSensor(uint8_t TogPin, uint8_t OutputPin)
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
 *   Reset the obtecle dectection Sensor available PIN by its arduino port.
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
void TKAvoidSensor::setpin(uint8_t TogPin, uint8_t OutputPin)
{
  _TogPin = TogPin;
  _OutputPin = OutputPin;
  pinMode(_TogPin,INPUT);
  pinMode(_OutputPin,INPUT);
#ifdef TK_PORT_DEFINED
  s1 = _TogPin;
  s2 = _OutputPin;
#endif // TK_PORT_DEFINED
}

/**
 * \par Function
 *   Avoidtested
 * \par Description
 *   Read and return the output signal.
 * \par Output
 *   None
 * \return
 *   The output signal of touch sensor
 * \par Others
 *   None
 */
bool TKAvoidSensor::Avoidtested(void)
{
#ifdef TK_PORT_DEFINED
  return(digitalRead(s1));
  //return(TKPort::dRead1());
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
void TKAvoidSensor::SetTogMode(uint8_t TogMode)
{
#ifdef TK_PORT_DEFINED
  TKPort::dWrite1(TogMode);
#else // TK_PORT_DEFINED
  digitalWrite(_TogPin,TogMode);
#endif // TK_PORT_DEFINED
}



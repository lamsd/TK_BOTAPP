

#include "TKLineFollower.h"

#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the line follwer device to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
TKLineFollower::TKLineFollower(void) : TKPort(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the line follwer device to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
TKLineFollower::TKLineFollower(uint8_t port) : TKPort(port)
{

}
#else // TK_PORT_DEFINED 
/**
 * Alternate Constructor which can call your own function to map the line follwer device to arduino port,
 * it will assigned the input pin.
 * \param[in]
 *   Sensor1 - arduino port(should digital pin)
 * \param[in]
 *   Sensor2 - arduino port(should digital pin)
 */
TKLineFollower::TKLineFollower(uint8_t Sensor1,uint8_t Sensor2)
{
  _Sensor1 = Sensor1;
  _Sensor2 = Sensor2;
  pinMode(_Sensor1,INPUT);
  pinMode(_Sensor2,INPUT);
}
#endif // TK_PORT_DEFINED

/**
 * \par Function
 *   setpin
 * \par Description
 *   Reset the line follwer device available PIN by its arduino port.
 * \param[in]
 *   Sensor1 - arduino port(should digital pin)
 * \param[in]
 *   Sensor2 - arduino port(should digital pin)
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void TKLineFollower::setpin(uint8_t Sensor1,uint8_t Sensor2)
{
  _Sensor1 = Sensor1;
  _Sensor2 = Sensor2;
  pinMode(_Sensor1,INPUT);
  pinMode(_Sensor2,INPUT);
#ifdef TK_PORT_DEFINED
  s1 = _Sensor1;
  s2 = _Sensor2;
#endif // TK_PORT_DEFINED
}

/**
 * \par Function
 *   readSensors
 * \par Description
 *   Get the sensors state.
 * \par Output
 *   None
 * \return
 *   (0x00)-S1_IN_S2_IN:   sensor1 and sensor2 are both inside of black line \n
 *   (0x01)-S1_IN_S2_OUT:  sensor1 is inside of black line and sensor2 is outside of black line \n
 *   (0x02)-S1_OUT_S2_IN:  sensor1 is outside of black line and sensor2 is inside of black line \n
 *   (0x03)-S1_OUT_S2_OUT: sensor1 and sensor2 are both outside of black line
 * \par Others
 *   None
 */
uint8_t TKLineFollower::readSensors(void)
{
  uint8_t state	= S1_IN_S2_IN;
#ifdef TK_PORT_DEFINED
  bool s1State = TKPort::dRead1();
  bool s2State = TKPort::dRead2();
#else // TK_PORT_DEFINED
  bool s1State = digitalRead(_Sensor1);
  bool s2State = digitalRead(_Sensor2);
#endif // TK_PORT_DEFINED
  state = ( (1 & s1State) << 1) | s2State;
  return(state);
}

/**
 * \par Function
 *   readSensor1
 * \par Description
 *   Get the sensors1(left sensors) state.
 * \par Output
 *   None
 * \return
 *   0: sensor1 is inside of black line \n
 *   1: sensor1 is outside of black line
 * \par Others
 *   None
 */
bool TKLineFollower::readSensor1(void)
{
#ifdef TK_PORT_DEFINED
  return(TKPort::dRead1() );
#else // TK_PORT_DEFINED
  return digitalRead(_Sensor1);
#endif // TK_PORT_DEFINED
}

/**
 * \par Function
 *   readSensor2
 * \par Description
 *   Get the sensors2(right sensors) state.
 * \par Output
 *   None
 * \return
 *   0: sensor1 is inside of black line \n
 *   1: sensor1 is outside of black line
 * \par Others
 *   None
 */
bool TKLineFollower::readSensor2(void)
{
#ifdef TK_PORT_DEFINED
	return(TKPort::dRead2() );
#else // TK_PORT_DEFINED
  return digitalRead(_Sensor2);
#endif // TK_PORT_DEFINED
}



#include "TKJoystick.h"

volatile uint8_t TKJoystick::_X_port = 0;
volatile uint8_t TKJoystick::_Y_port = 0;
volatile int16_t TKJoystick::_X_offset = 0;
volatile int16_t TKJoystick::_Y_offset = 0;

#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the TKJoystick to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
TKJoystick::TKJoystick(void) : TKPort(0)
{
}

/**
 * Alternate Constructor which can call your own function to map the TKJoystick to arduino port.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
TKJoystick::TKJoystick(uint8_t port) : TKPort(port)
{
}
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the TKJoystick to arduino port,
 * it will assigned the X-axis pin and Y-axis pin.
 * \param[in]
 *   x_port - arduino port(should analog pin)
 * \param[in]
 *   y_port - arduino port(should analog pin)
 */
TKJoystick::TKJoystick(uint8_t x_port,uint8_t y_port)
{
  _X_port = x_port;
  _Y_port = y_port;
}
#endif // TK_PORT_DEFINED

/**
 * \par Function
 *   setpin
 * \par Description
 *   Reset the TKJoystick available PIN by its arduino port.
 * \param[in]
 *   x_port - arduino port for X value PIN(should analog pin)
 * \param[in]
 *   y_port - arduino port for Y value PIN(should analog pin)
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void TKJoystick::setpin(uint8_t x_port,uint8_t y_port)
{
  _X_port = x_port;
  _Y_port = y_port;
#ifdef TK_PORT_DEFINED
  s1 = x_port;
  s2 = y_port;
#endif // TK_PORT_DEFINED
}

/**
 * \par Function
 *   readX
 * \par Description
 *   Get the value of X-axis
 * \par Output
 *   None
 * \return
 *   The X-axis value from(-500 - 500)
 * \par Others
 *   None
 */
int16_t TKJoystick::readX(void)
{
  int16_t x_value;
#ifdef TK_PORT_DEFINED
  x_value = TKPort::aRead1();
#else // TK_PORT_DEFINED
  x_value = analogRead(_X_port);
#endif // TK_PORT_DEFINED
  x_value = (x_value - CENTER_VALUE) + _X_offset;
  return x_value;
}

/**
 * \par Function
 *   readY
 * \par Description
 *   Get the value of Y-axis
 * \par Output
 *   None
 * \return
 *   The Y-axis value from(-500 - 500)
 * \par Others
 *   None
 */
int16_t TKJoystick::readY(void)
{
  int16_t y_value;
#ifdef TK_PORT_DEFINED
  y_value = TKPort::aRead2();
#else // TK_PORT_DEFINED
  y_value = analogRead(_Y_port);
#endif // TK_PORT_DEFINED
  y_value = (y_value - CENTER_VALUE) + _Y_offset;
  return y_value;
}

/**
 * \par Function
 *   read
 * \par Description
 *   Get the value of setting axis
 * \param[in]
 *   index - '1' for X-axis and '2' for Y-axis
 * \par Output
 *   None
 * \return
 *   The setting axis value from(-500 - 500)
 * \par Others
 *   None
 */
int16_t TKJoystick::read(uint8_t index)
{
  int16_t value = 0;
  if(index == 1)
  {
#ifdef TK_PORT_DEFINED
    value = TKPort::aRead1();
#else // TK_PORT_DEFINED
    value = analogRead(_X_port);
#endif // TK_PORT_DEFINED
    value = (value - CENTER_VALUE) + _X_offset;
  }
  else if(index == 2)
  {
#ifdef TK_PORT_DEFINED
    value = TKPort::aRead2();
#else // TK_PORT_DEFINED
    value = analogRead(_Y_port);
#endif // TK_PORT_DEFINED
    value = (value - CENTER_VALUE) + _Y_offset;
  }
  return value;
}

/**
 * \par Function
 *   CalCenterValue
 * \par Description
 *   If joystick not been triggered(The default middle position), But the X-axis
 *   and Y-axis is not 0, we can use this function to calibration its 0 value.
 * \param[in]
 *   x_offset - The offset vlaue we needed to calibrate the X-axis
 * \param[in]
 *   y_offset - The offset vlaue we needed to calibrate the Y-axis
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void TKJoystick::CalCenterValue(int16_t x_offset,int16_t y_offset)
{
  _X_offset = x_offset;
  _Y_offset = y_offset;
}

/**
 * \par Function
 *   angle
 * \par Description
 *   We can use function to get the angle of the joystick
 * \par Output
 *   None
 * \return
 *   The angle of the joystick(-180 - 180)
 * \par Others
 *   None
 */
float TKJoystick::angle(void)
{
  int16_t x_value;
  int16_t y_value;
  float angle;
#ifdef TK_PORT_DEFINED
  x_value = TKPort::aRead1();
  y_value = TKPort::aRead2();
#else // TK_PORT_DEFINED
  x_value = analogRead(_X_port);
  y_value = analogRead(_Y_port);
#endif // TK_PORT_DEFINED
  x_value = (x_value - CENTER_VALUE) + _X_offset;
  y_value = (y_value - CENTER_VALUE) + _Y_offset;
  if((abs(x_value) < 10) && (abs(y_value) < 10))
  {
    angle = 0;
  }
  else
  {
    angle = atan2(x_value, y_value) * 180.0 / PI;
  }
  return angle;
}

/**
 * \par Function
 *   OffCenter
 * \par Description
 *   We can use function to get the off-center distance of the joystick
 * \par Output
 *   None
 * \return
 *   The off-center distance of the joystick(0 - 700)
 * \par Others
 *   None
 */
float TKJoystick::OffCenter(void)
{
  long dx   = abs(readX());
  long dy   = abs(readY());
  long dist = dx * dx + dy * dy;
  return(min(CENTER_VALUE*sqrt(2), sqrt(dist)));
}


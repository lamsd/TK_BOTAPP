
#ifndef TKJoystick_H
#define TKJoystick_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "TKConfig.h"

#ifdef TK_PORT_DEFINED
#include "TKPort.h"
#endif // TK_PORT_DEFINED

#define CENTER_VALUE    (490)

/**
 * Class: TKJoystick
 * \par Description
 * Declaration of Class TKJoystick.
 */
#ifndef TK_PORT_DEFINED
class TKJoystick
#else // !TK_PORT_DEFINED
class TKJoystick : public TKPort
#endif
{
  public:
#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the TKJoystick to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
    TKJoystick(void);

/**
 * Alternate Constructor which can call your own function to map the TKJoystick to arduino port.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
    TKJoystick(uint8_t port);
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the TKJoystick to arduino port,
 * it will assigned the X-axis pin and Y-axis pin
 * \param[in]
 *   x_port - arduino port(should analog pin)
 * \param[in]
 *   y_port - arduino port(should analog pin)
 */
    TKJoystick(uint8_t x_port,uint8_t y_port);
#endif  // TK_PORT_DEFINED

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
    void setpin(uint8_t x_port, uint8_t y_port);

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
    int16_t readX(void);

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
    int16_t readY(void);

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
  int16_t read(uint8_t index);

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
    void CalCenterValue(int16_t = 0, int16_t = 0);

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
    float angle(void);

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
    float OffCenter(void);
  private:
    static volatile int16_t _X_offset;
    static volatile int16_t _Y_offset;
    static volatile uint8_t _X_port;
    static volatile uint8_t _Y_port;
};
#endif

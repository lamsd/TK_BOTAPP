
#ifndef TKLineFollower_H
#define TKLineFollower_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "TKConfig.h"

#ifdef TK_PORT_DEFINED
#include "TKPort.h"
#endif // TK_PORT_DEFINED

#define S1_IN_S2_IN   (0x00)    // sensor1 and sensor2 are both inside of black line
#define S1_IN_S2_OUT  (0x01)    // sensor1 is inside of black line and sensor2 is outside of black line
#define S1_OUT_S2_IN  (0x02)    // sensor1 is outside of black line and sensor2 is inside of black line
#define S1_OUT_S2_OUT (0x03)    // sensor1 and sensor2 are both outside of black line

/**
 * Class: TKLineFollower
 * \par Description
 * Declaration of Class TKLineFollower.
 */
#ifndef TK_PORT_DEFINED
class TKLineFollower
#else // !TK_PORT_DEFINED
class TKLineFollower : public TKPort
#endif  // TK_PORT_DEFINED
{
public:
#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the line follwer device to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
  TKLineFollower(void);

/**
 * Alternate Constructor which can call your own function to map the line follwer device to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  TKLineFollower(uint8_t port);
#else // TK_PORT_DEFINED 
/**
 * Alternate Constructor which can call your own function to map the line follwer device to arduino port,
 * it will assigned the input pin.
 * \param[in]
 *   Sensor1 - arduino port(should digital pin)
 * \param[in]
 *   Sensor2 - arduino port(should digital pin)
 */
  TKLineFollower(uint8_t Sensor1,uint8_t Sensor2);
#endif  // TK_PORT_DEFINED
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
  void setpin(uint8_t Sensor1,uint8_t Sensor2);

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
  uint8_t readSensors(void);

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
  bool readSensor1(void);

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
  bool readSensor2(void);
private:
  volatile uint8_t  _Sensor1;
  volatile uint8_t  _Sensor2;
};
#endif

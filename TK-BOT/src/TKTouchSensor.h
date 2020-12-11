
#ifndef TKTouchSensor_H
#define TKTouchSensor_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "TKConfig.h"

#ifdef TK_PORT_DEFINED
#include "TKPort.h"
#endif /* TK_PORT_DEFINED */

/**
 * Class: TKTouchSensor
 * \par Description
 * Declaration of Class TKTouchSensor.
 */
#ifndef TK_PORT_DEFINED
class TKTouchSensor
#else /* !TK_PORT_DEFINED */
class TKTouchSensor : public TKPort
#endif // !TK_PORT_DEFINED
{
public:
#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the touch Sensor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
  TKTouchSensor(void);
  
/**
 * Alternate Constructor which can call your own function to map the touch Sensor to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  TKTouchSensor(uint8_t port);
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the touch Sensor to arduino port,
 * it will assigned the TogPin PIN and OutputPin pin.
 * \param[in]
 *   TogPin - arduino port for output type option pin(should digital pin)
 * \param[in]
 *   OutputPin - arduino port for output pin(should digital pin)
 */
  TKTouchSensor(uint8_t TogPin, uint8_t OutputPin);
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
  void setpin(uint8_t TogPin, uint8_t OutputPin);

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
  bool touched(void);

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
  void SetTogMode(uint8_t TogMode);
private:
  volatile uint8_t _TogPin;
  volatile uint8_t _OutputPin;
};

#endif


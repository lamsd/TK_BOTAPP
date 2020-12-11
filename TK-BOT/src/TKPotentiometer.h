
#ifndef TKPotentiometer_H
#define TKPotentiometer_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "TKConfig.h"

#ifdef TK_PORT_DEFINED
#include "TKPort.h"
#endif // TK_PORT_DEFINED

/**
 * Class: TKPotentiometer
 * \par Description
 * Declaration of Class TKPotentiometer.
 */
#ifndef TK_PORT_DEFINED
class TKPotentiometer
#else // !TK_PORT_DEFINED
class TKPotentiometer : public TKPort
#endif  // !TK_PORT_DEFINED
{
public:
#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the TK potentiometer device to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
  TKPotentiometer(void);

/**
 * Alternate Constructor which can call your own function to map the TK potentiometer device to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  TKPotentiometer(uint8_t port);
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the TK potentiometer device to arduino port
 * \param[in]
 *   potentiometerPin - arduino port for potentiometer output port
 */
  TKPotentiometer(uint8_t potentiometerPin);
#endif // TK_PORT_DEFINED
/**
 * \par Function
 *    setpin
 * \par Description
 *    Reset the potentiometer device available PIN by its arduino port.
 * \param[in]
 *   potentiometerPin - arduino port for potentiometer output port
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void setpin(uint8_t potentiometerPin);

/**
 * \par Function
 *    read()
 * \par Description
 *    Read DAC value of TK potentiometer module.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    The value of potentiometer device(0-1024)
 * \par Others
 *    None
 */
  uint16_t read(void);
private:
  volatile uint8_t _potentiometerPin;
};
#endif // TKPotentiometer_H

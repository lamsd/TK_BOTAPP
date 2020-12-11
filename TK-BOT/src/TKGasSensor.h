#ifndef TKGasSensor_H
#define TKGasSensor_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "TKConfig.h"


#ifdef TK_PORT_DEFINED
#include "TKPort.h"
#endif // TK_PORT_DEFINED

#define Gas_Exceeded     (0x00)
#define Gas_not_Exceeded (0x01)

/**
 * Class: TKGasSensor
 * \par Description
 * Declaration of Class TKGasSensor
 */
#ifndef TK_PORT_DEFINED  
class TKGasSensor
#else // !TK_PORT_DEFINED
class TKGasSensor : public TKPort
#endif  // !TK_PORT_DEFINED
{
public:
#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the gas snesor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
  TKGasSensor(void);

/**
 * Alternate Constructor which can call your own function to map the gas snesor to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  TKGasSensor(uint8_t port);
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the gas snesor to arduino port,
 * it will assigned the input pin for gas snesor.
 * \param[in]
 *   digital_pin - arduino port for digital signal input
 * \param[in]
 *   analog_pin - arduino port for analog signal input
 */
  TKGasSensor(uint8_t digital_pin,uint8_t analog_pin)
#endif // TK_PORT_DEFINED
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
  void setpin(uint8_t digital_pin,uint8_t analog_pin);

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
  uint8_t readDigital(void);

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
  int16_t readAnalog(void);
private:
  volatile uint8_t _digital_pin;
  volatile uint8_t _analog_pin;
};
#endif


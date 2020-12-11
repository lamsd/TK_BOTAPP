

#ifndef TKSoundSensor_H
#define TKSoundSensor_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "TKConfig.h"

#ifdef TK_PORT_DEFINED
#include "TKPort.h"
#endif /* TK_PORT_DEFINED */

/**
 * Class: TKSoundSensor
 * \par Description
 * Declaration of Class TKSoundSensor.
 */
#ifndef TK_PORT_DEFINED
class TKSoundSensor
#else // !TK_PORT_DEFINED
class TKSoundSensor : public TKPort
#endif // !TK_PORT_DEFINED
{
public:
#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Sound Sensor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
  TKSoundSensor(void);

/**
 * Alternate Constructor which can call your own function to map the Sound Sensor to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  TKSoundSensor(uint8_t port);
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Sound Sensor to arduino port,
 * it will assigned the output pin.
 * \param[in]
 *   port - arduino port(should analog pin)
 */
  TKSoundSensor(uint8_t port);
#endif // TK_PORT_DEFINED

/**
 * \par Function
 *   setpin
 * \par Description
 *   Reset the Sound Sensor available PIN by its arduino port.
 * \param[in]
 *   SoundSensorPin - arduino port for sensor read(should analog pin)
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  void setpin(uint8_t SoundSensorPin);

/**
 * \par Function
 *   strength
 * \par Description
 *   Read and return the sensor value.
 * \par Output
 *   None
 * \return
 *   The sensor value of sound sensor
 * \par Others
 *   None
 */
  int16_t strength(void);
private:
  volatile uint8_t  _SoundSensorRead;
};

#endif

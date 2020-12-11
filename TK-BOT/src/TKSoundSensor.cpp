

#include "TKSoundSensor.h"

#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Sound Sensor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
TKSoundSensor::TKSoundSensor(void) : TKPort(0)
{
}

/**
 * Alternate Constructor which can call your own function to map the Sound Sensor to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
TKSoundSensor::TKSoundSensor(uint8_t port) : TKPort(port)
{
}
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Sound Sensor to arduino port,
 * it will assigned the output pin.
 * \param[in]
 *   port - arduino port(should analog pin)
 */
TKSoundSensor::TKSoundSensor(uint8_t port)
{
  _SoundSensorRead = port;
}
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
void TKSoundSensor::setpin(uint8_t SoundSensorPin)
{
  _SoundSensorRead = SoundSensorPin;

#ifdef TK_PORT_DEFINED
  s2 = _SoundSensorRead;
#endif // TK_PORT_DEFINED
}

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
int16_t TKSoundSensor::strength(void)
{
#ifdef TK_PORT_DEFINED
  return(TKPort::aRead2());
#else // TK_PORT_DEFINED
  return analogRead(_SoundSensorRead);
#endif // TK_PORT_DEFINED
}



#include "TKTemperatureTh.h"

#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
TKTemperatureTh::TKTemperatureTh(void) : TKPort()
{

}

/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port,
 * the slot2 pin will be used here since specify slot is not be set.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
TKTemperatureTh::TKTemperatureTh(uint8_t port) : TKPort(port)
{
  _DataPin = s1;
  _ts.reset(s1);
}

/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 * \param[in]
 *   slot - SLOT1 or SLOT2
 */
TKTemperatureTh::TKTemperatureTh(uint8_t port, uint8_t slot) : TKPort(port)
{
  TKPort::reset(port, slot);
  _DataPin = SLOT2 ? s1 : s2;
  _ts.reset(slot == SLOT2 ? s1 : s2);
}
#else //TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port.
 * \param[in]
 *   port - arduino port
 */
TKTemperatureTh::TKTemperatureTh(uint8_t port)
{
  _DataPin = port;
  _ts.reset(port);
}
#endif //TK_PORT_DEFINED

/**
 * \par Function
 *   reset
 * \par Description
 *   Reset the available PIN for temperature sensor by its RJ25 port,
 *   the slot2 pin will be used here since specify slot is not be set
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void TKTemperatureTh::reset(uint8_t port)
{
  TKPort::reset(port);
  _ts.reset(s1);
}

/**
 * \par Function
 *   reset
 * \par Description
 *   Reset the available PIN for temperature sensor by its RJ25 port.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 * \param[in]
 *   slot - SLOT1 or SLOT2
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void TKTemperatureTh::reset(uint8_t port, uint8_t slot)
{
  TKPort::reset(port, slot);
  _ts.reset(slot == SLOT2 ? s1 : s2);
}

/**
 * \par Function
 *   setpin
 * \par Description
 *   Reset available PIN for temperature sensor by its arduino port.
 * \param[in]
 *   port - arduino port(should digital pin)
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void TKTemperatureTh::setpin(uint8_t port)
{
  _DataPin = port;
  _ts.reset(port);
}
/**
 * \par Function
 *   temperature
 * \par Description
 *   Get the celsius of temperature
 * \par Output
 *   None
 * \return
 *   The temperature value get from the sensor.
 * \par Others
 *   None
 */
float TKTemperatureTh::temperature(void)
{ 
  _ts.reset();
  _ts.skip();
  int B = 3950;
  int RT0 = 10000;
  float VRT = analogRead(_DataPin);
  VRT = (5.00 /1023.00) * VRT;
  float VR = 5.00 - VRT;
  float RT = VRT /(VR/10000);
  return (1/((log(RT/RT0)/B)+(1/(25+273.15)))) -273.15;
}


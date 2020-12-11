
#include "TKTemperature.h"

#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
TKTemperature::TKTemperature(void) : TKPort()
{

}

/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port,
 * the slot2 pin will be used here since specify slot is not be set.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
TKTemperature::TKTemperature(uint8_t port) : TKPort(port)
{
  _DataPin = s2;
  _ts.reset(s2);
}

/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 * \param[in]
 *   slot - SLOT1 or SLOT2
 */
TKTemperature::TKTemperature(uint8_t port, uint8_t slot) : TKPort(port)
{
  TKPort::reset(port, slot);
  _DataPin = SLOT2 ? s2 : s1;
  _ts.reset(slot == SLOT2 ? s2 : s1);
}
#else //TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port.
 * \param[in]
 *   port - arduino port
 */
TKTemperature::TKTemperature(uint8_t port)
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
void TKTemperature::reset(uint8_t port)
{
  TKPort::reset(port);
  _ts.reset(s2);
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
void TKTemperature::reset(uint8_t port, uint8_t slot)
{
  TKPort::reset(port, slot);
  _ts.reset(slot == SLOT2 ? s2 : s1);
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
void TKTemperature::setpin(uint8_t port)
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
float TKTemperature::temperature(void)
{
  byte  i;
  byte  present = 0;
  byte  type_s;
  byte  data[12];
  byte	addr[8];
  float celsius;
  long  time;

  _ts.reset();
  _ts.skip();
  _ts.write(STARTCONVO);       // start conversion, with parasite power on at the end
  time = millis();
  while(!_ts.readIO() && (millis() - time) < 750)
  {
    ;
  }

  present = _ts.reset();
  _ts.skip();
  _ts.write(READSCRATCH);
  for(i = 0; i < 5; i++)      // we need 9 bytes
  {
    data[i] = _ts.read();
  }

  int16_t rawTemperature = (data[1] << 8) | data[0];

  return( (float)rawTemperature * 0.0625); // 12 bit
}


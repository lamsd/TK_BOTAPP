#ifndef TKBluetooth_H
#define TKBluetooth_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "TKConfig.h"
#include "TKSerial.h"

#ifdef TK_PORT_DEFINED
#include "TKPort.h"
#endif

/**
 * Class: TKBluetooth
 * \par Description
 * Declaration of Class TKBluetooth.
 */
#ifndef TK_PORT_DEFINED
class TKBluetooth
#else // !TK_PORT_DEFINED
class TKBluetooth : public TKSerial
#endif // !TK_PORT_DEFINED
{
public:
#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Bluetooth to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
  TKBluetooth();

/**
 * Alternate Constructor which can call your own function to map the Bluetooth to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  TKBluetooth(uint8_t port);
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Bluetooth to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * \param[in]
 *   receivePin - the rx pin of serial(arduino port)
 * \param[in]
 *   transmitPin - the tx pin of serial(arduino port)
 * \param[in]
 *   inverse_logic - Whether the Serial level need inv.
 */
  TKBluetooth(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic = false);
#endif // TK_PORT_DEFINED
};
#endif


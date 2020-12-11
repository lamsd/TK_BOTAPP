
#include "TKBluetooth.h"

#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Bluetooth to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
TKBluetooth::TKBluetooth() : TKSerial(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the Bluetooth to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
TKBluetooth::TKBluetooth(uint8_t port) : TKSerial(port)
{

}
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
TKBluetooth::TKBluetooth(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic)\
                        : TKSerial(receivePin, transmitPin, inverse_logic)
{

}
#endif // TK_PORT_DEFINED



#ifndef TKPS2_H
#define TKPS2_H

#include <stdbool.h>
#include <stdint.h>
#include <Arduino.h>
#include "TKConfig.h"
#include "TKSerial.h"

#ifdef TK_PORT_DEFINED
#include "TKPort.h"
#endif 

#define TKJOYSTICK_RX           6
#define TKJOYSTICK_RY           8
#define TKJOYSTICK_LX           2
#define TKJOYSTICK_LY           4

#define TKJOYSTICK_R1           1
#define TKJOYSTICK_R2           3
#define TKJOYSTICK_L1           5
#define TKJOYSTICK_L2           7
#define TKJOYSTICK_TRIANGLE     9
#define TKJOYSTICK_XSHAPED      10
#define TKJOYSTICK_SQUARE       11
#define TKJOYSTICK_ROUND        12
#define TKJOYSTICK_START        13
#define TKJOYSTICK_UP           14
#define TKJOYSTICK_DOWN         15
#define TKJOYSTICK_LEFT         16
#define TKJOYSTICK_RIGHT        17
#define TKJOYSTICK_SELECT       18
#define TKJOYSTICK_MODE         19
#define TKJOYSTICK_BUTTON_L     20
#define TKJOYSTICK_BUTTON_R     21
#define TKJOYSTICK_INIT_VALUE   0
#define TKJOYSTICK_ANALOG_ERROR 0

/**
 * Class: TKPS2
 * \par Description
 * Declaration of Class TKPS2.
 */
#ifndef TK_PORT_DEFINED
  class TKPS2
#else /* !TK_PORT_DEFINED */
  class TKPS2 : public TKSerial
#endif  /* !TK_PORT_DEFINED */

{
public:

#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the TKPS2 to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
  TKPS2();

/**
 * Alternate Constructor which can call your own function to map the TKPS2 to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  TKPS2(uint8_t port);
#else  // TK_PORT_DEFINED

/**
 * Alternate Constructor which can call your own function to map the TKPS2 to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * \param[in]
 *   receivePin - the rx pin of serial(arduino port)
 * \param[in]
 *   transmitPin - the tx pin of serial(arduino port)
 * \param[in]
 *   inverse_logic - Whether the Serial level need inv.
 */	
  TKPS2(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic);
#endif  // TK_PORT_DEFINED

/**
 * \par Function
 *    readSerial
 * \par Description
 *    Read the Serial data.
 * \param[in]
 *   None
 * \par Output
 *    None
 * \par Return
 *   None
 * \par Others
 *    Save the data to _serialRead.
 */
  void readSerial(void);

/**
 * \par Function
 *    readBuffer
 * \par Description
 *    Read the buffer data.
 * \param[in]
 *    index
 * \par Output
 *    None
 * \par Return
 *    buffer
 * \par Others
 *    None
 */
  uint8_t readBuffer(int16_t index);

/**
 * \par Function
 *    writeBuffer
 * \par Description
 *    Write the datas to the buffer.
 * \param[in]
 *    index,c
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void writeBuffer(int16_t index,uint8_t c);

/**
 * \par Function
 *    readjoystick
 * \par Description
 *    This function is used to read the handle datas.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Returns 0 if no data ready, 1 if data ready.
 * \par Others
 *    None
 */
  boolean readjoystick(void);

/**
 * \par Function
 *    TKAnalog
 * \par Description
 *    Read the handle remote sensing analog value.
 * \param[in]
 *    Button
 * \par Output
 *    None
 * \par Return
 *    Analog value(0~255). if none return 128.
 * \par Others
 *    None
 */
  int16_t TKAnalog(uint8_t button);

/**
 * \par Function
 *    ButtonPressed
 * \par Description
 *   This function is used to check the button whether to press.
 * \param[in]
 *    Button
 * \par Output
 *    None
 * \par Return
 *   Return button state.
 * \par Others
 *    None
 */
  boolean ButtonPressed(uint8_t button);

/**
 * \par Function
 *   loop
 * \par Description
 *   Save the TKPS2 datas to the datalist.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void loop(void);

private:
  uint8_t _serialRead;
  uint8_t _dataLen;
  uint8_t _index = 0;
  uint8_t _prevc = 0;
  uint8_t buffer[16];
  uint8_t ps2_data_list[23];
  uint8_t ps2_data_list_bak[23];
  long _lasttime;

  boolean _isStart;
  boolean _isAvailable;
  boolean _isReady;
};
#endif
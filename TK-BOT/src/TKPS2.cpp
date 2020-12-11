


#include "TKPS2.h"
#include "TKSerial.h"

#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the TKPS2 to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
TKPS2::TKPS2() : TKSerial(0)
{
  _isReady = false;
  _isAvailable = false;
  _isStart = false;
  _lasttime = millis();
}

/**
 * Alternate Constructor which can call your own function to map the TKPS2 to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
 TKPS2::TKPS2(uint8_t port) : TKSerial(port)
{
  _isReady = false;
  _isAvailable = false;
  _isStart = false;
  _lasttime = millis();
}
#else // TK_PORT_DEFINED
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
TKPS2::TKPS2(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic)\
                        : TKSerial(receivePin, transmitPin, inverse_logic)
{
  _isReady = false;
  _isAvailable = false;
  _isStart = false;
  _lasttime = millis();
}
#endif  // TK_PORT_DEFINED


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
uint8_t TKPS2::readBuffer(int16_t index)
{
  _index=index;
  return buffer[_index];
}

/**
 * \par Function
 *    writeBuffer
 * \par Description
 *    Write the data to the buffer.
 * \param[in]
 *    index,c
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void TKPS2::writeBuffer(int16_t index,uint8_t c)
{
  _index=index;
  buffer[_index]=c;
}

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
void TKPS2::readSerial(void)
{
  _isAvailable = false;
  if(TKSerial::available() > 0)
  {
    _isAvailable = true;
    _serialRead = TKSerial::read();
  }
}

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
boolean TKPS2::readjoystick(void)
{
  boolean result = false;
  if(millis() - _lasttime > 200)
  {
    _isReady = false;
    _isStart=false;
    _prevc = 0x00;
    buffer[2] = buffer[4] = buffer[6] =buffer[8] =0x80;
    buffer[1] = buffer[3] = buffer[5] =buffer[7] =0x00;
  }
  readSerial();
  while(_isAvailable)
  {
    _lasttime = millis();
    unsigned char c = _serialRead & 0xff;
    if((c == 0x55) && (_isStart == false))
    {
      if(_prevc == 0xff)
      {
        _index=1;
        _isStart = true;
      }
    }
    else
    {
      _prevc = c;
      if(_isStart)
      {
        writeBuffer(_index,c);
      }
    }
    _index++;
    if((_isStart == false) && (_index > 12))
    {
      _index=0; 
      _isStart=false;
      buffer[2] = buffer[4] = buffer[6] =buffer[8] =0x80;
      buffer[1] = buffer[3] = buffer[5] =buffer[7] =0x00;
    }
    else if(_isStart && (_index > 9))
    {
      uint8_t checksum;
      checksum = buffer[2]+buffer[3]+buffer[4]+buffer[5]+buffer[6]+buffer[7]+buffer[8];
      if(checksum == buffer[9])
      {
        _isReady = true;
       	_isStart = false;
       	_index = 0;
       	result = true;
      }
      else
      {
        _isStart = false;
        _index = 0;
        _prevc = 0x00;
        _isStart=false;
        result = false;
      }
    }
    readSerial();
   }
   return result;
}

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
 *    Analog value(-128~127). if none return 0.
 * \par Others
 *    None
 */
int16_t TKPS2::TKAnalog(uint8_t button)
{
  int16_t result;
  if (!_isReady)
  {
    return (TKJOYSTICK_ANALOG_ERROR);
  }
  else
  {
    if(button == TKJOYSTICK_RX || button == TKJOYSTICK_RY || button == TKJOYSTICK_LX || button == TKJOYSTICK_LY)
    {
      result = 2*(ps2_data_list[button]-128);
      if((button == TKJOYSTICK_RY) || (button == TKJOYSTICK_LY))
      {
        result = -result;
      }
      if((result == -256) || (result == -254))
      {
        result = -255;
      }
      else if((result == 254) || (result == 256))
      {
        result = 255;
      }
      return result;
    }
    else
    {
      return TKJOYSTICK_INIT_VALUE;
    }
  }
}

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
boolean TKPS2::ButtonPressed(uint8_t button) 
{
  if (!_isReady)
  {
    return ps2_data_list_bak[button];
  }
  else
  {
    ps2_data_list_bak[button] = ps2_data_list[button];
    return  ps2_data_list[button];
  }
}

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
void TKPS2::loop(void)
{
  if(readjoystick())
  {
    ps2_data_list[TKJOYSTICK_LX] = buffer[2];
    ps2_data_list[TKJOYSTICK_LY] = buffer[4];
    ps2_data_list[TKJOYSTICK_RX] = buffer[6];
    ps2_data_list[TKJOYSTICK_RY] = buffer[8];
    ps2_data_list[TKJOYSTICK_R1] = (buffer[3] & 0x01) == 0x01 ? true : false;
    ps2_data_list[TKJOYSTICK_R2] = (buffer[3] & 0x02) == 0x02 ? true : false;
    ps2_data_list[TKJOYSTICK_L1] = (buffer[3] & 0x04) == 0x04 ? true : false; 
    ps2_data_list[TKJOYSTICK_L2] = (buffer[3] & 0x08) == 0x08 ? true : false;
    ps2_data_list[TKJOYSTICK_MODE] = (buffer[3] & 0x10) ==0x10 ? true : false;
    ps2_data_list[TKJOYSTICK_TRIANGLE] = (buffer[5] & 0x01) == 0x01 ? true : false;
    ps2_data_list[TKJOYSTICK_XSHAPED] = (buffer[5] & 0x02) == 0x02 ? true : false;
    ps2_data_list[TKJOYSTICK_SQUARE] = (buffer[5] & 0x04) == 0x04 ? true : false;
    ps2_data_list[TKJOYSTICK_ROUND] = (buffer[5] & 0x08) == 0x08 ? true : false;
    ps2_data_list[TKJOYSTICK_START] = (buffer[5] & 0x10) == 0x10 ? true : false;
    ps2_data_list[TKJOYSTICK_UP] = (buffer[7] & 0x01) == 0x01 ? true : false;
    ps2_data_list[TKJOYSTICK_DOWN] = (buffer[7] & 0x02) == 0x02 ? true : false ;
    ps2_data_list[TKJOYSTICK_LEFT] = (buffer[7] & 0x04) == 0x04 ? true : false ;
    ps2_data_list[TKJOYSTICK_RIGHT] = (buffer[7] & 0x08) == 0x08 ? true : false ;
    ps2_data_list[TKJOYSTICK_SELECT] = (buffer[7] & 0x10) == 0x10 ? true : false ;
    ps2_data_list[TKJOYSTICK_BUTTON_L] = (buffer[3] & 0x20) == 0x20 ? true : false ;
    ps2_data_list[TKJOYSTICK_BUTTON_R] = (buffer[7] & 0x20) == 0x20 ? true : false ;
  }
}

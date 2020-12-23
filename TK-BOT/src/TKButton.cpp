/**
 *
 * \par Description
 * This file is a drive for 4 Button module, It supports TK Button V1.0 device provided 
 * by TiTKul.
 *
 * \par Method List:
 *
 *    1.  void    TKButton::setpin(uint8_t port);
 *    2.  uint8_t TKButton::pressed();
 * @example TKButtonTest.ino
 */

/* Includes ------------------------------------------------------------------*/
#include "TKButton.h"

/* Private functions ---------------------------------------------------------*/
#ifdef TK_PORT_DEFINED

/**
 *  Alternate Constructor which can call your own function to map the TKButton to arduino port, \n
 *  no pins are used or initialized here.
 * \param[in]
 *    None
 */
TKButton::TKButton(void) : TKPort()
{

}

/**
 *  Alternate Constructor which can call your own function to map the TKButton to arduino port, \n
 *  the slot2 pin will be used for key pin.
 * \param[in]
 *    port - RJ25 port from PORT_1 to M2
 */
TKButton::TKButton(uint8_t port) : TKPort(port)
{
  _KeyPin = s1;
  Pre_Button_Value = 950;
}
#else  // TK_PORT_DEFINED

/**
 * Alternate Constructor which can call your own function to map the _KeyPin to arduino port,
 * \param[in]
 *    port - arduino gpio number
 */
TKButton::TKButton(uint8_t port)
{
  _KeyPin = port;
  Pre_Button_Value = 950;
}
#endif // TK_PORT_DEFINED

/**
 * \par Function
 *    setpin
 * \par Description
 *    Set the PIN for button module.
 * \param[in]
 *    port - arduino gpio number
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
void TKButton::setpin(uint8_t port)
{
  _KeyPin = port;
#ifdef TK_PORT_DEFINED
  s1 = port;
#endif // TK_PORT_DEFINED
  Pre_Button_Value = 950;
}
bool TKButton::tkpressed(void)
{
  #ifdef TK_PORT_DEFINED
    return(digitalRead(s1));
  #endif
}
/**
 * \par Function
 *    pressed
 * \par Description
 *    Read key ADC value to a variable.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \return
 *    Return the key vlaue, the value maybe  KEY_1,KEY_2,KEY_3,KEY_4,KEY_NULL.
 * \par Others
 *    The key should periodically read, if it was delayed, It will affect the sensitivity of the keys
 */
uint8_t TKButton::pressed(void)
{
  uint8_t returnKey      = KEY_NULL;
  int16_t key_temp_value = KEY_NULL;
  int16_t button_key_val = Pre_Button_Value;
  uint32_t current_time  = 0;
  // current_time will be return to 0 after about 50 days
  // 2E32 / (float)(24*3600*1000) = 49.71026
  current_time = millis();
  if (current_time - previous_time > DEBOUNCED_INTERVAL)
  {
    // This statement will handle rollover itself, see more in arduino site.
    // http://playground.arduino.cc/Code/TimingRollover
    // If you want key resbonse faster, you can set DEBOUNCED_INTERVAL to a
    // smaller number in TKButton.h.
    previous_time = current_time;
#ifdef TK_PORT_DEFINED
    key_temp_value = TKButton::aRead2();
#else  // TK_PORT_DEFINED
    key_temp_value = analogRead(_KeyPin);
#endif // TK_PORT_DEFINED
    if (key_debounced_count == 0)
    {
      key_debounced_value = key_temp_value;
    }
    if (abs(key_temp_value - key_debounced_value) < 20)
    {
      key_match_count++;
    }
    key_debounced_count++;
  }

  if (key_debounced_count == 5)
  {
    key_debounced_count = 0;
    if (key_match_count > 2)
    {
      button_key_val = key_debounced_value;
      Pre_Button_Value = button_key_val;
    }
    else
    {
      button_key_val = Pre_Button_Value;
    }
    key_match_count = 0;
  }

  button_key_val = button_key_val / 100;
  // Division is slow in 8bit MCU, division should be replaced with right shift.
  switch (button_key_val)
  {
    case 0:
      returnKey = KEY_1;
      break;

    case 4:
    case 5:
      returnKey = KEY_2;
      break;

    case 6:
      returnKey = KEY_3;
      break;

    case 7:
      returnKey = KEY_4;
      break;

    case 9:
    case 10:
      returnKey = KEY_NULL;
      break;
  }
  return(returnKey);
}


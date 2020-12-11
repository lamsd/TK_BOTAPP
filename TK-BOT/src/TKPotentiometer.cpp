

/* Includes ------------------------------------------------------------------*/
#include "TKPotentiometer.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the TK potentiometer device to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
TKPotentiometer::TKPotentiometer(void) : TKPort(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the TK potentiometer device to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
TKPotentiometer::TKPotentiometer(uint8_t port) : TKPort(port)
{

}
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the TK potentiometer device to arduino port
 * \param[in]
 *   potentiometerPin - arduino port for potentiometer output port
 */
TKPotentiometer::TKPotentiometer(uint8_t potentiometerPin)
{
  _potentiometerPin = potentiometerPin;
  pinMode(_potentiometerPin, INPUT);
}
#endif // TK_PORT_DEFINED 
/**
 * \par Function
 *    setpin
 * \par Description
 *    Reset the potentiometer device available PIN by its arduino port.
 * \param[in]
 *   potentiometerPin - arduino port for potentiometer output port
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void TKPotentiometer::setpin(uint8_t potentiometerPin)
{
  _potentiometerPin = potentiometerPin;
  pinMode(_potentiometerPin, INPUT);
#ifdef TK_PORT_DEFINED
  s2 = potentiometerPin;
#endif // TK_PORT_DEFINED
}

/**
 * \par Function
 *    read()
 * \par Description
 *    Read DAC value of TK potentiometer module.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    The value of potentiometer device(0-1024)
 * \par Others
 *    None
 */
uint16_t TKPotentiometer::read(void)
{
#ifdef TK_PORT_DEFINED
  return(TKPort::aRead2() );
#else // TK_PORT_DEFINED
  return analogRead(_potentiometerPin);
#endif // TK_PORT_DEFINED
}


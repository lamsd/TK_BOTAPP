
#include "TKDCMotor.h"

#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the DC motor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
TKDCMotor::TKDCMotor(void) : TKPort(0)
{
  //The PWM frequency is 976 Hz
#if defined(__AVR_ATmega32U4__) //TKBaseBoard use ATmega32U4 as MCU
  TCCR1A =  _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);

  TCCR3A = _BV(WGM30);
  TCCR3B = _BV(CS31) | _BV(CS30) | _BV(WGM32);

  TCCR4B = _BV(CS42) | _BV(CS41) | _BV(CS40);
  TCCR4D = 0;

#elif defined(__AVR_ATmega328__) // else ATmega328

  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);

  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);

#elif defined(__AVR_ATmega2560__) //else ATmega2560
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);

  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);
#endif
}

/**
 * Alternate Constructor which can call your own function to map the DC motor to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
TKDCMotor::TKDCMotor(uint8_t port) : TKPort(port)
{
  //The PWM frequency is 976 Hz
#if defined(__AVR_ATmega32U4__) //TKBaseBoard use ATmega32U4 as MCU
  TCCR1A =  _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);

  TCCR3A = _BV(WGM30);
  TCCR3B = _BV(CS31) | _BV(CS30) | _BV(WGM32);

  TCCR4B = _BV(CS42) | _BV(CS41) | _BV(CS40);
  TCCR4D = 0;

#elif defined(__AVR_ATmega328__) // else ATmega328

  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);

  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);

#elif defined(__AVR_ATmega2560__) //else ATmega2560
  /*if((mePort[port].s1 == 13) || (mePort[port].s1 == 4))//timer0 default 970hz
  {
    TCCR0A = _BV(WGM01) | _BV(WGM00);//8KHZ
    TCCR0B = _BV(CS01) | _BV(CS01);//
  }
  else */if((mePort[port].s1 == 12) || (mePort[port].s1 == 11))
  {
    TCCR1A = _BV(WGM10);
    TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);//970hz
  }
  else if((mePort[port].s1 == 10) || (mePort[port].s1 == 9))
  {
    TCCR2A = _BV(WGM21) | _BV(WGM20);//970hz
    TCCR2B = _BV(CS22);
  }
  else if((mePort[port].s1 == 5) || (mePort[port].s1 == 3) || (mePort[port].s1 == 2))
  {
    TCCR3A = _BV(WGM30);
    TCCR3B = _BV(CS31) | _BV(CS30) | _BV(WGM32);//970hz
  }
  else if((mePort[port].s1 == 8) || (mePort[port].s1 == 7) || (mePort[port].s1 == 6))
  {
    TCCR4A = _BV(WGM40);
    TCCR4B = _BV(CS41) | _BV(CS40) | _BV(WGM42);//970hz
  }
  else if((mePort[port].s1 == 45) || (mePort[port].s1 == 46) ||  (mePort[port].s1 == 44))
  {
    TCCR5A = _BV(WGM50);
    TCCR5B = _BV(CS51) | _BV(CS50) | _BV(WGM52);//970hz
  }
#endif
}
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the DC motor to arduino port,
 * it will assigned the output pin.
 * \param[in]
 *   dir_pin - arduino port for direction pin(should analog pin)
 * \param[in]
 *   pwm_pin - arduino port for pwm input(should analog pin)
 */
TKDCMotor::TKDCMotor(uint8_t dir_pin,uint8_t pwm_pin)
{
  dc_dir_pin = dir_pin;
  dc_pwm_pin = pwm_pin;
  
  pinMode(dc_dir_pin, OUTPUT);
}
#endif /* TK_PORT_DEFINED */

/**
 * \par Function
 *   setpin
 * \par Description
 *   Reset the DC motor available PIN by its arduino port.
 * \param[in]
 *   dir_pin - arduino port for direction pin(should analog pin)
 * \param[in]
 *   pwm_pin - arduino port for pwm input(should analog pin)
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void TKDCMotor::setpin(uint8_t dir_pin,uint8_t pwm_pin)
{
  dc_dir_pin = dir_pin;
  dc_pwm_pin = pwm_pin;
  pinMode(dc_dir_pin, OUTPUT);
#ifdef TK_PORT_DEFINED
  s1 = pwm_pin;
  s2 = dir_pin;
#endif // TK_PORT_DEFINED
}

/**
 * \par Function
 *   reset
 * \par Description
 *   Reset the DC motor available PIN by its RJ25 port.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void TKDCMotor::reset(uint8_t port)
{
  TKPort::reset(port);
  last_speed = 500;
}

/**
 * \par Function
 *   reset
 * \par Description
 *   Reset the DC motor available PIN by its RJ25 port and slot.
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
void TKDCMotor::reset(uint8_t port, uint8_t slot)
{
  TKPort::reset(port, slot);
  last_speed = 500;
}

/**
 * \par Function
 *   run
 * \par Description
 *   Control the motor forward or reverse
 * \param[in]
 *   speed - Speed value from -255 to 255
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void TKDCMotor::run(int16_t speed)
{
  speed	= speed > 255 ? 255 : speed;
  speed	= speed < -255 ? -255 : speed;

  if(last_speed != speed)
  {
    last_speed = speed;
  }
  else
  {
    return;
  }

  if(speed >= 0)
  {
#ifdef TK_PORT_DEFINED
    TKPort::dWrite2(HIGH);
    delayMicroseconds(5);
    TKPort::aWrite1(speed);
#else /* TK_PORT_DEFINED */
    digitalWrite(dc_dir_pin,HIGH);
    analogWrite(dc_pwm_pin,speed);
#endif/* TK_PORT_DEFINED */
  }
  else
  {
#ifdef TK_PORT_DEFINED
    TKPort::dWrite2(LOW);
    delayMicroseconds(5);
    TKPort::aWrite1(-speed);
#else /* TK_PORT_DEFINED */
    digitalWrite(dc_dir_pin,LOW);
    analogWrite(dc_pwm_pin,-speed);
#endif/* TK_PORT_DEFINED */
  }
}

/**
 * \par Function
 *   stop
 * \par Description
 *   Stop the rotation of the motor
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void TKDCMotor::stop(void)
{
  TKDCMotor::run(0);
}


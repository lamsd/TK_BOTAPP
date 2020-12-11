
#include "TKUltrasonicSensorB.h"

#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the ultrasonic sensor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
TKUltrasonicSensorB::TKUltrasonicSensorB(void) : TKPort(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the ultrasonic Sensor to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
TKUltrasonicSensorB::TKUltrasonicSensorB(uint8_t port) : TKPort(port)
{

}
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the ultrasonic Sensor to arduino port,
 * it will assigned the signal pin.
 * \param[in]
 *   port - arduino port(should analog pin)
 */
TKUltrasonicSensorB::TKUltrasonicSensorB(uint8_t port)
{
  _SignalPin = port;
  _lastEnterTime = millis();
  _measureFlag = true;
  _measureValue = 0;
}
#endif // TK_PORT_DEFINED

/**
 * \par Function
 *   setpin
 * \par Description
 *   Reset the ultrasonic Sensor available PIN by its arduino port.
 * \param[in]
 *   SignalPin - arduino port for sensor read(should analog pin)
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void TKUltrasonicSensorB::setpin(uint8_t trig_sig, uint8_t echo_sig)
{
  _SignalPin1 = echo_sig;
  _ExsignalPin = trig_sig;
  _lastEnterTime = millis();
  _measureFlag = true;
  _measureValue = 0;
#ifdef TK_PORT_DEFINED
  s1 = _ExsignalPin;
  s2 = _SignalPin1;
#endif // TK_PORT_DEFINED
}

/**
 * \par Function
 *   distanceCm
 * \par Description
 *   Centimeters return the distance
 * \param[in]
 *   MAXcm - The Max centimeters can be measured, the default value is 400.
 * \par Output
 *   None
 * \return
 *   The distance measurement in centimeters
 * \par Others
 *   None
 */
double TKUltrasonicSensorB::distanceCm(uint16_t MAXcm)
{
  float distance = measure();

  if((((float)distance *0.0343 / 2) >= 400.0) || (distance <= 2))
  {
    return( (float)400.0);//MAXcm
  }
  else
  {
    return( (float)distance *0.0343 / 2);
  }
}

/**
 * \par Function
 *   distanceInch
 * \par Description
 *   Inch return the distance
 * \param[in]
 *   MAXinch - The Max inch can be measured, the default value is 180.
 * \par Output
 *   None
 * \return
 *   The distance measurement in inch
 * \par Others
 *   None
 */
double TKUltrasonicSensorB::distanceInch(uint16_t MAXinch)
{
  float distance = measure();

  if((((float)distance / 148.0) >= 400.0) || (distance == 0))
  {
    return( (float)180.0);//MAXinch
  }
  else
  {
    return( (float)distance / 148.0);
  }
}

/**
 * \par Function
 *   measure
 * \par Description
 *   To get the duration of the ultrasonic sensor
 * \param[in]
 *   timeout - This value is used to define the measurement range, The
 *   default value is 30000.
 * \par Output
 *   None
 * \return
 *   The duration value associated with distance
 * \par Others
 *   None
 */
long TKUltrasonicSensorB::measure(unsigned long timeout)
{
  float duration;
  if(millis() - _lastEnterTime > 23)
  {
    _measureFlag = true;
    pinMode(s2,OUTPUT); 
  }

  if(_measureFlag == true)
  {
    digitalWrite(s2,LOW);
    delayMicroseconds(2);
    digitalWrite(s2,HIGH);
    delayMicroseconds(10);
    digitalWrite(s2,LOW);
    pinMode(s1, INPUT);
    duration = pulseIn(s1, HIGH);
    _measureValue = duration;
    _lastEnterTime = millis();
    _measureFlag = false;
  }
  else
  {
    duration = _measureValue;
  }
  return(duration);
}


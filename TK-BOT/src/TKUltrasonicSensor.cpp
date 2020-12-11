
#include "TKUltrasonicSensor.h"

#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the ultrasonic sensor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
TKUltrasonicSensor::TKUltrasonicSensor(void) : TKPort(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the ultrasonic Sensor to arduino port
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
TKUltrasonicSensor::TKUltrasonicSensor(uint8_t port) : TKPort(port)
{

}
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the ultrasonic Sensor to arduino port,
 * it will assigned the signal pin.
 * \param[in]
 *   port - arduino port(should analog pin)
 */
TKUltrasonicSensor::TKUltrasonicSensor(uint8_t port)
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
void TKUltrasonicSensor::setpin(uint8_t SignalPin)
{
  _SignalPin = SignalPin;
  _lastEnterTime = millis();
  _measureFlag = true;
  _measureValue = 0;
#ifdef TK_PORT_DEFINED
  s2 = _SignalPin;
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
double TKUltrasonicSensor::distanceCm(uint16_t MAXcm)
{
  long distance = measure();

  if((((double)distance / 58.0) >= 400.0) || (distance == 0))
  {
    return( (double)400.0);//MAXcm
  }
  else
  {
    return( (double)distance / 58.0);
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
double TKUltrasonicSensor::distanceInch(uint16_t MAXinch)
{
  long distance = measure();

  if((((double)distance / 148.0) >= 400.0) || (distance == 0))
  {
    return( (double)180.0);//MAXinch
  }
  else
  {
    return( (double)distance / 148.0);
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
long TKUltrasonicSensor::measure(unsigned long timeout)
{
  long duration;
  if(millis() - _lastEnterTime > 23)
  {
    _measureFlag = true; 
  }

  if(_measureFlag == true)
  {
    _lastEnterTime = millis();
    _measureFlag = false;
    TKPort::dWrite2(LOW);
    delayMicroseconds(2);
    TKPort::dWrite2(HIGH);
    delayMicroseconds(10);
    TKPort::dWrite2(LOW);
    pinMode(s2, INPUT);
    duration = pulseIn(s2, HIGH);
    _measureValue = duration;
  }
  else
  {
    duration = _measureValue;
  }
  return(duration);
}


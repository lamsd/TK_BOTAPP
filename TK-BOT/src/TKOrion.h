
#ifndef TKOrion_H
#define TKOrion_H

#include <Arduino.h>
#include "TKConfig.h"

// Supported Modules drive needs to be added here
#include "TKButton.h"
#include "TKUltrasonicSensor.h"
#include "TKUltrasonicSensorB.h"
#include "TKDCMotor.h"
#include "TKPotentiometer.h"
#include "TKJoystick.h"
#include "TKLineFollower.h"
#include "TKSoundSensor.h"
#include "TKSerial.h"
#include "TKBluetooth.h"
#include "TKTemperature.h"
#include "TKTemperatureTh.h"
#include "TKTouchSensor.h"
#include "TKAvoidSensor.h"
#include "TKBuzzer.h"
#include "TKGasSensor.h"
#include "TKColorSensor.h"

/*********************  Orion Board GPIO Map *********************************/
// struct defined in TKPort.h
TKPort_Sig mePort[17] =
{
  { NC, NC }, { A6, A7 }, { A0, A1 }, { A2, A3 }, { NC, NC },
  { 12, 13 }, { 10, 11 }, { 8, 9 }, { 2, 7 }, { 6, 3 },
  { 5, 4 }, { NC, NC }, { NC, NC }, { NC, NC }, { NC, NC },
  { NC, NC },{ NC, NC },
};
#endif // TKOrion_H

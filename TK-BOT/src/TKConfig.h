
#ifndef TKConfig_H
#define TKConfig_H

#include <utility/Servo.h>
#include <utility/Wire.h>
#include <utility/EEPROM.h>
#include <utility/SoftwareSerial.h>
#include <utility/SPI.h>

#define TK_PORT_DEFINED

#if defined(__AVR__)
#define TKPIN_TO_BASEREG(pin)               ( portInputRegister (digitalPinToPort (pin) ) )
#define TKPIN_TO_BITMASK(pin)               ( digitalPinToBitMask (pin) )
#define TKIO_REG_TYPE                       uint8_t
#define TKIO_REG_ASM                        asm ("r30")
#define TKDIRECT_READ(base, mask)           ( ( (*(base) ) & (mask) ) ? 1 : 0)
#define TKDIRECT_MODE_INPUT(base, mask)     ( (*( (base) + 1) ) &= ~(mask) ), ( (*( (base) + 2) ) |= (mask) ) // INPUT_PULLUP
#define TKDIRECT_MODE_OUTPUT(base, mask)    ( (*( (base) + 1) ) |= (mask) )
#define TKDIRECT_WRITE_LOW(base, mask)      ( (*( (base) + 2) ) &= ~(mask) )
#define TKDIRECT_WRITE_HIGH(base, mask)     ( (*( (base) + 2) ) |= (mask) )
#endif // __AVR__

#endif // TKConfig_H


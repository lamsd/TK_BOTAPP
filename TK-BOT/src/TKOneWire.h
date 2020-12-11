
#ifndef TKOneWire_H
#define TKOneWire_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "TKConfig.h"

/**
 * Class: TKOneWire
 * \par Description
 * Declaration of Class TKOneWire.
 */
class TKOneWire
{
private:
  TKIO_REG_TYPE   bitmask;
  volatile TKIO_REG_TYPE *baseReg;
  /* global search state */
  uint8_t ROM_NO[8];
  uint8_t LastDiscrepancy;
  uint8_t LastFamilyDiscrepancy;
  uint8_t LastDeviceFlag;

public:
/**
 * Alternate Constructor which can call your own function to map the TKOneWire to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
  TKOneWire(void);

/**
 * Alternate Constructor which can call your own function to map the TKOneWire to arduino port,
 * it will assigned the shot PIN and focus pin.
 * \param[in]
 *   pin - arduino port for 1-wire(should digital pin)
 */
  TKOneWire(uint8_t pin);

/**
 * \par Function
 *   readIO
 * \par Description
 *   Read a bit from 1-wire data port
 * \par Output
 *   None 
 * \return
 *   return the bit value we read
 * \par Others
 *   None
 */
  bool readIO(void);

/**
 * \par Function
 *   reset
 * \par Description
 *   Reset the available PIN for 1-wire
 * \param[in]
 *   pin - arduino port(should digital pin)
 * \par Output
 *   None 
 * \return
 *   None
 * \par Others
 *   None
 */
  void reset(uint8_t pin);

/**
 * \par Function
 *   reset
 * \par Description
 *   Perform the TKOneWire reset function.  We will wait up to 250uS for
 *   the bus to come high, if it doesn't then it is broken or shorted.
 * \param[in]
 *   v - The bit value need be written
 * \par Output
 *   None 
 * \return
 *   Returns 1 if a device asserted a presence pulse, 0 otherwise.
 * \par Others
 *   None
 */
  uint8_t reset(void);

/**
 * \par Function
 *   select
 * \par Description
 *   Issue a 1-Wire rom select command.
 * \param[in]
 *   rom[8] - 64bit ROM code.
 * \par Output
 *   None 
 * \return
 *   None
 * \par Others
 *   None
 */
  void select(const uint8_t rom[8]);

/**
 * \par Function
 *   skip
 * \par Description
 *   Issue a 1-Wire rom skip command.
 * \par Output
 *   None 
 * \return
 *   None
 * \par Others
 *   None
 */
  void skip(void);

/**
 * \par Function
 *   write
 * \par Description
 *   Write a byte of data
 * \param[in]
 *   v - The value need be written
 * \param[in]
 *   power - Should we need active drivers to raise the pin high
 * \par Output
 *   None 
 * \return
 *   None
 * \par Others
 *   None
 */
  void write(uint8_t v, uint8_t power = 0);

/**
 * \par Function
 *   write_bytes
 * \par Description
 *   Write certain number of data
 * \param[in]
 *   buf - The buffer used to store the data that need be written
 * \param[in]
 *   count - The count of the bytes we need to write
 * \param[in]
 *   power - Should we need active drivers to raise the pin high
 * \par Output
 *   None 
 * \return
 *   None
 * \par Others
 *   None
 */
  void write_bytes(const uint8_t *buf, uint16_t count, bool power = 0);

/**
 * \par Function
 *   read
 * \par Description
 *   Read a byte of data
 * \par Output
 *   None 
 * \return
 *   The read data(8-bit data)
 * \par Others
 *   None
 */
  uint8_t read(void);

/**
 * \par Function
 *   read_bytes
 * \par Description
 *   Read certain number of data
 * \param[out]
 *   buf - The buffer used to store the read data
 * \param[in]
 *   count - The count of the bytes we need to read
 * \par Output
 *   None 
 * \return
 *   None
 * \par Others
 *   None
 */
  void read_bytes(uint8_t *buf, uint16_t count);

/**
 * \par Function
 *   write_bit
 * \par Description
 *   Write a bit. The bus is always left powered at the end, see
 *   note in write() about that.
 * \param[in]
 *   v - The bit value need be written
 * \par Output
 *   None 
 * \return
 *   None
 * \par Others
 *   None
 */
  void write_bit(uint8_t v);

/**
 * \par Function
 *   read_bit
 * \par Description
 *   Read a bit. Port and bit is used to cut lookup time and provide
 *   more certain timing
 * \par Output
 *   None 
 * \return
 *   return the bit value we read
 * \par Others
 *   None
 */
  uint8_t read_bit(void);

/**
 * \par Function
 *   depower
 * \par Description
 *   Stop forcing power onto the bus. You only need to do this if
 *   you used the 'power' flag to write() or used a write_bit() call
 *   and aren't about to do another read or write. You would rather
 *   not leave this powered if you don't have to, just in case
 *   someone shorts your bus.
 * \par Output
 *   None 
 * \return
 *   None
 * \par Others
 *   None
 */
  void depower(void);

/**
 * \par Function
 *   reset_search
 * \par Description
 *   If we need search a new device, we need call this function to clear 
 *   the search state and all stored values  
 * \par Output
 *   Reset all stored values 
 * \return
 *   None
 * \par Others
 *   None
 */
  void reset_search(void);

/**
 * \par Function
 *   target_search
 * \par Description
 *   Setup the search to find the device type 'family_code' on the next call
 *   of search(*newAddr) if it is present.
 * \param[in]
 *   family_code - the device type we need search
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  void target_search(uint8_t family_code);

/**
 * \par Function
 *   search
 * \par Description
 *   Perform a search. If this function returns a '1' then it has
 *   enumerated the next device and you may retrieve the ROM from the
 *   TKOneWire::address variable. If there are no devices, no further
 *   devices, or something horrible happens in the middle of the
 *   enumeration then a '0' is returned. If a new device is found then
 *   its address is copied to newAddr.  Use TKOneWire::reset_search() to
 *   start over. you can get the algorithm from
 *   doc\TK_Temperature\Datasheet\1-Wire_Search_Algorithm.pdf
 * \param[out]
 *   newAddr - The adrress to store the ROM data 
 * \par Output
 *   None
 * \return
 *   true - device found, ROM number in ROM_NO buffer\r\n
 *   false - device not found, end of search
 * \par Others
 *   None
 */
  uint8_t search(uint8_t *newAddr);
};

#endif


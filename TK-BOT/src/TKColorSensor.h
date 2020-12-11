
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TKColorSensor_H_
#define _TKColorSensor_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "TKConfig.h"

 #ifdef TK_PORT_DEFINED
#include "TKPort.h"
 #endif // TK_PORT_DEFINED

/* Exported macro ------------------------------------------------------------*/
#define I2C_ERROR                       (-1)
#define COLORSENSOR_DEFAULT_ADDRESS     (0x38)//0011 1000

/* Register List define------------------------------------------------------------*/
#define SYSTEM_CONTROL         (0X40)
#define MODE_CONTROL1          (0X41)
#define MODE_CONTROL2          (0X42)
#define MODE_CONTROL3          (0X44)
#define RED_DATA_LSBs          (0X50)
#define RED_DATA_MSBs          (0X51)
#define GREEN_DATA_LSBs        (0X52)
#define GREEN_DATA_MSBs        (0X53)
#define BLUE_DATA_LSBs         (0X54)
#define BLUE_DATA_MSBs         (0X55)
#define CLEAR_DATA_LSBs        (0X56)
#define CLEAR_DATA_MSBs        (0X57)
#define DINT_DATA_LSBs         (0X58)
#define DINT_DATA_MSBs         (0X59)
#define INTERRUPT              (0X60)
#define PERSISTENCE            (0X61)
#define TH_LSBs                (0X62)
#define TH_MSBs                (0X63)
#define TL_LSBs                (0X64)
#define TL_MSBs                (0X65)
#define MANUFACTURER_ID        (0X92)
#define CHIP_ID                (0XE0)

#define SW_RESET               (1 << 7)
#define INT_RESET              (1 << 6)

/* REG_MODECONTROL1(0x41) */
#define TKASURE_160MS          (0x00)
#define TKASURE_320MS          (0x01)
#define TKASURE_640MS          (0x02)
#define TKASURE_1280MS         (0x03)
#define TKASURE_2560MS         (0x04)
#define TKASUREMENT_MAX        (0x05)

/* Color result list*/
typedef enum
{
  WHITE = 0,
  PINKE = 1,
  RED   = 2,
  ORANGE= 3,
  YELLOW= 4,
  GREEN = 5,
  CYAN  = 6,
  BLUE  = 7,
  PURPLE= 8,
  BLACK = 9,
  GOLD  = 10,
}COLORTYPES;

/*
 * Class: TKColorSensor
 * \par Description
 * Declaration of Class TKColorSensor
 */

#ifndef TK_PORT_DEFINED
class TKColorSensor
#else // !TK_PORT_DEFINED
class TKColorSensor : public TKPort
#endif // !TK_PORT_DEFINED
{
public:
#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the TKColorSensor to arduino port,
 * no pins are used or initialized here
 */
  TKColorSensor(void);

/**
 * Alternate Constructor which can call your own function to map the TKColorSensor to arduino port.
 * \param[in]
 *   port - RJ25 port number
 */
  TKColorSensor(uint8_t port);

/**
 * Alternate Constructor which can call your own function to map the TKColorSensor to arduino port
 * and change the i2c device address
 * \param[in]
 *   port - RJ25 port number
 * \param[in]
 *   address - the i2c address you want to set
 */
  TKColorSensor(uint8_t port, uint8_t address);
#else // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the _AD0 and _INT to arduino port,
 * \param[in]
 *   _AD0 - arduino gpio number
 * \param[in]
 *   _INT - arduino gpio number
 */
  TKColorSensor(uint8_t _AD0, uint8_t _INT);

/**
 * Alternate Constructor which can call your own function to map the _AD0 and _INT to arduino port
 * and change the i2c device address.
 * \param[in]
 *   _AD0 - arduino gpio number
 * \param[in]
 *   _INT - arduino gpio number
 * \param[in]
 *   address - the i2c address you want to set
 */
  TKColorSensor(uint8_t _AD0, uint8_t _INT, uint8_t address);
#endif  /* TK_PORT_DEFINED */

/**
 * \par Function
 *   SensorInit
 * \par Description
 *   Initialize the TKColorSensor.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   You can check the bh1745 datasheet for the registor address.
 */
  void SensorInit(void);
 
/**
 * \par Function
 *   ReportId
 * \par Description
 *   Report the TKColorSensor Module ID.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   default ID 0xE0
 * \par Others
 *   None
 */
  uint8_t ReportId(void);

/**
 * \par Function
 *   ColorDataRead
 * \par Description
 *   read the TKColorSensor module color data.
 * \param[in]
 *   None
 * \par Output
 *   color RGB value
 * \return
 *   None
 * \par Others
 *   None
 */
  void ColorDataRead(void);

/**
 * \par Function
 *   ColorDataReadOnebyOne
 * \par Description
 *   one by on to read the TKColorSensor module color data.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  uint8_t ColorDataReadOnebyOne(void);

/**
 * \par Function
 *   ReturnColorCode
 * \par Description
 *   Return the TKColorSensor Color Code.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
 long ReturnColorCode(void);
 
/**
 * \par Function
 *   ColorIdentify
 * \par Description
 *   Identify Color for the Module.when you want to use two modules, you can use this methods to get data.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
 uint8_t ColorIdentify(void);

/**
 * \par Function
 *   Returnresult
 * \par Description
 *  Identify Color for the Module.when you use just one module, you can use this methods to get data.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
 uint8_t Returnresult(void);

/**
 * \par Function
 *   ReturnGrayscale
 * \par Description
 *  Return Color Grayscale.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 * Gray = R*0.299 + G*0.587 + B*0.114
 * Gray = (r*38 + g*75 + b*15)>>7;  
 */
 uint8_t ReturnGrayscale(void);

/**
 * \par Function
 *   ReturnColorhue
 * \par Description
 *   Return Color hue.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
 uint16_t ReturnColorhue(void);

/**
 * \par Function
 *   ReturnRedData
 * \par Description
 *   Return Color Red value.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
uint16_t ReturnRedData(void);

/**
 * \par Function
 *   ReturnGreenData
 * \par Description
 *   Return Color Green value.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  uint16_t ReturnGreenData(void);

/**
 * \par Function
 *   ReturnBlueData
 * \par Description
 *   Return Color Blue value.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  uint16_t ReturnBlueData(void);

/**
 * \par Function
 *   ReturnColorData
 * \par Description
 *   Return Color data value.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  uint16_t ReturnColorData(void);

/**
 * \par Function
 *  TurnOnLight
 * \par Description
 *  Turn On the TKColorSensor module Light.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  void TurnOnLight(void);
 
/**
 * \par Function
 *  TurnOffLight
 * \par Description
 *  Turn Off the TKColorSensor module Light.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  void TurnOffLight(void);

/**
 * \par Function
 *  TurnOffmodule
 * \par Description
 *  Turn Off the TKColorSensor module.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  void TurnOffmodule(void);
 
/**
 * \par Function
 *  TurnOnmodule
 * \par Description
 *  Turn On the TKColorSensor module.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  void TurnOnmodule(void);

/**
 * \par Function
 *  writeReg
 * \par Description
 *  write the TKColorSensor module register.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   Return the error code.
 *   the definition of the value of variable return_value:
 *   0:success
 *   1:BUFFER_LENGTH is shorter than size
 *   2:address send, nack received
 *   3:data send, nack received
 *   4:other twi error
 *   refer to the arduino official library twi.c
 * \par Others
 *   To set the register for initializing.
 */
  int8_t writeReg(int16_t reg, uint8_t data);

/**
 * \par Function
 *   readData
 * \par Description
 *   Write the data to i2c device.
 * \param[in]
 *   start - the address which will write the data to.
 * \param[in]
 *   pData - the head address of data array.
 * \param[in]
 *   size - set the number of data will be written to the devide.
 * \par Output
 *   None
 * \return
 *   Return the error code.
 *   the definition of the value of variable return_value:
 *   0:success
 *   1:BUFFER_LENGTH is shorter than size
 *   2:address send, nack received
 *   3:data send, nack received
 *   4:other twi error
 *   refer to the arduino official library twi.c
 * \par Others
 *   Calling the official i2c library to read data.
 */
  int8_t readData(uint8_t start, uint8_t *buffer, uint8_t size);

/**
 * \par Function
 *   writeData
 * \par Description
 *   Write the data to i2c device.
 * \param[in]
 *   start - the address which will write the data to.
 * \param[in]
 *   pData - the head address of data array.
 * \param[in]
 *   size - set the number of data will be written to the devide.
 * \par Output
 *   None
 * \return
 *   Return the error code.
 *   the definition of the value of variable return_value:
 *   0:success
 *   1:BUFFER_LENGTH is shorter than size
 *   2:address send, nack received
 *   3:data send, nack received
 *   4:other twi error
 *   refer to the arduino official library twi.c
 * \par Others
 *   Calling the official i2c library to write data.
 */
  int8_t writeData(uint8_t start, const uint8_t *pData, uint8_t size);

/**
 * \par Function
 *   MAX
 * \par Description
 *   find the max one from r g b.
 * \param[in]
 *  r g b  
 * \par Output
 *   None
 * \return
 *   Return the max one.
 * \par Others
 */
  uint8_t MAX(uint8_t r,uint8_t g,uint8_t b);

/**
 * \par Function
 *   MIN
 * \par Description
 *   find the min one from r g b.
 * \param[in]
 *  r g b  
 * \par Output
 *   None
 * \return
 *   Return the min one.
 * \par Others
 */
  uint8_t MIN(uint8_t r,uint8_t g,uint8_t b);

/***********************************/
  uint8_t Device_Address;

private:
  volatile uint8_t  _S1;
  volatile uint8_t  _S2;
  volatile uint8_t  _AD0;
  volatile uint8_t  _INT;
  uint16_t Redvalue;
  uint16_t Greenvalue;
  uint16_t Bluevalue;
  uint16_t Colorvalue;
};
#endif




/* Includes ------------------------------------------------------------------*/
#include "TKColorSensor.h"

/* Private functions ---------------------------------------------------------*/
#ifdef TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the TKColorSensor to arduino port,
 * no pins are used or initialized here
 */
TKColorSensor::TKColorSensor(void) : TKPort(0)
{
  Device_Address = COLORSENSOR_DEFAULT_ADDRESS;
}

/**
 * Alternate Constructor which can call your own function to map the TKColorSensor to arduino port,
 * \param[in]
 *   port - RJ25 port number
 */
TKColorSensor::TKColorSensor(uint8_t port) : TKPort(port)
{
  Device_Address = COLORSENSOR_DEFAULT_ADDRESS;
}

/**
 * Alternate Constructor which can call your own function to map the TKColorSensor to arduino port
 * and change the i2c device address
 * \param[in]
 *   port - RJ25 port number
 * \param[in]
 *   address - the i2c address you want to set
 */
TKColorSensor::TKColorSensor(uint8_t port, uint8_t address) : TKPort(port)
{
  Device_Address = address;
}
#else  // TK_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the _AD0 and _INT to arduino port,
 * \param[in]
 *   _AD0 - arduino gpio number
 * \param[in]
 *   _INT - arduino gpio number
 */
TKColorSensor::TKColorSensor(uint8_t _AD0, uint8_t _INT)
{
  Device_Address = COLORSENSOR_DEFAULT_ADDRESS;
  _AD0 = _AD0;
  _INT = _INT;
}

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
TKColorSensor::TKColorSensor(uint8_t AD0, uint8_t INT, uint8_t address)
{
  Device_Address = address;
  _AD0 = AD0;
  _INT = INT;
}
#endif /* TK_PORT_DEFINED */
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
void TKColorSensor::SensorInit(void)
{
  TKColorSensor::TurnOnmodule();   //power on
  TKColorSensor::TurnOnLight();    //light on
  Wire.begin();
  writeReg(SYSTEM_CONTROL, SW_RESET | INT_RESET);  //SW reset and INT reset
  writeReg(MODE_CONTROL1, TKASURE_160MS);          //selet 160ms measure frequency
  writeReg(MODE_CONTROL2, 0x10);                   //active and set rgb measure gain
  writeReg(MODE_CONTROL3, 0x02);
  writeReg(INTERRUPT, 0x00);
  writeReg(PERSISTENCE, 0x01);
}

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
 *   return default ID 0xE0
 * \par Others
 *   None
 */
uint8_t TKColorSensor::ReportId(void)
{
  uint8_t temp = 0;
  readData(MANUFACTURER_ID,&temp,1);
  return temp;
}

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
void TKColorSensor::ColorDataRead(void)
{
  uint8_t ColorData[8] = {0};
  readData(RED_DATA_LSBs, ColorData, sizeof(ColorData));
  Redvalue   = (uint16_t)ColorData[1] << 8 | ColorData[0];
  Greenvalue = (uint16_t)ColorData[3] << 8 | ColorData[2];
  Bluevalue  = (uint16_t)ColorData[5] << 8 | ColorData[4];
  Colorvalue = (uint16_t)ColorData[7] << 8 | ColorData[6];
}

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
 *   return 0 is detected ID,else return Black
 * \par Others
 *   None
 */
uint8_t TKColorSensor::ColorDataReadOnebyOne(void)
{
  uint8_t id = 0;
  TKColorSensor::SensorInit();
  id = TKColorSensor::ReportId();
  if(id != CHIP_ID)
  {
      return BLACK;
  }
  delay(160);//delay 160ms tramsfer time
  TKColorSensor::ColorDataRead();
  TKColorSensor::TurnOffmodule();//power off
  return 0;
}

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
 *   return color RGB code
 * \par Others
 *   None
 */
long TKColorSensor::ReturnColorCode(void)
{
  long colorcode = 0;
  uint16_t r,g,b;
  r = Redvalue / 20;
  g = Greenvalue / 30;
  b = Bluevalue / 20;
  if(r>255) 
  {
    r=255;
  }
  if(g>255) 
  {
    g=255;
  }
  if(b>255) 
  {
    b=255;
  }
  colorcode = (long)((long)r<<16) | ((long)g<<8) | (long)b;
  return colorcode;
}

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
 *   return Color result
 * \par Others
 *   None
 */
uint8_t TKColorSensor::ColorIdentify(void)
{
  uint8_t result,r,g,b;
  if(TKColorSensor::ColorDataReadOnebyOne())
  {
    return BLACK;//id return error!
  }
  /*********************************/
  if(Redvalue < 1200 && Greenvalue < 1700 && Bluevalue < 1200)
  {
    if(Bluevalue < Redvalue && Redvalue <= Greenvalue)  
    {
      if((Greenvalue + Redvalue + Bluevalue >300) && (Greenvalue > 1.5*Redvalue) && (Greenvalue > Bluevalue + Bluevalue))
      {
        result = GREEN;
      }
      else if((Greenvalue > Bluevalue + Bluevalue) && (Redvalue > Bluevalue + Bluevalue) && (Redvalue +  Greenvalue + Bluevalue > 120))
      {
        result = YELLOW;
      }
      else if(Redvalue > 400 && Greenvalue > 580 && Bluevalue > 320)
      {
        result = WHITE;
      }
      else
      {
        result = BLACK;
      }
    }
    else if(Greenvalue < Redvalue && Bluevalue < Greenvalue)  
    {
      if(Redvalue + Greenvalue + Bluevalue > 220)
      {
        if(Greenvalue < 2.4 * Bluevalue)
        {
          result = RED;
        }
        
        else if(Greenvalue >= 2.4 * Bluevalue)
        {
          result = RED;
        }
        else
        {
          result = BLACK;
        }
      }
      else
      {
        result = BLACK;
      }
    }
    else if(Greenvalue <= Bluevalue && Redvalue < Bluevalue)
    {
      result = BLUE;
    }
    else if(Redvalue <= Greenvalue && Bluevalue >= Redvalue)
    {
      if((Redvalue + Greenvalue + Bluevalue) > 400)
      {
        if(Greenvalue > 2.2 * Redvalue && Greenvalue > 2.2 * Bluevalue)
        {
          result = GREEN;
        }
        else
        {
          result = BLUE;
        }
      }
      else
      {
        result = BLACK;
      }
    }
    else if((Greenvalue < (Redvalue + Bluevalue)) && ((Greenvalue + Redvalue + Bluevalue) > 700))
    {
      result = WHITE;
    }
    else if((Greenvalue + Redvalue + Bluevalue) < 1000)
    {
      result = BLACK;
    }
    else
    {
      result = BLACK;
    }
  }
  /*****************************/
  else if(Bluevalue > Greenvalue && Bluevalue > Redvalue) 
  {
    result = BLUE;
  }
  else if((Redvalue > Greenvalue) && (Greenvalue > Bluevalue) &&  (Redvalue > Greenvalue))
  {
    result = RED;
  }
  /****************************/
  else
  {
    r = Redvalue / Colorvalue;
    g = Greenvalue / Colorvalue;
    b = Bluevalue / Colorvalue;
    if(r >= 9 && g <= 4 && b <= 1)
    {
      result = RED;
    }
    else if(r > 10 && g <= 4 && b <= 4)
    {
      result = RED;
    }
    else if(r < 3 && g <= 4 && b < 3)
    {
      result = BLACK;
    }
    else if(r <= 5 && g > 10 && b < 5)
    {
      result = GREEN;
    }
    else if((r < 5 && g < 5 && b > 10) || (r <= 3 && g >= 8 && b >= 8))
    {
      result = BLUE;
    }
    else if(r >= 5 && g > 6 && b >= 7)
    {
      result = BLUE;
    }
    else if(r <= 4 && g >= 10 && b >= 6)
    {
      result = BLUE;
    }
    else if(r <= 8 && r >= 6 && g >= 6 && b < 2)
    {
      result = YELLOW;
    }
    else if(r <= 8 && r <= 8 && b < 2)
    {
      //result = RED;
    }
    else if(r >= 10 && g <= 7 && b < 2)
    {
      result = RED;
    }
    else if(r >= 4 && g >= 9 && b >= 4)
    {
      result = WHITE;
    }
    else
    {
      result = WHITE;
    }
  }
  return result;
}

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
 *   return color result
 * \par Others
 *   None
 */
uint8_t TKColorSensor::Returnresult(void)
{
  static uint8_t cnt_;
  static uint16_t temp[3];
  uint8_t result,r,g,b;

  TKColorSensor::ColorDataRead();

  /*********************************/
  if(Redvalue < 1200 && Greenvalue < 1700 && Bluevalue < 1200)
  {
    if(Greenvalue + Redvalue + Bluevalue <700)
    {
        result = BLACK;
    }
    else if(Bluevalue < Redvalue && Redvalue <= Greenvalue) 
    {
        if((Greenvalue + Redvalue + Bluevalue > 300) && (Greenvalue > 1.5 * Redvalue) && (Greenvalue > Bluevalue + Bluevalue))
        {
            result = GREEN;
        }
        else if((Greenvalue > Bluevalue + Bluevalue) && (Redvalue > Bluevalue + Bluevalue) && (Redvalue +  Greenvalue + Bluevalue > 120))
        {
            result = YELLOW;
        }
        else if(Redvalue > 450 && Greenvalue > 580 && Bluevalue > 320)
        {
            result = WHITE;
        }
        else
        {
            result = BLACK;
        }
    }
    else if(Greenvalue < Redvalue && Bluevalue < Greenvalue)
    {
        if((Redvalue + Greenvalue + Bluevalue > 500) && Redvalue > 300)
        {
            result = RED;
        }
        else
        {
            result = BLACK;
        }
    }
    else if(Greenvalue <= Bluevalue && Redvalue < Bluevalue)
    {
        result = BLUE;
    }
    else if(Redvalue <= Greenvalue && Bluevalue >= Redvalue)
    {
        if(Redvalue + Greenvalue + Bluevalue > 400)
        {
            if(Greenvalue > 2.2 * Redvalue && Greenvalue > 2.2 * Bluevalue)
            {
                result = GREEN;
            }
            else
            {
                result = BLUE;
            }
        }
        else
        {
            result = BLACK;
        }
    }
    else if((Greenvalue < Redvalue + Bluevalue) && (Greenvalue + Redvalue + Bluevalue >700))
    {
        result = WHITE;
    }
    else
    {
        result = BLACK;
    }
  }
  /*****************************/
  else
  {
    r = Redvalue / Colorvalue;
    g = Greenvalue / Colorvalue;
    b = Bluevalue / Colorvalue;

    if(r >= 9 && g <= 4 && b <= 1)
    {
      result = RED;
    }
    else if(r > 10 && g <= 4 && b <= 4)
    {
      result = RED;
    }
    else if(r < 3 && g <= 4 && b < 3)
    {
      result = BLACK;
    }
    else if(r <= 5 && g > 10 && b < 5)
    {
      result = GREEN;
    }
    else if((r < 5 && g < 5 && b > 10) || (r <= 3 && g >= 8 && b >= 8))
    {
      result = BLUE;
    }
    else if(r >= 5 && g > 6 && b >= 7)
    {
      result = BLUE;
    }
    else if(r <= 4 && g >= 10 && b >= 6)
    {
      result = BLUE;
    }
    else if(r <= 8 && r >= 6 && g >= 6 && b < 2)
    {
      result = YELLOW;
    }
    else if(r >= 10 && g <= 7 && b < 2)
    {
      result = RED;
    }
    else if(r >= 4 && g >= 9 && b >= 4)
    {
      result = WHITE;
    }
    else
    {
      result = WHITE;
    }
  }
  /***************move filter***************/
  temp[cnt_++] = result;
  if(cnt_>=3) 
  {
    cnt_ = 0;
  }
  return (temp[0] + temp[1] + temp[2])/3;
}

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
 *   return Color Grayscale value
 * \par Others
 * Gray = R*0.299 + G*0.587 + B*0.114
 * Gray = (r*38 + g*75 + b*15)>>7;  
 */
uint8_t TKColorSensor::ReturnGrayscale(void)
{
  uint8_t r,g,b;
  uint16_t gray = 0;

  r = Redvalue>>8;
  g = Greenvalue>>8;
  b = Bluevalue>>8;

  gray = (r * 38 + g * 75 + b * 15) >> 4;
  if(gray > 255) 
  {
    gray = 255;
  }
  return gray;
}

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
 *   return color hue
 * \par Others
 *   None
 */
uint16_t TKColorSensor::ReturnColorhue(void)
{
  uint8_t r,g,b,max,min,c;
  uint16_t h;

  r = Redvalue>>8;
  g = Greenvalue>>8;
  b = Bluevalue>>8;

  if((r == g) && (g == b))
  {
    h = 0;
  }
  else
  {
    max = MAX(r,g,b);
    min = MIN(r,g,b);
    c = max - min;
    if(max == r)
    {
      h = ((g-b) / c % 6)*60; 
    }
    else if(max == g)
    {
      h = ((b-r) / c + 2) * 60; 
    }
    else if(min == b)
    {
      h = ((r-g) / c + 4)*60; 
    }
  }
  return h;
}
  
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
 *   return red value
 * \par Others
 *   None
 */
uint16_t TKColorSensor::ReturnRedData(void)
{
  return Redvalue;
}

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
 *   return green value
 * \par Others
 *   None
 */
uint16_t TKColorSensor::ReturnGreenData(void)
{
  return Greenvalue;
}

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
 *   return blue value
 * \par Others
 *   None
 */
uint16_t TKColorSensor::ReturnBlueData(void)
{
  return Bluevalue;
}

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
 *   return color data value
 * \par Others
 *   None
 */
uint16_t TKColorSensor::ReturnColorData(void)
{
  return Colorvalue;
}

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
void TKColorSensor::TurnOnLight(void)
{
  TKPort::dWrite1(1);
}

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
void TKColorSensor::TurnOffLight(void)
{
  TKPort::dWrite1(0);
}
  
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
void TKColorSensor::TurnOffmodule(void)
{
TKPort::dWrite2(1);
}

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
void TKColorSensor::TurnOnmodule(void)
{
  TKPort::dWrite2(0);//power on
}

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
int8_t TKColorSensor::writeReg(int16_t reg, uint8_t data)
{
  int8_t return_value = 0;

  return_value = writeData(reg, &data, 1);
  
  return(return_value);
}

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
int8_t TKColorSensor::readData(uint8_t start, uint8_t *buffer, uint8_t size)
{
  int16_t i = 0;
  int8_t return_value = 0;
  Wire.beginTransmission(Device_Address);
  return_value = Wire.write(start);

  if(return_value != 1)
  {
    return(I2C_ERROR);
  }
  return_value = Wire.endTransmission(false);

  if(return_value != 0)
  {
    return(return_value);
  }
  delayMicroseconds(1);
  /* Third parameter is true: relase I2C-bus after data is read. */
  Wire.requestFrom(Device_Address, size, (uint8_t)true);
  
  while(Wire.available() && i < size)
  {
    buffer[i++] = Wire.read();
  }
  delayMicroseconds(1);
  
  if(i != size)
  {
    return(I2C_ERROR);
  }
  return 0; 
}

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
int8_t TKColorSensor::writeData(uint8_t start, const uint8_t *pData, uint8_t size)
{
  int8_t return_value = 0;
  Wire.beginTransmission(Device_Address);
  return_value = Wire.write(start); 
  if(return_value != 1)
  {
      return(I2C_ERROR);
  }
  Wire.write(pData, size);  
  return_value = Wire.endTransmission(true); 
  return return_value;                      
}

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
uint8_t TKColorSensor::MAX(uint8_t r, uint8_t g, uint8_t b)
{
  uint8_t max;
  if(r >= g)
  {
    if(r >= b)
    {
      max = r;
    }
    else
    {
      max = b;
    }
  }
  else if(g >= b)
  {
    max = g;
  }
  else
  {
    max = b;
  }
  return max;
}

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
uint8_t TKColorSensor::MIN(uint8_t r, uint8_t g, uint8_t b)
{
  uint8_t min;
  if(r <= g)
  {
    if(r <= b)
    {
      min = r;
    }
    else
    {
      min = b;
    }
  }
  else if(g <= b)
  {
    min = g;
  }
  else
  {
    min = b;
  }
  return min;
}





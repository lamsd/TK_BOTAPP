

#ifndef TKHostParser_h
#define TKHostParser_h
#include <Arduino.h>
#define BUF_SIZE            256
#define MASK                255

/**
 * Class: TKHostParser
 * \par Description
 * Declaration of Class TKHostParser.
 */
class TKHostParser
{
public:
/**
 * Alternate Constructor which can call your own function to map the Host Parser to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
*/
  TKHostParser();
	
/**
 * Alternate Destructor which can call the system's destructor to free space,
 * no pins are used or initialized here.
 * \param[in]
 *   None
*/
  ~TKHostParser();

/**
 * \par Function
 *    pushStr
 * \par Description
 *    To push a string to Host Parser.
 * \param[in]
 *    str - A pointer to a string.
 * \param[in]
 *    length - The length of the string.
 * \par Output
 *    None
 * \par Return
 *    Return the index of pushing string.
 * \par Others
 *    None
 */
   uint8_t pushStr(uint8_t * str, uint32_t length);
   
/**
 * \par Function
 *    pushByte
 * \par Description
 *    To push a byte to Host Parser.
 * \param[in]
 *    ch - A pointer to a char.
 * \par Output
 *    None
 * \par Return
 *    Return the status of pushing char.
 * \par Others
 *    None
 */
   uint8_t pushByte(uint8_t ch);

/**
 * \par Function
 *    run
 * \par Description
 *    The running status of Host Parser.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Return the status of Host Parser's running.
 * \par Others
 *    None
 */
  uint8_t run();

/**
 * \par Function
 *    getPackageReady
 * \par Description
 *    Get the package ready state.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Return the status ready or not.
 * \par Others
 *    None
 */
   //  get the package ready state
   uint8_t getPackageReady();
   
/**
 * \par Function
 *    getData
 * \par Description
 *    Copy data to user's buffer.
 * \param[in]
 *    buf - A buffer for a getting data.
 * \param[in]
 *    size - The length of getting data.
 * \par Output
 *    None
 * \par Return
 *    Return the length of getting data or 0.
 * \par Others
 *    None
 */
  uint8_t getData(uint8_t *buf, uint32_t size);

  void print(char *str, uint32_t * cnt);
private:
  int state;
  uint8_t buffer[BUF_SIZE];
  uint32_t in;
  uint32_t out;
  uint8_t packageReady;

  uint8_t module;
  uint32_t length;
  uint8_t *data;
  uint8_t check;

  uint32_t lengthRead;
  uint32_t currentDataPos;

/**
 * \par Function
 *    getByte
 * \par Description
 *    To get a byte from Host Parser.
 * \param[in]
 *    ch - A pointer to a char.
 * \par Output
 *    None
 * \par Return
 *    Return the status of getting char.
 * \par Others
 *    None
 */
  uint8_t getByte(uint8_t * ch);
};


#endif 

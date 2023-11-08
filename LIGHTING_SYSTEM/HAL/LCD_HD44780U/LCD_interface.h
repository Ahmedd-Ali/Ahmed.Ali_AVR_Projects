/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : HAL                  **********************/
/****************    SWC       : LCD                  *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef LCD_HD44780U_LCD_INTERFACE_H_
#define LCD_HD44780U_LCD_INTERFACE_H_


#include <util/delay.h>
#include "STD_TYPES.h"
#include "DIO_interface.h"

#define   _4_BIT   1
#define   _8_BIT   2

/***********************************************************/
#define   LCD_MODE   _4_BIT

#define   RS   PINA3
#define   EN   PINA2

#define   D7   PINB4
#define   D6   PINB2
#define   D5   PINB1
#define   D4   PINB0



ErrorState_t LCD_Init(void);
ErrorState_t LCD_WriteNumber(sint32 num);
ErrorState_t LCD_WriteNumber_4D(uint16 num);
ErrorState_t LCD_WriteChar(uint8 ch);
ErrorState_t LCD_WriteString(uint8 * str);
ErrorState_t LCD_Clear(void);
ErrorState_t LCD_WriteBinary(uint8 num);
//ErrorState_t LCD_WriteHex(uint8 num);
//ErrorState_t LCD_WriteHex2(uint32 num);
ErrorState_t LCD_SetCursor(uint8 line, uint8 cell);  // line 1,2  cell  1 : 16
ErrorState_t LCD_GoToClear(uint8 line, uint8 cell, uint8 numOfCells);
ErrorState_t LCD_GoToWriteString(uint8 line, uint8 cell, uint8 * str);
ErrorState_t LCD_Create_Character(uint8 * pattern, uint8 location);


#endif /* LCD_HD44780U_LCD_INTERFACE_H_ */

/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : HAL                  **********************/
/****************    SWC       : KEYPAD               *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#define  KeyPad   1

#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "KEYPAD_config.h"
#include "KEYPAD_private.h"
#include "KEYPAD_interface.h"


ErrorState_t KEYPAD_Init(void)
{
	ErrorState_t ret= E_OK;

	int i;
	for(i= 0; i<ROWS; i++)
	{
		ret|= DIO_WritePin(keypad_rows[i], HIGH);
	}

	return ret;
}

ErrorState_t KEYPAD_GetKey(uint8 * pKey)
{
	ErrorState_t ret= E_OK;
	uint8 row, col, value= LOW;

	if(NULL == pKey)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		*pKey= NOT_KEY;
		for(row=0; row<ROWS; row++)
		{
			ret|= DIO_WritePin(keypad_rows[row], LOW);
			for(col=0; col<COLS; col++)
			{
				ret|= DIO_ReadPin(keypad_cols[col], &value);
				if(value == LOW)
				{
					*pKey= KeysArray[row][col];
					//_delay_ms(10); 			 // Debounce delay
					while(value == LOW)    	 // Wait until key is released
					{
						ret|= DIO_ReadPin(keypad_cols[col], &value);
					}
				}
			}
			ret|= DIO_WritePin(keypad_rows[row], HIGH);
		}
	}

	return ret;
}



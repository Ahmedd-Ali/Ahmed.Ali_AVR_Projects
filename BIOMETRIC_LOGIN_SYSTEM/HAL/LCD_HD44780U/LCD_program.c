/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : HAL                  **********************/
/****************    SWC       : LCD                  *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "MEM_MAP.h"
#include "BIT_MATH.h"
#include "LCD_interface.h"


static ErrorState_t Enable_Pulse(void)
{
	ErrorState_t ret= E_OK;
		ret|= DIO_WritePin(EN, HIGH);
		_delay_us(1);
		ret|= DIO_WritePin(EN, LOW);
		_delay_ms(1);
	return ret;
}


#if  LCD_MODE==_8_BIT

static ErrorState_t LCD_SendCmd(uint8 ins)
{
	ErrorState_t ret= E_OK;

	ret|= DIO_WritePin(RS, LOW);
	ret|= DIO_WritePort(LCD_PORT, ins);
	ret|= Enable_Pulse();

	return ret;
}

static ErrorState_t LCD_SendData(uint8 data)
{
	ErrorState_t ret= E_OK;
	ret|= DIO_WritePin(RS, HIGH);
	ret|= DIO_WritePort(LCD_PORT, data);
	ret|= Enable_Pulse();
	return ret;
}

ErrorState_t LCD_Init(void)
{
	ErrorState_t ret= E_OK;
	_delay_ms(50);
	ret|= LCD_WriteInstruction(0x38); // Function Set ... DL=1(8 bit mode), N=1(2 lines), F=0(font 5x7)
	ret|= LCD_WriteInstruction(0x0c); // Display ON/OFF Control ... D=1(LCD ON), C=0(No Cursor), B=0(No C Blink) 0x0e, 0x0f
	ret|= LCD_WriteInstruction(0x01); // Clear Screen
	_delay_ms(1);
	ret|= LCD_WriteInstruction(0x06); // Entry Mode Set ... I/D=1(Increase DDRAM Address), SH=0(No Shift Data)
	return ret;
}

#elif   LCD_MODE==_4_BIT

static ErrorState_t LCD_SendCmd(uint8 ins)
{
	ErrorState_t ret= E_OK;

	ret|= DIO_WritePin(RS, LOW);
	ret|= DIO_WritePin(D7, GET_BIT(ins, 7));
	ret|= DIO_WritePin(D6, GET_BIT(ins, 6));
	ret|= DIO_WritePin(D5, GET_BIT(ins, 5));
	ret|= DIO_WritePin(D4, GET_BIT(ins, 4));
	ret|= Enable_Pulse();
	ret|= DIO_WritePin(D7, GET_BIT(ins, 3));
	ret|= DIO_WritePin(D6, GET_BIT(ins, 2));
	ret|= DIO_WritePin(D5, GET_BIT(ins, 1));
	ret|= DIO_WritePin(D4, GET_BIT(ins, 0));
	ret|= Enable_Pulse();

	return ret;
}

static ErrorState_t LCD_SendData(uint8 data)
{
	ErrorState_t ret= E_OK;

	ret|= DIO_WritePin(RS, HIGH);
	ret|= DIO_WritePin(D7, GET_BIT(data, 7));
	ret|= DIO_WritePin(D6, GET_BIT(data, 6));
	ret|= DIO_WritePin(D5, GET_BIT(data, 5));
	ret|= DIO_WritePin(D4, GET_BIT(data, 4));
	ret|= Enable_Pulse();
	ret|= DIO_WritePin(D7, GET_BIT(data, 3));
	ret|= DIO_WritePin(D6, GET_BIT(data, 2));
	ret|= DIO_WritePin(D5, GET_BIT(data, 1));
	ret|= DIO_WritePin(D4, GET_BIT(data, 0));
	ret|= Enable_Pulse();

	return ret;
}

ErrorState_t LCD_Init(void)
{
	ErrorState_t ret= E_OK;

	_delay_ms(20);
	ret|= LCD_SendCmd(0x03); // Function Set
	_delay_ms(5);
	ret|= LCD_SendCmd(0x03); // Function Set
	_delay_us(100);
	ret|= LCD_SendCmd(0x03); // Function Set
	ret|= LCD_SendCmd(0x02); // Function Set
	ret|= LCD_SendCmd(0x28); // Function Set ... DL=0(4 bit mode), N=1(2 lines), F=0(font 5x7)
	ret|= LCD_SendCmd(0x0c); // Display ON/OFF Control ... D=1(LCD ON), C=0(No Cursor), B=0(No C Blink) 0x0e, 0x0f
	ret|= LCD_SendCmd(0x01); // Clear Screen
	_delay_ms(1);
	ret|= LCD_SendCmd(0x06); // Entry Mode Set ... I/D=1(Increase DDRAM Address), SH=0(No Shift Data)

	return ret;
}

#endif

/****************************************************************/

ErrorState_t LCD_WriteChar(uint8 ch)
{
	ErrorState_t ret= E_OK;

	ret|= LCD_SendData(ch);

	return ret;
}

ErrorState_t LCD_Clear(void)
{
	ErrorState_t ret= E_OK;

	ret|= LCD_SendCmd(0x01);
	_delay_ms(1);

	return ret;
}

ErrorState_t LCD_WriteNumber(sint32 num)
{
	ErrorState_t ret= E_OK;
	uint8 i=0, j, rem, str[16]= {0};

	if(num == 0)
	{
		ret|= LCD_WriteChar('0');
	}
	else
	{
		if(num < 0)
		{
			num = num *(-1);
			ret|= LCD_WriteChar('-');
		}
		while(num > 0)
			{
				rem = num % 10;
				str[i] = rem + '0';
				i++;
				num = num / 10;
			}
			for(j=i; j>0; j--)
			{
				ret|= LCD_WriteChar(str[j-1]);
			}
	}

	return ret;
}

ErrorState_t LCD_WriteNumber_4D(uint16 num)
{
	ErrorState_t ret= E_OK;

	ret|= LCD_WriteChar(((num%10000)/1000)+'0');
	ret|= LCD_WriteChar(((num%1000)/100)+'0');
	ret|= LCD_WriteChar(((num%100)/10)+'0');
	ret|= LCD_WriteChar(((num%10)/1)+'0');

	return ret;
}

ErrorState_t LCD_WriteString(uint8 * str)
{
	ErrorState_t ret= E_OK;
	uint8 i;

	if(str == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		for(i=0; str[i]; i++)
			{
				ret|= LCD_WriteChar(str[i]);
			}
	}

	return ret;
}

ErrorState_t LCD_WriteBinary(uint8 num)
{
	ErrorState_t ret= E_OK;
	uint8 i, flag=0;

	for(i=8; i>0; i--){
		if((num>>(i-1))&1){
			ret|= LCD_WriteNumber(1);
			flag = 1;
		}
		else
		{
			if(flag == 1)
			{
				ret|= LCD_WriteNumber(0);
			}
		}
	}
	return ret;
}


ErrorState_t LCD_SetCursor(uint8 line, uint8 cell)
{
	ErrorState_t ret= E_OK;
	if((line > 4 || line < 1) || (cell > 20 || cell < 1))
	{
		ret|= E_OUT_OF_RANGE;
	}
	else
	{
		if(line == 1)
			{
				ret|= LCD_SendCmd(0x80+cell-1);
			}
			else if(line == 2)
			{
				ret|= LCD_SendCmd(0x80+0x40+cell-1);
			}
			else if(line == 3)
			{
				ret|= LCD_SendCmd(0x80+0x14+cell-1);
			}
			else if(line == 4)
			{
				ret|= LCD_SendCmd(0x80+0x54+cell-1);
			}

	}

	return ret;
}

ErrorState_t LCD_GoToClear(uint8 line, uint8 cell, uint8 numOfCells)
{
	ErrorState_t ret= E_OK;
	uint8 i;

	if((line > 4 || line < 1) || (cell > 20 || cell < 1))
		{
			ret|= E_OUT_OF_RANGE;
		}
		else
		{
			ret|= LCD_SetCursor(line, cell);
				for(i=0; i<numOfCells; i++)
				{
					ret|= LCD_WriteChar(' ');
				}
		}

	return ret;
}

ErrorState_t LCD_GoToWriteString(uint8 line, uint8 cell, uint8* str)
{
	ErrorState_t ret= E_OK;

	if(str == NULL)
	{
		ret|= E_NULL_PTR;
	}
	else if((line > 4 || line < 1) || (cell > 20 || cell < 1))

	{
		ret|= E_OUT_OF_RANGE;
	}
	else
	{
		ret|= LCD_SetCursor(line, cell);
		ret|= LCD_WriteString(str);
	}

	return ret;
}

ErrorState_t LCD_Create_Character(uint8 * pattern, uint8 location)
{
	ErrorState_t ret= E_OK;
	uint8 iLoop=0;

	if(pattern == NULL)
	{
		ret|= E_NULL_PTR;
	}
	else
	{
		ret|= LCD_SendCmd(0x40+(location*8)); // Send the address of CGRAM
		for(iLoop=0; iLoop<8; iLoop++)
		{
			ret|= LCD_SendData(pattern[iLoop]); // Pass The bytes of pattern on LCD
		}
		ret|= LCD_SendCmd(0x80);
	}

	return ret;
}

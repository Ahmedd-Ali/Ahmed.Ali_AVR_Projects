/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : DIO                  *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MEM_MAP.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"



static ErrorState_t DIO_PinInit(DIO_Pin_t pin_num, DIO_PinStatus_t status)
{
	ErrorState_t ret= E_OK;
	DIO_Port_t port = pin_num / 8;
	pin_num = pin_num % 8;
	
	switch(status)
	{
		case OUTPUT:
		switch(port)
		{
			case PORT_A:
			SET_BIT(DDRA, pin_num);
			CLR_BIT(PORTA, pin_num);
			break;
			case PORT_B:
			SET_BIT(DDRB, pin_num);
			CLR_BIT(PORTB, pin_num);
			break;
			case PORT_C:
			SET_BIT(DDRC, pin_num);
			CLR_BIT(PORTC, pin_num);
			break;
			case PORT_D:
			SET_BIT(DDRD, pin_num);
			CLR_BIT(PORTD, pin_num);
			break;
			
			default:
			ret= E_OUT_OF_RANGE;
			break;
		}
		break;
		
		case INFREE:
		switch(port)
		{
			case PORT_A:
			CLR_BIT(DDRA, pin_num);
			CLR_BIT(PORTA, pin_num);
			break;
			case PORT_B:
			CLR_BIT(DDRB, pin_num);
			CLR_BIT(PORTB, pin_num);
			break;
			case PORT_C:
			CLR_BIT(DDRC, pin_num);
			CLR_BIT(PORTC, pin_num);
			break;
			case PORT_D:
			CLR_BIT(DDRD, pin_num);
			CLR_BIT(PORTD, pin_num);
			break;
			
			default:
			ret= E_OUT_OF_RANGE;
			break;
		}
		break;
		
		case INPULL:
		switch(port)
		{
			case PORT_A:
			CLR_BIT(DDRA, pin_num);
			SET_BIT(PORTA, pin_num);
			break;
			case PORT_B:
			CLR_BIT(DDRB, pin_num);
			SET_BIT(PORTB, pin_num);
			break;
			case PORT_C:
			CLR_BIT(DDRC, pin_num);
			SET_BIT(PORTC, pin_num);
			break;
			case PORT_D:
			CLR_BIT(DDRD, pin_num);
			SET_BIT(PORTD, pin_num);
			break;
			
			default:
			ret= E_OUT_OF_RANGE;
			break;
		}
		break;
		
		default:
		ret= E_OUT_OF_RANGE;
		break;
	}
	return ret;
}

ErrorState_t DIO_WritePin(DIO_Pin_t pin_num, DIO_PinVoltage_t volt)
{
	ErrorState_t ret= E_OK;
	DIO_Port_t port = pin_num / 8;
	pin_num = pin_num % 8;
	if(volt == HIGH)
	{
		switch(port)
		{
			case PORT_A:
			SET_BIT(PORTA, pin_num);
			break;
			case PORT_B:
			SET_BIT(PORTB, pin_num);
			break;
			case PORT_C:
			SET_BIT(PORTC, pin_num);
			break;
			case PORT_D:
			SET_BIT(PORTD, pin_num);
			break;
			
			default:
			ret= E_OUT_OF_RANGE;
			break;
		}
	}
	else if(volt == LOW)
	{
		switch(port)
		{
			case PORT_A:
			CLR_BIT(PORTA, pin_num);
			break;
			case PORT_B:
			CLR_BIT(PORTB, pin_num);
			break;
			case PORT_C:
			CLR_BIT(PORTC, pin_num);
			break;
			case PORT_D:
			CLR_BIT(PORTD, pin_num);
			break;
			
			default:
			ret= E_OUT_OF_RANGE;
			break;
		}
	}
	return ret;
}

ErrorState_t DIO_ReadPin(DIO_Pin_t pin_num, DIO_PinVoltage_t * value)
{
	ErrorState_t ret = E_OK;
	DIO_Port_t port = pin_num / 8;
	pin_num = pin_num % 8;
	
	if(value == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		switch(port)
		{
			case PORT_A:
			*value=(DIO_PinVoltage_t)GET_BIT(PINA, pin_num);
			break;
			case PORT_B:
			*value=(DIO_PinVoltage_t)GET_BIT(PINB, pin_num);
			break;
			case PORT_C:
			*value=(DIO_PinVoltage_t)GET_BIT(PINC, pin_num);
			break;
			case PORT_D:
			*value=(DIO_PinVoltage_t)GET_BIT(PIND, pin_num);
			break;
			
			default:
			ret= E_OUT_OF_RANGE;
			break;
		}
	}
	return ret;
}

ErrorState_t DIO_TogglePin(DIO_Pin_t pin_num)
{
	ErrorState_t ret= E_OK;
	DIO_Port_t port = pin_num / 8;
	pin_num = pin_num % 8;
	
	switch(port)
	{
		case PORT_A:
		TOG_BIT(PORTA, pin_num);
		break;
		case PORT_B:
		TOG_BIT(PORTB, pin_num);
		break;
		case PORT_C:
		TOG_BIT(PORTC, pin_num);
		break;
		case PORT_D:
		TOG_BIT(PORTD, pin_num);
		break;
		
		default:
		ret= E_OUT_OF_RANGE;
		break;
	}
	return ret;
}

ErrorState_t DIO_PortInit(DIO_Port_t port, DIO_PinStatus_t status)
{
	ErrorState_t ret= E_OK;
	
	switch(status)
	{
		case OUTPUT:
		switch(port)
		{
			case PORT_A:
			DDRA=DIO_U8PORT_HIGH;
			PORTA=DIO_U8PORT_LOW;
			break;
			case PORT_B:
			DDRB=DIO_U8PORT_HIGH;
			PORTB=DIO_U8PORT_LOW;
			break;
			case PORT_C:
			DDRC=DIO_U8PORT_HIGH;
			PORTC=DIO_U8PORT_LOW;
			break;
			case PORT_D:
			DDRD=DIO_U8PORT_HIGH;
			PORTD=DIO_U8PORT_LOW;
			break;
			
			default:
			ret= E_OUT_OF_RANGE;
			break;
		}
		break;
		
		case INFREE:
		switch(port)
		{
			case PORT_A:
			DDRA=DIO_U8PORT_LOW;
			PORTA=DIO_U8PORT_LOW;
			break;
			case PORT_B:
			DDRB=DIO_U8PORT_LOW;
			PORTB=DIO_U8PORT_LOW;
			break;
			case PORT_C:
			DDRC=DIO_U8PORT_LOW;
			PORTC=DIO_U8PORT_LOW;
			break;
			case PORT_D:
			DDRD=DIO_U8PORT_LOW;
			PORTD=DIO_U8PORT_LOW;
			break;
			
			default:
			ret= E_OUT_OF_RANGE;
			break;
		}
		break;
		
		case INPULL:
		switch(port)
		{
			case PORT_A:
			DDRA=DIO_U8PORT_LOW;
			PORTA=DIO_U8PORT_HIGH;
			break;
			
			case PORT_B:
			DDRB=DIO_U8PORT_LOW;
			PORTB=DIO_U8PORT_HIGH;
			break;
			
			case PORT_C:
			DDRC=DIO_U8PORT_LOW;
			PORTC=DIO_U8PORT_HIGH;
			break;
			
			case PORT_D:
			DDRD= DIO_U8PORT_LOW;
			PORTD= DIO_U8PORT_HIGH;
			break;
			
			default:
				ret= E_OUT_OF_RANGE;
				break;
		}
		break;
		
		default:
		ret= E_OUT_OF_RANGE;
		break;
	}
	return ret;
}

ErrorState_t DIO_WritePort(DIO_Port_t port, uint8 data)
{
	ErrorState_t ret= E_OK;
	
	switch(port)
	{
		case PORT_A:
		PORTA=data;
		break;
		case PORT_B:
		PORTB=data;
		break;
		case PORT_C:
		PORTC=data;
		break;
		case PORT_D:
		PORTD=data;
		break;
		
		default:
		ret= E_OUT_OF_RANGE;
		break;
	}
	return ret;
}

ErrorState_t DIO_ReadPort(DIO_Port_t port, uint8 * data)
{
	ErrorState_t ret= E_OK;
	if(data == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		switch(port)
		{
			case PORT_A:
			*data=PINA;
			break;
			case PORT_B:
			*data=PINB;
			break;
			case PORT_C:
			*data=PINC;
			break;
			case PORT_D:
			*data=PIND;
			break;
			
			default:
			ret= E_OUT_OF_RANGE;
			break;
		}
	}
	
	return ret;
}


ErrorState_t DIO_Init(void)
{
	ErrorState_t ret= E_OK;
	DIO_Pin_t pin;
	
	for(pin=PINA0; pin<TOTAL_PINS; pin++)
	{
		ret|= DIO_PinInit(pin, PinsStatusArray[pin]);
	}
	
	return ret;
}

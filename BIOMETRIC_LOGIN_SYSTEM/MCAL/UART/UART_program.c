/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : UART                 *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/


#include "STD_TYPES.h"
#include "MEM_MAP.h"
#include "BIT_MATH.h"
#include "UART_private.h"
#include "UART_config.h"
#include "UART_interface.h"


uint8 init_flag=0;
static void(*UART_RX_Fptr)(void)= NULL;
static void(*UART_TX_Fptr)(void)= NULL;

ErrorState_t UART_Init(UART_BaudRate_t buad_rate)
{
	ErrorState_t ret= E_OK;

	// baud rate 9600 // 103 -> FCPU 16MHZ
	// baud rate 57600 // 16 -> FCPU 16MHZ
	UBRRL= buad_rate;

	// normal speed
	CLR_BIT(UCSRA, U2X); // initial value = 0 from data sheet but sometimes change so we force it to be 0

	// frame -> parity , data bits , stop bits
	/* Initial values : Asynchronous, no parity, 1-stop bit, 8-bit data */
	/* we will work with this frame, so we don't need to change initial values */

	// enable interrupt for transmitter and receiver
	SET_BIT(UCSRB, TXEN);
	SET_BIT(UCSRB, RXEN);

	return ret;
}

/* The Tx & Rx will override normal port operation for the TxD & RxD pins when enabled */ /* data sheet */
/* So we don't need to change its configuration from DIO_cfg */


ErrorState_t UART_Send(uint8 data)
{
	ErrorState_t ret= E_OK;

	while(!GET_BIT(UCSRA, UDRE)); // wait while buffer not empty
	UDR=data;

	return ret;
}


ErrorState_t UART_Receive(uint8 * data)
{
	ErrorState_t ret= E_OK;

	if(data == NULL)
	{
		ret|= E_NULL_PTR;
	}
	else
	{
		while(!GET_BIT(UCSRA,RXC)); // it will affect whole program stuck till data received
		*data= UDR;				 // and with high rate receiving the data will overrun
	}

	return ret;
}



ErrorState_t UART_ReceivePerodic(uint8 * data)
{
	ErrorState_t ret= E_OK;

	if(data == NULL)
	{
		ret|= E_NULL_PTR;
	}
	else
	{
		if(GET_BIT(UCSRA, RXC)) // it will fix program stuck but still the data will overrun at high receiving rate
			{
				*data = UDR;
				ret|= E_OK;
			}
		ret|= E_OK;
	}

	return ret;
}

/******************************** interrupt ****************************************/

ErrorState_t UART_SendNoBlock(uint8 data)
{
	ErrorState_t ret= E_OK;

	UDR= data;

	return ret;
}

ErrorState_t UART_ReceiveNoBlock(uint8 * data)
{
	ErrorState_t ret= E_OK;

	if(data == NULL)
	{
		ret|= E_NULL_PTR;
	}
	else
	{
		*data= UDR;
	}

	return ret;
}


ErrorState_t UART_RX_InterruptEnable(void)
{
	ErrorState_t ret= E_OK;

	SET_BIT(UCSRB,RXCIE);

	return ret;
}

ErrorState_t UART_RX_InterruptDisable(void)
{
	ErrorState_t ret= E_OK;

	CLR_BIT(UCSRB,RXCIE);

	return ret;
}

ErrorState_t UART_TX_InterruptEnable(void)
{
	ErrorState_t ret= E_OK;

	SET_BIT(UCSRB,TXCIE);

	return ret;
}

ErrorState_t UART_TX_InterruptDisable(void)
{
	ErrorState_t ret= E_OK;

	CLR_BIT(UCSRB,TXCIE);

	return ret;
}

ErrorState_t UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	ErrorState_t ret= E_OK;

	UART_RX_Fptr = LocalFptr;

	return ret;
}

ErrorState_t UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	ErrorState_t ret= E_OK;

	UART_TX_Fptr = LocalFptr;

	return ret;
}


ISR(UART_RX_vect)
{
	if (UART_RX_Fptr != NULL)
	{
		UART_RX_Fptr();
	}
}

ISR(UART_TX_vect)
{
	if (UART_TX_Fptr != NULL)
	{
		UART_TX_Fptr();
	}
}



/*****************************************************************/


/******************************* Send/Receive Synchronous ***************************/

ErrorState_t UART_SendString(uint8 * str)
{
	ErrorState_t ret= E_OK;

	uint8 i;
	for(i=0; str[i]; i++)
	{
		UART_Send(str[i]);
	}

	return ret;
}

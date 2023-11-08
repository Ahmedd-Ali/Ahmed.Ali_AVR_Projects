/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : HAL                  **********************/
/****************    SWC       : BLUETOOTH_HC_05      *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "BLUETOOTH_HC_05_config.h"
#include "BLUETOOTH_HC_05_private.h"
#include "BLUETOOTH_HC_05_interface.h"
#include "UART_interface.h"


volatile uint8 Bluetooth_Buffer[BLUETOOTH_BUFFER_SIZE];
volatile uint8 Command_Rec_Flag= 0;
static volatile uint8 Index= 0;


void Receive_Rx(void)
{
	UART_ReceiveNoBlock((uint8 *)&Bluetooth_Buffer[Index]);
	if(Bluetooth_Buffer[Index] == 13)
	{
		UART_Receive((uint8 *)&Bluetooth_Buffer[Index]);
		Command_Rec_Flag= 1;
		Index= 0;
	}
	else if(Index < (BLUETOOTH_BUFFER_SIZE-1))
	{
		Index++;
	}
}


ErrorState_t BLUETOOTH_Init(void)
{
	ErrorState_t ret= E_OK;

	ret|= UART_Init(BAUD_9600);
	ret|= UART_RX_SetCallBack(&Receive_Rx);

	return ret;
}


ErrorState_t BLUETOOTH_Transmit(uint8 * str)
{
	ErrorState_t ret= E_OK;

	ret|= UART_SendString(str);

	return ret;
}


ErrorState_t BLUETOOTH_Start_Receive(void)
{
	ErrorState_t ret= E_OK;

	ret|= UART_RX_InterruptEnable();

	return ret;
}


ErrorState_t BLUETOOTH_Stop_Receive(void)
{
	ErrorState_t ret= E_OK;

	ret|= UART_RX_InterruptDisable();

	return ret;
}

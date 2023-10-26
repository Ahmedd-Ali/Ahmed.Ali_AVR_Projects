/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : UART                 *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef UART_UART_INTERFACE_H_
#define UART_UART_INTERFACE_H_


typedef enum{
	BAUD_9600 = 103,
	BAUD_57600= 16
}UART_BaudRate_t;

ErrorState_t UART_Init(UART_BaudRate_t buad_rate);
ErrorState_t UART_Send(uint8 data); // busy wait on UDRE (Buffer empty = 1)
ErrorState_t UART_Receive(uint8 * data); // busy wait on RxC flag
ErrorState_t UART_ReceivePerodic(uint8 * data); // polling on RxC flag

ErrorState_t UART_RX_InterruptEnable(void);
ErrorState_t UART_RX_InterruptDisable(void);

ErrorState_t UART_TX_InterruptEnable(void);
ErrorState_t UART_TX_InterruptDisable(void);

ErrorState_t UART_RX_SetCallBack(void (*LocalFptr)(void));
ErrorState_t UART_TX_SetCallBack(void (*LocalFptr)(void));

ErrorState_t UART_SendNoBlock(uint8 data);
ErrorState_t UART_ReceiveNoBlock(uint8 * data);

ErrorState_t UART_SendString(uint8 * str);


#endif /* UART_UART_INTERFACE_H_ */

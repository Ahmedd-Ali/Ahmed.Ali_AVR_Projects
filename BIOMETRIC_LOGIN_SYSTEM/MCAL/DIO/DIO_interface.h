/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : DIO                  *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/


#ifndef DIO_interface_H_
#define DIO_interface_H_

#include "STD_TYPES.h"

typedef enum{
	PINA0=0,
	PINA1=1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	TOTAL_PINS
}DIO_Pin_t;

typedef enum{
	PORT_A= 0,
	PORT_B= 1,
	PORT_C= 2,
	PORT_D= 3
}DIO_Port_t;

typedef enum{
	OUTPUT= 0,
	INFREE= 1,
	INPULL= 2
}DIO_PinStatus_t;

typedef enum{
	LOW= 0,
	HIGH= 1
}DIO_PinVoltage_t;


#define DIO_U8PORT_HIGH       0xff
#define DIO_U8PORT_LOW        0x00

  
extern ErrorState_t DIO_Init(void);
extern ErrorState_t DIO_WritePin(DIO_Pin_t pin_num, DIO_PinVoltage_t volt);
extern ErrorState_t DIO_ReadPin(DIO_Pin_t pin_num, DIO_PinVoltage_t * volt);
extern ErrorState_t DIO_TogglePin(DIO_Pin_t pin_num);

extern ErrorState_t DIO_WritePort(DIO_Port_t port, uint8 data);
extern ErrorState_t DIO_ReadPort(DIO_Port_t port, uint8 * data);

extern ErrorState_t DIO_PortInit(DIO_Port_t port, DIO_PinStatus_t status);


#endif

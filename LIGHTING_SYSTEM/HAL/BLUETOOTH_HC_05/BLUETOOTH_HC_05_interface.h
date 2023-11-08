/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : HAL                  **********************/
/****************    SWC       : BLUETOOTH_HC_05      *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef BLUETOOTH_HC_05_BLUETOOTH_HC_05_INTERFACE_H_
#define BLUETOOTH_HC_05_BLUETOOTH_HC_05_INTERFACE_H_


#define BLUETOOTH_BUFFER_SIZE     10

extern volatile uint8 Bluetooth_Buffer[BLUETOOTH_BUFFER_SIZE];
extern volatile uint8 Command_Rec_Flag;

ErrorState_t BLUETOOTH_Init(void);
ErrorState_t BLUETOOTH_Transmit(uint8 * str);
ErrorState_t BLUETOOTH_Start_Receive(void);
ErrorState_t BLUETOOTH_Stop_Receive(void);

#endif /* BLUETOOTH_HC_05_BLUETOOTH_HC_05_INTERFACE_H_ */

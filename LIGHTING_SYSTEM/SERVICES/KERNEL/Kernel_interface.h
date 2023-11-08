/*********************************************************************************/
/*********************************************************************************/
/**************************   Author: Ahmed Ali   ********************************/
/**************************   Layer: Kernel	      ********************************/
/**************************   Stack: OS           ********************************/
/**************************   Version: 1.00       ********************************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef KERNEL_INTERFACE_H_
#define KERNEL_INTERFACE_H_


ErrorState_t RTOS_Start(void);
ErrorState_t RTOS_CreateTask(uint8 Copy_u8Priority, void (*Copy_pvTaskFunc)(void), uint16 Copy_u16Periodicity, uint16 Copy_u16FirstDelay);
ErrorState_t RTOS_SuspendTask(uint8 Copy_u8Priority);
ErrorState_t RTOS_ResumeTask(uint8 Copy_u8Priority);
ErrorState_t RTOS_DeleteTask(uint8 Copy_u8Priority);


#endif /* KERNEL_INTERFACE_H_ */

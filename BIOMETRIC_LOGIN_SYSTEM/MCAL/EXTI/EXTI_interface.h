/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : EXTI                 *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef EXTI_EXTI_INTERFACE_H_
#define EXTI_EXTI_INTERFACE_H_


typedef enum{
	LOW_LEVEL=0,
	ANY_LOGIC_CHANGE= 1,
	FALLING_EDGE= 2,
	RISING_EDGE= 3
}TriggerEdge_t;

typedef enum{
	EX_INT0= 0,
	EX_INT1= 2,
	EX_INT2= 3
}EXInterruptSource_t;


ErrorState_t EXTI_Enable(EXInterruptSource_t copy_u8ExtiNum, TriggerEdge_t copy_u8EdgeSense);
ErrorState_t EXTI_SetCallBack(EXInterruptSource_t copy_u8ExtiNum, void(*LocalPtr)(void));
ErrorState_t EXTI_Disable(EXInterruptSource_t copy_u8ExtiNum);


#endif /* EXTI_EXTI_INTERFACE_H_ */

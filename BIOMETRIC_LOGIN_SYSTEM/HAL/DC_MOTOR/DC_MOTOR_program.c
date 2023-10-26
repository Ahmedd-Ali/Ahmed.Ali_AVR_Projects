/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : HAL                  **********************/
/****************    SWC       : DC MOTOR             *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "MEM_MAP.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "TIMER1_interface.h"
#include "DC_MOTOR_config.h"
#include "DC_MOTOR_private.h"
#include "DC_MOTOR_interface.h"

ErrorState_t DC_MOTOR_Init(void)
{
	ErrorState_t ret= E_OK;

	return ret;
}


ErrorState_t DC_MOTOR_On(void)
{
	ErrorState_t ret= E_OK;

	return ret;
}


ErrorState_t DC_MOTOR_Off(void)
{
	ErrorState_t ret= E_OK;

	return ret;
}


ErrorState_t SERVO_MOTOR_Init(void)
{
	ErrorState_t ret= E_OK;

	ret|= TIMER1_Init(TIMER1_FAST_PWM_OCR1A_TOP, TIMER1_PRESCALLER_8);
	ret|= TIMER1_OC1B_Mode(OC1_NON_INVERTING);
	TIMER1_SET_OCA(39999);
	ret|= TIMER1_Start();

	return ret;
}


ErrorState_t SERVO_MOTOR_Set_Angle(uint8 angle)
{
	ErrorState_t ret= E_OK;

	TIMER1_SET_OCB((((uint16)angle * 20) + 1099)) ;

	return ret;
}




/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : HAL                  **********************/
/****************    SWC       : STEPPER_MOTOR        *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/


#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "STEPPER_config.h"
#include "STEPPER_private.h"
#include "STEPPER_interface.h"



//ErrorState_t STEPPER_Rotate(Stpr_direction_t Direction, uint16 Angle)
//{
//	ErrorState_t ret= E_OK;
//
//	uint16 Iterator_Pins;
//	uint16 Iterator_Steps;
//	uint16 Steps= (uint16)(((uint32)Angle * 2048UL)/360UL);
//	uint8  Stepper_ArrSteps[4]=STEPS;
//
//	switch(Direction)
//	{
//	case CW_DICECTION:
//
//		for(Iterator_Steps=0, Iterator_Pins= 0; Iterator_Steps<Steps; Iterator_Steps++, Iterator_Pins++)
//		{
//			if(Iterator_Pins == 4)
//			{
//				Iterator_Pins= 0;
//			}
//			else
//			{
//				/* Do Nothing */
//			}
//			DIO_WritePin(STPR_PIN1, ((Stepper_ArrSteps[Iterator_Pins]>>3)&1));
//			DIO_WritePin(STPR_PIN2, ((Stepper_ArrSteps[Iterator_Pins]>>2)&1));
//			DIO_WritePin(STPR_PIN3, ((Stepper_ArrSteps[Iterator_Pins]>>1)&1));
//			DIO_WritePin(STPR_PIN4, ((Stepper_ArrSteps[Iterator_Pins]>>0)&1));
//			_delay_ms(DELAY);
//		}
//		break;
//
//	case CCW_DICECTION:    //turn 1 full_step in C.C.W. direction
//		for(Iterator_Steps=0, Iterator_Pins= 0; Iterator_Steps<Steps; Iterator_Steps++, Iterator_Pins++)
//		{
//			if(Iterator_Pins == 4)
//			{
//				Iterator_Pins= 0;
//			}
//			else
//			{
//				/* Do Nothing */
//			}
//			DIO_WritePin(STPR_PIN1, ((Stepper_ArrSteps[Iterator_Pins]>>0)&1));
//			DIO_WritePin(STPR_PIN2, ((Stepper_ArrSteps[Iterator_Pins]>>1)&1));
//			DIO_WritePin(STPR_PIN3, ((Stepper_ArrSteps[Iterator_Pins]>>2)&1));
//			DIO_WritePin(STPR_PIN4, ((Stepper_ArrSteps[Iterator_Pins]>>3)&1));
//			_delay_ms(DELAY);
//		}
//		break;
//
//	default:
//		ret= E_OUT_OF_RANGE;
//		break;
//	}
//
//	return ret;
//}


/************************************************************************/

uint16 Iterator_Pins= 0;
uint16 Iterator_Steps= 0;
uint16 Steps= 0;
uint8  Stepper_ArrSteps[4]=STEPS;

ErrorState_t STEPPER_Rotate_OneStep_CW(void)
{
	ErrorState_t ret= E_OK;

	if(Iterator_Pins == 4)
	{
		Iterator_Pins= 0;
	}
	else
	{
		/* Do Nothing */
	}

	//Iterator_Steps<Steps

	ret|= DIO_WritePin(STPR_PIN1, ((Stepper_ArrSteps[Iterator_Pins]>>3)&1));
	ret|= DIO_WritePin(STPR_PIN2, ((Stepper_ArrSteps[Iterator_Pins]>>2)&1));
	ret|= DIO_WritePin(STPR_PIN3, ((Stepper_ArrSteps[Iterator_Pins]>>1)&1));
	ret|= DIO_WritePin(STPR_PIN4, ((Stepper_ArrSteps[Iterator_Pins]>>0)&1));
	Iterator_Pins++;

	return ret;
}


ErrorState_t STEPPER_Rotate_OneStep_CCW(void)
{
	ErrorState_t ret= E_OK;

	if(Iterator_Pins == 4)
	{
		Iterator_Pins= 0;
	}
	else
	{
		/* Do Nothing */
	}
	ret|= DIO_WritePin(STPR_PIN1, ((Stepper_ArrSteps[Iterator_Pins]>>0)&1));
	ret|= DIO_WritePin(STPR_PIN2, ((Stepper_ArrSteps[Iterator_Pins]>>1)&1));
	ret|= DIO_WritePin(STPR_PIN3, ((Stepper_ArrSteps[Iterator_Pins]>>2)&1));
	ret|= DIO_WritePin(STPR_PIN4, ((Stepper_ArrSteps[Iterator_Pins]>>3)&1));
	Iterator_Pins++;

	return ret;
}


ErrorState_t STEPPER_Rotate(Stpr_direction_t Direction, uint16 Angle)
{
	ErrorState_t ret= E_OK;

	Steps= (uint16)(((uint32)Angle * 2048UL)/360UL);

	switch(Direction)
	{
	case CW_DICECTION:

		for(Iterator_Steps=0, Iterator_Pins= 0; Iterator_Steps<Steps; Iterator_Steps++, Iterator_Pins++)
		{
			ret|= STEPPER_Rotate_OneStep_CW();
		}
		break;

	case CCW_DICECTION:    //turn 1 full_step in C.C.W. direction
		for(Iterator_Steps=0, Iterator_Pins= 0; Iterator_Steps<Steps; Iterator_Steps++, Iterator_Pins++)
		{
			ret|= STEPPER_Rotate_OneStep_CCW();
		}
		break;

	default:
		ret= E_OUT_OF_RANGE;
		break;
	}

	return ret;
}

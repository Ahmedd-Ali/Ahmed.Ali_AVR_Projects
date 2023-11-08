/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : EXTI                 *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

/************************************ Includes **********************************/

#include "STD_TYPES.h"
#include "MEM_MAP.h"
#include "BIT_MATH.h"
#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_interface.h"


/************************* Pointer to functions to be assigned to ISR **********************/

static void (*INT0_Fptr) (void)= NULL;
static void (*INT1_Fptr) (void)= NULL;
static void (*INT2_Fptr) (void)= NULL;


/************************************Enable/Disable functions***********************************/

ErrorState_t EXTI_Enable(EXInterruptSource_t copy_u8ExtiNum, TriggerEdge_t copy_u8EdgeSense)
{
	ErrorState_t ret= E_OK;

	switch(copy_u8ExtiNum){
		case EX_INT0:
		switch(copy_u8EdgeSense)
		{
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;

			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;

			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;

			case RISING_EDGE:
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;

			default:
				ret= E_OUT_OF_RANGE;
				break;
		}
		SET_BIT(GICR,INT0);
		break;

		case EX_INT1:
		switch(copy_u8EdgeSense){
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			case ANY_LOGIC_CHANGE:
			SET_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;

			default:
				ret= E_OUT_OF_RANGE;
				break;
		}
		SET_BIT(GICR,INT1);
		break;

		case EX_INT2:
		switch(copy_u8EdgeSense){
			case FALLING_EDGE:
			CLR_BIT(MCUCSR,ISC2);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCSR,ISC2);
			break;


			default:
			CLR_BIT(MCUCSR,ISC2);
			ret= E_OUT_OF_RANGE;
			break;
		}
		SET_BIT(GICR,INT2);
		break;

		default:
			ret= E_OUT_OF_RANGE;
			break;
	}

	return ret;
}


ErrorState_t EXTI_Disable(EXInterruptSource_t copy_u8ExtiNum)
{
	ErrorState_t ret= E_OK;

	switch(copy_u8ExtiNum){
		case EX_INT0:
		CLR_BIT(GICR,INT0);
		break;
		case EX_INT1:
		CLR_BIT(GICR,INT1);
		break;
		case EX_INT2:
		CLR_BIT(GICR,INT2);
		break;

		default:
			ret= E_OUT_OF_RANGE;
			break;
	}

	return ret;
}


/*********************************** Call back functions ***************************************/

ErrorState_t EXTI_SetCallBack(EXInterruptSource_t copy_u8ExtiNum, void(*LocalPtr)(void))
{
	ErrorState_t ret= E_OK;

	switch(copy_u8ExtiNum){
		case EX_INT0:
		INT0_Fptr=LocalPtr;
		break;
		case EX_INT1:
		INT1_Fptr=LocalPtr;
		break;
		case EX_INT2:
		INT2_Fptr=LocalPtr;
		break;

		default:
			ret= E_OUT_OF_RANGE;
			break;
	}

	return ret;
}


/**************************************************************************/

/********************************* ISR ************************************/

ISR(INT0_vect)
{

	if (INT0_Fptr != NULL)
	{
		INT0_Fptr();
	}
	else
	{
		/* Do Nothing */
	}
}

ISR(INT1_vect)
{
	if (INT1_Fptr != NULL)
	{
		INT1_Fptr();
	}
	else
	{
		/* Do Nothing */
	}
}

ISR(INT2_vect)
{
	if (INT2_Fptr != NULL)
	{
		INT2_Fptr();
	}
	else
	{
		/* Do Nothing */
	}
}

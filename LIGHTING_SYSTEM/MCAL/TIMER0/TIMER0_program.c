/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : TIMER0               *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "MEM_MAP.h"
#include "BIT_MATH.h"
#include "TIMER0_config.h"
#include "TIMER0_interface.h"
#include "TIMER0_private.h"

#include "LCD_interface.h"

/***********************************************************************/
/*                            TIMER0                                   */
/***********************************************************************/

static TIMER0Scaler_t TIMER0_Scaler_Value;

void(*TIMER0_OV_pFunc)(void) = NULL;
void(*TIMER0_OC_pFunc)(void) = NULL;

/**
 *
 * @brief
 * @param timerMode
 * @param scaler
 * @return
 */

ErrorState_t TIMER0_Init(TIMER0Mode_t timerMode,TIMER0Scaler_t scaler)
{
	ErrorState_t ret= E_OK;

	TIMER0_Scaler_Value= scaler;
	TCCR0&= TIMER0_RESET_MODE_MASK;
	/* Set Mode */
	switch(timerMode)
	{
	case TIMER0_NORMAL_MODE:
		TCCR0|= TIMER0_NORMAL_MODE_MASK;
		break;

	case TIMER0_PHASECORRECT_MODE:
		TCCR0|= TIMER0_PHASECORRECT_MODE_MASK;
		break;

	case TIMER0_CTC_MODE:
		TCCR0|= TIMER0_CTC_MODE_MASK;
		break;

	case TIMER0_FASTPWM_MODE:
		TCCR0|= TIMER0_FASTPWM_MODE_MASK;
		break;

	default:
		ret= E_OUT_OF_RANGE;
		break;
	}

	return ret;
}


ErrorState_t TIMER0_OC0Mode(OC0Mode_t OC0_mode)
{
	ErrorState_t ret= E_OK;

	/* Set OC Mode */
	TCCR0&= OC0_RESET_MODE_MASK;
	switch(OC0_mode)
	{
	case OC0_DISCONNECTED:
		TCCR0|= OC0_DISCONNECTED_MASK;
		break;

	case OC0_TOGGLE:
		TCCR0|= OC0_TOGGLE_MASK;
		break;

	case OC0_NON_INVERTING:
		TCCR0|= OC0_NON_INVERTING_MASK;
		break;

	case OC0_INVERTING:
		TCCR0|= OC0_INVERTING_MASK;
		break;

	default:
		ret= E_OUT_OF_RANGE;
		break;
	}

	return ret;
}


ErrorState_t TIMER0_Start(void)
{
	ErrorState_t ret= E_OK;

	TCCR0&= TIMER0_RESET_PRESCALER_MASK; //0b11111000
	TCCR0|= TIMER0_Scaler_Value;

	return ret;
}


ErrorState_t TIMER0_Stop(void)
{
	ErrorState_t ret= E_OK;

	TCCR0&= TIMER0_RESET_PRESCALER_MASK; //0b11111000
	TCCR0|= TIMER0_STOP;

	return ret;
}


/*************** CallBack Functions **************/

ErrorState_t TIMER0_OV_SetCallBack(void(*local_fptr)(void))
{
	ErrorState_t ret= E_OK;

	if(local_fptr == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		TIMER0_OV_pFunc= local_fptr;
	}

	return ret;
}


ErrorState_t TIMER0_OC_SetCallBack(void(*local_fptr)(void))
{
	ErrorState_t ret= E_OK;

	if(local_fptr == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		TIMER0_OC_pFunc= local_fptr;
	}

	return ret;
}

/*********************************************************/

volatile static uint16 NofOverFlow= 0;
static void(*Fptr_TIMER0)(void);

static void TIMER0_IntFunc(void)
{
	static uint16 c=0;
	c++;
	if (c == NofOverFlow)
	{
		c=0;
		Fptr_TIMER0();
	}
	else
	{
		/* Misra: Do Nothing */
	}
}

ErrorState_t TIMER0_SetInterruptTime_ms(uint16 timeDelay,void(*LocalFptr)(void))
{
	ErrorState_t ret= E_OK;

	if(NULL == LocalFptr)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		TIMER0_SET_OC(249);
		NofOverFlow= (uint16)timeDelay;
		Fptr_TIMER0= LocalFptr;
		TIMER0_OC_SetCallBack(TIMER0_IntFunc);
		TIMER0_OC_INTERRUPT_ENABLE();
	}

	return ret;
}

/************************* ISRS *************************/

ISR(TIMER0_OVF_vect)
{
	if(TIMER0_OV_pFunc != NULL)
	{
		TIMER0_OV_pFunc();
	}
	else
	{
		/* Do Nothing */
	}
}


ISR(TIMER0_OC_vect)
{
	if(TIMER0_OC_pFunc != NULL)
	{
		TIMER0_OC_pFunc();
	}
	else
	{
		/* Do Nothing */
	}
}


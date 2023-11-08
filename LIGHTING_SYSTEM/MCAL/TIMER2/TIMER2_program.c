/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : TIMER2               *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/


#include "STD_TYPES.h"
#include "MEM_MAP.h"
#include "BIT_MATH.h"
#include "TIMER2_config.h"
#include "TIMER2_private.h"
#include "TIMER2_interface.h"

/* Prescaler Value */
static TIMER2Scaler_t TIMER2_Scaler_Value;

/* Call Back Pointers to Function */
static void (*Timer2_OVF_Fptr) (void)= NULL;
static void (*Timer2_OC2_Fptr) (void)= NULL;

ErrorState_t TIMER2_Init(TIMER2Mode_t mode,TIMER2Scaler_t scaler)
{
	ErrorState_t ret= E_OK;

	TIMER2_Scaler_Value= scaler;

	switch (mode)
	{
	case TIMER2_NORMAL_MODE:
		CLR_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break;
	case TIMER2_PHASECORRECT_MODE:
		SET_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break;
	case TIMER2_CTC_MODE:
		CLR_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		break;
	case TIMER2_FASTPWM_MODE:
		SET_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		break;
	}

	//TCCR2&=0XF8;//0b11111000
	//TCCR2|=scaler;

	return ret;
}


ErrorState_t TIMER2_OC2Mode(OC2Mode_t mode)
{
	ErrorState_t ret= E_OK;

	switch (mode)
	{
	case OC2_DISCONNECTED:
		CLR_BIT(TCCR2,COM20);
		CLR_BIT(TCCR2,COM21);
		break;
	case OC2_TOGGLE:
		SET_BIT(TCCR2,COM20);
		CLR_BIT(TCCR2,COM21);
		break;
	case OC2_NON_INVERTING:
		CLR_BIT(TCCR2,COM20);
		SET_BIT(TCCR2,COM21);
		break;
	case OC2_INVERTING:
		SET_BIT(TCCR2,COM20);
		SET_BIT(TCCR2,COM21);
		break;
	}

	return ret;
}

ErrorState_t TIMER2_OVF_SetCallBack(void(*local_fptr)(void))
{
	ErrorState_t ret= E_OK;

	Timer2_OVF_Fptr= local_fptr;

	return ret;
}

ErrorState_t TIMER2_OC2_SetCallBack(void(*local_fptr)(void))
{
	ErrorState_t ret= E_OK;

	Timer2_OC2_Fptr= local_fptr;

	return ret;
}
/************ Start/Stop Timer *******************/

ErrorState_t TIMER2_Start(void)
{
	ErrorState_t ret= E_OK;

	TCCR2&=0XF8;//0b11111000
	TCCR2|=TIMER2_Scaler_Value;

	return ret;
}


ErrorState_t TIMER2_Stop(void)
{
	ErrorState_t ret= E_OK;

	TCCR2&=0XF8;//0b11111000
	TCCR2|= TIMER2_STOP;

	return ret;
}


/********************** Set Delay Time ************************/
volatile static uint16 NofOverFlow= 0;
static void(*Fptr_TIMER2)(void);

static void TIMER2_IntFunc(void)
{
	static uint16 c=0;
	c++;
	if (c == NofOverFlow)
	{
		c=0;
		Fptr_TIMER2();
	}
	else
	{
		/* Misra: Do Nothing */
	}
}

ErrorState_t TIMER2_SetInterruptTime_ms(uint16 timeDelay,void(*LocalFptr)(void))
{
	ErrorState_t ret= E_OK;

	if(NULL == LocalFptr)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		ret|= TIMER2_Init(TIMER2_CTC_MODE, TIMER2_SCALER_64);
		TIMER2_SET_OC(249);
		NofOverFlow= (uint16)timeDelay;
		Fptr_TIMER2= LocalFptr;
		TIMER2_OC2_SetCallBack(TIMER2_IntFunc);
		TIMER2_OC_INTERRUPT_ENABLE();
	}

	return ret;
}
/************************ ISRs ***********************/


ISR(TIMER2_OVF_vect)
{
	if(Timer2_OVF_Fptr!= NULL)
	{
		Timer2_OVF_Fptr();
	}
	else
	{
		/* Misra : Do Nothing */
	}
}

ISR(TIMER2_COMP_vect)
{
	if(Timer2_OC2_Fptr!= NULL)
	{
		Timer2_OC2_Fptr();
	}
	else
	{
		/* Misra : Do Nothing */
	}
}


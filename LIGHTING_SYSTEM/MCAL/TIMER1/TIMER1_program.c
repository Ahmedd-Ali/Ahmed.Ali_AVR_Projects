/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : TIMER1               *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "MEM_MAP.h"
#include "BIT_MATH.h"
#include "TIMER1_config.h"
#include "TIMER1_private.h"
#include "TIMER1_interface.h"


/**********************************************************************************************************/
/*                                              TIMER 1                                                   */
/**********************************************************************************************************/


/**********************************************************************************************************/
/*                                            Global Variables                                            */
/**********************************************************************************************************/
static TIMER1_Scaler_t TIMER1_Scaler_Value;

void(*TIMER1_OV_pFunc) (void) = NULL;
void(*TIMER1_OCA_pFunc)(void) = NULL;
void(*TIMER1_OCB_pFunc)(void) = NULL;
void(*TIMER1_ICU_pFunc)(void) = NULL;

/**********************************************************************************************************/
/*                                        Functions Definitions                                           */
/**********************************************************************************************************/
ErrorState_t TIMER1_Init(TIMER1_Mode_t Timer_Mode, TIMER1_Scaler_t Scaler)
{
	ErrorState_t ret= E_OK;

	/* Setting TIMER1 Mode and Saving Desired Scaler Value in a Global Variable till the user start the timer */
	TIMER1_Scaler_Value = Scaler;

	switch(Timer_Mode)
	{
	case TIMER1_NORMAL_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_PHASE_CORRECT_PWM_8_BIT:
		SET_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_PHASE_CORRECT_PWM_9_BIT:
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_PHASE_CORRECT_PWM_10_BIT:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_CTC_OCR1A_TOP:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_FAST_PWM_8_BIT:
		SET_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_FAST_PWM_9_BIT:
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_FAST_PWM_10_BIT:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_PHASE_FREQ_CORRECT_ICR1_TOP:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_PHASE_FREQ_CORRECT_OCR1A_TOP:
		SET_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_PHASE_CORRECT_PWM_ICR1_TOP:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_PHASE_CORRECT_PWM_OCR1A_TOP:
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_CTC_ICR1_TOP:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_FAST_PWM_ICR1_TOP:
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;

	case TIMER1_FAST_PWM_OCR1A_TOP:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;

	default:
		ret= E_OUT_OF_RANGE;
		break;
	}

	return ret;
}

ErrorState_t TIMER1_ICU_Init(void)
{
	ErrorState_t ret= E_OK;

	/* Set Trigger Source to Rising Edge Initially */
	SET_BIT(TCCR1B,ICES1);
	/* Enable Input Capture Interrupt */
	SET_BIT(TIMSK,TICIE1);

	return ret;
}

ErrorState_t TIMER1_ICU_SetTriggerEdge(ICU_TriggerEdge_t Edge)
{
	ErrorState_t ret= E_OK;

	if(Edge == ICU_FALLING_EDGE)
	{
		CLR_BIT(TCCR1B,ICES1);
	}
	else if(Edge == ICU_RISING_EDGE)
	{
		SET_BIT(TCCR1B,ICES1);
	}
	else
	{
		ret= E_OUT_OF_RANGE;
	}

	return ret;
}


ErrorState_t TIMER1_Start(void)
{
	ErrorState_t ret= E_OK;

	/* Start Counter Register by loading Prescaler Value */
	TCCR1B &= TIMER1_STOP_MASK;
	TCCR1B |= TIMER1_Scaler_Value;

	return ret;
}


ErrorState_t TIMER1_Stop(void)
{
	ErrorState_t ret= E_OK;

	/* Start Counter Register by Resetting first 3 bits in TCCR0 */
	TCCR1B &= TIMER1_STOP_MASK;

	return ret;
}


ErrorState_t TIMER1_ReadTimerValue(uint16 * pdata)
{
	ErrorState_t ret= E_OK;

	if(pdata == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		*pdata= TCNT1;
	}

	return ret;
}

ErrorState_t TIMER1_OC1A_Mode(OC1_Mode_t OC1_Mode)
{
	ErrorState_t ret= E_OK;

	/* Setting Compare Output Mode */
	switch(OC1_Mode)
	{
	case OC1_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;

	case OC1_TOGGLE:
		SET_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;

	case OC1_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;

	case OC1_INVERTING:
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;

	default:
		ret= E_OUT_OF_RANGE;
		break;
	}

	return ret;
}

ErrorState_t TIMER1_OC1B_Mode(OC1_Mode_t OC1_Mode)
{
	ErrorState_t ret= E_OK;

	/* Setting Compare Output Mode */
	switch(OC1_Mode)
	{
	case OC1_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;

	case OC1_TOGGLE:
		SET_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;

	case OC1_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;

	case OC1_INVERTING:
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;

	default:
		ret= E_OUT_OF_RANGE;
		break;
	}

	return ret;
}

ErrorState_t TIMER1_OV_InterruptEnable(void)
{
	ErrorState_t ret= E_OK;

	SET_BIT(TIMSK,TOIE1);

	return ret;
}

ErrorState_t TIMER1_OV_InterruptDisable(void)
{
	ErrorState_t ret= E_OK;

	CLR_BIT(TIMSK,TOIE1);

	return ret;
}

ErrorState_t TIMER1_OCA_InterruptEnable(void)
{
	ErrorState_t ret= E_OK;

	SET_BIT(TIMSK,OCIE1A);

	return ret;
}

ErrorState_t TIMER1_OCA_InterruptDisable(void)
{
	ErrorState_t ret= E_OK;

	CLR_BIT(TIMSK,OCIE1A);

	return ret;
}

ErrorState_t TIMER1_OCB_InterruptEnable(void)
{
	ErrorState_t ret= E_OK;

	SET_BIT(TIMSK,OCIE1B);

	return ret;
}

ErrorState_t TIMER1_OCB_InterruptDisable(void)
{
	ErrorState_t ret= E_OK;

	CLR_BIT(TIMSK,OCIE1B);

	return ret;
}

ErrorState_t TIMER1_ICU_InterruptEnable(void)
{
	ErrorState_t ret= E_OK;

	SET_BIT(TIMSK,TICIE1);

	return ret;
}

ErrorState_t TIMER1_ICU_InterruptDisable(void)
{
	ErrorState_t ret= E_OK;

	CLR_BIT(TIMSK,TICIE1);

	return ret;
}

ErrorState_t TIMER1_OV_SetCallBack(void(*Local_fPtr)(void))
{
	ErrorState_t ret= E_OK;

	if(Local_fPtr != NULL)
	{
		TIMER1_OV_pFunc = Local_fPtr;
	}
	else
	{
		ret= E_NULL_PTR;
	}

	return ret;
}

ErrorState_t TIMER1_OCA_SetCallBack(void(*Local_fPtr)(void))
{
	ErrorState_t ret= E_OK;

	if(Local_fPtr != NULL)
	{
		TIMER1_OCA_pFunc = Local_fPtr;
	}
	else
	{
		ret= E_NULL_PTR;
	}

	return ret;
}

ErrorState_t TIMER1_OCB_SetCallBack(void(*Local_fPtr)(void))
{
	ErrorState_t ret= E_OK;

	if(Local_fPtr != NULL)
	{
		TIMER1_OCB_pFunc = Local_fPtr;
	}
	else
	{
		ret= E_NULL_PTR;
	}

	return ret;
}

ErrorState_t TIMER1_ICU_SetCallBack(void(*Local_fPtr)(void))
{
	ErrorState_t ret= E_OK;

	if(Local_fPtr != NULL)
	{
		TIMER1_ICU_pFunc = Local_fPtr;
	}
	else
	{
		ret= E_NULL_PTR;
	}

	return ret;
}


/******************* Set Interrupt Delay Normal Mode ************************/

volatile static uint16 NumOfOverFLow= 0;
volatile static uint16 PreloadValue= 0;

static void(*fptr_timer1_Normal)(void);

static void TIMER1_delayNORMAL_ISR(void)
{
	static uint32 c=0;
	c++;
	TCNT1+= PreloadValue;
	if (c == NumOfOverFLow)
	{
		c=0;
		fptr_timer1_Normal();
	}
}

ErrorState_t TIMER1_setDelayTimeMilliSec_Normal(uint16 delay_ms, void(*LocalFptr)(void))
{
	ErrorState_t ret= E_OK;

	switch(TIMER1_Scaler_Value)
	{
	case TIMER1_No_Prescaller:
		PreloadValue= 49535;
		TCNT1= PreloadValue;
		NumOfOverFLow= delay_ms;
		break;

	case TIMER1_PRESCALLER_8:
		if((delay_ms >= 10) && (delay_ms % 10 == 0))
		{
			PreloadValue= 45535;
			TCNT1= PreloadValue;
			NumOfOverFLow= (delay_ms / 10);
		}
		else
		{
			PreloadValue= 63535;
			TCNT1= PreloadValue;
			NumOfOverFLow= delay_ms;
		}

		break;

	case TIMER1_PRESCALLER_64:
		if((delay_ms >= 100) && (delay_ms % 100 == 0))
		{
			PreloadValue= 40535;
			TCNT1= PreloadValue;
			NumOfOverFLow= (delay_ms / 100);
		}
		else if((delay_ms >= 10) && (delay_ms % 10 == 0))
		{
			PreloadValue= 63035;
			TCNT1= PreloadValue;
			NumOfOverFLow= (delay_ms / 10);
		}
		else
		{
			PreloadValue= 65285;
			TCNT1= PreloadValue;
			NumOfOverFLow= delay_ms;
		}
		break;

	default:
		ret= E_OUT_OF_RANGE;
		break;
	}
	fptr_timer1_Normal= LocalFptr;
	ret|= TIMER1_OV_InterruptEnable();
	ret|= TIMER1_OV_SetCallBack(TIMER1_delayNORMAL_ISR);

	return ret;
}



ErrorState_t TIMER1_setDelayTimeSec_Normal(uint16 delay_s, void(*LocalFptr)(void))
{
	ErrorState_t ret= E_OK;

	if(LocalFptr == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		switch(TIMER1_Scaler_Value)
		{
		case TIMER1_No_Prescaller:
			PreloadValue= 49535;
			TCNT1= PreloadValue;
			NumOfOverFLow= (delay_s * 1000);
			break;

		case TIMER1_PRESCALLER_8:
			PreloadValue= 45535;
			TCNT1= PreloadValue;
			NumOfOverFLow= (delay_s * 100);
			break;

		case TIMER1_PRESCALLER_64:
			PreloadValue= 40535;
			TCNT1= PreloadValue;
			NumOfOverFLow= (delay_s * 10);
			break;

		case TIMER1_PRESCALLER_256:
			PreloadValue= 3035;
			TCNT1= PreloadValue;
			NumOfOverFLow= delay_s;
			break;

		case TIMER1_PRESCALLER_1024:
			PreloadValue= 49910;
			TCNT1= PreloadValue;
			NumOfOverFLow= delay_s;
			break;

		default:
			ret= E_OUT_OF_RANGE;
			break;
		}
		fptr_timer1_Normal= LocalFptr;
		ret|= TIMER1_OV_SetCallBack(TIMER1_delayNORMAL_ISR);
		ret|= TIMER1_OV_InterruptEnable();
	}

	return ret;
}

/******************* Set Interrupt Delay CTC Mode ************************/
static uint16 NumOfCompMatch= 0;

static void(*fptr_timer1_CTC)(void);

static void TIMER1_delayCTC_ISR(void)
{
	static uint32 c=0;
	c++;
	if (c == NumOfCompMatch)
	{
		c=0;
		fptr_timer1_CTC();
	}
}


ErrorState_t TIMER1_setDelayTimeMilliSec_CTC(uint16 delay_ms, void(*LocalFptr)(void))
{
	ErrorState_t ret= E_OK;

	if(LocalFptr == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		switch(TIMER1_Scaler_Value)
		{
		case TIMER1_No_Prescaller:
			OCR1A= 15999;
			NumOfCompMatch= delay_ms;
			break;

		case TIMER1_PRESCALLER_8:
			if((delay_ms >= 10) && (delay_ms % 10 == 0))
			{
				OCR1A= 19999;
				NumOfCompMatch= delay_ms / 10;
			}
			else
			{
				OCR1A= 1999;
				NumOfCompMatch= delay_ms;
			}
			break;

		case TIMER1_PRESCALLER_64:
			if((delay_ms >= 100) && (delay_ms % 100 == 0))
			{
				OCR1A= 24999;
				NumOfCompMatch= delay_ms / 100;
			}
			else if((delay_ms >= 10) && (delay_ms % 10 == 0))
			{
				OCR1A= 2499;
				NumOfCompMatch= delay_ms / 10;
			}
			else
			{
				OCR1A= 249;
				NumOfCompMatch= delay_ms;
			}
			break;

		default:
			ret= E_OUT_OF_RANGE;
			break;
		}
		fptr_timer1_CTC= LocalFptr;
		ret|= TIMER1_OCA_SetCallBack(TIMER1_delayCTC_ISR);
		ret|= TIMER1_OCA_InterruptEnable();
	}

	return ret;
}

ErrorState_t TIMER1_setDelayTimeSec_CTC(uint16 delay_s, void(*LocalFptr)(void))
{
	ErrorState_t ret= E_OK;

	if(LocalFptr == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		switch(TIMER1_Scaler_Value)
		{
		case TIMER1_No_Prescaller:
			OCR1A= 15999;
			NumOfCompMatch= delay_s * 1000;
			break;

		case TIMER1_PRESCALLER_8:
			OCR1A= 19999;
			NumOfCompMatch= delay_s * 100;
			break;

		case TIMER1_PRESCALLER_64:
			OCR1A= 24999;
			NumOfCompMatch= delay_s * 10;
			break;

		case TIMER1_PRESCALLER_256:
			OCR1A= 62499;
			NumOfCompMatch= delay_s;
			break;

		case TIMER1_PRESCALLER_1024:
			OCR1A= 15624;
			NumOfCompMatch= delay_s;
			break;

		default:
			ret= E_OUT_OF_RANGE;
			break;
		}
		fptr_timer1_CTC= LocalFptr;
		ret|= TIMER1_OCA_SetCallBack(TIMER1_delayCTC_ISR);
		ret|= TIMER1_OCA_InterruptEnable();
	}

	return ret;
}


/******************** ISRs ********************/

ISR(TIMER1_OVF_vect)
{
	if(TIMER1_OV_pFunc != NULL)
	{
		TIMER1_OV_pFunc();
	}
	else
	{
		/* Do Nothing */
	}
}

ISR(TIMER1_OCA_vect)
{
	if(TIMER1_OCA_pFunc != NULL)
	{
		TIMER1_OCA_pFunc();
	}
	else
	{
		/* Do Nothing */
	}
}

ISR(TIMER1_OCB_vect)
{
	if(TIMER1_OCB_pFunc != NULL)
	{
		TIMER1_OCB_pFunc();
	}
	else
	{
		/* Do Nothing */
	}
}


ISR(TIMER1_ICU_vect)
{
	if(TIMER1_ICU_pFunc != NULL)
	{
		TIMER1_ICU_pFunc();
	}
	else
	{
		/* Do Nothing */
	}
}

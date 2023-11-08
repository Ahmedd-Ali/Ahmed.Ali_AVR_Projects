/***************************************************************************************/
/***************************************************************************************/
/**************************   Author : Ahmed Ali        ********************************/
/**************************   Module : RGB              ********************************/
/**************************   Layer  : HAL       	    ********************************/
/**************************   Version: 1.00             ********************************/
/***************************************************************************************/
/***************************************************************************************/

/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%    Inclusions    %%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

#include "STD_TYPES.h"
#include "MEM_MAP.h"
#include "DIO_interface.h"
#include "TIMER2_interface.h"
#include "TIMER1_interface.h"
#include "RGB_Cfg.h"
#include "RGB_Private.h"
#include "RGB_Interface.h"

/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%    Functions     %%%%%%%%%%%%%%%%%%%%%%%%%%%%% */


ErrorState_t RGB_Init(void)
{
	ErrorState_t ret= E_OK;

	// Timer initialization
	ret|= TIMER2_Init(TIMER2_FASTPWM_MODE, TIMER2_SCALER_64);
	ret|= TIMER1_Init(TIMER1_FAST_PWM_ICR1_TOP, TIMER1_PRESCALLER_64);
	// Timer Output Compare unit initialization
	ret|= TIMER1_OC1A_Mode(OC1_INVERTING);
	ret|= TIMER1_OC1B_Mode(OC1_INVERTING);
	ret|= TIMER2_OC2Mode(OC2_INVERTING);
	// Set top for timer 1
	TIMER1_SET_ICU(255);
	// RGB initially disabled

	ret|= TIMER2_Start();
	ret|= TIMER1_Start();

	return ret;
}


static Color_type Applied_Color; // Shared with functions (File scope)

ErrorState_t RGB_Enable(void)
{
	ErrorState_t ret= E_OK;

	ret|= TIMER1_OC1A_Mode(OC1_INVERTING);
	ret|= TIMER1_OC1B_Mode(OC1_INVERTING);
	ret|= TIMER2_OC2Mode(OC2_INVERTING);
	ret|= RGB_SetColor(White);

	return ret;
}

ErrorState_t RGB_Disable(void)
{
	ErrorState_t ret= E_OK;

	/* To neglect Signal Spikes */
	ret|= TIMER2_OC2Mode(OC2_DISCONNECTED);
	ret|= DIO_WritePin(PIND7, HIGH);
	ret|= TIMER1_OC1A_Mode(OC1_DISCONNECTED);
	ret|= DIO_WritePin(PIND5, HIGH);
	ret|= TIMER1_OC1B_Mode(OC1_DISCONNECTED);
	ret|= DIO_WritePin(PIND4, HIGH);

	return ret;
}


ErrorState_t RGB_SetColor(Color_type color)
{
	ErrorState_t ret= E_OK;

	TIMER1_SET_OCA(Colors_Arr[color][RED_PHASE]);
	TIMER2_SET_OC (Colors_Arr[color][GREEN_PHASE]);
	TIMER1_SET_OCB(Colors_Arr[color][BLUE_PHASE]);
	Applied_Color= color;

	return ret;
}

/******************* Service **********************/

ErrorState_t RGB_SetIntensity(uint8 intensity)
{
	ErrorState_t ret= E_OK;
	uint8 red, green, blue;

	if(intensity >= MAX_INTENS)
	{
		//intensity= MAX_INTENS;
		ret|= RGB_SetColor(Applied_Color);
	}
	else
	{
		red   =  (Colors_Arr[Applied_Color][RED_PHASE]   / MAX_INTENS) * intensity;
		green =  (Colors_Arr[Applied_Color][GREEN_PHASE] / MAX_INTENS) * intensity;
		blue  =  (Colors_Arr[Applied_Color][BLUE_PHASE]  / MAX_INTENS) * intensity;

		TIMER1_SET_OCA(red);
		TIMER2_SET_OC (green);
		TIMER1_SET_OCB(blue);
	}

	return ret;
}


ErrorState_t RGB_SetIndexPhase(RGB_PHASE_type phase, uint8 index) // show mode
{
	ErrorState_t ret= E_OK;

	switch(phase)
	{
		case RED_PHASE:
			TIMER1_SET_OCA(index);
		break;

		case GREEN_PHASE:
			TIMER2_SET_OC (index);
		break;

		case BLUE_PHASE:
			TIMER1_SET_OCB(index);
		break;

		default:
			ret= E_OUT_OF_RANGE;
		break;
	}

	return ret;
}

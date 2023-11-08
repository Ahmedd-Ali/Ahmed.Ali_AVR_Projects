/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : APP                  **********************/
/****************    SWC       : LIGHTING_SYSTEM      *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/


#include "STD_TYPES.h"
#include "MEM_MAP.h"
#include "DIO_interface.h"
#include "TIMER0_interface.h"
#include "ADC_interface.h"
#include "Kernel_interface.h"
#include "LCD_interface.h"
#include "STEPPER_interface.h"
#include "RGB_Interface.h"
#include "BLUETOOTH_HC_05_interface.h"
#include "SENSORS_interface.h"
#include "LIGHTING_interface.h"

/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%   Definitions   %%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

static Light_State_t RGB_state= LIGHT_OFF;
LightShow_State_t LightShow_state= LIGHT_SHOW_OFF;
Garden_State_t Garden_state= GARDEN_LIGHTS_ON;


volatile static uint16 Stepper_Steps= 0;
volatile static Stpr_direction_t Stepper_Direction= 0;
volatile static uint16 Steps_Iterator= 0;
//static TASKS_State_t RGB_state= TASK_OFF;
volatile static uint8 LDR_FILTER_Reading= 0;
volatile static uint8 LDR_Displayed= 0;

static uint16 AvgLDR= 0;
static uint8 Counter= 0;
static	uint16 LDR_Reading= 0;


static void LDRFilter_ADC_AutoTrigger(void)
{
	POT_GetPercent(&LDR_Reading);
	AvgLDR+= (uint8) (100-LDR_Reading);
	Counter++;

	/* Reach Filter Max */
	if(Counter == LDR_FILTER_SIZE)
	{
		/* update average */
		LDR_FILTER_Reading = (uint8) (AvgLDR / LDR_FILTER_SIZE);
		AvgLDR= 0;
		/* reset counter */
		Counter = 0;
	}
	else
	{
		/* Do Nothing */
	}
}



ErrorState_t RTOS_System_Init_Task(void)
{
	ErrorState_t ret= E_OK;

	ret|= DIO_Init();
	ret|= ADC_AutoTrigger_Init(ADC_VCC, ADC_SCALER_128);
	ret|= TIMER0_Init(TIMER0_CTC_MODE, TIMER0_SCALER_64);
	ret|= TIMER0_OC0Mode(OC0_TOGGLE);
	TIMER0_SET_OC(250);
	ret|= TIMER0_OC_INTERRUPT_ENABLE();
	ret|= TIMER0_Start();
	ret|= BLUETOOTH_Init();
	ret|= BLUETOOTH_Start_Receive();
	ret|= RGB_Init();

	return ret;
}


static void STEPPER_Handler(void)
{
	Steps_Iterator= 0;
	Stepper_Steps= (uint16)((uint16)(Bluetooth_Buffer[1] - '0') * 2048UL);
	Stepper_Direction= Bluetooth_Buffer[2] - '0';
}
/*********************************************************/

static ErrorState_t Light_on_off(void)
{
	ErrorState_t ret= E_OK;

	switch(RGB_state)
	{
	case LIGHT_OFF:

		ret|= RGB_Enable();
		RGB_state= LIGHT_ON;
		break;

	case LIGHT_ON:

		ret|= RGB_Disable();
		RGB_state= LIGHT_OFF;
		break;

	default:
		ret= E_OUT_OF_RANGE;
		break;
	}

	return ret;
}

static ErrorState_t Light_color(void)
{
	ErrorState_t ret= E_OK;

	if(RGB_state == LIGHT_ON)
	{
		Color_type Color= Bluetooth_Buffer[2]-'1';
		ret|= RGB_SetColor(Color);
	}
	else
	{
		ret= E_NOT_OK;
	}

	return ret;
}

static ErrorState_t Light_Intensity(void)
{
	ErrorState_t ret= E_OK;

	if(RGB_state == LIGHT_ON)
	{
		uint8 Intensity= Bluetooth_Buffer[2]-'0';
		ret|= RGB_SetIntensity(Intensity);
	}
	else
	{
		ret= E_NOT_OK;
	}

	return ret;
}

static ErrorState_t LightShow_on_off(void)
{
	ErrorState_t ret= E_OK;

	switch(LightShow_state)
	{
	case LIGHT_SHOW_OFF:
		LightShow_state= LIGHT_SHOW_ON;
		break;

	case LIGHT_SHOW_ON:
		LightShow_state= LIGHT_SHOW_OFF;
		break;

	default:
		ret= E_OUT_OF_RANGE;
		break;
	}

	return ret;
}

ErrorState_t Light_Show(void) // Runnable Task
{
	ErrorState_t ret= E_OK;

	static uint8 RGB_PhaseIndexArr[TOTAL_PHASES]= {0    ,0     ,0     };
	static RGB_PHASE_type First_PHASE= RED_PHASE;
	static RGB_PHASE_type Second_PHASE= GREEN_PHASE;

	if(RGB_PhaseIndexArr[First_PHASE] < 254 && RGB_PhaseIndexArr[Second_PHASE] == 0)
	{
		RGB_PhaseIndexArr[First_PHASE]++;
		ret|= RGB_SetIndexPhase(First_PHASE, RGB_PhaseIndexArr[First_PHASE]);
	}
	if(RGB_PhaseIndexArr[First_PHASE] == 254 && RGB_PhaseIndexArr[Second_PHASE] < 254)
	{
		RGB_PhaseIndexArr[Second_PHASE]++;
		ret|= RGB_SetIndexPhase(Second_PHASE, RGB_PhaseIndexArr[Second_PHASE]);
	}
	if(RGB_PhaseIndexArr[First_PHASE] > 0 && RGB_PhaseIndexArr[Second_PHASE] == 254)
	{
		RGB_PhaseIndexArr[First_PHASE]--;
		ret|= RGB_SetIndexPhase(First_PHASE, RGB_PhaseIndexArr[First_PHASE]);
	}
	if(RGB_PhaseIndexArr[First_PHASE] == 0 && RGB_PhaseIndexArr[Second_PHASE] == 254)
	{
		First_PHASE= Second_PHASE;
		Second_PHASE+= 1;
	}
	if(Second_PHASE == TOTAL_PHASES)
	{
		Second_PHASE= RED_PHASE;
	}

	return ret;
}
/************************** LDR Filter / GARDEN Lights ********************************/



static ErrorState_t GARDEN_Lights_Enable(void)
{
	ErrorState_t ret= E_OK;

	ret|= DIO_WritePin(GARDEN_LIGHTS_PIN, HIGH);

	return ret;
}

static ErrorState_t GARDEN_Lights_Disable(void)
{
	ErrorState_t ret= E_OK;

	ret|= DIO_WritePin(GARDEN_LIGHTS_PIN, LOW);

	return ret;
}


void RTOS_LDR_Task(void)
{
	if(LDR_Displayed != LDR_FILTER_Reading)
	{
		LDR_Displayed= LDR_FILTER_Reading;
		if(LDR_Displayed <= 50)
		{
			GARDEN_Lights_Enable();
		}
		else
		{
			/* Do Nothing */
		}

		if(LDR_Displayed > 55)
		{
			GARDEN_Lights_Disable();
		}
		else
		{
			/* Do Nothing */
		}
	}
	else
	{
		/* Do Nothing */
	}
}
/********************* 7-Segment ***************************/

#define SEGMENT_COM1_PIN   PINA3
#define SEGMENT_COM2_PIN   PINA2
#define SEGMENT_COM3_PIN   PINB5
#define SEGMENT_COM4_PIN   PINB6

#define SEGMENT_CLEAR_MASK     (0xE8)

void Segment_Display_Task(void)
{
	static uint8 Segment_Flag= 0;
	uint8 d0, d1, arr[]={0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x10, 0x11};
	d0 = LDR_Displayed % 10;
	d1 = LDR_Displayed / 10;
	PORTB|= arr[d0];


	if(Segment_Flag == 0)
	{
		PORTB&= SEGMENT_CLEAR_MASK;
		PORTB|= arr[0];
		DIO_WritePin(SEGMENT_COM1_PIN, LOW);
		DIO_WritePin(SEGMENT_COM2_PIN, HIGH);
		DIO_WritePin(SEGMENT_COM3_PIN, HIGH);
		DIO_WritePin(SEGMENT_COM4_PIN, HIGH);
		Segment_Flag= 1;
	}
	else if(Segment_Flag == 1)
	{
		PORTB&= SEGMENT_CLEAR_MASK;
		PORTB|= arr[d0];
		DIO_WritePin(SEGMENT_COM1_PIN, HIGH);
		DIO_WritePin(SEGMENT_COM2_PIN, LOW);
		DIO_WritePin(SEGMENT_COM3_PIN, HIGH);
		DIO_WritePin(SEGMENT_COM4_PIN, HIGH);
		Segment_Flag= 2;
	}
	else if(Segment_Flag == 2)
	{
		PORTB&= SEGMENT_CLEAR_MASK;
		PORTB|= arr[d1];
		DIO_WritePin(SEGMENT_COM1_PIN, HIGH);
		DIO_WritePin(SEGMENT_COM2_PIN, HIGH);
		DIO_WritePin(SEGMENT_COM3_PIN, LOW);
		DIO_WritePin(SEGMENT_COM4_PIN, HIGH);
		Segment_Flag= 3;
	}
	else if(Segment_Flag == 3)
	{
		PORTB&= SEGMENT_CLEAR_MASK;
		PORTB|= arr[0];
		DIO_WritePin(SEGMENT_COM1_PIN, HIGH);
		DIO_WritePin(SEGMENT_COM2_PIN, HIGH);
		DIO_WritePin(SEGMENT_COM3_PIN, HIGH);
		DIO_WritePin(SEGMENT_COM4_PIN, LOW);
		Segment_Flag= 0;
	}
}

/***********************************************************/
static void RGB_Handler(void)
{
	LIGHTING_Command_t Command= Bluetooth_Buffer[1];

	/* Execute Command */
	switch(Command)
	{
	case LIGHT_ON_OFF:
		Light_on_off();
		break;

	case LIGHT_COLOR:
		Light_color();
		break;

	case LIGHT_INTENSITY:
		Light_Intensity();
		break;

	case LIGHT_SHOW:
		LightShow_on_off();
		Light_Show();
		break;

		//			case GARDEN_ON_OFF:
		//				GARDEN_LightsSystem_on_off();
		//			break;

	default:
		/* Do Nothing */
		break;
	}
}


static void Command_Handler(void)
{
	SYSTEMS_TASKS_CommandType Command= Bluetooth_Buffer[0];

	switch(Command)
	{
	case STEPPER_TASK:

		STEPPER_Handler();
		RTOS_ResumeTask(1);
		break;

	case RGB_TASK:

		RGB_Handler();

		break;


	default:
		/* Return Error type */
		break;

	}
}


void RTOS_Main_Task(void)
{
	if(Command_Rec_Flag == 1)
	{
		Command_Handler();
		Command_Rec_Flag= 0;
	}
	else
	{
		/* Do Nothing */
	}
}


void RTOS_Stepper_Task(void)
{
	if(Steps_Iterator < Stepper_Steps)
	{
		switch(Stepper_Direction)
		{
		case CW_DICECTION:
			STEPPER_Rotate_OneStep_CW();

			break;

		case CCW_DICECTION:
			STEPPER_Rotate_OneStep_CCW();
			DIO_TogglePin(PINB7);
			break;

		default:
			/* Do Nothing */
			break;
		}
		Steps_Iterator++;
	}
	else
	{
		RTOS_SuspendTask(1);
	}
}


void RTOS_RGB_Task(void)
{
	if(LightShow_state == LIGHT_SHOW_ON)
	{
		Light_Show();
	}
	else
	{
		/* Do Nothing */
	}
}

ISR(ADC_vect)
{
	LDRFilter_ADC_AutoTrigger();
}

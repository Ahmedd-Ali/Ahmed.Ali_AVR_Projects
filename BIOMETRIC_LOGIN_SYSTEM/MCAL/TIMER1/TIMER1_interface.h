/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : TIMER1               *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef TIMER1_TIMER1_INTERFACE_H_
#define TIMER1_TIMER1_INTERFACE_H_


/*********************************************************************************/
/*                                TIMER 1                                        */
/*********************************************************************************/

/* ============================ Enums Declarations ========================*/

/* Prescaler Select */

typedef enum
{
	TIMER1_Timer_Stop 			 = 0,
	TIMER1_No_Prescaller		 = 1,
	TIMER1_PRESCALLER_8          = 2,
	TIMER1_PRESCALLER_64         = 3,
	TIMER1_PRESCALLER_256        = 4,
	TIMER1_PRESCALLER_1024       = 5,
	TIMER1_PRESCALLER_FALEXTCLK  = 6,
	TIMER1_PRESCALLER_RAISEXTCLK = 7,
}TIMER1_Scaler_t;

/* TIMER1 Modes */
typedef enum
{
	TIMER1_NORMAL_MODE                   = 0,
	TIMER1_PHASE_CORRECT_PWM_8_BIT       = 1,
	TIMER1_PHASE_CORRECT_PWM_9_BIT       = 2,
	TIMER1_PHASE_CORRECT_PWM_10_BIT      = 3,
	TIMER1_CTC_OCR1A_TOP                 = 4,
	TIMER1_FAST_PWM_8_BIT                = 5,
	TIMER1_FAST_PWM_9_BIT                = 6,
	TIMER1_FAST_PWM_10_BIT               = 7,
	TIMER1_PHASE_FREQ_CORRECT_ICR1_TOP   = 8,
	TIMER1_PHASE_FREQ_CORRECT_OCR1A_TOP  = 9,
	TIMER1_PHASE_CORRECT_PWM_ICR1_TOP    = 10,
	TIMER1_PHASE_CORRECT_PWM_OCR1A_TOP   = 11,
	TIMER1_CTC_ICR1_TOP                  = 12,
	TIMER1_FAST_PWM_ICR1_TOP             = 13,
	TIMER1_FAST_PWM_OCR1A_TOP            = 14
}TIMER1_Mode_t;

/* Output Compare Modes */
typedef enum
{
	OC1_DISCONNECTED   = 0,
	OC1_TOGGLE         = 1,
	OC1_NON_INVERTING  = 2,
	OC1_INVERTING      = 3
}OC1_Mode_t;


typedef enum
{
	ICU_FALLING_EDGE = 0,
	ICU_RISING_EDGE  = 1,
}ICU_TriggerEdge_t;

/****************** Setters & Getters *****************************/
#define TIMER1_SET_COUNT(value)    (TCNT1=(value))
#define TIMER1_SET_ICU(value)      (ICR1 =(value))
#define TIMER1_SET_OCA(value)      (OCR1A=(value))
#define TIMER1_SET_OCB(value)      (OCR1B=(value))

#define TIMER1_GET_COUNT(var)	   ((var)= TCNT1)
#define TIMER1_GET_ICU(var)        ((var)= ICR1)
#define TIMER1_GET_OCA(var)        ((var)= OCR1A)
#define TIMER1_GET_OCB(var)        ((var)= OCR1B)
/* ============================ Functions Prototypes ========================*/

ErrorState_t TIMER1_Init(TIMER1_Mode_t Timer_Mode, TIMER1_Scaler_t Scaler);
ErrorState_t TIMER1_ICU_Init(void);
ErrorState_t TIMER1_ICU_SetTriggerEdge(ICU_TriggerEdge_t Edge);

ErrorState_t TIMER1_Start(void);
ErrorState_t TIMER1_Stop(void);

ErrorState_t TIMER1_OC1A_Mode(OC1_Mode_t OC1_Mode);
ErrorState_t TIMER1_OC1B_Mode(OC1_Mode_t OC1_Mode);

/* Interrupt Functions for OV Mode and OC Mode */
ErrorState_t TIMER1_OV_InterruptEnable(void);
ErrorState_t TIMER1_OV_InterruptDisable(void);

ErrorState_t TIMER1_OCA_InterruptEnable(void);
ErrorState_t TIMER1_OCA_InterruptDisable(void);

ErrorState_t TIMER1_OCB_InterruptEnable(void);
ErrorState_t TIMER1_OCB_InterruptDisable(void);

ErrorState_t TIMER1_ICU_InterruptEnable(void);
ErrorState_t TIMER1_ICU_InterruptDisable(void);
/*
ErrorState_t TIMER1_SetICR1_Value(uint16 Value);
ErrorState_t TIMER1_SetOCR1A_Value(uint16 Value);
ErrorState_t TIMER1_SetOCR1B_Value(uint16 Value);
ErrorState_t TIMER1_SetTimerValue(uint16 Value);
*/
ErrorState_t TIMER1_ReadTimerValue(uint16 * pdata);

//ErrorState_t TIMER1_SetDesiredTime_ms(uint32 time_ms);
//ErrorState_t TIMER1_SetDesiredTime_us(uint32 time_us);

ErrorState_t TIMER1_setDelayTimeMilliSec_Normal(uint16 delay_ms, void(*LocalFptr)(void));
ErrorState_t TIMER1_setDelayTimeSec_Normal(uint16 delay_s, void(*LocalFptr)(void));

ErrorState_t TIMER1_setDelayTimeMilliSec_CTC(uint16 delay_ms, void(*LocalFptr)(void));
ErrorState_t TIMER1_setDelayTimeSec_CTC(uint16 delay_s, void(*LocalFptr)(void));

ErrorState_t TimerSchedular(uint32 DelayTime_ms, void(*pFunc)(void),uint8 Periodic);

/* Set Call Back Function to set ISR Functions */
ErrorState_t TIMER1_OV_SetCallBack(void(*Local_fPtr)(void));
ErrorState_t TIMER1_OCA_SetCallBack(void(*Local_fPtr)(void));
ErrorState_t TIMER1_OCB_SetCallBack(void(*Local_fPtr)(void));
ErrorState_t TIMER1_ICU_SetCallBack(void(*Local_fPtr)(void));



#endif /* TIMER1_TIMER1_INTERFACE_H_ */

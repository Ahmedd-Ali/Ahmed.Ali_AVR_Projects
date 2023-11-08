/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : TIMER2               *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef TIMER2_TIMER2_INTERFACE_H_
#define TIMER2_TIMER2_INTERFACE_H_

/* Section : Macro Declarations */


/* Section : Macro Functions Declarations */
/* SETTERS */
#define TIMER2_SET_COUNTR(value)       (TCNT2=value)
#define TIMER2_SET_OC(value)           (OCR2=value)
/* GETTERS */
#define TIMER2_GET_COUNT(var)          ((var)= TCNT0)
#define TIMER2_GET_OC(var)    		   ((var)= OCR0)
/* INTERRUPT */
#define TIMER2_OV_INTERRUPT_ENABLE()        SET_BIT(TIMSK,TOIE2)
#define TIMER2_OV_INTERRUPT_DISABLE()		CLR_BIT(TIMSK,TOIE2)
#define TIMER2_OC_INTERRUPT_ENABLE()		SET_BIT(TIMSK,OCIE2)
#define TIMER2_OC_INTERRUPT_DISABLE()		CLR_BIT(TIMSK,OCIE2)

/* Section : Data Type Declarations */

typedef enum{
	TIMER2_STOP       = 0,
	TIMER2_SCALER_1   = 1,
	TIMER2_SCALER_8   = 2,
	TIMER2_SCALER_32  = 3,
	TIMER2_SCALER_64  = 4,
	TIMER2_SCALER_256 = 5,
	TIMER2_SCALER_128 = 6,
	TIMER2_SCALER_1024= 7
}TIMER2Scaler_t;

typedef enum
{
	TIMER2_NORMAL_MODE      = 0,
	TIMER2_PHASECORRECT_MODE= 1,
	TIMER2_CTC_MODE			= 2,
	TIMER2_FASTPWM_MODE		= 3
}TIMER2Mode_t;

typedef enum
{
	OC2_DISCONNECTED = 0,
	OC2_TOGGLE		 = 1,
	OC2_NON_INVERTING= 2,
	OC2_INVERTING	 = 3
}OC2Mode_t;

/* Section : Function Declarations */

ErrorState_t TIMER2_Init(TIMER2Mode_t mode,TIMER2Scaler_t scaler);
ErrorState_t TIMER2_OC2Mode(OC2Mode_t mode);
ErrorState_t TIMER2_OVF_SetCallBack(void(*local_fptr)(void));
ErrorState_t TIMER2_OC2_SetCallBack(void(*local_fptr)(void));
ErrorState_t TIMER2_Start(void);
ErrorState_t TIMER2_Stop(void);
ErrorState_t TIMER2_SetInterruptTime_ms(uint16 timeDelay,void(*LocalFptr)(void));

#endif /* TIMER2_TIMER2_INTERFACE_H_ */

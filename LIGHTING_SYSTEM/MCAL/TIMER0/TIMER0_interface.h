/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : TIMER0               *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef TIMER0_TIMER0_INTERFACE_H_
#define TIMER0_TIMER0_INTERFACE_H_

/***********************************************************************/
/*                            TIMER0                                   */
/***********************************************************************/

/****************** Setters & Getters *****************************/
#define TIMER0_SET_COUNTR(value)   (TCNT0= (value))
#define TIMER0_SET_OC(value)       (OCR0=  (value))

#define TIMER0_GET_COUNT(var)      ((var)= TCNT0)
#define TIMER0_GET_OC(var)         ((var)= OCR0)

/* INTERRUPT */
#define TIMER0_OV_INTERRUPT_ENABLE()        SET_BIT(TIMSK,TOIE0)
#define TIMER0_OV_INTERRUPT_DISABLE()		CLR_BIT(TIMSK,TOIE0)
#define TIMER0_OC_INTERRUPT_ENABLE()		SET_BIT(TIMSK,OCIE0)
#define TIMER0_OC_INTERRUPT_DISABLE()		CLR_BIT(TIMSK,OCIE0)

/******************* PostBuild Configurations *****************************/
typedef enum{
	TIMER0_STOP   	    = 0,
	TIMER0_SCALER_1     = 1,
	TIMER0_SCALER_8     = 2,
	TIMER0_SCALER_64    = 3,
	TIMER0_SCALER_256   = 4,
	TIMER0_SCALER_1024  = 5,
	EXTERNALl_FALLING   = 6,
	EXTERNAL_RISING     = 7
}TIMER0Scaler_t;

typedef enum
{
	TIMER0_NORMAL_MODE        = 0,
	TIMER0_PHASECORRECT_MODE  = 1,
	TIMER0_CTC_MODE           = 2,
	TIMER0_FASTPWM_MODE       = 3

}TIMER0Mode_t;

typedef enum
{
	OC0_DISCONNECTED   = 0,
	OC0_TOGGLE         = 1,
	OC0_NON_INVERTING  = 2,
	OC0_INVERTING      = 3

}OC0Mode_t;

ErrorState_t TIMER0_Init(TIMER0Mode_t mode,TIMER0Scaler_t scaler);
ErrorState_t TIMER0_OC0Mode(OC0Mode_t mode);
ErrorState_t TIMER0_Start(void);
ErrorState_t TIMER0_Stop(void);
ErrorState_t TIMER0_OV_SetCallBack(void(*local_fptr)(void));
ErrorState_t TIMER0_OC_SetCallBack(void(*local_fptr)(void));

ErrorState_t TIMER0_SetInterruptTime_ms(uint16 timeDelay,void(*LocalFptr)(void));

#endif /* TIMER0_TIMER0_INTERFACE_H_ */

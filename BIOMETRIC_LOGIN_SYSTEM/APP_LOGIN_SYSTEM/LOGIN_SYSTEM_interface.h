/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : APP                  **********************/
/****************    SWC       : LOGIN_SYSTEM         *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef LOGIN_SYSTEM_INTERFACE_H_
#define LOGIN_SYSTEM_INTERFACE_H_


#define MAX_TRIALS        3
#define SIGNED_IN_TIME    20


typedef enum{
	SYSTEM_LOCKED   = 0,
	SYSTEM_UNLOCKED = 1,
	SYSTEM_BLOCK    = 2
}LOGIN_SYSTEM_State_t;

typedef enum{
	TIME_OUT= 0,
	TIME_IN = 1
}LOGIN_SYSTEM_TimeState_t;


ErrorState_t LOGIN_SYSTEM_Init(void);
ErrorState_t LOGIN_SYSTEM_Handler(void);
ErrorState_t LOGIN_SYSTEM_FingerPrintState(void);
ErrorState_t LOGIN_SYSTEM_PasswordState(void);
ErrorState_t LOGIN_SYSTEM_CheckLogging(void);
ErrorState_t LOGIN_SYSTEM_Reset(void);


ErrorState_t RTC_Runnable(void);
#endif /* LOGIN_SYSTEM_INTERFACE_H_ */

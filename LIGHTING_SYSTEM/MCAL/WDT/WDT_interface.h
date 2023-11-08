/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : WDT                  *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef WDT_WDT_INTERFACE_H_
#define WDT_WDT_INTERFACE_H_


typedef enum
{
	MS_16_3 = 0,
	MS_32_5 = 1,
	MS_65   = 2,
	S_0_13  = 3,
	S_0_26  = 4,
	S_0_52  = 5,
	S_1     = 6,
	S_2_1   = 7
}WDT_SleepTimer_t;

/* Functions Prototypes */

ErrorState_t WDT_Sleep(WDT_SleepTimer_t Time);

ErrorState_t WDT_Enable(void);
ErrorState_t WDT_Disable(void);

ErrorState_t WDT_Refresh(void);

#endif /* WDT_WDT_INTERFACE_H_ */

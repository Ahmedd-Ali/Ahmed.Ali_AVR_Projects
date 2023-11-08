/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : WDT                  *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MEM_MAP.h"
#include "WDT_config.h"
#include "WDT_private.h"
#include "WDT_interface.h"


ErrorState_t WDT_Sleep(WDT_SleepTimer_t Time)
{
	ErrorState_t ret= E_OK;

	/* Resetting the prescaler bits */
	WDTCR &= 0xF8;

	/* Set the required prescaler */
	WDTCR |= Time;

	return ret;
}

ErrorState_t WDT_Enable(void)
{
	ErrorState_t ret= E_OK;

	/* Enabling the Watchdog Timer */
	SET_BIT(WDTCR, WDE);

	return ret;
}
ErrorState_t WDT_Disable(void)
{
	ErrorState_t ret= E_OK;

	/* Watchdog Timer Di */
	/* Writing a logic 1 to WDTOE and WDE */
	WDTCR |= 0x18;

	/* Writting a logic 0 to WDE */
	WDTCR = 0x00;

	return ret;
}


ErrorState_t WDT_Refresh(void)
{
	ErrorState_t ret= E_OK;

	CLR_BIT(MCUCSR, WDRF);

	return ret;
}



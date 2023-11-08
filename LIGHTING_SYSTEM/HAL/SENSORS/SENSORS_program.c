/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : HAL                  **********************/
/****************    SWC       : SENSORS              *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "MEM_MAP.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"
#include "SENSORS_config.h"
#include "SENSORS_private.h"
#include "SENSORS_interface.h"
#include "TIMER1_interface.h"

ErrorState_t LM35_GetTemp(uint16 * pdata)
{
	ErrorState_t ret= E_OK;

	if(pdata == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		ret|= ADC_GetChannelVolt(LM35_CH, pdata);
		*pdata = *pdata / 10;
	}

	return ret;
}


ErrorState_t POT_GetPercent(uint16 * pdata)
{
	ErrorState_t ret= E_OK;

	if(pdata == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		ret|= ADC_GetReadNoBlock(pdata);
		*pdata = ((uint32)(*pdata)*100)/1023;
	}

	return ret;
}

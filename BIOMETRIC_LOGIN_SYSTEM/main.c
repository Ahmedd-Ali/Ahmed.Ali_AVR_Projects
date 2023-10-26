/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : APP                  **********************/
/****************    SWC       : LOGIN_SYSTEM         *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "LOGIN_SYSTEM_interface.h"

int main(void)
{
	ErrorState_t ret= E_OK;

	ret|= LOGIN_SYSTEM_Init();

	while(1)
	{
		ret|= LOGIN_SYSTEM_Handler();
		ret|= LOGIN_SYSTEM_CheckLogging();
	}
}

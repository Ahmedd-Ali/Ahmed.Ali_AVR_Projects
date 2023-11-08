/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : APP                  **********************/
/****************    SWC       : Main Function        *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "Kernel_interface.h"
#include "LIGHTING_interface.h"

int main(void)
{
	ErrorState_t ret= E_OK;

	ret|= RTOS_System_Init_Task();
	ret|= RTOS_CreateTask(0, &RTOS_Main_Task, 1, 0);
	ret|= RTOS_CreateTask(1, &RTOS_Stepper_Task, 3, 0);
	ret|= RTOS_CreateTask(2, &RTOS_RGB_Task, 1, 0);
	ret|= RTOS_CreateTask(3, &Segment_Display_Task, 2, 0);
	ret|= RTOS_CreateTask(4, &RTOS_LDR_Task, 10, 0);
	ret|= RTOS_SuspendTask(1);
	ret|= RTOS_Start();

	while (1)
	{

	}
}

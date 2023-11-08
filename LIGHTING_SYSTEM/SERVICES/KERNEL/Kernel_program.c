/*********************************************************************************/
/*********************************************************************************/
/**************************   Author: Ahmed Ali   ********************************/
/**************************   Layer: Kernel	      ********************************/
/**************************   Stack: OS           ********************************/
/**************************   Version: 1.00       ********************************/
/*********************************************************************************/
/*********************************************************************************/

#include "STD_TYPES.h"
#include "MEM_MAP.h"
#include "TIMER0_interface.h"
#include "Kernel_cfg.h"
#include "Kernel_private.h"
#include "Kernel_interface.h"


typedef struct 
{
	uint16 Periodicity;
	void (*TaskFunc) (void);
	uint8 State;
	uint16 FirstDelay;
}Task_t;
	

static Task_t SystemTasks[TASK_NUM] = {{0}};


ErrorState_t RTOS_Start(void)
{
	ErrorState_t Local_u8ErrorState= E_OK;

	/* Configure Timer to generate Interrupt every 1 ms */
	
	Local_u8ErrorState|= TIMER0_SetInterruptTime_ms(1, &Scheduler);
	Local_u8ErrorState|= TIMER0_Start();

	/* Enable Global Interrupt */
	sei();

	return Local_u8ErrorState;
}

ErrorState_t RTOS_CreateTask(uint8 Copy_u8Priority, void (*Copy_pvTaskFunc)(void), uint16 Copy_u16Periodicity, uint16 Copy_u16FirstDelay)
{
	ErrorState_t Local_u8ErrorState= E_OK;

	if(Copy_pvTaskFunc != NULL)
	{
		if(SystemTasks[Copy_u8Priority].TaskFunc == NULL)
		{
			SystemTasks[Copy_u8Priority].Periodicity= Copy_u16Periodicity;
			SystemTasks[Copy_u8Priority].TaskFunc= Copy_pvTaskFunc;
			SystemTasks[Copy_u8Priority].State= RESUMED;
			SystemTasks[Copy_u8Priority].FirstDelay= Copy_u16FirstDelay;
		}
		else
		{
			/* Priority is not available */
			Local_u8ErrorState= E_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_u8ErrorState= E_NOT_OK;
	}

	return Local_u8ErrorState;
}

ErrorState_t RTOS_SuspendTask(uint8 Copy_u8Priority)
{
	ErrorState_t Local_u8ErrorState= E_OK;

	SystemTasks[Copy_u8Priority].State= SUSPENDED;

	return Local_u8ErrorState;
}

ErrorState_t RTOS_ResumeTask(uint8 Copy_u8Priority)
{
	ErrorState_t Local_u8ErrorState= E_OK;

	SystemTasks[Copy_u8Priority].State= RESUMED;

	return Local_u8ErrorState;
}

ErrorState_t RTOS_DeleteTask(uint8 Copy_u8Priority)
{
	ErrorState_t Local_u8ErrorState= E_OK;

	SystemTasks[Copy_u8Priority].TaskFunc= NULL;

	return Local_u8ErrorState;
}

static void Scheduler(void)
{
	uint8 Local_u8TaskCounter;

	for(Local_u8TaskCounter= 0; Local_u8TaskCounter<TASK_NUM; Local_u8TaskCounter++)
	{
		if(SystemTasks[Local_u8TaskCounter].State == RESUMED)
		{
			if(SystemTasks[Local_u8TaskCounter].FirstDelay == NULL)
			{
				/* Invoke The Task Function, If it is not NULL */
				if(SystemTasks[Local_u8TaskCounter].TaskFunc != NULL)
				{
					SystemTasks[Local_u8TaskCounter].TaskFunc();
				}
				/* Make 1st delay equal to periodicity-1 */
				SystemTasks[Local_u8TaskCounter].FirstDelay= SystemTasks[Local_u8TaskCounter].Periodicity-1;
			}
			else
			{
				/* 1st delay is not equal to zero, so decrement the 1st delay by 1 */
				SystemTasks[Local_u8TaskCounter].FirstDelay--;
			}
		}
		else
		{
			/* Task is suspended, Do nothing */
		}
	}
}

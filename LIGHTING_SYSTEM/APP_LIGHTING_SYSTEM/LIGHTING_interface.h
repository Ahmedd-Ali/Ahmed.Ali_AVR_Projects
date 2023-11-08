/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : APP                  **********************/
/****************    SWC       : LIGHTING_SYSTEM      *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/


#ifndef LIGHTING_INTERFACE_H_
#define LIGHTING_INTERFACE_H_

#define LDR_FILTER_SIZE       20
#define LDR_TRANSITION_READ   50
#define GARDEN_LIGHTS_PIN     PINA5

typedef enum{
	STEPPER_TASK = '0',
	RGB_TASK     = '1'
}SYSTEMS_TASKS_CommandType;

typedef enum{
	TASK_OFF= 0,
	TASK_ON = 1
}TASKS_State_t;

typedef enum{
	LIGHT_ON_OFF    = '0',
	LIGHT_COLOR     = '1',
	LIGHT_INTENSITY = '2',
	LIGHT_SHOW      = '3',
	GARDEN_ON_OFF   = '4'

}LIGHTING_Command_t;

typedef enum{
	LIGHT_OFF= 0,
	LIGHT_ON = 1
}Light_State_t;


typedef enum{
	LIGHT_SHOW_OFF= 0,
	LIGHT_SHOW_ON = 1
}LightShow_State_t;

typedef enum{
	GARDEN_LIGHTS_OFF= 0,
	GARDEN_LIGHTS_ON = 1
}Garden_State_t;

ErrorState_t RTOS_System_Init_Task(void);

void RTOS_Main_Task(void);
void RTOS_RGB_Task(void);
void RTOS_Stepper_Task(void);
void RTOS_LDR_Task(void);
void Segment_Display_Task(void);


#endif /* LIGHTING_INTERFACE_H_ */

/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : HAL                  **********************/
/****************    SWC       : DC MOTOR             *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef DC_MOTOR_DC_MOTOR_INTERFACE_H_
#define DC_MOTOR_DC_MOTOR_INTERFACE_H_




ErrorState_t DC_MOTOR_Init(void);
ErrorState_t DC_MOTOR_On(void);
ErrorState_t DC_MOTOR_Off(void);


ErrorState_t SERVO_MOTOR_Init(void);
ErrorState_t SERVO_MOTOR_Set_Angle(uint8 angle);

#endif /* DC_MOTOR_DC_MOTOR_INTERFACE_H_ */

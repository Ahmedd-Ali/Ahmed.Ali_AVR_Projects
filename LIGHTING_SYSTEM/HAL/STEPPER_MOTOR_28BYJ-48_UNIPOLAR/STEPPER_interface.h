/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : HAL                  **********************/
/****************    SWC       : STEPPER_MOTOR        *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef STEPPER_MOTOR_28BYJ_48_UNIPOLAR_STEPPER_INTERFACE_H_
#define STEPPER_MOTOR_28BYJ_48_UNIPOLAR_STEPPER_INTERFACE_H_

#define DELAY    3


typedef enum{
	CCW_DICECTION  = 0,//!< CCW_DICECTION
	CW_DICECTION   = 1 //!< CW_DICECTION
}Stpr_direction_t;




ErrorState_t STEPPER_Rotate_OneStep_CW(void);
ErrorState_t STEPPER_Rotate_OneStep_CCW(void);

/**
 * @brief This function makes  the stepper rotate by Angle in a specific Direction
 * @param Direction
 * @param Angle
 * @return Status of the Function
 */
ErrorState_t STEPPER_Rotate(Stpr_direction_t Direction, uint16 Angle);


#endif /* STEPPER_MOTOR_28BYJ_48_UNIPOLAR_STEPPER_INTERFACE_H_ */

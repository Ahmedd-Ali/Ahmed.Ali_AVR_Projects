/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : HAL                  **********************/
/****************    SWC       : SENSORS              *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/


#ifndef SENSORS_SENSORS_INTERFACE_H_
#define SENSORS_SENSORS_INTERFACE_H_


ErrorState_t LM35_GetTemp(uint16 * pdata);
ErrorState_t POT_GetPercent(uint16 * pdata);

#define ULTRASPIN  PIND0

void ULTRASONIC_INIT(void);
uint8 Ultrasonic_Gettable(uint16*pdata);


#endif /* SENSORS_SENSORS_INTERFACE_H_ */

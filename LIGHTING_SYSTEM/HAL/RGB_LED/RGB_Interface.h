/***************************************************************************************/
/***************************************************************************************/
/**************************   Author : Ahmed Ali        ********************************/
/**************************   Module : RGB              ********************************/
/**************************   Layer  : HAL       	    ********************************/
/**************************   Version: 1.00             ********************************/
/***************************************************************************************/
/***************************************************************************************/

#ifndef RGB_INTERFACE_H_
#define RGB_INTERFACE_H_


/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%    Inclusions    %%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

#include "RGB_Cfg.h"


/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%   Declarations   %%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

extern const uint8 Colors_Name[9][8];

/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%      Enums       %%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

typedef enum{
	White   = 0,
	Red     = 1,
	Green   = 2,
	Blue    = 3,
	Yellow  = 4,
	Cyan    = 5,
	Fuchsia = 6,
	Gray    = 7,
	Brown   = 8
}Color_type;

typedef enum{
	RED_PHASE   = 0,
	GREEN_PHASE = 1,
	BLUE_PHASE  = 2,
	TOTAL_PHASES= 3
}RGB_PHASE_type;

/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%    Prototypes    %%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

ErrorState_t RGB_Init(void);

ErrorState_t RGB_Enable(void);
ErrorState_t RGB_Disable(void);

ErrorState_t RGB_SetColor(Color_type color);

/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%     Service      %%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

ErrorState_t RGB_SetIntensity(uint8 intensity);
ErrorState_t RGB_SetIndexPhase(RGB_PHASE_type phase, uint8 index);


#endif /* RGB_INTERFACE_H_ */

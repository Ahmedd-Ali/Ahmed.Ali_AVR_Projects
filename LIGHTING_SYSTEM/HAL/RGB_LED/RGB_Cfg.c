/***************************************************************************************/
/***************************************************************************************/
/**************************   Author : Ahmed Ali        ********************************/
/**************************   Module : RGB              ********************************/
/**************************   Layer  : HAL       	    ********************************/
/**************************   Version: 1.00             ********************************/
/***************************************************************************************/
/***************************************************************************************/

/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%    Inclusions    %%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

#include "STD_TYPES.h"
#include "RGB_Cfg.h"

/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Configrations   %%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

const uint8 Colors_Arr[NUM_OF_COLORS][3]= {/*  { Red  , Green, Blue } */ /* Color   */
											{254   ,254   ,254	 },	  /* 1 White */
											{254   ,0     ,0     },   /* 2 Red   */
											{0	   ,254   ,0     },   /* 3 Green */
											{0	   ,0     ,254   },   /* 4 Blue  */
											{254   ,254   ,0     },   /* 5 Yellow*/
											{0	   ,254   ,254   },   /* 6 Cyan  */
											{254   ,0     ,254   },   /* 7 Fuchsia */
											{128   ,128   ,128   },   /* 8 Gray  */
											{165   ,42    ,42    },   /* 9 Brown */
											};
										
const uint8 Colors_Name[9][8]= {"White  ", "Red    ", "Green  ", "Blue   ", "Yellow ", "Cyan   ", "Fuchsia", "Gray   ", "Brown  "};

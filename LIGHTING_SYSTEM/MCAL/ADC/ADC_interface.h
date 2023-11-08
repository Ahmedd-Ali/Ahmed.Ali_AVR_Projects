/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : ADC                  *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/


#ifndef ADC_interface_H_
#define ADC_interface_H_
 
 /* Section : Includes */

 /* Section : Macro Declarations */

 /* Section : Macro Functions Declarations */

 /* Section : Data Type Declarations */

 typedef enum{
	 ADC_AREF= 0,
	 ADC_VCC = 1,
	 ADC_v256= 3
 }ADC_Vref_t;
 
 typedef enum{
	 ADC_SCALER_2  =  0,
	 ADC_SCALER_4  =  2,
	 ADC_SCALER_8  =  3,
	 ADC_SCALER_16 = 4,
	 ADC_SCALER_32 = 5,
	 ADC_SCALER_64 = 6,
	 ADC_SCALER_128= 7
 }ADC_Scaler_t;

 typedef enum{
	 CH_0= 0,
	 CH_1= 1,
	 CH_2= 2,
	 CH_3= 3,
	 CH_4= 4,
	 CH_5= 5,
	 CH_6= 6,
	 CH_7= 7
 }ADC_Channel_t;
 

 typedef enum{
	 FREE_RUNNING_MODE		= 0,
	 ANALOG_COMPARATOR	    = 1,
	 EX_INT0				= 2,
	 TIMER0_COMPARE_MATCH   = 3,
	 TIMER0_OVER_FLOW       = 4,
	 TIMER1_COMPARE_MATCH_B = 5,
	 TIMER1_OVER_FLOW       = 6,
	 TIMER1_CAPTURE_EVENT   = 7
 }ADC_AutoTriggerSrc_t;

 /* Section : Function Declarations */

ErrorState_t ADC_Init(ADC_Vref_t vref, ADC_Scaler_t scalar);
ErrorState_t ADC_AutoTrigger_Init(ADC_Vref_t vref, ADC_Scaler_t scalar); /* INT0 Auto Trigger */

ErrorState_t ADC_GetChannelReading(ADC_Channel_t channel, uint16 * pdata);
ErrorState_t ADC_GetChannelVolt(ADC_Channel_t channel, uint16 * pdata);

ErrorState_t ADC_InterruptEnable(void);
ErrorState_t ADC_InterruptDisable(void);

ErrorState_t ADC_StartConversion(ADC_Channel_t channel);
ErrorState_t ADC_GetReadNoBlock(uint16 * pdata);
ErrorState_t ADC_GetReadPeriodicCheck(uint16 * pdata);


		
#endif

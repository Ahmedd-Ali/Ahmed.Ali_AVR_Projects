/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : ADC                  *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MEM_MAP.h"
#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_interface.h"


ErrorState_t ADC_Init(ADC_Vref_t vref, ADC_Scaler_t scalar)
{
	ErrorState_t ret= E_OK;

	//adc disable
	CLR_BIT(ADCSRA, ADEN);

	//Vref
	switch(vref)
	{
	case ADC_AREF:
		CLR_BIT(ADMUX, REFS1);
		CLR_BIT(ADMUX, REFS0);
		break;

	case ADC_VCC:
		CLR_BIT(ADMUX, REFS1);
		SET_BIT(ADMUX, REFS0);
		break;

	case ADC_v256:
		SET_BIT(ADMUX, REFS1);
		SET_BIT(ADMUX, REFS0);
		break;

	default:
		ret= E_OUT_OF_RANGE;
		break;

	}

	//prescaler
	ADCSRA=ADCSRA&0xf8;//11111000
	scalar=scalar&0x07;//00000111
	ADCSRA=ADCSRA|scalar;

	//adjust read to the right
	CLR_BIT(ADMUX, ADLAR);

	//interrupt disable
	ret|= ADC_InterruptDisable();


	//adc enable
	SET_BIT(ADCSRA, ADEN);

	return ret;
}


ErrorState_t ADC_AutoTrigger_Init(ADC_Vref_t vref, ADC_Scaler_t scalar)
{
	ErrorState_t ret= E_OK;

	//Vref
	switch (vref)
	{
	case ADC_AREF:
		CLR_BIT(ADMUX, REFS1);
		CLR_BIT(ADMUX, REFS0);
		break;

	case ADC_VCC:
		CLR_BIT(ADMUX, REFS1);
		SET_BIT(ADMUX, REFS0);
		break;

	case ADC_v256:
		SET_BIT(ADMUX, REFS1);
		SET_BIT(ADMUX, REFS0);
		break;

	}

	//prescaler
	ADCSRA=ADCSRA&0xf8;//11111000
	scalar=scalar&0x07;//00000111
	ADCSRA=ADCSRA|scalar;

	//adjust read to the right
	CLR_BIT(ADMUX, ADLAR);

	//select channel
	ADMUX&=0xe0;//0b11100000
	ADMUX|=AUTO_TRIGGER_CHANNEL;

	//Enable Auto Trigger With EXTI0
	SET_BIT(ADCSRA, ADATE);

	SFIOR&= 00011111;
	SFIOR|= (AUTO_TRIGGER_SOURCE << 5);


//	CLR_BIT(SFIOR, 5);
//	SET_BIT(SFIOR, 6);
//	CLR_BIT(SFIOR, 7);

	//interrupt Enable
	ret|= ADC_InterruptEnable();

	//adc enable
	SET_BIT(ADCSRA, ADEN);

	return ret;
}



ErrorState_t ADC_GetChannelReading(ADC_Channel_t channel, uint16 * pdata)
{
	ErrorState_t ret= E_OK;

	if(pdata == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		//select channel
		ADMUX&=0xe0;//0b11100000
		ADMUX|=channel;
		//start conversion
		SET_BIT(ADCSRA, ADSC);
		// busy wait
		while(GET_BIT(ADCSRA, ADSC));
		//clear interrupt flag
		SET_BIT(ADCSRA, ADIF);
		//READING
		*pdata= ADC;
	}

	return ret;
}


ErrorState_t ADC_GetChannelVolt(ADC_Channel_t channel, uint16 * pdata)
{
	ErrorState_t ret= E_OK;

	if(pdata == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		ret|= ADC_GetChannelReading(channel, pdata);
		*pdata= (((uint32)(*pdata)*5000)/1024); // casting to apply operation of multiplication in 4 bytes to save result
	}

	return ret;
}


ErrorState_t ADC_InterruptEnable(void)
{
	ErrorState_t ret= E_OK;

	//interrupt Enable
	SET_BIT(ADCSRA, ADIE);

	//clear interrupt flag
	SET_BIT(ADCSRA, ADIF);

	return ret;
}


ErrorState_t ADC_InterruptDisable(void)
{
	ErrorState_t ret= E_OK;

	//interrupt disable
	CLR_BIT(ADCSRA, ADIE);

	//clear interrupt flag
	SET_BIT(ADCSRA, ADIF);

	return ret;
}

/**************************************************************************/
static uint8 read_flag= 1;

ErrorState_t ADC_StartConversion(ADC_Channel_t channel)
{
	ErrorState_t ret= E_OK;

	if(read_flag == 1)
	{
		//select channel
		ADMUX&=0xe0;//0b11100000
		ADMUX|=channel;
		//start conversion
		SET_BIT(ADCSRA, ADSC);
		read_flag = 0;
	}

	return ret;
}



ErrorState_t ADC_GetReadNoBlock(uint16 * pdata)
{
	ErrorState_t ret= E_OK;

	if(pdata == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		*pdata= ADC;
		ret= E_OK;
	}

	return ret;
}

ErrorState_t ADC_GetReadPeriodicCheck(uint16 * pdata)
{
	ErrorState_t ret= E_OK;

	if(pdata == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		if(GET_BIT(ADCSRA, ADSC) == 0)
		{
			*pdata=ADC;
			read_flag=1;
			ret= E_OK;
		}
		else
		{
			ret= E_NOT_OK;
		}
	}


	return ret;
}

/***************************************************************************/


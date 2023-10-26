/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : I2C                  *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "I2C_Private.h"
#include "I2C_Config.h"
#include "I2C_Interface.h"
#include "DIO_interface.h"

ErrorState_t I2C_MasterInit(I2C_SCL_FREQ_t SCL_FREQ)
{
	ErrorState_t ret= E_OK;

	switch(SCL_FREQ){

	case SCL_100KHZ:

		// Set prescaler == 1 (CLR TWSR 0,1)
		CLR_BIT(TWSR_REG,TWSR_TWPS0);
		CLR_BIT(TWSR_REG,TWSR_TWPS1);
		// Set TWBR with value => 100 KHz ( TWBR = 72 )
		TWBR_REG = 72;
		break;

	case SCL_400KHZ:

		// Set prescaler == 1 (CLR TWSR 0,1)
		CLR_BIT(TWSR_REG,TWSR_TWPS0);
		CLR_BIT(TWSR_REG,TWSR_TWPS1);
		// Set TWBR with value => 400 KHz ( TWBR = 12 )
		TWBR_REG = 12;
		break;

	default:

		ret= E_OUT_OF_RANGE;
		break;

	}

	return ret;
}


ErrorState_t I2C_SlaveInit(uint8 LOC_u8SlaveAdress)
{
	ErrorState_t ret= E_OK;

	/*TWAR-SLAVE ADRESS*/
	TWAR_REG=(LOC_u8SlaveAdress << 1)| TWAR_REG;
	/*ENABLE ACK*/
	SET_BIT(TWCR_REG,TWCR_TWEA);
	/*ENABLE TWI*/
	SET_BIT(TWCR_REG,TWCR_TWEN);

	return ret;
}

ErrorState_t I2C_Master_u8SendSLA_Write_ACK (uint8 Copy_u8SlaveAddress)
{
	ErrorState_t ret= E_OK;
	uint8 status_val;

	// Write 7 bits slave address ( TWDR == address<<1 )
	TWDR_REG = (Copy_u8SlaveAddress<<1) ;

	TWCR_REG = (1<<TWCR_TWINT) | (1<<TWCR_TWEN);

	// Wait for flag ( TWCR 7 == 0 )
	while((GET_BIT(TWCR_REG,TWCR_TWINT)) == 0);

	ret|= getStatus(&status_val);

	// Check status code == SLA + Write + ACK == (0x18)
	if (status_val != MASTER_SLA_Write_ACK)
	{
		ret= E_NOT_OK;
	}
	else
	{
		/* Do Nothing */
	}

	return ret ;
}

/* this function should send 1 data byte to the other device */
ErrorState_t I2C_Master_u8WriteDataByte_ACK(uint8 copy_u8data)
{
	ErrorState_t ret= E_OK;
	uint8 status_val;

	// Write data in TWDR
	TWDR_REG = copy_u8data ;

	// clear interrupt flag
	TWCR_REG = (1<<TWCR_TWINT) | (1<<TWCR_TWEN);

	// Wait for flag ( TWCR 7 == 0 )
	while (!(TWCR_REG & (1<<TWCR_TWINT)));

	ret|= getStatus(&status_val);

	// Check status code == Master Send Data + ACK == (0x28)
	if (status_val != MASTER_WR_DataByte_ACK)
	{
		ret= E_NOT_OK;
	}
	else
	{
		/* Do Nothing */
	}

	return ret ;
}

/* this function should send start condition */
ErrorState_t I2C_Master_u8StartCondition(void)
{
	ErrorState_t ret= E_OK;
	uint8 status_val;

	// Enable I2C  ( set TWCR 2 ) , Start condition ( Set TWCR 5) , Clear flag ( Set TWCR 7 )
	TWCR_REG = (1<<TWCR_TWINT)|(1<<TWCR_TWSTA)|(1<<TWCR_TWEN);

	ret|= getStatus(&status_val);

	// Wait for flag ( TWCR 7 == 0 )
	while (!(TWCR_REG & (1<<TWCR_TWINT)));

	// Check status code == start condition ( TWSR & 0xf8 ) == 0x08
	if ( status_val != MASTER_START_ACK )
	{
		ret= E_NOT_OK;
	}
	else
	{
		/* Do Nothing */
	}

	return ret;
}

/* this function should send stop condition */
ErrorState_t I2C_Master_u8StopCondition(void)
{
	ErrorState_t ret= E_OK;

	TWCR_REG = (1<<TWCR_TWINT)|(1<<TWCR_TWEN)|(1<<TWCR_TWSTO);

	return ret;
}

/* this function should receive 1 byte and respond with ACK */
ErrorState_t I2C_Master_u8ReadDataByte_ACK(uint8 * pdata)
{
	ErrorState_t ret= E_OK;
	uint8 status_val;

	if(pdata == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		// Enable ACK  ( Set TWCR 6 )
		SET_BIT(TWCR_REG,TWCR_TWEA);

		ret|= getStatus(&status_val);

		// Wait for flag ( TWCR 7 == 0 )
		while (!(TWCR_REG & (1<<TWCR_TWINT)));

		// Check status code == Master Read Data + ACK == (0x50)
		if (status_val != MASTER_RD_DataByte_ACK)
		{
			ret= E_NOT_OK;
		}
		else
		{
			/* Do Nothing */
		}

		// Read Data From Register TWDR
		*pdata = TWDR_REG ;
	}

	return ret ;

}

/* this function should receive 1 byte and respond with NO ACK */
ErrorState_t I2C_Master_u8ReadDataByte_NOTACK(uint8 * pdata)
{
	ErrorState_t ret= E_OK;
	uint8 status_val;

	if(pdata == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		// Disable ACK  ( CLR TWCR 6 )
		CLR_BIT(TWCR_REG,TWCR_TWEA);

		// Wait for flag ( TWCR 7 == 0 )
		while (!(TWCR_REG & (1<<TWCR_TWINT)));

		ret|= getStatus(&status_val);

		// Check status code == Master Read Data + NOTACK == (0x58)
		if ( status_val != MASTER_RD_DataByte_NOTACK )
		{
			ret= E_NOT_OK;
		}
		else
		{
			/* Do Nothing */
		}

		// Read Data From Register TWDR
		*pdata = TWDR_REG ;
	}

	return ret ;
}

ErrorState_t I2C_Master_u8ReStartCondition(void)
{
	ErrorState_t ret= E_OK;
	uint8 status_val;

	// Enable I2C  ( set TWCR 2 ) , Start condition ( Set TWCR 5) , Clear flag ( Set TWCR 7 )
	TWCR_REG = (1<<TWCR_TWINT)|(1<<TWCR_TWSTA)|(1<<TWCR_TWEN);

	// Wait for flag ( TWCR 7 == 0 )
	while( ( GET_BIT(TWCR_REG,TWCR_TWINT) ) == 0 );

	ret|= getStatus(&status_val);

	// Check status code == Repeat condition ( TWSR & 0xf8 ) == 0x10
	if ( status_val != MASTER_REP_START_ACK )
	{
		ret= E_NOT_OK;
	}
	else
	{
		/* Do Nothing */
	}

	return ret;
}


ErrorState_t I2C_Master_u8SendSLA_Read_ACK (uint8 Copy_u8SlaveAddress)
{
	ErrorState_t ret= E_OK;
	uint8 status_val;

	// Write 7 bits slave address ( TWDR == address<<1 )
	TWDR_REG = (Copy_u8SlaveAddress<<1) | 0x01;

	// Read condition ( SET TWDR 0 )
	TWCR_REG = (1<<TWCR_TWINT) | (1<<TWDR_TWD0);

	// Wait for flag ( TWCR 7 == 0 )
	while( ( GET_BIT(TWCR_REG,TWCR_TWINT) ) == 0 );

	ret|= getStatus(&status_val);

	// Check status code == SLA + Read + ACK == (0x40)
	if (status_val != MASTER_SLA_Read_ACK)
	{
		ret= E_NOT_OK;
	}

	return ret ;
}


/* this function should read status of status register */
ErrorState_t getStatus(uint8 * status)
{
	ErrorState_t ret= E_OK;

	if(status == NULL)
	{
		ret= E_NULL_PTR;
	}
	else
	{
		*status = (TWSR_REG & STATUS_BIT_MASK);
	}

	return ret;
}

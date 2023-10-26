/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : I2C                  *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

/*
typedef enum
{
    I2C_NO_Error= 0 ,
    I2C_Error_Master_StartCond_ACK=1 ,
    I2C_Error_Master_ReStartCond_ACK=2 ,
    I2C_Error_Master_SendSLA_Write_ACK=3 ,
    I2C_Error_Master_SendSLA_Write_NOTACK=4 ,
    I2C_Error_Master_SendSLA_Read_ACK=5 ,
    I2C_Error_Master_SendSLA_Read_NOTACK=6 ,
    I2C_Error_Master_WriteDataByte_ACK=7 ,
    I2C_Error_Master_WriteDataByte_NOTACK=8 ,
    I2C_Error_Master_ReadDataByte_ACK = 9 ,
    I2C_Error_Master_ReadDataByte_NOTACK =10
}I2C_Error_t ;
*/

typedef enum{
	SCL_100KHZ =0,
	SCL_400KHZ =1
}I2C_SCL_FREQ_t;


/* this function should configure prescaler and enables the TWI */
ErrorState_t I2C_MasterInit(I2C_SCL_FREQ_t SCL_FREQ);

/* this function should configure slave address */
ErrorState_t I2C_SlaveInit(uint8 LOC_u8SlaveAdress);

/* this function should send 1 byte to the other device */
ErrorState_t I2C_Master_u8WriteDataByte_ACK(uint8 copy_u8data);

/* this function should send start condition */
ErrorState_t I2C_Master_u8StartCondition(void);

/* repeated start condition */
ErrorState_t I2C_Master_u8ReStartCondition (void);

/* write slave address + write */
ErrorState_t I2C_Master_u8SendSLA_Write_ACK(uint8 Copy_u8SlaveAddress);

/* this function should send stop condition */
ErrorState_t I2C_Master_u8StopCondition(void);

/* this function should receive 1 byte and respond with ACK */
ErrorState_t I2C_Master_u8ReadDataByte_ACK(uint8 * pdata);

ErrorState_t I2C_Master_u8SendSLA_Read_ACK (uint8 Copy_u8SlaveAddress);

/* this function should receive 1 byte and respond with NO ACK */
ErrorState_t I2C_Master_u8ReadDataByte_NOTACK(uint8 * pdata);

/* this function should read status of status register */
ErrorState_t getStatus(uint8 * status);


#endif /* I2C_INTERFACE_H_ */

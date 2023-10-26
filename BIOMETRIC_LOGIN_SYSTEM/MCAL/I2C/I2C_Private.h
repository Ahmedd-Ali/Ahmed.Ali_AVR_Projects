/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : I2C                  *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_


/*============     [TWI] Registers     ============*/
#define     TWBR_REG       (*(volatile uint8 *)(0x20))        // TWI Bit Rate Register TWBR
#define     TWCR_REG       (*(volatile uint8 *)(0x56))        // TWI Control Register  TWCR
#define     TWSR_REG       (*(volatile uint8 *)(0x21))        // TWI Status Register   TWSR
#define     TWDR_REG       (*(volatile uint8 *)(0x23))        // TWI Data Register     TWDR
#define     TWAR_REG       (*(volatile uint8 *)(0x22))        // TWI (Slave) Address Register TWAR

/*=======   TWI [TWCR] BITS  ========*/
#define     TWCR_TWIE                0             // Bit 0  TWIE: TWI Interrupt Enable
#define     TWCR_TWEN                2             // Bit 2  TWEN: TWI Enable Bit
#define     TWCR_TWWC                3             // Bit 3  TWWC: TWI Write Collision Flag
#define     TWCR_TWSTO               4             // Bit 4  TWSTO: TWI STOP Condition Bit
#define     TWCR_TWSTA               5             // Bit 5  TWSTA: TWI START Condition Bit
#define     TWCR_TWEA                6             // Bit 6  TWEA: TWI Enable Acknowledge Bit
#define     TWCR_TWINT               7             // Bit 7  TWINT: TWI Interrupt Flag

/*=======   TWI [TWSR] BITS  ========*/
#define     TWSR_TWPS0               0             // Bits [1:0]  TWPS: TWI Prescaler Bits
#define     TWSR_TWPS1               1             // Bits [1:0]  TWPS: TWI Prescaler Bits
#define     TWSR_TWS3                3             // Bits [7:3]  TWS: TWI Status
#define     TWSR_TWS4                4             // Bits [7:3]  TWS: TWI Status
#define     TWSR_TWS5                5             // Bits [7:3]  TWS: TWI Status
#define     TWSR_TWS6                6             // Bits [7:3]  TWS: TWI Status
#define     TWSR_TWS7                7             // Bits [7:3]  TWS: TWI Status

/*=======   TWI [TWAR] BITS  ========*/
#define     TWAR_TWGCE               0             // Bit 0  TWGCE: TWI General Call Recognition Enable Bit
#define     TWAR_TWA0                1             // Bits 7..1  TWA: TWI (Slave) Address Register
#define     TWAR_TWA1                2             // Bits 7..1  TWA: TWI (Slave) Address Register
#define     TWAR_TWA2                3             // Bits 7..1  TWA: TWI (Slave) Address Register
#define     TWAR_TWA3                4             // Bits 7..1  TWA: TWI (Slave) Address Register
#define     TWAR_TWA4                5             // Bits 7..1  TWA: TWI (Slave) Address Register
#define     TWAR_TWA5                6             // Bits 7..1  TWA: TWI (Slave) Address Register
#define     TWAR_TWA6                7             // Bits 7..1  TWA: TWI (Slave) Address Register

/*=======   TWI [TWDR] BITS  ========*/
#define     TWDR_TWD0               0             // Bits 0  TWD0: Read/Write BIT That Send with 7-Bits of Address

/*=======   Private Macros  ========*/
#define     STATUS_BIT_MASK		 0xF8

/*=======   Status Codes for Master Transmitter Mode  ========*/

#define MASTER_START_ACK                   0x08       // Master transmit START condition
#define MASTER_REP_START_ACK               0x10       // Master transmit Repeated START conditions
#define MASTER_SLA_Write_ACK               0x18       // Master transmit ( Slave Address + Write request + ACK [Received] )
#define MASTER_SLA_Write_NOTACK            0x20       // Master transmit ( Slave Address + Write request + NOTACK [Received] )
#define MASTER_WR_DataByte_ACK             0x28       // Master transmit ( Data Byte + ACK [Received] )
#define MASTER_WR_DataByte_NOTACK          0x30       // Master transmit ( Data Byte + NOTACK [Received] )

/*=======    Status Codes for Master Receiver Mode    ========*/
#define MASTER_SLA_Read_ACK                0x40       // Master transmit ( Slave Address + Read request + ACK [Received] )
#define MASTER_SLA_Read_NOTACK             0x48       // Master transmit ( Slave Address + Read request + NOTACK [Received] )
#define MASTER_RD_DataByte_ACK             0x50       // Master Received ( Data Byte + ACK [Returned] )
#define MASTER_RD_DataByte_NOTACK          0x58       // Master Received ( Data Byte + NOTACK [Returned] )


#endif /* I2C_PRIVATE_H_ */

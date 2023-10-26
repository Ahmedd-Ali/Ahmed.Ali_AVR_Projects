

#include <util/delay.h>
/* Include Header Files From LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "EXT_EEPROM_Config.h"
#include "EXT_EEPROM_Private.h"
#include "EXT_EEPROM_Interface.h"
#include "I2C_Interface.h"



ErrorState_t EEPROM_SendDataByte(uint16 Copy_u16LocationAddress, uint8 Copy_u8DataByte)
{
	ErrorState_t ret= 0;
    uint8 Local_Address;

    //Local_Address = EEPROM_FIXED_ADDRESS_W | (EEPROM_A2<<2) | ((uint8)(Copy_u16LocationAddress>>8));
    Local_Address = EEPROM_FIXED_ADDRESS_W | ((Copy_u16LocationAddress>>8) << 1);

    // Send Start Condition
    ret|= I2C_Master_u8StartCondition();
    // Send the address packet
    ret|= I2C_Master_u8WriteDataByte_ACK(Local_Address);
    // send the rest 8 BITS of the location Address
    ret|= I2C_Master_u8WriteDataByte_ACK( (uint8)(Copy_u16LocationAddress));
    // Send The Data Byte to the Memory Location
    ret|= I2C_Master_u8WriteDataByte_ACK(Copy_u8DataByte);
    // Send Stop Condition
    ret|= I2C_Master_u8StopCondition();
    // Delay Until the Write cycle is finished
    _delay_ms(10);

    return ret;
}

ErrorState_t EEPROM_ReadDataByte(uint16 Copy_u16LocationAddress, uint8 * Copy_u8pDataByte)
{
	ErrorState_t ret= E_OK;
    uint8 Local_Address;

    Local_Address= EEPROM_FIXED_ADDRESS_W | (((uint8)(Copy_u16LocationAddress>>8)) << 1) ;
    // Send Start Condition 
    ret|= I2C_Master_u8StartCondition();
    // Send the address packet with Write operation
    ret|= I2C_Master_u8WriteDataByte_ACK(Local_Address);
    // send the rest 8 BITS of the location Address
    ret|= I2C_Master_u8WriteDataByte_ACK((uint8)(Copy_u16LocationAddress) );
    // Send Repeated Start to change write request to Read request
    ret|= I2C_Master_u8ReStartCondition();
    // Send the address packet with Read operation
    ret|= I2C_Master_u8WriteDataByte_ACK(EEPROM_FIXED_ADDRESS_R);
    // Get The Data From Memory
    ret|= I2C_Master_u8ReadDataByte_NOTACK(Copy_u8pDataByte);
    // Send Stop Condition
    ret|= I2C_Master_u8StopCondition();
    // Delay Until the Read cycle is finished
    _delay_ms(10);

    return ret;
}

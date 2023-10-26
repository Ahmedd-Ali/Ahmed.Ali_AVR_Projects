/* File Gaurd by ifndef & endif */
#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H



ErrorState_t EEPROM_SendDataByte(uint16 Copy_u16LocationAddress, uint8 Copy_u8DataByte);

ErrorState_t EEPROM_ReadDataByte(uint16 Copy_u16LocationAddress, uint8 * Copy_u8pDataByte);


#endif

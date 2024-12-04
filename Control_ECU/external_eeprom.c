 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for the External EEPROM Memory
 *
 * Author: Doaa Said
 *
 *******************************************************************************/
#include "external_eeprom.h"
#include "../MCAL_Drivers/TWI.h"
#include "util/delay.h"

uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR; 
		 
    /* Send the required memory location address */
    TWI_writeByte((uint8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;
		
    /* write byte to eeprom */
    TWI_writeByte(u8data);
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();
	
    return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;
		
    /* Send the required memory location address */
    TWI_writeByte((uint8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;
		
    /* Send the Repeated Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_REP_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
    if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *u8data = TWI_readByteWithNACK();
    if (TWI_getStatus() != TWI_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();

    return SUCCESS;
}
/*
 * Description:
 * Writes an array of bytes to the EEPROM.
 * Parameters:
 *   - u16addr: The starting address in EEPROM to write the data.
 *   - array: Pointer to the array of data to be written.
 *   - size: The number of bytes to write from the array.
 */
void EEPROM_writeArray(uint16 u16addr, uint8* array, uint8 size) {
    // Loop through each element of the array
	for (int i = 0; i < size; i++) {
        // Write each byte to the specified EEPROM address
		EEPROM_writeByte(u16addr + i, array[i]);

		_delay_ms(10);
	}
}

/*
 * Description:
 * Reads an array of bytes from the EEPROM.
 * Parameters:
 *   - u16addr: The starting address in EEPROM to read the data from.
 *   - array: Pointer to the array where the read data will be stored.
 *   - size: The number of bytes to read into the array.
 */
void EEPROM_readArray(uint16 u16addr, uint8 *array, uint8 size) {
    // Loop through each element of the array
	for (int i = 0; i < size; i++) {
        // Read each byte from the specified EEPROM address
		EEPROM_readByte(u16addr + i, &array[i]);

		_delay_ms(10);
	}
}

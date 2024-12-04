 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.h
 *
 * Description: Header file for the External EEPROM Memory
 *
 * Author:Doaa Said
 *
 *******************************************************************************/

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "../imp_files/std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0   // Indicates an error occurred
#define SUCCESS 1 // Indicates the operation was successful

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Writes a single byte to the specified address in the EEPROM.
 * Parameters:
 *   - u16addr: The address in EEPROM where the byte will be written.
 *   - u8data: The byte of data to be written to EEPROM.
 * Returns:
 *   - SUCCESS if the write operation is successful; ERROR otherwise.
 */
uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data);

/*
 * Description:
 * Reads a single byte from the specified address in the EEPROM.
 * Parameters:
 *   - u16addr: The address in EEPROM from which the byte will be read.
 *   - u8data: Pointer to store the read byte.
 * Returns:
 *   - SUCCESS if the read operation is successful; ERROR otherwise.
 */
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data);

/*
 * Description:
 * Writes an array of bytes to the EEPROM starting from the specified address.
 * Parameters:
 *   - u16addr: The starting address in EEPROM where the array will be written.
 *   - array: Pointer to the array of data to be written.
 *   - size: The number of bytes to write from the array.
 */
void EEPROM_writeArray(uint16 u16addr, uint8* array, uint8 size);

/*
 * Description:
 * Reads an array of bytes from the EEPROM starting from the specified address.
 * Parameters:
 *   - u16addr: The starting address in EEPROM from which the array will be read.
 *   - array: Pointer to store the read data.
 *   - size: The number of bytes to read into the array.
 */
void EEPROM_readArray(uint16 u16addr, uint8 *array, uint8 size);

#endif /* EXTERNAL_EEPROM_H_ */

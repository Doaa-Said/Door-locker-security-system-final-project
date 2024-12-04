/*
 * I2C.c
 *
 *  Created on: Oct 21, 2024
 *     Author: Doaa
 */

#include "TWI.h"

#include "../MCAL_Drivers/GPIO.h"
#include"../imp_files/common_macros.h"
#include"../imp_files/std_types.h"
void TWI_init(TWI_ConfigType *TWI_ConfigType) {

	/* TWPS=the configured prescaler                                                    */
	TWSR_REG.Bits.TWPS0_Bit = GET_BIT(TWI_ConfigType->Prescaler, 0);

	TWSR_REG.Bits.TWPS1_Bit = GET_BIT(TWI_ConfigType->Prescaler, 1);
	/*TWBR=*/
	TWBR_REG.Byte = (F_CPU - (16 * (TWI_ConfigType->SCL_frequency)))
			/ (2 * (TWI_ConfigType->SCL_frequency)
					* (1 << (2 * TWI_ConfigType->Prescaler)));

	/* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
	 General Call Recognition: Off */
	TWAR_REG.Byte = (TWI_ConfigType->my_address) << TWA0_Bitnum;

	TWCR_REG.Byte = TWI_Enable_Bit;/* enable TWI */
}
void TWI_start(void) {
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR_REG.Byte = TWI_CLEAR_INT_FLAG_W_SET_ENABLE_Bit_W_START_CONDITION;
	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while (!TWCR_REG.Bits.TWINT_Bit)
		;

}
void TWI_stop(void) {
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR_REG.Byte = TWI_CLEAR_INT_FLAG_W_SET_ENABLE_Bit_W_STOP_CONDITION;

}
void TWI_writeByte(uint8 data) {
	/* Put data On TWI data Register */
	TWDR_REG = data;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR_REG.Byte = TWI_CLEAR_INT_FLAG_W_SET_ENABLE_Bit;
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while (TWCR_REG.Bits.TWINT_Bit == LOGIC_LOW)
		;

}
uint8 TWI_readByteWithACK(void) {
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR_REG.Byte = TWI_CLEAR_INT_FLAG_W_SET_ENABLE_Bit_W_ACK_Bit;
	/* Wait for TWINT flag set in TWCR Register (data received successfully)*/
	while (!TWCR_REG.Bits.TWINT_Bit)
		;
	/* Read Data */
	return TWDR_REG;

}
uint8 TWI_readByteWithNACK(void) {
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR_REG.Byte = TWI_CLEAR_INT_FLAG_W_SET_ENABLE_Bit;
	/* Wait for TWINT flag set in TWCR Register (data received successfully)*/
	while (!TWCR_REG.Bits.TWINT_Bit)
		;
	/* Read Data */
	return TWDR_REG;

}

uint8 TWI_getStatus(void) {
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR_REG.Byte & 0xF8;
	return status;
}


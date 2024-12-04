/******************************************************************************
 *
 * Module: I2C
 *
 * File Name: TWI.h
 *
 * Description: header file for the TWI AVR driver
 *
 * Author: Doaa Said
 *
 *******************************************************************************/
#ifndef TWI_H_
#define TWI_H_
#include"../imp_files/std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TWCR_REG (*(volatile TWI_TWCR_Type*)(0x56))
#define TWSR_REG (*(volatile TWI_TWSR_Type*)(0x21))
#define TWDR_REG (*(volatile uint8*)(0x23))
#define TWAR_REG (*(volatile TWI_TWAR_Type*)(0x22))
#define TWBR_REG (*(volatile TWI_TWBR_Type*)(0x20))

#define TWA0_Bitnum 1

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */
/* I2C values of Bits of TWCR_REG   */
#define TWI_Enable_Bit 0x04
#define TWI_CLEAR_INT_FLAG_W_SET_ENABLE_Bit_W_START_CONDITION 0xA4
#define TWI_CLEAR_INT_FLAG_W_SET_ENABLE_Bit_W_STOP_CONDITION 0x94
#define TWI_CLEAR_INT_FLAG_W_SET_ENABLE_Bit 0x84
#define TWI_CLEAR_INT_FLAG_W_SET_ENABLE_Bit_W_ACK_Bit 0xC4




/*******************************************************************************
 *                      Types Declaration                                    *
 *******************************************************************************/
typedef enum {
	fSCL, fSCL_over_4, fSCL_over_16, fSCL_over_64
} TWI_Prescaler;
typedef enum {
	NORMAL_MODE = 100000,
	FAST_MODE = 400000,
	FAST_MODE_PLUS = 1000000,
	HIGH_SPEED_MODE = 3400000
} TWI_Data_transfer_rate;
typedef struct {
	TWI_Data_transfer_rate SCL_frequency;
	TWI_Prescaler Prescaler;
	uint8 my_address;
} TWI_ConfigType;
typedef union {
	uint8 Byte;
	struct {
		uint8 TWIE_Bit :1;
		uint8 :1;
		uint8 TWEN_Bit :1;
		uint8 TWWC_Bit :1;
		uint8 TWSTO_Bit :1;
		uint8 TWSTA_Bit :1;
		uint8 TWEA_Bit :1;
		uint8 TWINT_Bit :1;
	} Bits;
} TWI_TWCR_Type;

typedef union {
	uint8 Byte;
	struct {
		uint8 TWPS0_Bit :1;
		uint8 TWPS1_Bit :1;
		uint8 :1;
		uint8 TWS3_Bit :1;
		uint8 TWS4_Bit :1;
		uint8 TWS5_Bit :1;
		uint8 TWS6_Bit :1;
		uint8 TWS7_Bit :1;
	} Bits;
} TWI_TWSR_Type;

typedef union {
	uint8 Byte;
	struct {
		uint8 TWD0_Bit :1;
		uint8 TWD1_Bit :1;
		uint8 TWD2_Bit :1;
		uint8 TWD3_Bit :1;
		uint8 TWD4_Bit :1;
		uint8 TWD5_Bit :1;
		uint8 TWD6_Bit :1;
		uint8 TWD7_Bit :1;
	} Bits;
} TWI_TWDR_Type;
typedef union {
	uint8 Byte;
	struct {
		uint8 TWGCE_Bit :1;
		uint8 TWA0_Bit :1;
		uint8 TWA1_Bit :1;
		uint8 TWA2_Bit :1;
		uint8 TWA3_Bit :1;
		uint8 TWA4_Bit :1;
		uint8 TWA5_Bit :1;
		uint8 TWA6_Bit :1;
	} Bits;
} TWI_TWAR_Type;
typedef union {
	uint8 Byte;
	struct {
		uint8 TWBR0_Bit :1;
		uint8 TWBR1_Bit :1;
		uint8 TWBR2_Bit :1;
		uint8 TWBR3_Bit :1;
		uint8 TWBR4_Bit :1;
		uint8 TWBR5_Bit :1;
		uint8 TWBR6_Bit :1;
		uint8 TWBR7_Bit :1;
	} Bits;
} TWI_TWBR_Type;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(TWI_ConfigType *TWI_ConfigType);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);

#endif /* TWI_H_ */

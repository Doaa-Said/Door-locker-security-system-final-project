/******************************************************************************
 * File Name: main.h
 *
 * Description: Header file for the CONTROL_ECU application
 *
 * Author: Doaa Said
 *
 *******************************************************************************/
#ifndef MAIN_H_
#define MAIN_H_
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
// Register definition for the status register (SREG)
#define SREG_REG      (*(volatile SREG_Type*)0x5F)

// size of the password
#define PASS_SIZE 5

// Status constants for password matching
#define matched 1
#define unmatched 0

// Communication codes between HMI and Control
#define HMI_ready 0x01
#define CONTROL_ready 0x02
#define OPEN_DOOR 0X03
#define CHANGE_PASS 0X04
#define SAVE_PASS_and_confirm 0X05
#define CHECK_PASS 0X06
#define recieve_result 0x44

// Motion detection status
#define people_detected 1
#define people_notdetected 0

// Alarm signal code
#define Alarm 0x55



/*******************************************************************************
 *                      Types Declaration                                    *
 *******************************************************************************/

// Structure to represent the bits of the status register (SREG)
typedef union {
	uint8 Byte; // Byte representation
	struct {
		uint8 C_Bit :1; // Carry flag
		uint8 Z_Bit :1; // Zero flag
		uint8 N_Bit :1; // Negative flag
		uint8 V_Bit :1; // Overflow flag
		uint8 S_Bit :1; // Sign flag
		uint8 H_Bit :1; // Half-carry flag
		uint8 T_Bit :1; // T flag
		uint8 I_Bit :1; // Interrupt flag
	} Bits; // Individual bits
} SREG_Type;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
// Function to compare two password arrays and return whether they match
boolean is_match(uint8* p1, uint8* p2);

// Function to send the result of a password comparison to the UART
uint8 send_result(uint8* p1, uint8* p2);

// Function to save a password to the external EEPROM
void save_pass(uint8* pass);

// Function to read the saved password from the external EEPROM
void check_pass(uint8* pass_saved);

// Function to stop the DC motor and close the door
void close_door(void);

// Function to open the door if a person is detected
void open_door(void);

// Function to deactivate the alarm and turn off the buzzer
void close_Alarm(void);


#endif /* MAIN_H_ */

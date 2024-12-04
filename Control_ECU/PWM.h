/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: PWM.h
 *
 * Description: header file for the ATmega32 PWM driver
 *
 * Author: Doaa Said
 */
#ifndef PWM_H_
#define PWM_H_

#include "../imp_files/std_types.h" // Include standard type definitions

/*******************************************************************************
 //                                Definitions                                  *
 *******************************************************************************/

// Register definitions for Timer 0
#define TCCR0_REG  (*(volatile Timer0_TCCR0_Type*) 0x53) // Timer/Counter Control Register
#define OCR0_REG   (*(volatile uint8*) 0x5C)                // Output Compare Register
#define TCNT0_REG  (*(volatile uint8*) 0x52)                // Timer/Counter Register

// Definitions for PWM output pin
#define PWM_OCO_PORT_ID   PORTB_ID  // Port ID for PWM output
#define PWM_OCO_PIN_ID    PIN3_ID    // Pin ID for PWM output

// Maximum ticks for PWM
#define PWM_MAX_TICKS     256

/*******************************************************************************
 //                      Types Declaration                                     *
 *******************************************************************************/

// Enumeration for PWM modes
typedef enum {
	OC0_disconnected,       // Output Compare 0 disconnected
	non_inverting_mode = 2, // Non-inverting mode
	inverting_mode          // Inverting mode
} PWM_Fast_PWM_Mode;

// Enumeration for PWM prescaler values
typedef enum {
	NO_CLOCK,        // No clock source
	NO_Prescaling,   // No prescaling
	clk_over_8,      // Clock / 8
	clk_over_64,     // Clock / 64
	clk_over_256,    // Clock / 256
	clk_over_1024    // Clock / 1024
} PWM_Prescaler;

// Configuration structure for PWM
typedef struct {
	PWM_Fast_PWM_Mode Mode; // PWM mode configuration
	PWM_Prescaler Prescaler; // Prescaler configuration
} PWM_ConfigType;

// Union for Timer 0 Control Register
typedef union {
	uint8 Byte; // Full byte access
	struct {
		uint8 CS00_Bit :1; // Clock Select Bit 0
		uint8 CS01_Bit :1; // Clock Select Bit 1
		uint8 CS02_Bit :1; // Clock Select Bit 2
		uint8 WGM01_Bit :1; // Waveform Generation Mode Bit 1
		uint8 COM00_Bit :1; // Compare Output Mode Bit 0
		uint8 COM01_Bit :1; // Compare Output Mode Bit 1
		uint8 WGM00_Bit :1; // Waveform Generation Mode Bit 0
		uint8 FOC0_Bit :1;  // Force Output Compare
	} Bits; // Bit access
} Timer0_TCCR0_Type;

/*******************************************************************************
 //                       Functions Prototypes                                 *
 *******************************************************************************/
/*
 * Description:
 * Generate a PWM signal with configured prescaler, mode, and duty cycle.
 */
void PWM_Timer0_Start(const PWM_ConfigType *config, uint8 duty_cycle); // Start PWM on Timer 0

#endif /* PWM_H_ */

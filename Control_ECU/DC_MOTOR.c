/******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: DC_MOTOR.c
 *
 * Description: source file for the DC-motor driver
 *
 * Author: Doaa Said
 *
 *******************************************************************************/
#include "DC_MOTOR.h"

#include "../MCAL_Drivers/GPIO.h"
#include "../MCAL_Drivers/PWM.h"
static PWM_ConfigType PWM_config={non_inverting_mode,clk_over_64};
void DcMotor_Init(void) {
	// Set the direction of the IN1,IN2 pins to output
	GPIO_setupPinDirection(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID,
			PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID,
			PIN_OUTPUT);
	/// Set the control pins initially for DC motor IN1,2 to logic low (turning it off)
	GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);

}

void DcMotor_Rotate(DcMotor_State state, uint8 speed) {
	// Check if the provided state is valid
	if (state >= NUM_OF_STATES) {
		/* Do Nothing */
	} else {
		// Control the motor based on the desired state
		switch (state) {
		case CW: // Clockwise rotation
			GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID,
					LOGIC_HIGH);
			break;
		case A_CW: // Anti-Clockwise rotation
			GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID,
					LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
			break;
		case Stop: // Stop the motor
			GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
			break;

		}
		// Start the PWM signal for the motor speed
		PWM_Timer0_Start(&PWM_config,(uint8) (((uint16) speed * (PWM_MAX_TICKS)) / (100)));
	}
}


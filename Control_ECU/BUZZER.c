/******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name:BUZZER.c
 *
 * Description: source file for the BUZZER driver
 *
 * Author: Doaa Said
 *
 *******************************************************************************/
#include "BUZZER.h"

#include "../MCAL_Drivers/GPIO.h"

void Buzzer_init(void) {
	// Set the direction of the buzzer pin to output
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);

}

void Buzzer_on(void) {
	//turn on buzzer
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);

}
void Buzzer_off(void) {
	//turn off buzzer
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);

}

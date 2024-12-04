/******************************************************************************
 *
 * Module: PIR SENSOR
 *
 * File Name: PIR.h
 *
 * Description: source file for the flame sensor driver
 *
 * Author: Doaa Said
 *
 *******************************************************************************/
#include "PIR.h"

#include "../MCAL_Drivers/GPIO.h"
#include "../imp_files/common_macros.h"

void PIR_init(void) {
// Set the direction of the PIR Sensor pin to input
	GPIO_setupPinDirection(PIR_PORT_ID, PIR_PIN_ID, PIN_INPUT);

}
uint8 PIR_getState(void) {
// Read and return the state of the PIR sensor pin
	return GPIO_readPin(PIR_PORT_ID, PIR_PIN_ID);

}

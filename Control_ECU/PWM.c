/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: PWM.c
 *
 * Description: Source file for the ATmega32 PWM driver
 *
 * Author: Doaa Said
 *
 *******************************************************************************/
#include"PWM.h"

#include "GPIO.h"
#include "../imp_files/common_macros.h"
uint8 g_PWM_MAX_TICKS ;
void PWM_Timer0_Start(const PWM_ConfigType* config,uint8 duty_cycle) {

	TCCR0_REG.Bits.FOC0_Bit = 0;/*Fast PWM mode FOC0=0*/
	TCCR0_REG.Bits.WGM00_Bit = 1;/*Fast PWM Mode WGM01=1 & WGM00=1*/
	TCCR0_REG.Bits.WGM01_Bit = 1;

	TCCR0_REG.Bits.COM00_Bit = GET_BIT(config->Mode,0);/*select configured mode*/
	TCCR0_REG.Bits.COM01_Bit = GET_BIT(config->Mode,1);
	TCCR0_REG.Bits.CS00_Bit = GET_BIT(config->Prescaler,0);/*select configured prescaler*/
	TCCR0_REG.Bits.CS01_Bit = GET_BIT(config->Prescaler,1);
	TCCR0_REG.Bits.CS02_Bit = GET_BIT(config->Prescaler,2);
	TCNT0_REG = 0; //Set Timer Initial Value to 0
	GPIO_setupPinDirection(PWM_OCO_PORT_ID, PWM_OCO_PIN_ID, PIN_OUTPUT);
	// Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC
	OCR0_REG = duty_cycle; // Set Compare Value


}

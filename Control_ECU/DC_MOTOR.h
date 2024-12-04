/******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: DC_MOTOR.h
 *
 * Description: Header file for the DC motor driver
 *
 * Author:Doaa Said
 *
 *******************************************************************************/
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "../imp_files/std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/*DC motor HW Ports and Pins Ids */
#define DC_MOTOR_IN1_PORT_ID                  PORTD_ID
#define DC_MOTOR_IN1_PIN_ID                   PIN6_ID

#define DC_MOTOR_IN2_PORT_ID                  PORTD_ID
#define DC_MOTOR_IN2_PIN_ID                   PIN7_ID

#define NUM_OF_STATES            3

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum {
	CW, A_CW, Stop
} DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for Initializing the DC motor by setting the direction for the motor pins and stopping the
 motor at the beginning.
 */
void DcMotor_Init(void);

/*
 * Description :
 * Function responsible for Controlling the motor's state (Clockwise/Anti-Clockwise/Stop) and adjusts the speed based
 on the input duty cycle.
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* DC_MOTOR_H_ */

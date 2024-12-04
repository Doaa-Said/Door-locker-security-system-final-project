/******************************************************************************
 *
 * Module: PIR SENSOR
 *
 * File Name: PIR.h
 *
 * Description: header file for the PIR driver
 *
 * Author: Doaa Said
 *
 *******************************************************************************/
#ifndef PIR_H_
#define PIR_H_

#include "../imp_files/std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/*PIR sensor HW Port and Pin Id */
#define PIR_PORT_ID  PORTC_ID
#define PIR_PIN_ID   PIN2_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :Function responsible for Initializing
 *  the PIR sensor pin direction.
 */
void PIR_init(void);


/*
 * Description :Function responsible for Reading
 *  the value from the PIR sensor and returns it.
 */

uint8 PIR_getState(void);


#endif /* PIR_H_ */

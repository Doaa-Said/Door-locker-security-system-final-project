/******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name:BUZZER.h
 *
 * Description: header file for the BUZZER driver
 *
 * Author: Doaa Said
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_
#include "../imp_files/std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* buzzer HW Port and Pin Id */
#define BUZZER_PORT_ID  PORTC_ID
#define BUZZER_PIN_ID   PIN7_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 *Description :Function responsible for Initializing
 * the buzzer pin direction and turn off the buzzer.
 */
void Buzzer_init(void);

/*
 *Description :Function responsible for Activating the buzzer.
 */

void Buzzer_on(void);

/*
 *Description :Function responsible for Deactivating the buzzer.
 */
void Buzzer_off(void);

#endif /* BUZZER_H_ */

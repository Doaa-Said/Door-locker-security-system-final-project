/******************************************************************************
 * File Name: main.c
 *
 * Description: source file for the CONTROL_ECU application
 *
 * Author: Doaa Said
 *
 *******************************************************************************/
#include "../imp_files/std_types.h"
#include "../MCAL_Drivers/UART.h"
#include "../MCAL_Drivers/TWI.h"
#include "../MCAL_Drivers/Timer.h"

#include "../HAL_Drivers/external_eeprom.h"
#include "../HAL_Drivers/BUZZER.h"
#include "../HAL_Drivers/PIR.h"
#include "../HAL_Drivers/DC_MOTOR.h"
#include <util/delay.h>
#include "main.h"
/*Timer configuration for Timer1 in CTC mode
 ** F_CPU = 8MHz, prescaler = 256
 ** For a timer to generate an interrupt every second:
 ** OCR1A=1s/(256/8000000)=31250;
 ** Therefore, we set OCR1A to 31250
 */
Timer_ConfigType Timer_config = {0, 31250, TIMER1_ID, CLK_OVER_256, CTC_1};



// Main function
int main(void) {
    SREG_REG.Bits.I_Bit = LOGIC_HIGH; // Enable global interrupts
    uint8 pass[6], tested_pass[6], pass_saved[6];
    uint8 confirm_pass[6];

    // TWI configuration
    TWI_ConfigType Twi_CONFIG = {FAST_MODE,fSCL, 0x01};
    TWI_init(&Twi_CONFIG); // Initialize TWI/I2C Driver

    // Timer configuration
    Buzzer_init(); // Initialize buzzer
    DcMotor_Init(); // Initialize DC motor
    PIR_init(); // Initialize PIR sensor

    // UART configuration
    UART_ConfigType config = {EIGHT_BITS, DISABLED, one_bit, 9600};
    UART_init(&config); // Initialize UART

    for (;;) {
        switch (UART_recieveByte()) {
            case SAVE_PASS_and_confirm:
                UART_sendByte(CONTROL_ready); // Send control ready signal
                while (UART_recieveByte() != HMI_ready);
                UART_receiveString(pass); // Receive password
                UART_receiveString(confirm_pass); // Receive confirmed password
                if (send_result(pass, confirm_pass)) {
                    save_pass(pass); // Save password if matched
                }
                break;

            case CHECK_PASS:
                UART_sendByte(CONTROL_ready); // Send control ready signal
                UART_receiveString(tested_pass); // Receive tested password
                check_pass(pass_saved); // Check saved password
                send_result(pass_saved, tested_pass);

                break;

            case OPEN_DOOR:
            	DcMotor_Rotate(CW, 99);
            	 g_total_ticks = 15; // Set total ticks
                Timer_init(&Timer_config); // Initialize timer
                Timer_setCallBack(open_door, TIMER1_ID); // Set callback to open door

                break;

            case Alarm:
                Buzzer_on(); // Turn on buzzer
                g_total_ticks = 60; // Set total ticks
                Timer_init(&Timer_config); // Initialize timer
                Timer_setCallBack(close_Alarm, TIMER1_ID); // Set callback to close alarm

                break;
        }
    }
}

// Function to compare two password arrays
boolean is_match(uint8* p1, uint8* p2) {
    for (int i = 0; i < 5; i++) {
        if (p1[i] != p2[i]) {
            return unmatched; // Return unmatched if any character differs
        }
    }
    return matched; // Return matched if all characters are the same
}

// Function to send result of password comparison
uint8 send_result(uint8* p1, uint8* p2) {
    boolean is_matched = is_match(p1, p2);
    UART_sendByte(CONTROL_ready); // Send control ready signal
    while (UART_recieveByte() != HMI_ready); // Wait for HMI ready signal
    UART_sendByte(is_matched); // Send match result
    return is_matched;
}

// Function to save a password to EEPROM
void save_pass(uint8* pass) {
    EEPROM_writeArray(0x00, pass, PASS_SIZE); // Write password to EEPROM
}

// Function to check saved password from EEPROM
void check_pass(uint8* pass_saved) {
    EEPROM_readArray(0x00, pass_saved, PASS_SIZE); // Read password from EEPROM
}

// Function to close the door
void close_door(void) {
    DcMotor_Rotate(Stop, LOGIC_LOW); // Stop the motor
    Timer_deInit(TIMER1_ID); // Deinitialize timer
}

// Function to open the door
void open_door(void) {
    DcMotor_Rotate(Stop, LOGIC_LOW); // Stop the motor
    Timer_deInit(TIMER1_ID); // Deinitialize timer

    // Wait for PIR sensor to detect a person
    while (PIR_getState() == people_notdetected);

    if (PIR_getState() == people_detected) {
        while (UART_recieveByte() != HMI_ready); // Wait for HMI ready signal
        UART_sendByte(people_detected); // Send detected signal
        while (PIR_getState() == people_detected);
        UART_sendByte(people_notdetected); // Send not detected signal
        DcMotor_Rotate(A_CW, 99); // Rotate motor to open the door
        g_total_ticks = 15; // Set total ticks
        Timer_init(&Timer_config); // Initialize timer
        Timer_setCallBack(close_door, TIMER1_ID); // Set callback for closing the door

    }
}

// Function to close the alarm
void close_Alarm() {
    Timer_deInit(TIMER1_ID); // Deinitialize timer
    Buzzer_off(); // Turn off the buzzer
}

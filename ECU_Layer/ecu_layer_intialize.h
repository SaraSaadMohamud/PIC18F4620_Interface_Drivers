/* 
 * File:   ecu_layer_intialize.h
 * Author: DELL
 *
 * Created on August 19, 2024, 10:34 PM
 */

#ifndef ECU_LAYER_INTIALIZE_H
#define	ECU_LAYER_INTIALIZE_H

/* Section : Includes*/

#include"LED/ecu_led.h"
#include "button/ecu_button.h"
#include "Relay/relay.h"
#include "DC_Motoer/DC_Motor.h"
#include "../MCAL_Layer/Gpio/hal_gpio.h"
#include "Seven_Segment/ecu_seven_Seg.h"
#include "Keypad/ecu_keypad.h"

#include "Char_LCD/ecu_char_lcd.h"
#include "../MCAL_Layer/EEPROM/hal_eeprom.h"

#include "../MCAL_Layer/interrupt/mcal_external_interrupt.h"
#include "../MCAL_Layer/ADC/hal_adc.h"

#include "../MCAL_Layer/Timer0/hal_timer0.h"
#include "../MCAL_Layer/Timer1/hal_timer1.h"
#include "../MCAL_Layer/Timer2/hal_timer2.h"
#include "../MCAL_Layer/Timer3/hal_timer3.h"

#include "../MCAL_Layer/CCP1/hal-ccp1.h"
#include "../MCAL_Layer/USART/hal_usart.h"

#include "../MCAL_Layer/I2c/hal_I2C.h"

#include "../RealTimeClockDS1307/RealTimeClockDs1307.h"
/* Section : Macros Declaration */

/* Section : Function like Macros Declaration*/

/* Section : User Defined Data Type */

/* Section : Function Declaration */
void TIMER1_TIMER_INIT(void);
void TIMER1_COUNTER_INIT(void);
void TIMER3_APP_HANDELER(void);
void TIMER1_APP_ISR(void);

void CCP1_APP_ISR(void);

void EUSART_TX_APP_ISR(void);
void EUSART_RX_APP_ISR(void);
void EUSART_FRAM_ERORR_APP_ISR(void);
void EUSART_OVERRUN_ERROR_APP_ISR(void);
void MSSP_I2C_APP_ISR(void);

#endif	/* ECU_LAYER_INTIALIZE_H */


/* 
 * File:   hal_timer1.h
 * Author: DELL
 *
 * Created on September 11, 2024, 7:08 AM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* Section : Includes*/
#include <pic18f4620.h>
#include "../../MCAL_Layer/Gpio/hal_gpio.h"
#include "../../MCAL_Layer/mcal_std_types.h"
#include "../../MCAL_Layer/interrupt/mcal_internal_interrupt.h"
/* Section : Macros Declaration */
#define TIMER1_TIMER_MODE   0
#define TIMER1_COUNTER_MODE 1

#define TIMER1_ASYNC_COUNTER_MODE 1
#define TIMER1_SYNC_COUNTER_MODE  0

#define TIMER1_TIMER_OSCILLATOR_ENABLE  1
#define TIMER1_TIMER_OSCILLATOR_DISABLE 0

#define TIMER1_PRESCALER_DISABLE 0
#define TIMER1_PRESCALER_DIV_2   1
#define TIMER1_PRESCALER_DIV_4   2
#define TIMER1_PRESCALER_DIV_8   3

#define TIMER1_16BIT_MODE 1
#define TIMER1_8BIT_MODE  0
/* Section : Function like Macros Declaration*/
#define TIMER1_MODULE_ENABLE()  (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE() (T1CONbits.TMR1ON = 0)

#define TIMER1_TIMER_MODE_ENABLE()   (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE() (T1CONbits.TMR1CS = 1)

#define TIMER1_ASYNC_COUNTER_MODE_ENABLE() (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()  (T1CONbits.T1SYNC = 0)

#define TIMER1_EXTERNAL_TIMER_OSILLATOR_ENABLE()  (T1CONbits.T1OSCEN = 1)
#define TIMER1_EXTERNAL_TIMER_OSILLATOR_DISABLE() (T1CONbits.T1OSCEN = 0)

#define TIMER1_PRESCALER_VALUE_SELECT(_PRESCALER_VALUE) (T1CONbits.T1CKPS = _PRESCALER_VALUE)

#define TIMER1_16BIT_REGISTER_MODE_ENABLE() (T1CONbits.RD16 = 1)
#define TIMER1_8BIT_REGISTER_MODE_MODE()    (T1CONbits.RD16 = 0)

/*RETURN TIMER1 CLOCK SOURCE STATUS*/
#define TIMER1_SYSTEM_CLOCK_SOURCE_STATUS() (T1CONbits.T1RUN )

/* Section : User Defined Data Type */

typedef struct{
    #if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void(*TIMER1_INTERRUPT_HANDELER)(void);
        interrupt_priority_cfg TIMER1_INTERRUPT_PRIORITY;
    #endif
    uint16 Timer1_Preloaded_Value ;
    uint8 Timer1_Register_Read_Write_Mode : 1;
    uint8 Timer1_Oscillator_confige: 1;
    uint8 Timer1_prescaler_Value : 2;
    uint8 Timer1_Counter_Mode : 1;
    uint8 Timer1_Mode : 1;
    uint8 : 2;
    
}timer1_config_t;
/* Section : Function Declaration */
STD_ReturnType Timer1_Init(const timer1_config_t * timer);
STD_ReturnType Timer1_De_Init(const timer1_config_t * timer);
STD_ReturnType Timer1_Write_Value(const timer1_config_t * timer,uint16 value);
STD_ReturnType Timer1_Read_Value(const timer1_config_t * timer,uint16 *value);
#endif	/* HAL_TIMER1_H */


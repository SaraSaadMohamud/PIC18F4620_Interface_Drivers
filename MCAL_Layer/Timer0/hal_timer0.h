/* 
 * File:   hal_timer0.h
 * Author: DELL
 *
 * Created on September 9, 2024, 9:33 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/* Section : Includes*/
#include <pic18f4620.h>
#include "../Gpio/hal_gpio.h"
#include "../../MCAL_Layer/interrupt/mcal_internal_interrupt.h"
#include "../../MCAL_Layer/mcal_std_types.h"
/* Section : Macros Declaration */
#define TIMER0_TIMER_MODE   1
#define TIMER0_COUNTER_MODE 0

#define TIMER0_8BIT_REGISTER_SIZE_CFG 1
#define TIMER0_16BIT_REGISTER_SIZE_CFG 0

#define TIMER0_FALLING_EDGE_CFG 0
#define TIMER0_RISING_EDGE_CFG  1

#define TIMER0_PRESCALER_ENABLE_CFG  1
#define TIMER0_PRESCALER_DISABLE_CFG 0

/* Section : Function like Macros Declaration*/
#define TIMER0_MODULE_ENABLE() (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE() (T0CONbits.TMR0ON = 0)

#define TIMER0_TIMER0_MODE_ENABLE()  (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE() (T0CONbits.T0CS = 1)

#define TIMER0_FALLING_EDGE_ENABLE()   (T0CONbits.T0SE = 1)
#define TIMER0_RISING_EDGE_ENABLE() (T0CONbits.T0SE = 0)

#define TIMER0_PRESCALER_ENABLE()  (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE() (T0CONbits.PSA = 1)

#define TIMER0_16BIT_REGISTER_SIZE() (T0CONbits.T08BIT = 0)
#define TIMER0_8BIT_REGISTER_SIZE()  (T0CONbits.T08BIT = 1)

/* Section : User Defined Data Type */
typedef enum
{
    TIMER0_PRESCALER_DIV_2 = 0,
    TIMER0_PRESCALER_DIV_4,
    TIMER0_PRESCALER_DIV_8,
    TIMER0_PRESCALER_DIV_16,
    TIMER0_PRESCALER_DIV_32,
    TIMER0_PRESCALER_DIV_64,
    TIMER0_PRESCALER_DIV_128,
    TIMER0_PRESCALER_DIV_256,
}timer0_prescaler_select_t;

typedef struct {
    #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void(*timer0_interrupt_handeler)(void);
        interrupt_priority_cfg interrupt_priority;
    #endif
    timer0_prescaler_select_t timer0_prescaler_value;
    uint16 timer0_register_preload_value;
    uint8 timer0_prescaler_enable : 1;
    uint8 timer0_register_size : 1;
    uint8 timer0_counter_edge :1;
    uint8 timer0_mode : 1;
    uint8 : 4 ;
}timer0_config_t;
/* Section : Function Declaration */
STD_ReturnType Timer0_Init(const timer0_config_t * timer);
STD_ReturnType Timer0_De_Init(const timer0_config_t * timer);
STD_ReturnType Timer0_Write_Value(const timer0_config_t * timer,uint16 value);
STD_ReturnType Timer0_Read_Value(const timer0_config_t * timer,uint16 *value);
#endif	/* HAL_TIMER0_H */


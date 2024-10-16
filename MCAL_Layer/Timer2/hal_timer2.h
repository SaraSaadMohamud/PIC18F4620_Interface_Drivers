/* 
 * File:   hal_timer2.h
 * Author: DELL
 *
 * Created on September 11, 2024, 2:09 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H
/* Section : Includes*/
#include <pic18f4620.h>
#include "../../MCAL_Layer/mcal_std_types.h"
#include "../../MCAL_Layer/interrupt/mcal_internal_interrupt.h"
#include "../Gpio/hal_gpio.h"
/* Section : Macros Declaration */
#define TIMER2_MODULE_ENABLE  1
#define TIMER2_MODULE_DISABLE 0

#define TIMER2_PRESCALER_DIV_1  0
#define TIMER2_PRESCALER_DIV_4  1
#define TIMER2_PRESCALER_DIV_16 2

#define TIMER2_POSTCALER_DIV_1  0
#define TIMER2_POSTCALER_DIV_2  1
#define TIMER2_POSTCALER_DIV_3  2
#define TIMER2_POSTCALER_DIV_4  3
#define TIMER2_POSTCALER_DIV_5  4
#define TIMER2_POSTCALER_DIV_6  5
#define TIMER2_POSTCALER_DIV_7  6
#define TIMER2_POSTCALER_DIV_8  7
#define TIMER2_POSTCALER_DIV_9  8
#define TIMER2_POSTCALER_DIV_10 9
#define TIMER2_POSTCALER_DIV_11 10
#define TIMER2_POSTCALER_DIV_12 11
#define TIMER2_POSTCALER_DIV_13 12
#define TIMER2_POSTCALER_DIV_14 13
#define TIMER2_POSTCALER_DIV_15 14
#define TIMER2_POSTCALER_DIV_16 15

/* Section : Function like Macros Declaration*/
#define _TIMER2_MODULE_ENABLE_()  (T2CONbits.TMR2ON = 1)
#define _TIMER2_MODULE_DISABLE_() (T2CONbits.TMR2ON = 0)

#define TIMER2_PRESCALER_SELECT_BIT(_PRESCALER_VALUE) (T2CONbits.T2CKPS = _PRESCALER_VALUE)
#define TIMER2_POSTCALER_SELECT_BIT(_POSTCALER_VALUE) (T2CONbits.TOUTPS = _POSTCALER_VALUE)

/* Section : User Defined Data Type */
typedef struct{
    #if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void(*TIMER2_INTERRUPT_HANDELER)(void);
        interrupt_priority_cfg Timer2_priority;
    #endif
    uint8 Timer2_Preloaded_Value;
    uint8 Timer2_Prescaler_Value : 2;
    uint8 Timer2_postcaler_Value : 4;
    uint8 : 2;
}timer2_config_t;
/* Section : Function Declaration */
STD_ReturnType Timer2_Init(const timer2_config_t * timer);
STD_ReturnType Timer2_De_Init(const timer2_config_t * timer);
STD_ReturnType Timer2_Write_Value(const timer2_config_t * timer,uint8 value);
STD_ReturnType Timer2_Read_Value(const timer2_config_t * timer,uint8 *value);

#endif	/* HAL_TIMER2_H */


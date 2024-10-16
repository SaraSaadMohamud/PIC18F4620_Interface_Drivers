/* 
 * File:   hal_timer3.h
 * Author: DELL
 *
 * Created on September 11, 2024, 2:17 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/* Section : Includes*/
#include <pic18f4620.h>
#include "../../MCAL_Layer/mcal_std_types.h"
#include "../../MCAL_Layer/Timer2/hal_timer2.h"
#include "../Gpio/hal_gpio.h"
/* Section : Macros Declaration */
#define TIMER3_TIMER_MODE   0
#define TIMER3_COUNTER_MODE 1

#define TIMER3_PRESCALER_DISABLE 0
#define TIMER3_PRESCALER_DIV_2   1
#define TIMER3_PRESCALER_DIV_4   2
#define TIMER3_PRESCALER_DIV_8   3

#define TIMER3_ASYNC_COUNTER_MODE 1
#define TIMER3_SYNC_COUNTER_MODE  0

#define TIMER3_16BIT_MODE 1
#define TIMER3_8BIT_MODE  0

#define TIMER3_TIMER_OSCILLATOR_ENABLE  1
#define TIMER3_TIMER_OSCILLATOR_DISABLE 0
/* Section : Function like Macros Declaration*/
#define TIMER3_MODULE_ENABLE()  (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE() (T3CONbits.TMR3ON = 0)

#define TIMER3_TIMER_MODE_ENABLE()   (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE() (T3CONbits.TMR3CS = 1)

#define TIMER3_ASYNC_COUNTER_MODE_ENABLE() (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()  (T3CONbits.T3SYNC = 0)

#define TIMER3_PRESCALER_VALUE_SELECT(_PRESCALER_VALUE) (T3CONbits.T3CKPS = _PRESCALER_VALUE)

#define TIMER3_16BIT_REGISTER_MODE_ENABLE() (T3CONbits.RD16 = 1)
#define TIMER3_8BIT_REGISTER_MODE_MODE()    (T3CONbits.RD16 = 0)
/* Section : User Defined Data Type */
typedef struct{
    #if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void(*TIMER3_INTERRUPT_HANDELER)(void);
        interrupt_priority_cfg TIMER3_INTERRUPT_PRIORITY;
    #endif
    uint16 Timer3_Preloaded_Value ;
    uint8  Timer3_Register_Read_Write_Mode : 1;
    uint8  Timer3_prescaler_Value : 2;
    uint8  Timer3_Counter_Mode : 1;
    uint8  Timer3_Mode : 1;
    uint8  : 3;
    
}timer3_config_t;
/* Section : Function Declaration */
STD_ReturnType Timer3_Init(const timer3_config_t * timer);
STD_ReturnType Timer3_De_Init(const timer3_config_t * timer);
STD_ReturnType Timer3_Write_Value(const timer3_config_t * timer,uint16 value);
STD_ReturnType Timer3_Read_Value(const timer3_config_t * timer,uint16 *value);
#endif	/* HAL_TIMER3_H */


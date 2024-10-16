/* 
 * File:   hal-ccp1.h
 * Author: DELL
 *
 * Created on September 13, 2024, 3:16 AM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/* Section : Includes*/

#include <pic18f4620.h>
#include "hal_ccp1_cfg.h"
#include "../../MCAL_Layer/mcal_std_types.h"
#include "../Gpio/hal_gpio.h"
#include "../../MCAL_Layer/interrupt/mcal_internal_interrupt.h"

/* Section : Macros Declaration */
#define CCP_PRESCALER_DIV_1  1
#define CCP_PRESCALER_DIV_4  4
#define CCP_PRESCALER_DIV_16 16

#define CCP_POSTCALER_DIV_1  1
#define CCP_POSTCALER_DIV_2  2
#define CCP_POSTCALER_DIV_3  3
#define CCP_POSTCALER_DIV_4  4
#define CCP_POSTCALER_DIV_5  5
#define CCP_POSTCALER_DIV_6  6
#define CCP_POSTCALER_DIV_7  7
#define CCP_POSTCALER_DIV_8  8
#define CCP_POSTCALER_DIV_9  9
#define CCP_POSTCALER_DIV_10 10
#define CCP_POSTCALER_DIV_11 11
#define CCP_POSTCALER_DIV_12 12
#define CCP_POSTCALER_DIV_13 13
#define CCP_POSTCALER_DIV_14 14
#define CCP_POSTCALER_DIV_15 15
#define CCP_POSTCALER_DIV_16 16

#define CCP_MODULE_DISABLE ((uint8)0X00)

#define CCP_CAPTURE_MODEL_1_FALLING_EDG  ((uint8)0X04)
#define CCP_CAPTURE_MODEL_1_RISING_EDG   ((uint8)0X05)
#define CCP_CAPTURE_MODEL_4_RISING_EDG   ((uint8)0X06)
#define CCP_CAPTURE_MODEL_16_RISING_EDG  ((uint8)0X07)

#define CCP_COMPARE_MODEULE_SET_PIN_LOW        ((uint8)0X08)
#define CCP_COMPARE_MODEULE_SET_PIN_HIGH       ((uint8)0X09)
#define CCP_COMPARE_MODEULE_TOGGLE_ON_MATCH    ((uint8)0X02)
#define CCP_COMPARE_MODEULE_GNT_SFT_INTERRUPTR ((uint8)0X0A)
#define CCP_COMPARE_MODEULE_GNT_SPECIAL_EVENT  ((uint8)0X0B)

#define CCP_PWM_MODE_ENABLE ((uint8)0X0C)

#define CCP_CAPTURE_NOT_READY 0X00
#define CCP_CAPTURE_READY     0X01

#define CCP_COMPARE_NOT_READY 0x00
#define CCP_COMPARE_READY     0x01
/* Section : Function like Macros Declaration*/
#define CCP1_CONFIG_SELECTE_MODE(_CONFIG) (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_CONFIG_SELECTE_MODE(_CONFIG) (CCP2CONbits.CCP2M = _CONFIG)
/* Section : User Defined Data Type */
typedef enum{
    CCP1_CAPTURE_MODE=0,
    CCP1_COMPARE_MODE,
    CCP_PWM_MODE
}ccp_mode_cfg_t;

typedef union{
    struct{
        uint8 ccp_low;
        uint8 ccp_high;
    };
    struct{
        uint16 ccp_16bit;
    };
}ccp_reg_t;

typedef enum{
   CCP1_INIT = 0,
   CCP2_INIT
}ccp_init_t;

typedef enum{
    CCP1_CCP2_TIMER1 = 0,
    CCP2_TIMER3_CCP1_TIMER1,
    CCP1_CCP2_TIMER3
}ccp_capture_compare_timer_t;

typedef struct{
    
    #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void(*CCP1_INTERRUPT_HANDELER)(void);
        interrupt_priority_cfg CCP1_INTERRUPT_PRIORITY;
    #endif
    #if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void(*CCP2_INTERRUPT_HANDELER)(void);
        interrupt_priority_cfg CCP2_INTERRUPT_PRIORITY;
    #endif

    #if CCP1_MODULE_SELECT == CCP_CAPTURE_MODULE_ENABLE || CCP2_MODULE_SELECT == CCP_CAPTURE_MODULE_ENABLE
        ccp_capture_compare_timer_t CCP_Capture_Timer;
    #elif CCP1_MODULE_SELECT == CCP_COMPARE_MODULE_ENABLE || CCP2_MODULE_SELECT == CCP_COMPARE_MODULE_ENABLE
         ccp_capture_compare_timer_t CCP_Compare_Timer;
    #elif CCP_PWM_MODULE_ENABLE == CCP1_MODULE_SELECT || CCP_PWM_MODULE_ENABLE == CCP2_MODULE_SELECT
        uint32 PWM_Frequancy; 
        uint8 Timer2_Prescaler_Value : 2;
        uint8 Timer2_postcaler_Value : 4;
    #endif
   ccp_init_t ccp_init;
   ccp_mode_cfg_t ccp_mode_select;
   uint8 CCP_Mode_Variant : 4;
   pin_config_t ccp_pin;
}ccp_t;

/* Section : Function Declaration */
STD_ReturnType CCP_Init(const ccp_t * ccp1_obj);
STD_ReturnType CCP_De_Init(const ccp_t * ccp1_obj);
#if CCP1_MODULE_SELECT == CCP_CAPTURE_MODULE_ENABLE || CCP2_MODULE_SELECT == CCP_CAPTURE_MODULE_ENABLE
STD_ReturnType CCP1_Is_Capture_Data_Ready(uint8 *capture_status);
STD_ReturnType CCP1_Capture_Read_Data(uint16 *value);
#elif CCP1_MODULE_SELECT == CCP_COMPARE_MODULE_ENABLE || CCP2_MODULE_SELECT == CCP_COMPARE_MODULE_ENABLE
STD_ReturnType CCP_Is_Compare_Data_Ready(const ccp_t * ccp_obj,uint8 *compare_status); 
STD_ReturnType CCP_Compare_Write_Data(const ccp_t * ccp_obj,uint16 value);
#else 
STD_ReturnType CCP_PWM_Set_Duty_Sycle(const ccp_t * ccp_obj,const uint8 duty);
STD_ReturnType CCP_PWM_Start(const ccp_t * ccp_obj);
STD_ReturnType CCP_PWM_End(const ccp_t * ccp_obj);
#endif

#endif	/* HAL_CCP1_H */


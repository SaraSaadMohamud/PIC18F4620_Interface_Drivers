/* 
 * File:   hal_adc.h
 * Author: DELL
 *
 * Created on September 4, 2024, 9:59 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* Section : Includes*/
#include "hal_adc_cnf.h"
#include "../../MCAL_Layer/mcal_std_types.h" 
#include "../../MCAL_Layer/interrupt/mcal_internal_interrupt.h"
#include "../../MCAL_Layer/Gpio/hal_gpio.h"

/* Section : Macros Declaration */

/* 
 * IF YPU CHOSE ADC_AN4_ANALOG_FUNCTIONALITY THAT IS MEANS THAT AN4, AN3 ,AN2 ,AN1 ,AN0 WILL BE ANAOLOG PINS
 * AND AN12, AN11, AN10, AN9, AN8, AN7 ,AN6 ,AN5 WILL BE DIGITAL PINS
 */
#define ADC_AN0_ANALOG_FUNCTIONALITY  0X0E
#define ADC_AN1_ANALOG_FUNCTIONALITY  0X0D
#define ADC_AN2_ANALOG_FUNCTIONALITY  0X0C
#define ADC_AN3_ANALOG_FUNCTIONALITY  0X0B
#define ADC_AN4_ANALOG_FUNCTIONALITY  0X0A
#define ADC_AN5_ANALOG_FUNCTIONALITY  0X09
#define ADC_AN6_ANALOG_FUNCTIONALITY  0X08
#define ADC_AN7_ANALOG_FUNCTIONALITY  0X07
#define ADC_AN8_ANALOG_FUNCTIONALITY  0X06
#define ADC_AN9_ANALOG_FUNCTIONALITY  0X05
#define ADC_AN10_ANALOG_FUNCTIONALITY 0X04
#define ADC_AN11_ANALOG_FUNCTIONALITY 0X03
#define ADC_AN12_ANALOG_FUNCTIONALITY 0X02
#define ADC_ALL_ANALOG_FUNCTIONALITY  0X00
#define ADC_ALL_DIGITAL_FUNCTIONALITY 0X0F

#define ADC_RESULT_RIGHT 0X01
#define ADC_RESULT_LEFT  0X00

#define VOLTAGE_REFRANCE_ENABLE  0X01
#define VOLTAGE_REFRANCE_DISABLE 0X00

#define CONVERSION_COMPLETED   0X01
#define CONVERSION_IN_PROGRESS 0X00

/* Section : Function like Macros Declaration*/

/*ADC CONVERSION STARUS : 1 = ADC CONVERSION IN PROGRESS , 0 = IDL STATE*/
#define ADC_CONVERSION_STATUS()(ADCON0bits.GO_nDONE)
/*ADC START CONVERSION PROCESS*/
#define ADC_START_CONVERSION() (ADCON0bits.GO_nDONE = 1)

/*?ADC_MODULE_ENABLE*/
#define ADC_CONVERTER_ENABLE()  (ADCON0bits.ADON = 1)

/*?ADC_MODULE_DISABLE*/
#define ADC_CONVERTER_DISABLE() (ADCON0bits.ADON = 0)

/*ENABLE THE VOLTAGE REFRANCE*/
#define ADC_VOLTAGE_REFRANCE_ENABLE() do{ADCON1bits.VCFG0 = 1;\
                                         ADCON1bits.VCFG01 =1;\
                                        }while(0)

/*DISABLE THE VOLTAGE REFRANCE*/
#define ADC_VOLTAGE_REFRANCE_DISABLE() do{ADCON1bits.VCFG0 = 0;\
                                         ADCON1bits.VCFG01 =0 ;\
                                        }while(0)
/* TO SELECT THE PIN TO BE ANALOG OR DIGITAL*/
#define ADC_ANLOG_DIGITAL_PORT_CONFIGURATION(_CONFIG) (ADCON1bits.PCFG = _CONFIG)

/*ENABLE THE ADC RIGHT JUSTIFICATION */
#define ADC_RIGHT_FORMATE_ENABLE() (ADCON2bits.ADFM = ADC_RESULT_RIGHT)

/*ENABLE THE ADC LEFT JUSTIFICATION */
#define ADC_LEFT_FORMATE_ENABLE()  (ADCON2bits.ADFM = ADC_RESULT_LEFT)

/* Section : User Defined Data Type */

/*ENUM TO SELECT THE SPECIFIC CHANNEL*/
typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12,           
}adc_channel_select_t;
/*DESCRIBE THE ACQUIsaTION TIME*/
typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD,
}adc_acquisation_time_t;
/*DESCRIBE THE CLOCK SOURSE*/
typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2=0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64,               
}adc_conversion_clock_t;

typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void (* ADC_INTERRUPT_HANDELLER)(void);
    interrupt_priority_cfg Interrupt_priority;
#endif
   adc_acquisation_time_t acqusation_time;
   adc_conversion_clock_t conversion_clock;
   adc_channel_select_t   adc_channel;
   uint8 voltage_refrance : 4;
   uint8 result_formate : 4;

}adc_config_t;
/* Section : Function Declaration */
STD_ReturnType ADC_Init(const adc_config_t * adc_obj);
STD_ReturnType ADC_De_Init(const adc_config_t * adc_obj);
STD_ReturnType ADC_Select_Channel(const adc_config_t * adc_obj, adc_channel_select_t channel);
STD_ReturnType ADC_Start_Conversion(const adc_config_t * adc_obj);
STD_ReturnType ADC_IS_Conversion_Done(const adc_config_t * adc_obj,uint8 *conversion_status);
STD_ReturnType ADC_Get_Conversion_Results(const adc_config_t * adc_obj,uint16 *conversion_result);
STD_ReturnType ADC_Get_Conversion_BLOCKING(const adc_config_t * adc_obj, adc_channel_select_t channel  ,uint16 *conversion_result);
STD_ReturnType ADC_START_Conversion_INTERRUPT(const adc_config_t * adc_obj, adc_channel_select_t channel);
#endif	/* HAL_ADC_H */


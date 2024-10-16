/* 
 * File: hal_gpio.h
 * Author: DELL
 *
 * Created on July 17, 2024, 8:45 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Section : Includes*/
#include "../mcal_std_types.h"
#include "../device_config.h"
#include <pic18f4620.h>
#include "hal_gpio_cfg.h"
/* Section : Macros Declaration */
#define BIT_MASK         1
/* Section : Function like Macros Declaration*/
#define HWREG8(_X)     (*((volatile uint8*)(_X)))

#define PORT_MAX_PIN_NUMBER 8
#define PORT_MAX_NUMBER 5
#define PORT_MASK  0xFF

#define SET_BIT(REG,BIT_POSITION)        ((REG) |= (BIT_MASK << BIT_POSITION))
#define CLEAR_BIT(REG,BIT_POSITION)      ((REG) &= ~(BIT_MASK<< BIT_POSITION))
#define TOGGLE_BIT(REG,BIT_POSITION)     ((REG) ^= (BIT_MASK<< BIT_POSITION))
#define READ_BIT(REG,BIT_POSITION)       ((REG >> BIT_POSITION) & BIT_MASK)
/////////////////////////////////////////
#define GPIO_PORT_PIN_CONFIG GPIO_ENABLE 
#define GPIO_PORT_CONFIG GPIO_ENABLE 
/* Section : User Defined Data Type */
typedef enum
{
    LOW=0,
    HIGHT
}logic_t;

typedef enum{
    GPIO_DIRECTION_OUTPUT=0,
    GPIO_DIRECTION_INPUT
}direction_t;

typedef enum{
    PIN0=0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}pin_index_t;

typedef enum{
    PORTA_Index=0,
    PORTB_Index,
    PORTC_Index,
    PORTD_Index,
    PORTE_Index
}port_index_t;

typedef struct{
    uint8 port      :3; /* @ref Port_Index_t*/
    uint8 pin       :3; /* @ref pin_Index_t*/
    uint8 direction :1; /* @ref direction_t*/
    uint8 logic     :1; /* @ref logic_t*/
}pin_config_t;

/* Section : Function Declaration */
STD_ReturnType gpio_pin_direction_intializtion(const pin_config_t *_pin_config);
STD_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_Config ,direction_t *direction_status);
STD_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_Config , logic_t logic);
STD_ReturnType gpio_pin_read_logic (const pin_config_t *_pin_config , logic_t *logic);
STD_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
STD_ReturnType gpio_pin_intializtion(const pin_config_t *_pin_config);

STD_ReturnType gpio_port_direction_intialize(port_index_t port,uint8 direction);
STD_ReturnType gpio_port_get_direction_status(port_index_t port,uint8 *direction_status);
STD_ReturnType gpio_port_write_logic(port_index_t port ,uint8 logic);
STD_ReturnType gpio_port_read_logic(port_index_t port ,uint8 *logic);
STD_ReturnType gpio_port_toggle_logic (port_index_t port);        
#endif	/* HAL_GPIO_H */


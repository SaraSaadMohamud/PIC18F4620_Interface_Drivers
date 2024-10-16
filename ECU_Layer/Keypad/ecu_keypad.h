/* 
 * File:   ecu_keypad.h
 * Author: DELL
 *
 * Created on August 19, 2024, 9:06 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H
/* Section : Includes*/
#include "ecu_keypad_cnf.h"
#include "../../MCAL_Layer/Gpio/hal_gpio.h"
/* Section : Macros Declaration */
#define ECU_KEYPAD_ROWS 4
#define ECU_KEYPAD_COLUMS 4
#define ZERO 0

/* Section : Function like Macros Declaration*/

/* Section : User Defined Data Type */
typedef struct{
    pin_config_t keypad_row_pin[ECU_KEYPAD_ROWS];
    pin_config_t keypad_colum_pin[ECU_KEYPAD_COLUMS];
}keypad_t;
/* Section : Function Declaration */
STD_ReturnType keypad_intialize(const keypad_t *keypad_obj);
STD_ReturnType keypad_get_value(const keypad_t *keypad_obj,uint8 *value);
#endif	/* ECU_KEYPAD_H */


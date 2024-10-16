/* 
 * File:   ecu_button.h
 * Author: Sara.Saad
 *
 * Created on July 29, 2024, 1:12 AM
 */
/////////////////////////
#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section : Includes*/
#include "../../MCAL_Layer/Gpio/hal_gpio.h"
#include "ecu_button_cnf.h"
/* Section : Macros Declaration */

/* Section : Function like Macros Declaration*/

/* Section : User Defined Data Type */
typedef enum{
    BUTTON_PREASED=0,
    BUTTON_REREASED
}button_status_t;

typedef enum {
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct {
    pin_config_t button_pin;
    button_status_t button_status;
    button_active_t button_connection;
}button_t;

/* Section : Function Declaration */
STD_ReturnType button_intialize(button_t *btn);
STD_ReturnType button_read_state(button_t *btn, button_status_t *button_state);
#endif	/* ECU_BUTTON_H */


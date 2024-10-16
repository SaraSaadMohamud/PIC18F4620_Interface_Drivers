/* 
 * File:  ecu_led.h
 * Author: DELL
 *
 * Created on July 17, 2024, 9:05 PM
 */
////////////////////////////////
#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes*/
#include "../../MCAL_Layer/Gpio/hal_gpio.h"
#include "ecu_led_conf.h"
/* Section : Macros Declaration */

/* Section : Function like Macros Declaration*/

/* Section : User Defined Data Type */
typedef enum {
    LED_OFF,
    LED_ON
}led_status;
typedef struct {
    uint8 port_name :4;
    uint8 pin :3;
    uint8 led_state :1;
}led_t;
/* Section : Function Declaration */
STD_ReturnType led_intialize(const led_t *led);
STD_ReturnType led_turn_on (const led_t *led); 
STD_ReturnType led_turn_off (const led_t *led);
STD_ReturnType led_toggle (const led_t *led);
#endif	/* ECU_LED_H */


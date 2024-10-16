/* 
 * File:   relay.h
 * Author: DELL
 *
 * Created on August 5, 2024, 1:19 PM
 */
/////////////////////////////////////
#ifndef RELAY_H
#define	RELAY_H

/* Section : Includes*/

#include "ecu_relay_cnf.h"
#include "../../MCAL_Layer/Gpio/hal_gpio.h"

/* Section : Macros Declaration */

#define REALY_ON_STATUS  0x01U
#define REALY_OFF_STATUS 0X00U

/* Section : Function like Macros Declaration*/

/* Section : User Defined Data Type */
 
typedef struct {
    uint8  realy_port    : 4;
    uint8  realy_pin     : 3;
    uint8  realy_statuse :1;
}realy_t;

/* Section : Function Declaration */
STD_ReturnType relay_intialize(const realy_t *_realy);
STD_ReturnType realy_turn_on( const realy_t * _realy);
STD_ReturnType realy_turn_off( const realy_t *_realy);
#endif	/* RELAY_H */


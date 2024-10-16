/* 
 * File:   application.h
 * Author: DELL
 *
 * Created on July 17, 2024, 9:12 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : Includes*/

#include "ECU_Layer/ecu_layer_intialize.h"

/* Section : Macros Declaration */

/* Section : Function like Macros Declaration*/

/* Section : User Defined Data Type */
extern chr_lcd_8bit_t lcd2;
extern chr_lcd_4bit_t lcd1;
/* Section : Function Declaration */
void INT0_App_ISR();

#endif	/* APPLICATION_H */


/* 
 * File:   RealTimeClockDs1307.h
 * Author: DELL
 *
 * Created on October 2, 2024, 2:20 AM
 */

#ifndef REALTIMECLOCKDS1307_H
#define	REALTIMECLOCKDS1307_H

/* Section : Includes*/
#include <pic18f4620.h>
#include "../MCAL_Layer/I2c/hal_I2C.h"
#include "../MCAL_Layer/interrupt/mcal_internal_interrupt.h"
#include "../MCAL_Layer/Gpio/hal_gpio.h"
#include "../MCAL_Layer/mcal_std_types.h"
/* Section : Macros Declaration */

/* Section : Function like Macros Declaration*/

/* Section : User Defined Data Type */
typedef struct{
    uint16 Hours;
    uint16 Minutes;
    uint16 Seconds;
    uint16 Days;
    uint16 Month;
    uint16 Years;
} RealTimeClockDs1307_t;
/* Section : Function Declaration */
RealTimeClockDs1307_t Real_Time_Clock_Ds1307_Get_Data_Time(void);

#endif	/* REALTIMECLOCKDS1307_H */


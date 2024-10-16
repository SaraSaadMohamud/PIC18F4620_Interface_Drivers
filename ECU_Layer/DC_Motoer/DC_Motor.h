/* 
 * File:   DC_Motor.h
 * Author: DELL
 *
 * Created on August 8, 2024, 8:51 PM
 */
//////////////////////////////
#ifndef DC_MOTOR_H
#define	DC_MOTOR_H
#define DC_MOTOR_PIN_1 0X00U
#define DC_MOTOR_PIN_2  0X01U

/* Section : Includes*/
#include "Dc_Motor_Cnf.h"
#include "../../MCAL_Layer/Gpio/hal_gpio.h"
/* Section : Macros Declaration */
#define DC_Motor_ON_Status  0x01U
#define DC_Motor_OFF_Status 0x00U
/* Section : Function like Macros Declaration*/

/* Section : User Defined Data Type */

typedef struct{
   pin_config_t dc_motor_pin[2] ;
}dc_motor_t;
/* Section : Function Declaration */
STD_ReturnType dc_motor_intialize(const dc_motor_t * _dc_motor);
STD_ReturnType dc_motor_move_right(const dc_motor_t * _dc_motor);
STD_ReturnType dc_motor_move_left(const dc_motor_t * _dc_motor);
STD_ReturnType dc_motor_stop(const dc_motor_t * _dc_motor);
#endif	/* DC_MOTOR_H */


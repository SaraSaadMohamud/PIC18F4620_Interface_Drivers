/* 
 * File:   hal_eeprom.h
 * Author: DELL
 *
 * Created on September 1, 2024, 7:48 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* Section : Includes*/
#include "../../MCAL_Layer/interrupt/mcal_internal_interrupt.h"
#include "../../MCAL_Layer/mcal_std_types.h"
#include "pic18f4620.h"
/* Section : Macros Declaration */
#define ACCESS_FLASH_PROGRAMM_MEMORY  1
#define ACCESS_EEPROM_PROGRAMM_MEMORY 0

#define ACCESS_CONFIGURATION_REGISTER  1
#define ACCESS_EEPROM_FLASH_MEMORY     0

#define ALLOW_WRITE_CYCLE_TO_FLAS_EEPROM_MEMORY    1
#define INHIBITS_WRITE_CYCLE_TO_FLAS_EEPROM_MEMORY 0

#define INTIATE_THE_EEPROM_ERASER_WRITE_CYCLE   1
#define THE_EEPROM_ERASER_WRITE_CYCLE_COMPLETED 0

#define INTIATE_THE_EEPROM_ERASER_READ_CYCLE   1
/* Section : Function like Macros Declaration*/

/* Section : User Defined Data Type */

/* Section : Function Declaration */

STD_ReturnType DATA_EEPROM_WRITE_BYTE(uint16 bAdd,uint8 bData);
STD_ReturnType DATA_EEPROM_READ_BYTE(uint16 bAdd,uint8 *bData);

#endif	/* HAL_EEPROM_H */


/* 
 * File:   ecu_seven_Seg.h
 * Author: DELL
 *
 * Created on August 14, 2024, 11:40 PM
 */

#ifndef ECU_SEVEN_SEG_H
#define	ECU_SEVEN_SEG_H

/* Section : Includes*/
#include "ecu_seven_seg_cnf.h"
#include "../../MCAL_Layer/Gpio/hal_gpio.h"
#include "../../MCAL_Layer/mcal_std_types.h"
/* Section : Macros Declaration */
#define SEGMNT_PIN0 0
#define SEGMNT_PIN1 1
#define SEGMNT_PIN2 2 
#define SEGMNT_PIN3 3
/* Section : Function like Macros Declaration*/

/* Section : User Defined Data Type */
typedef enum
{
   SEGMENT_COMMON_ANODE,
   SEGMENT_COMMON_CATHOD
}segment_type_t;

typedef struct 
{
    pin_config_t segment_pin[4]; // </editor-fold>

    segment_type_t segment_type ;
}segment_t;
/* Section : Function Declaration */
STD_ReturnType seven_segment_intialize(const segment_t *seg);
STD_ReturnType seven_segment_wite_number(const segment_t *seg,uint8 number);
#endif	/* ECU_SEVEN_SEG_H */


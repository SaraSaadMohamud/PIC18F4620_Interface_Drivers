 /* 
 * File:   mcal_std_types.h
 * Author: DELL
 *
 * Created on July 17, 2024, 8:54 PM
 */
/////////////////////////////////
#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section : Includes*/

#include "std_libraries.h"
#include "compiler.h"

/* Section : Macros Declaration */

#define STD_HIGH         0x01
#define STD_LOW          0X00

#define STD_ON           0X01
#define STD_OFF          0X00
 
#define ACTIVE_STATE     0X01
#define IDLE_STATE       0X00

#define E_OK             (STD_ReturnType)0X01;
#define E_NOK            (STD_ReturnType)0X00;


/* Section : Function like Macros Declaration*/

/* Section : User Defined Data Type */
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned int    uint32;

typedef signed char   sint8;
typedef signed short  sint16;
typedef signed int    sint32;

typedef uint8 STD_ReturnType;



/* Section : Function Declaration */
#endif/* MCAL_STD_TYPES_H */


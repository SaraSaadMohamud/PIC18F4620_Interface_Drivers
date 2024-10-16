/* 
 * File:   mcal_interrupt_cnf.h
 * Author: DELL
 *
 * Created on August 28, 2024, 12:33 AM
 */

#ifndef MCAL_INTERRUPT_CNF_H
#define	MCAL_INTERRUPT_CNF_H

/* Section : Includes*/
//#include <pic18f4620.h>
#include <xc.h>
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../../MCAL_Layer/Gpio/hal_gpio.h"
/* Section : Macros Declaration */

#define INTERRUPT_ENABLE            1
#define INTERRUPT_DISABLE           0

#define INTERRUPT_OCCURE            1
#define INTERRUPT_NOT_OCCUR         0

#define INTERRUPT_PERIOITY_ENABLE   1
#define INTERRUPT_PERIORITY_DISABLE 0

/* Section : Function like Macros Declaration*/

/*this macro will enable the interrupt priority feature*/
#if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

#define INTERRUPT_PERIORITY_LEVELS_ENABLE()       (RCONbits.IPEN = 1)

/*this macro will disable the interrupt priority feature*/
#define INTERRUPT_PERIORITY_LEVELS_DISABLE()      (RCONbits.IPEN = 0)

/*this macro will enable the high priority global interruptS*/
#define INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE()  (INTCONbits.GIEH = 1)

/*this macro will DISable the high priority global interruptS*/
#define INTERRUPT_GLOPAL_INTERRUPT_HIGHT_DISABLE() (INTCONbits.GIEH = 0)

/*this macro will enable the LOW priority global interruptS*/
#define INTERRUPT_GLOPAL_INTERRUPT_LOW_ENABLE()    (INTCONbits.GIEL = 1)

/*this macro will DISable the LOW priority global interruptS*/
#define INTERRUPT_GLOPAL_INTERRUPT_LOW_DISABLE()   (INTCONbits.GIEL = 0)

#else

/*this macro will enable the  global interrupts*/
#define INTERRUPT_GLOPAL_INTERRUPT_ENABLE()  (INTCONbits.GIE = 1)

/*this macro will DISable the global interrupts*/
#define INTERRUPT_GLOPAL_INTERRUPT_DISABLE() (INTCONbits.GIE = 0)
/*this macro will enable the LOW priority global interruptS*/

/*this macro will enable the peripheral interruptS*/
#define INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE()    (INTCONbits.PEIE = 1)

/*this macro will enable the peripheral interruptS*/
#define INTERRUPT_PERIPHERAL_INTERRUPT_DISABLE()   (INTCONbits.PEIE = 0)

#endif
/* Section : User Defined Data Type */
typedef enum{
    INTERRUPT_LOW_PRIORITY=0,
    INTERRUPT_HIGH_PRIORITY
}interrupt_priority_cfg;

/* Section : User Defined Data Type */

/* Section : Function Declaration */

#endif	/* MCAL_INTERRUPT_CNF_H */


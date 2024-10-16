/* 
 * File:   mcal_external_interrupt.h
 * Author: DELL
 *
 * Created on August 28, 2024, 12:30 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* Section : Includes*/
//*******************************************************************************************************************
#include "mcal_interrupt_cnf.h"
//*******************************************************************************************************************
/* Section : Macros Declaration */
//*******************************************************************************************************************
/* Section : Function like Macros Declaration*/
//*******************************************************************************************************************
#if EXTERNAL_INTERRUPT_INTX_FEARTURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* Macro to Enable Extern_INTX0_Interrupt*/
#define EXTERNAL_INT0_INTERRUPT_ENABLE()           (INTCONbits.INT0IE = 1)

/* Macro to Disable Extern_INTX0_Interrupt*/
#define EXTERNAL_INT0_INTERRUPT_DISABLE()          (INTCONbits.INT0IE = 0)

/* Macro to Clear the flag of Extern_INTX0_Interrupt*/
#define EXTERNAL_INT0_INTERRUPT_FLAG_CLEAR()       (INTCONbits.INT0IF = 0)

/*This routine set the edge detect of the external interrupt to the positive edge */
#define EXTERNAL_INT0_INTERRUPT_FALLING_EDGE_SET() (INTCON2bits.INTEDG0 = 0)

/*This routine set the edge detect of the external interrupt to the negative edge */
#define EXTERNAL_INT0_INTERRUPT_RAISING_EDGE_SET() (INTCON2bits.INTEDG0 = 1)

////////////////////////////////////////////////////////////////////////////////////////

/* Macro to Enable Extern_INTX0_Interrupt*/
#define EXTERNAL_INT1_INTERRUPT_ENABLE()      (INTCON3bits.INT1IE = 1)

/* Macro to Disable Extern_INTX0_Interrupt*/
#define EXTERNAL_INT1_INTERRUPT_DISABLE()     (INTCON3bits.INT1IE= 0)

/* Macro to Clear the flag of Extern_INTX0_Interrupt*/
#define EXTERNAL_INT1_INTERRUPT_FLAG_CLEAR()  (INTCON3bits.INT1IF = 0)

/*This routine set the edge detect of the external interrupt to the negative edge */
#define EXTERNAL_INT1_INTERRUPT_RAISING_EDGE_SET() (INTCON2bits.INTEDG1 = 1)

/*This routine set the edge detect of the external interrupt to the positive edge */
#define EXTERNAL_INT1_INTERRUPT_FALLING_EDGE_SET() (INTCON2bits.INTEDG1 = 0)

////////////////////////////////////////////////////////////////////////////////////////

/* Macro to Enable Extern_INTX0_Interrupt*/
#define EXTERNAL_INT2_INTERRUPT_ENABLE()      (INTCON3bits.INT2IE = 1)

/* Macro to Disable Extern_INTX0_Interrupt*/
#define EXTERNAL_INT2_INTERRUPT_DISABLE()     (INTCON3bits.INT2IE= 0)

/* Macro to Clear the flag of Extern_INTX0_Interrupt*/
#define EXTERNAL_INT2_INTERRUPT_FLAG_CLEAR()  (INTCON3bits.INT2IF = 0)

/*This routine set the edge detect of the external interrupt to the negative edge */
#define EXTERNAL_INT2_INTERRUPT_RAISING_EDGE_SET() (INTCON2bits.INTEDG2 = 1)

/*This routine set the edge detect of the external interrupt to the positive edge */
#define EXTERNAL_INT2_INTERRUPT_FALLING_EDGE_SET() (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PERIOITY_LEVEL_ENABLE  == INTERRUPT_FEATURE_ENABLE

/*MACRO TO ENABLE THE EXTERNAL_INTX1_INTERRUPT_HIGH_PERIORITY*/
#define EXTERNAL_INT1_INTERRUPT_HIGH_PRIORITY() (INTCON3bits.INT1IP = 1)

/*MACRO TO ENABLE THE EXTERNAL_INTX1_INTERRUPT_LOW_PERIORITY*/
#define EXTERNAL_INT1_INTERRUPT_LOW_PRIORITY() (INTCON3bits.INT1IP = 0)

/*MACRO TO ENABLE THE EXTERNAL_INTX1_INTERRUPT_HIGH_PERIORITY*/
#define EXTERNAL_INT2_INTERRUPT_HIGH_PRIORITY() (INTCON3bits.INT2IP = 1)

/*MACRO TO ENABLE THE EXTERNAL_INTX1_INTERRUPT_LOW_PERIORITY*/
#define EXTERNAL_INT2_INTERRUPT_LOW_PRIORITY() (INTCON3bits.INT2IP = 0)

#endif

#endif

////////////////////////////////////////////////////////////////////////////////////////
#if EXTERNAL_INTERRUPT_ONCHANGE_FEARTURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* Macro to Enable Extern_RBI_Interrupt*/
#define EXTERNAL_RBI_INTERRUPT_ENABLE()         (INTCONbits.RBIE = 1)

/* Macro to Disable Extern_RBI_Interrupt*/
#define EXTERNAL_RBI_INTERRUPT_DISABLE()        (INTCONbits.RBIE= 0)

/* Macro to Clear the flag of Extern_RBI_Interrupt*/
#define EXTERNAL_RBI_INTERRUPT_FLAG_CLEAR()     (INTCONbits.RBIF= 0)

#if INTERRUPT_PERIOITY_LEVEL_ENABLE  == INTERRUPT_FEATURE_ENABLE
/*MACRO TO ENABLE THE EXTERNAL_RBI_INTERRUPT_HIGH_PERIORITY*/
#define EXTERNAL_RBI_INTERRUPT_HIGH_PRIORITY() (INTCON2bits.RBIP= 1)

/*MACRO TO ENABLE THE EXTERNAL_RBI_INTERRUPT_LOW_PERIORITY*/
#define EXTERNAL_RBI_INTERRUPT_LOW_PRIORITY() (INTCON2bits.RBIP = 0)

#endif

#endif

//*******************************************************************************************************************
/* Section : User Defined Data Type */
//*******************************************************************************************************************
typedef enum{
    INTERRUPR_EXTERNAL_INT0=0,
    INTERRUPR_EXTERNAL_INT1,
    INTERRUPR_EXTERNAL_INT2
}interrupr_src_t;

typedef enum{
    INTERRUPR_FALLING_EDGE=0,
    INTERRUPR_RAISING_EDGE,
}interrupt_edge_t;
typedef struct{
    void (*ptr_External_Inturrupt)(void);
    pin_config_t mcu_pin;
    interrupt_edge_t Interrupt_Edge;
    interrupr_src_t Interrupt_Source;
    interrupt_priority_cfg Interrupt_priority;
}interrupt_INTx_t;

typedef struct{
    void (*ptr_External_Inturrupt_HIGH)(void);
    void (*ptr_External_Inturrupt_LOW)(void);
    pin_config_t mcu_pin;
    interrupt_priority_cfg Interrupt_priority;
}interrupt_RBx_t;

//*******************************************************************************************************************
/* Section : Function Declaration */
//*******************************************************************************************************************
STD_ReturnType Inturrupt_INTx_Init(const interrupt_INTx_t* int_obj);
STD_ReturnType Inturrupt_INTx_De_Init(const interrupt_INTx_t* int_obj);

STD_ReturnType Inturrupt_RBx_Init(const interrupt_RBx_t* int_obj);
STD_ReturnType Inturrupt_RBx_De_Init(const interrupt_RBx_t* int_obj);

//*******************************************************************************************************************
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */



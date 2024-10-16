/* 
 * File:   mcal_interrupt_manager.h
 * Author: DELL
 *
 * Created on August 28, 2024, 12:31 AM
 */
#ifndef MCAL_INTERRUPT_MANAGER_H 
#define MCAL_INTERRUPT_MANAGER_H 
/* Section : Includes*/
#include "mcal_interrupt_cnf.h"
/* Section : Macros Declaration */

/* Section : Function like Macros Declaration*/

/* Section : User Defined Data Type */

/* Section : Function Declaration */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RB4_Source);
void RB5_ISR(uint8 RB5_Source);
void RB6_ISR(uint8 RB6_Source);
void RB7_ISR(uint8 RB7_Source);

void ADC_ISR (void);

void TIMER0_ISR(void);
void TIMER1_ISR(void);
void Timer2_ISR(void);
void TIMER3_ISR(void);

void CCP1_ISR(void);
void CCP2_ISR(void);

void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);

void MSSP_I2C_ISR(void);
void MSSP_I2C_COLLISION_ISR(void);
#endif	/* MCAL_INTERRUPT_MANAGER_H */


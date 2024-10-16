/* 
 * File:   mcal_interrupt_manager.c
 * Author: DELL
 *
 * Created on August 28, 2024, 12:31 AM
 */
#include "mcal_interrupt_manager.h"
uint8 volatile RB4_flag = 1;
uint8 volatile RB5_flag = 1;
uint8 volatile RB6_flag = 1;
uint8 volatile RB7_flag = 1;
#if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
void __interrupt() INTERRUPT_MANAGER_HIGH(void)
{
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCURE ))
    {
        INT0_ISR();
    }
    else
    {
        
    }
    if((INTCON3bits.INT2IF == INTERRUPT_OCCURE) == (INTCON3bits.INT2IE == INTERRUPT_ENABLE))
    {
        INT2_ISR();
    }
    else
    {
        
    }
}
void __interrupt(low_priority) INTERRUPT_MANAGER_LOW(void)
{
    if((INTCON3bits.INT1IF == INTERRUPT_OCCURE) == (INTCON3bits.INT1IE == INTERRUPT_ENABLE))
    {
        INT1_ISR();
    }
    else
    {
        
    }
}
#else
void __interrupt() INTERRUPT_MANAGER_HIGH(void)
{
    if((PIE1bits.ADIE == INTERRUPT_ENABLE) && (PIR1bits.ADIF  == INTERRUPT_OCCURE ))
    {
        ADC_ISR();
    }
    else
    { 
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    if((INTCONbits.TMR0IE == INTERRUPT_ENABLE) && (INTCONbits.TMR0IF  == INTERRUPT_OCCURE ))
    {
        TIMER0_ISR();
    }
    else
    { 
    }
    
    if((PIE1bits.TMR1IE == INTERRUPT_ENABLE) && (PIR1bits.TMR1IF == INTERRUPT_OCCURE))
    {
        TIMER1_ISR();
    }
    else
    { 
    }
    
    if((PIE1bits.TMR2IE  == INTERRUPT_ENABLE) && (PIR1bits.TMR2IF == INTERRUPT_OCCURE))
    {
        Timer2_ISR();
    }
    else
    { 
    }
    if((PIE2bits.TMR3IE == INTERRUPT_ENABLE) && (PIR2bits.TMR3IF == INTERRUPT_OCCURE))
    {
       TIMER3_ISR();
    }
    else
    { 
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    if((PIE1bits.CCP1IE == INTERRUPT_ENABLE) && (PIR1bits.CCP1IF== INTERRUPT_OCCURE))
    {
        CCP1_ISR();
    }
    else
    { 
    }
    
    if((PIE2bits.CCP2IE == INTERRUPT_ENABLE) && (PIR2bits.CCP2IF == INTERRUPT_OCCURE))
    {
        CCP2_ISR();
    }
    else
    { 
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////
    if((PIE1bits.TXIE == INTERRUPT_ENABLE) && (PIR1bits.TXIF == INTERRUPT_OCCURE))
    {
        EUSART_TX_ISR();
    }
    else
    { 
    }
    
    if((PIE1bits.RCIE == INTERRUPT_ENABLE) && (PIR1bits.RCIF == INTERRUPT_OCCURE))
    {
        EUSART_RX_ISR();
    }
    else
    { 
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
    if((PIE1bits.SSPIE == INTERRUPT_ENABLE) && (PIR1bits.SSPIF == INTERRUPT_OCCURE))
    {
        MSSP_I2C_ISR();
    }
    else
    { 
    }
    
    if((PIE2bits.BCLIE == INTERRUPT_ENABLE) && (PIR2bits.BCLIF == INTERRUPT_OCCURE))
    {
        MSSP_I2C_COLLISION_ISR();
    }
    else
    { 
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCURE ))
    {
        INT0_ISR();
    }
    else
    { 
    }
    if((INTCON3bits.INT1IF == INTERRUPT_OCCURE) == (INTCON3bits.INT1IE == INTERRUPT_ENABLE))
    {
        INT1_ISR();
    }
    else
    {
    }
    if((INTCON3bits.INT2IF == INTERRUPT_OCCURE) == (INTCON3bits.INT2IE == INTERRUPT_ENABLE))
    {
        INT2_ISR();
    }
    else
    {
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURE )
            &&(PORTBbits.RB4 == HIGHT) &&(RB4_flag == 1) )
    {
        RB4_flag = 0;
        RB4_ISR(1);
    }
    else
    {
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURE )
             &&(PORTBbits.RB4== LOW) &&(RB4_flag == 0))
    {
         RB4_flag = 1;
         RB4_ISR(0);
    }
    else
    {
    }
    
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURE )
            &&(PORTBbits.RB5 == HIGHT) && (RB5_flag == 1) )
    {
        RB5_flag = 0;
        RB5_ISR(1);
    }
    else
    {
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURE )
             &&(PORTBbits.RB5== LOW) &&(RB5_flag == 0) )
    {
        RB5_flag = 1;
        RB5_ISR(0);
    }
    else
    {
    }
    
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURE )
            &&(PORTBbits.RB6 == HIGHT) &&(RB6_flag == 1) )
    {
        RB6_flag = 0;
        RB6_ISR(1);
    }
    else
    {
    }
     if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURE )
            &&(PORTBbits.RB6== LOW) &&(RB6_flag == 0) )
    {
         RB6_flag = 1;
         RB6_ISR(0);
    }
    else
    {
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURE )
            &&(PORTBbits.RB7 == HIGHT) &&(RB7_flag == 1) )
    {
        RB7_flag = 0;
        RB7_ISR(1);
    }
    else
    {
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURE )
            &&(PORTBbits.RB7== LOW) &&(RB7_flag == 0) )
    {
        RB7_flag = 1;
        RB7_ISR(0);
    }
    else
    {
    }
}
#endif
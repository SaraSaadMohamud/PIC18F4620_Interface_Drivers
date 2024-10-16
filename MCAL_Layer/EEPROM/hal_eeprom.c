/* 
 * File:   hal_eeprom.c
 * Author: DELL
 *
 * Created on September 1, 2024, 7:48 PM
 */
#include "hal_eeprom.h"

STD_ReturnType DATA_EEPROM_WRITE_BYTE(uint16 bAdd,uint8 bData)
{
    STD_ReturnType Ret = E_OK;
    /*READ THE INTERRUPT STATUS "ENABLED OR DISABLE "*/
    uint8 General_Interrupt_Status = INTCONbits.GIE;
    /*UPDATE THE ADDRESS REGISTERS*/
    EEADRH = ((uint8)((bAdd >> 8)& 0x03));
    EEADR = ((uint8)(bAdd &0xFF));
    /*UPDATE THE DATA REGISTER */
    EEDATA = bData;
    /*SELECT ADDRESS DATA EEPROM MEMORY*/
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAMM_MEMORY ;
    EECON1bits.CFGS  = ACCESS_EEPROM_FLASH_MEMORY ;
    /*ALLOW WRITE CYCLE TO FLASH_EEPROM_MEMORY */
    EECON1bits.WREN = ALLOW_WRITE_CYCLE_TO_FLAS_EEPROM_MEMORY ;
    /*DISABLE THE GENERAL INTERRUPT */
    INTERRUPT_GLOPAL_INTERRUPT_DISABLE();
    /*WRITE THE REQUIRED SEQUANCE */
    EECON2 = 0X55;
    EECON2 = 0XAA;
    /*INTIATE THE EEPROM ERASER/WRITE CYCLE*/
    EECON1bits.WR = INTIATE_THE_EEPROM_ERASER_WRITE_CYCLE;
    /*WAIT THE WRITE CYCLE TO COMPLETED*/
    while(EECON1bits.WR)
    /*INHIBTE THE WRITE CYCLE TO FLASH OR EEPROM*/
     EECON1bits.WREN = INHIBITS_WRITE_CYCLE_TO_FLAS_EEPROM_MEMORY;
    /* RESTORE THE INTERRUPT STATUS */
     INTCONbits.GIE = General_Interrupt_Status;
    return(Ret);
}
STD_ReturnType DATA_EEPROM_READ_BYTE(uint16 bAdd,uint8 *bData)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == bData)
    {
        Ret = E_NOK;
    }
    else
    {
        /*UPDATE THE ADDRESS REGISTERS*/
        EEADRH = ((uint8)((bAdd >> 8)& 0x03));
        EEADR = ((uint8)(bAdd &0xFF));
        /*SELECT ADDRESS DATA EEPROM MEMORY*/
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAMM_MEMORY ;
        EECON1bits.CFGS  = ACCESS_EEPROM_FLASH_MEMORY ;
        /*INYIATE THE DATA EEPROM READ*/
        EECON1bits.RD = INTIATE_THE_EEPROM_ERASER_READ_CYCLE ;
        NOP();
        NOP();
        /*RETURN DATA */
        *bData = EEDATA;
    }
   
    return(Ret);
}
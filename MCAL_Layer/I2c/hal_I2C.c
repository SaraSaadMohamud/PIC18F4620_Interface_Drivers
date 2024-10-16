/* 
 * File:   hal_I2C.c
 * Author: DELL
 *
 * Created on September 29, 2024, 1:14 AM
 */

#include "hal_I2C.h"

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*MSSP_I2C_INTERRUPT_HANDELLER)(void);
static void (*MSSP_I2C_REPORT_RECIVE_OVERFLOW)(void);
static void (*MSSP_I2C_BUS_CONTROL_INTERRUPT_HANDELLER)(void);

#endif
void MSSP_I2C_ISR(void);
void MSSP_I2C_COLLISION_ISR(void);

static inline void MSSP_I2C_MODE_GPIO_CONFIG(void);
static inline void MSSP_I2C_MASTER_MODE_CLOCK_CONFIGURATION(const mssp_i2c_t* i2c_obj);
static inline void MSSP_I2C_INTERRUPT_CONFIGURATION(const mssp_i2c_t* i2c_obj);
/**
 * @brief: enable the 12c module
 * @param i2c_obj: pointer point to I2C structure
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType MSSP_I2C_INIT(const mssp_i2c_t* i2c_obj )
{
    STD_ReturnType Ret = E_OK;
    if(NULL == i2c_obj)
    {
        Ret = E_NOK;
    }
    else
    {
        /*Disable MSSP_I2C_MODULE*/
        MSSP_MODULE_DISABLE();
        /*I2C SELECT MODE*/
        if(i2c_obj->I2c_cfg.I2C_Mode == MSSP_I2C_MASTER_MODE)
        {
            /*I2C MASTER MODE CONFIGURATION*/
            /*I2C MASTER CLOCK CONFIGYRATION*/
             MSSP_I2C_MASTER_MODE_CLOCK_CONFIGURATION(i2c_obj);
        }
        else if(i2c_obj->I2c_cfg.I2C_Mode == MSSP_I2C_SLAVE_MODE)
        {
            /*I2C SLAVE MODE CONFIGURATION*/
            SSPCON1bits.SSPM = i2c_obj->I2c_cfg.I2c_mode_config;
            /*I2C SALVE MODE  GENERAL CALL CONFIGURATION*/
            if(i2c_obj->I2c_cfg.I2C_General_Call == I2C_GENERAL_CALL_ADDRESS_ENABLE)
            {
                I2C_GENERAL_CALL_ENABLE();
            }
            else if(i2c_obj->I2c_cfg.I2C_General_Call == I2C_GENERAL_CALL_ADDRESS_DISABLE)
            {
                I2C_GENERAL_CALL_DISABLE();
            }
            
            /*CLEAR THE WRITE COLLISION DETECTED*/
            SSPCON1bits.WCOL = 0;/*NO COLLISION*/
            
            /*CLEAR THE RECIVE OVER FLOW INDICTOR*/
            SSPCON1bits.SSPOV = 0;/*NO OVER FLOW ON THE SSPBUF*/
            
            /*RELEASE THE CLOCK*/
            SSPCON1bits.CKP = 1;/*NO CLOCK STRECH*/
            
            /*ASSIGN THE I2C SLAVE ADDRESS*/
            SSPADD = i2c_obj->I2c_cfg.Slave_Address;
            
        }
        /*I2C GPIO CONFIGURATION*/
             MSSP_I2C_MODE_GPIO_CONFIG();
        /*I2C SLEW RATE CONTROL*/
            if(i2c_obj->I2c_cfg.I2C_slew_rate == I2C_SLEW_MODE_ENABLE)
            {
                I2C_SLEW_RATE_CFG_ENABLE();
            }
            else if(i2c_obj->I2c_cfg.I2C_slew_rate == I2C_SLEW_MODE_DISABLE)
            {
                I2C_SLEW_RATE_CFG_DISABLE();
            }
        /*I2C SMBUS CONTROL*/
            if(i2c_obj->I2c_cfg.I2C_SMBUS_Control == I2C_SMPUS_ENABLE)
            {
                 I2C_SMBUS_ENABLE();
            }
            else if(i2c_obj->I2c_cfg.I2C_SMBUS_Control == I2C_SMPUS_DISABLE)
            {
                 I2C_SMBUS_DISABLE();
            }
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_INTERRUPT_CONFIGURATION(i2c_obj);       
#endif
        /*ENABLE MSSP_I2C_MODULE*/
        MSSP_MODULE_ENABLE();
    }
    return(Ret);
}

/**
 * @brief: Desiable the i2c module
 * @param i2c_obj: pointer point to I2C structure
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType MSSP_I2C_DE_INIT(const mssp_i2c_t* i2c_obj )
{
    STD_ReturnType Ret = E_OK;
    if(NULL == i2c_obj)
    {
        Ret = E_NOK;
    }
    else
    {
         MSSP_MODULE_DISABLE();
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
      MSSP_I2C_INTERRUPT_DISABLE();
      MSSP_I2C_BUS_COLLISION_INTERRUPT_DISABLE();
#endif
    }
    return(Ret);
}

/**
 * @brief: send start bit to start control on the bus
 * @param i2c_obj: pointer point to I2C structure
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType MSSP_I2C_MASTER_SEND_START(const mssp_i2c_t* i2c_obj )
{
    STD_ReturnType Ret = E_OK;
    if(NULL == i2c_obj)
    {
        Ret = E_NOK;
    }
    else
    {
        /*INTIATE START CONDITION ON SDA AND SCL PINS*/
        SSPCON2bits.SEN = 1;
        /*WAIT FOR THE COMPLETION OF START CONDITION*/
        while(SSPCON2bits.SEN);
        /*CLEAR THE SSPIF FLAG */
        PIR1bits.SSPIF = 0;
        /*REPORT THE START CONDITION DETECTION*/
        if(SSPSTATbits.S == I2C_START_BIT_DETECTED)
        {
            Ret = E_OK;
        }
        else if(SSPSTATbits.S == I2C_START_BIT_NOT_DETECTED)
        {
            Ret = E_NOK;
        }
    }
    return(Ret);
}

/**
 * @brief: send restart bit to remain the control of bus
 * @param i2c_obj: pointer point to I2C structure
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType MSSP_I2C_MASTER_SEND_RESTART(const mssp_i2c_t* i2c_obj )
{
    STD_ReturnType Ret = E_OK;
    if(NULL == i2c_obj)
    {
        Ret = E_NOK;
    }
    else
    {
        /*intiate the repeated start condition on SDA AND SCL PINS*/
        SSPCON2bits.RSEN = 1;
        /*WAIT THE COMPLETION OF THE REPEATED START CONDITION*/
        while(SSPCON2bits.RSEN);
        /*CLEAR THE INTERRUPT CLEAR ->SSPIF */
        PIR1bits.SSPIF = 0;
    }
    return(Ret);
}

/**
 * @brief: send stop bit to miss control to the bus
 * @param i2c_obj: pointer point to I2C structure
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType MSSP_I2C_MASTER_SEND_STOP(const mssp_i2c_t* i2c_obj )
{
    STD_ReturnType Ret = E_OK;
    if(NULL == i2c_obj)
    {
        Ret = E_NOK;
    }
    else
    {
        /*INTIATE STOP CONDITION ON SDA AND SCL PINS*/
        SSPCON2bits.PEN = 1;
        /*WAIT FOR THE COMPLETION OF STOP CONDITION*/
        while(SSPCON2bits.PEN);
        /*CLEAR THE SSPIF FLAG */
        PIR1bits.SSPIF = 0;
        /*REPORT THE STOP CONDITION DETECTION*/
        if(I2C_STOP_BIT_DETECTED == SSPSTATbits.P)
        {
            Ret = E_OK;
        }
        else  if(I2C_STOP_BIT_NOT_DETECTED == SSPSTATbits.P)
        {
            Ret = E_NOK;
        }
    }
    return(Ret);
}

/**
 * @brief: write data at the Reciver
 * @param I2C_data : the data you want to transimtte 
 * @param i2c_obj: pointer point to I2C structure
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType MSSP_I2C_MASTER_WRITE_BLOKING(const mssp_i2c_t* i2c_obj, uint8 I2C_data, uint8 *ack)
{
    STD_ReturnType Ret = E_OK;
    if((NULL == i2c_obj) || (NULL == ack))
    {
        Ret = E_NOK;
    }
    else
    {
        /*WRITE DATE TO THE SSPBUF REGISTER*/
        SSPBUF = I2C_data;
        /*WAIT THE TRANSIMATION TO COMPLETED*/
        while(!PIR1bits.SSPIF);
        /*CLEAR THE SSPIF FLAHG*/
        PIR1bits.SSPIF = 0;
        /*REPORT THE ACKNOLEDGE RECIEVED FROM THE SLAVE*/
        if(I2C_ACKNOLEDGE_BIT_RECIVE_FROM_SLAVE_DETECTED == SSPCON2bits.ACKSTAT)
        {
           *ack = I2C_ACKNOLEDGE_BIT_RECIVE_FROM_SLAVE_DETECTED;
        }
        else if(I2C_ACKNOLEDGE_BIT_RECIVE_FROM_SLAVE_NOT_DETECTED == SSPCON2bits.ACKSTAT)
        {
            *ack = I2C_ACKNOLEDGE_BIT_RECIVE_FROM_SLAVE_NOT_DETECTED;
        }
    }
    return(Ret);
}

/**
 * @brief: Read date from Recever
 * @param I2C_data : pointer to store the read data
 * @param i2c_obj: pointer point to I2C structure
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType MSSP_I2C_MASTER_READ_BLOCKING(const mssp_i2c_t* i2c_obj, uint8 *I2C_data, uint8 ACK)
{
    STD_ReturnType Ret = E_OK;
    if((NULL == i2c_obj) || (NULL == I2C_data))
    {
        Ret = E_NOK;
    }
    else
    {
        /*ENABLE MASTER MODE RECIEVE ENABLE*/
        I2C_MASTER_RECIVER_ENABLE();
        /*WAIT FOR BUFFER FALL FLAG /*COMPLETE BYTE RECIVE*/
        while(!SSPSTATbits.BF);
        /*COPY THE DATE FROM BUFFER REGIDTER */
        *I2C_data = SSPBUF;
         /*SEND ACK OR NOT ACK AFTER READ*/
        if(ACK == I2C_MASTER_RECIVER_MODE_SEND_ACK )
        {
            SSPCON2bits.ACKDT = I2C_MASTER_RECIVER_MODE_SEND_ACK;
        }
        else if(ACK == I2C_MASTER_RECIVER_MODE_SEND_NOT_ACK )
        {
            SSPCON2bits.ACKDT = I2C_MASTER_RECIVER_MODE_SEND_NOT_ACK;
        }
        SSPCON2bits.ACKEN = 1;/*INTIATE TO ACKNOLEDGE SEQUANCE*/
    }
    return(Ret);
}
static inline void MSSP_I2C_MODE_GPIO_CONFIG(void)
{
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
}
static inline void MSSP_I2C_MASTER_MODE_CLOCK_CONFIGURATION(const mssp_i2c_t* i2c_obj)
{
    SSPCON1bits.SSPM = i2c_obj->I2c_cfg.I2c_mode_config;
    SSPADD =(uint8)( ( (_XTAL_FREQ / 4) / i2c_obj->I2C_clock_speed ) -1 );
}
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

static inline void MSSP_I2C_INTERRUPT_CONFIGURATION(const mssp_i2c_t* i2c_obj)
{
            /*INTERRUPT CONFIGURATION*/
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            /*MSSP_I2C_INTERRUPT_ENBLE*/
            MSSP_I2C_INTERRUPT_ENABLE();
            MSSP_I2C_BUS_COLLISION_INTERRUPT_ENABLE();
            /*CLEAR FLAG*/
            MSSP_I2C_INTERRUPT_CLEAR_FLAG();
            MSSP_I2C_BUS_COLLISION_INTERRUPT_CLEAR_FLAG();
            /*CONFIGURE CALL BACK*/
            MSSP_I2C_INTERRUPT_HANDELLER = i2c_obj->I2C_INTERRUPT_HANDELLER;
            MSSP_I2C_BUS_CONTROL_INTERRUPT_HANDELLER = i2c_obj->I2C_REPORT_WRITE_COLLISION;
            MSSP_I2C_REPORT_RECIVE_OVERFLOW = i2c_obj->I2C_REPORT_RECIVE_OVERFLOW;
            
#if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PERIORITY_LEVELS_ENABLE();
            if(INTERRUPT_LOW_PRIORITY == i2c_obj->mssp_i2c_priority)
            {
                MSSP_I2C_INTERRUPT_LOW_PRIORITY_ENABLE();
                INTERRUPT_GLOPAL_INTERRUPT_LOW_ENABLE();
            }
            else  if(INTERRUPT_HIGH_PRIORITY == i2c_obj->mssp_i2c_priority)
            {  
                MSSP_I2C_INTERRUPT_HIGH_PRIORITY_ENABLE();
                INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE();
            }
            
            if(INTERRUPT_LOW_PRIORITY == i2c_obj->I2C_REPORT_WRITE_COLLISION)
            {
                MSSP_I2C_BUS_COLLISION_INTERRUPT_LOW_PRIORITY_ENABLE();
                INTERRUPT_GLOPAL_INTERRUPT_LOW_ENABLE();
            }
            else  if(INTERRUPT_HIGH_PRIORITY == i2c_obj->I2C_REPORT_WRITE_COLLISION)
            {  
                MSSP_I2C_BUS_COLLISION_INTERRUPT_HIGH_PRIORITY_ENABLE();
                INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE();
            }
#else
    INTERRUPT_GLOPAL_INTERRUPT_ENABLE();
    INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
#endif
    
#endif
}
#endif


void MSSP_I2C_ISR(void)
{
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
     MSSP_I2C_INTERRUPT_CLEAR_FLAG();
    if(MSSP_I2C_INTERRUPT_HANDELLER)
    {
       MSSP_I2C_INTERRUPT_HANDELLER(); 
    }
#endif
}

void MSSP_I2C_COLLISION_ISR(void)
{
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    MSSP_I2C_BUS_COLLISION_INTERRUPT_CLEAR_FLAG();
    if(MSSP_I2C_BUS_CONTROL_INTERRUPT_HANDELLER )
    {
        MSSP_I2C_BUS_CONTROL_INTERRUPT_HANDELLER();
    }
#endif
}

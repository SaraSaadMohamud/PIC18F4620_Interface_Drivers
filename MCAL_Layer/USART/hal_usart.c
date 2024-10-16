/* 
 * File:   hal_usart.C
 * Author: DELL
 *
 * Created on September 23, 2024, 5:54 PM
 */
#include "hal_usart.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if EUSART_Tx_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*EUSART_TX_INTERRUPT_HANDELER)(void) =NULL;
#endif

#if EUSART_Rx_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*EUSART_RX_INTERRUPT_HANDELER)(void) =NULL;
    static void (*EUSART_FRAMING_ERROR_INTERRUPT_HANDELER)(void) =NULL;
    static void (*EUSART_OVERRUN_ERROR_INTERRUPT_HANDELER)(void) =NULL;
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static STD_ReturnType EUSART_BAUDRATE_CALCULATION(const usart_config_t * usart_obj);
static STD_ReturnType EUSART_TRANSMATION_CONFIG(const usart_config_t * usart_obj);
static STD_ReturnType EUSART_RECIVING_CONFIG(const usart_config_t * usart_obj);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief: function Enable the EUASRT Module
 * @param usart_obj: pointer point to the structure of EUSART 
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType EUSART_ASYN_INIT(const usart_config_t * usart_obj)
{
   STD_ReturnType Ret = E_OK;
   if(NULL == usart_obj)
   {
       Ret = E_NOK;
   }
   else
   {
       RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
       TRISCbits.RC7 = 1;
       TRISCbits.RC6 = 1;
       
       EUSART_BAUDRATE_CALCULATION(usart_obj);
       EUSART_TRANSMATION_CONFIG(usart_obj);
       EUSART_RECIVING_CONFIG(usart_obj);
       
       RCSTAbits.SPEN = EUSART_MODULE_ENABLE;
   }
   return(Ret);
}

/**
 * @brief: function Disable the EUASRT Module
 * @param usart_obj: pointer point to the structure of EUSART 
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType EUSART_ASYN_DE_INIT(const usart_config_t * usart_obj)
{
   STD_ReturnType Ret = E_OK;
   if(NULL == usart_obj)
   {
       Ret = E_NOK;
   }
   else
   {
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
   }
   return(Ret);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief: function to write the data at RCREG Register
 * @param usart_obj: pointer point to the structure of EUSART 
 * @param value : variable contain the date that will store at RCREG Register
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType EUSART_ASYN_WRITE_BYTE_BLOCKING(const usart_config_t * usart_obj,uint8 value)
{
   STD_ReturnType Ret = E_OK;
   if(NULL == usart_obj)
   {
       Ret = E_NOK;
   }
   else
   {
       while(!TXSTAbits.TRMT);
#if EUSART_Tx_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
      EUSART_Tx_INTERRUPT_ENABLE(); 
#endif
       
       TXREG = value;
   }
   return(Ret);
}

/**
 * @brief: function to write string at RCREG Register
 * @param usart_obj: pointer point to the structure of EUSART 
 * @param value : pointer contain the string that will store at RCREG Register
 * @param str_lenght: variable act the lenght of string 
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType EUSART_ASYN_WRITE_STRING_BLOCKING(const usart_config_t * usart_obj,uint8 *str,uint16 str_lenght)
{
    STD_ReturnType Ret = E_OK;
    uint16 str_count=0;
    
   if((NULL == usart_obj) || (NULL == str))
   {
       Ret = E_NOK;
   }
   else
   {
       for(str_count=0 ; str_count<str_lenght ; str_count++)
       {
           Ret = EUSART_ASYN_WRITE_BYTE_BLOCKING(usart_obj,str[str_count]);
       }
   }
   return(Ret);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief: function to read the data from RCREG Register
 * @param usart_obj: pointer point to the structure of EUSART 
 * @param value : pointer to the RCREG
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType EUSART_ASYN_READ_BYTE_BLOCKING(const usart_config_t * usart_obj,uint8 * value)
{
   STD_ReturnType Ret = E_OK;
   if((NULL == usart_obj) || (NULL == value))
   {
       Ret = E_NOK;
   }
   else
   {
       while(! PIR1bits.RCIF);
       * value = RCREG;
   }
   return(Ret);
}

/**
 * @brief: function to read the data from RCREG Register
 * @param usart_obj: pointer point to the structure of EUSART 
 * @param value : pointer to the RCREG
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType EUSART_ASYN_READ_BYTE_NON_BLOCKING(const usart_config_t * usart_obj,uint8 * value)
{
    STD_ReturnType Ret = E_OK;
    if((NULL == usart_obj) || (NULL == value))
    {
        Ret = E_NOK;
    }
    else
    {
        if(1 == PIR1bits.RCIF)
        {
            * value = RCREG;
        }
        else
        {
            Ret =  E_NOK;
        }
        
    }
    return(Ret);
}
/////////////////////////////////////////////////////////////////////////////////////////////
static STD_ReturnType EUSART_BAUDRATE_CALCULATION(const usart_config_t * usart_obj)
{
    STD_ReturnType Ret = E_OK;
    float BaudRate_Temp=0;
    
    if(NULL == usart_obj){
        Ret = E_NOK;
    }
    else
    {
       switch( usart_obj->baudrate_gen_cfg)
        {
            case USART_ASYN_8BIT_LOW_SPEED :
                TXSTAbits.SYNC =  EUSART_ASYNCRONOUS_MOOD ;
                TXSTAbits.BRGH = EUSART_ASYNCRONOUS_LOW_SPEED;
                BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;  
                BaudRate_Temp = ((_XTAL_FREQ/(float)(usart_obj->baudrate))/64)-1;
                break;
            case USART_ASYN_8BIT_HIGH_SPEED :
                TXSTAbits.SYNC =  EUSART_ASYNCRONOUS_MOOD ;
                TXSTAbits.BRGH = EUSART_ASYNCRONOUS_HIGH_SPEED;
                BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
                BaudRate_Temp = ((_XTAL_FREQ/(float)(usart_obj->baudrate))/16)-1;
                break;
            case USART_ASYN_16BIT_LOW_SPEED :
                TXSTAbits.SYNC =  EUSART_ASYNCRONOUS_MOOD ;
                TXSTAbits.BRGH = EUSART_ASYNCRONOUS_LOW_SPEED;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                BaudRate_Temp = ((_XTAL_FREQ/(float)(usart_obj->baudrate))/16)-1;
                break;
            case USART_ASYN_16BIT_HIGH_SPEED :
                TXSTAbits.SYNC =  EUSART_ASYNCRONOUS_MOOD ;
                TXSTAbits.BRGH = EUSART_ASYNCRONOUS_HIGH_SPEED;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                BaudRate_Temp = ((_XTAL_FREQ/(float)(usart_obj->baudrate))/4)-1;
                break;
            case USART_SYN_8BIT :
                TXSTAbits.SYNC =  EUSART_SYNCRONOUS_MOOD  ;
                BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
                BaudRate_Temp = ((_XTAL_FREQ/(float)(usart_obj->baudrate))/4)-1;
                break;
            case USART_SYN_16BIT :
                TXSTAbits.SYNC =  EUSART_SYNCRONOUS_MOOD  ;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                BaudRate_Temp = ((_XTAL_FREQ/(float)(usart_obj->baudrate))/4)-1;
                break;
            default :
                Ret = E_NOK;
                break;
        } 
       SPBRG = (uint8)( (uint32)BaudRate_Temp );
       SPBRGH = (uint8)( ((uint32)BaudRate_Temp) >> 8 );
    }
    return(Ret);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
static STD_ReturnType EUSART_TRANSMATION_CONFIG(const usart_config_t * usart_obj)
{
    STD_ReturnType Ret = E_OK;
    
    if(NULL == usart_obj){
        Ret = E_NOK;
    }
    else
    {
        /*ENABLE THE TRANSMITTER*/
        if(usart_obj->usart_tx_cfg.usart_asyn_tx_enable == EUSART_ASYNCRONOUS_TX_ENABLE)
        {
            TXSTAbits.TXEN = EUSART_ASYNCRONOUS_TX_ENABLE;
            /*Interrupt_config*/
            if(usart_obj->usart_tx_cfg.usart_asyn_tx_itrrupt_enable == EUSART_ASYNCRONOUS_TX_INTERRUPT_ENABLE)
            {
                EUSART_Tx_INTERRUPT_ENABLE();
#if EUSART_Tx_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
                EUSART_Tx_INTERRUPT_ENABLE();
                
                EUSART_TX_INTERRUPT_HANDELER = usart_obj->EUSART_TX_INTERRUPR_HANDELER;
                
#if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PERIORITY_LEVELS_ENABLE();
                if(usart_obj ->eusart_priority_enable == INTERRUPT_LOW_PRIORITY)
                {
                    INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE();
                    EUSART_Tx_INTERRUPT_LOW_PRIORITY_ENABLE();
                }
                else if(usart_obj ->eusart_priority_enable == INTERRUPT_HIGH_PRIORITY)
                {
                    INTERRUPT_GLOPAL_INTERRUPT_LOW_ENABLE();
                    EUSART_Tx_INTERRUPT_HIGH_PRIORITY_ENABLE();
                }
#else
                INTERRUPT_GLOPAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();              
#endif
                
#endif
                
            }
            else if(usart_obj->usart_tx_cfg.usart_asyn_tx_itrrupt_enable == EUSART_ASYNCRONOUS_TX_INTERRUPT_DISABLE)
            {
                EUSART_Tx_INTERRUPT_DISABLE();
            } 
            /*eusart_9bit_config*/
            if(usart_obj->usart_tx_cfg.usart_asyn_tx_9bit_enable == EUSART_ASYNCRONOUS_TX_9BIT_ENABLE)
            {
                TXSTAbits.TX9 = EUSART_ASYNCRONOUS_TX_9BIT_ENABLE;
            }
            else if(usart_obj->usart_tx_cfg.usart_asyn_tx_9bit_enable == EUSART_ASYNCRONOUS_TX_9BIT_DISABLE)
            {
                TXSTAbits.TX9 = EUSART_ASYNCRONOUS_TX_9BIT_DISABLE;
            } 
        }
        else if (usart_obj->usart_tx_cfg.usart_asyn_tx_enable == EUSART_ASYNCRONOUS_TX_DISABLE)
        {
            TXSTAbits.TXEN = EUSART_ASYNCRONOUS_TX_DISABLE;
        }
    }
    return(Ret);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static STD_ReturnType EUSART_RECIVING_CONFIG(const usart_config_t * usart_obj)
{
    STD_ReturnType Ret = E_OK;
    
    if(NULL == usart_obj){
        Ret = E_NOK;
    }
    else
    {
        /*ENABLE THE RECIVER*/
        if(usart_obj->usart_rx_cfg.usart_asyn_rx_enable == EUSART_ASYNCRONOUS_RX_ENABLE)
        {
             RCSTAbits.CREN = EUSART_ASYNCRONOUS_RX_ENABLE;
            /*Interrupt_config*/
            if(usart_obj->usart_rx_cfg.usart_asyn_rx_itrrupt_enable == EUSART_ASYNCRONOUS_RX_INTERRUPT_ENABLE)
            {
                EUSART_Rx_INTERRUPT_ENABLE();
#if EUSART_Rx_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
                EUSART_Rx_INTERRUPT_ENABLE();
                EUSART_RX_INTERRUPT_HANDELER = usart_obj->EUSART_RX_INTERRUPR_HANDELER;
                EUSART_FRAMING_ERROR_INTERRUPT_HANDELER = usart_obj->EUSART_FRAMING_ERROR_INTERRUPR_HANDELER;
                EUSART_OVERRUN_ERROR_INTERRUPT_HANDELER = usart_obj->EUSART_OVERRUN_ERROR_INTERRUPR_HANDELER;
#if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PERIORITY_LEVELS_ENABLE();
                if(usart_obj ->eusart_priority_enable == INTERRUPT_LOW_PRIORITY)
                {
                    INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE();
                    EUSART_Rx_INTERRUPT_LOW_PRIORITY_ENABLE();
                }
                else if(usart_obj ->eusart_priority_enable == INTERRUPT_HIGH_PRIORITY)
                {
                    INTERRUPT_GLOPAL_INTERRUPT_LOW_ENABLE();
                    EUSART_Rx_INTERRUPT_HIGH_PRIORITY_ENABLE();
                }
            #else
                INTERRUPT_GLOPAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();              
#endif
                
#endif
            }
            else if(usart_obj->usart_rx_cfg.usart_asyn_rx_itrrupt_enable == EUSART_ASYNCRONOUS_RX_INTERRUPT_DISABLE)
            {
                EUSART_Rx_INTERRUPT_DISABLE();
            } 
            /*eusart_9bit_config*/
            if(usart_obj->usart_rx_cfg.usart_asyn_rx_9bit_enable == EUSART_ASYNCRONOUS_RX_9BIT_ENABLE)
            {
                RCSTAbits.RC9= EUSART_ASYNCRONOUS_RX_9BIT_ENABLE;
            }
            else if(usart_obj->usart_tx_cfg.usart_asyn_tx_9bit_enable == EUSART_ASYNCRONOUS_TX_9BIT_DISABLE)
            {
                RCSTAbits.RC9 = EUSART_ASYNCRONOUS_RX_9BIT_DISABLE;
            } 
        }
        else if (usart_obj->usart_tx_cfg.usart_asyn_tx_enable == EUSART_ASYNCRONOUS_TX_DISABLE)
        {
            RCSTAbits.CREN = EUSART_ASYNCRONOUS_RX_DISABLE;
        }
        
        
    }
    return(Ret);
}
////////////////////////////////////////////////////////////////////////////////////////////
STD_ReturnType EUSART_ASYN_RESTART_RX(void)
{
    RCSTAbits.CREN = EUSART_ASYNCRONOUS_RX_DISABLE; /*DISABLE TO THE RECIVER*/
    RCSTAbits.CREN = EUSART_ASYNCRONOUS_RX_ENABLE;  /*ENABLE TO THE RECIVER*/
}
//////////////////////////////////////////////////////////////////////////////////////////
void EUSART_TX_ISR(void)
{
    EUSART_Tx_INTERRUPT_DISABLE();
    if(EUSART_TX_INTERRUPT_HANDELER )
    {
        EUSART_TX_INTERRUPT_HANDELER();
    }
}
void EUSART_RX_ISR(void)
{
    if(EUSART_RX_INTERRUPT_HANDELER )
    {
        EUSART_RX_INTERRUPT_HANDELER();
    }
    
    if(EUSART_FRAMING_ERROR_INTERRUPT_HANDELER )
    {
        EUSART_FRAMING_ERROR_INTERRUPT_HANDELER ();
    }
    
    if(EUSART_OVERRUN_ERROR_INTERRUPT_HANDELER  )
    {
        EUSART_OVERRUN_ERROR_INTERRUPT_HANDELER ();
    }
}
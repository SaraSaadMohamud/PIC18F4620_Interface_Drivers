/* 
 * File:   hal_adc.c
 * Author: DELL
 *
 * Created on September 4, 2024, 9:59 PM
 */

#include "hal_adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    static void (* ADC_INTERRUPT_HANDELER)(void) = NULL;    
#endif

static inline void adc_input_channel_port_configure( adc_channel_select_t channel);
static inline void select_result_format(const adc_config_t * adc_obj);
static inline void select_voltage_refrance(const adc_config_t * adc_obj);
/**
 * @brief :Intialize the ADC Conversion
 * @param adc_obj POINTER TO TH E STRUCTURE OF ADC_CONFIGURATUON
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType ADC_Init(const adc_config_t * adc_obj)
{
    STD_ReturnType Ret = E_OK;
    if((NULL == adc_obj))
    {
        Ret = E_NOK;
    }
    else
    {
        /*DISABLE THE ADC*/
        ADC_CONVERTER_DISABLE();
        /*CONFIGURE THE ACQUISATION TIME*/
        ADCON2bits.ACQT = (adc_obj ->acqusation_time) ;
        /*CONFIGURE THE CONVERSATION CLOCK*/
        ADCON2bits.ADCS = (adc_obj ->conversion_clock);
        /*CONFIGURE THE CHANNEL*/
        ADCON0bits.CHS = (adc_obj ->adc_channel);
        adc_input_channel_port_configure(adc_obj ->adc_channel);
        /*CONFIGURE THE INTERRUPT*/
        #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            ADC_INTERRUPT_ENABLE();
            ADC_INTERRUPT_CLEAR_FLAG();
            #if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PERIORITY_LEVELS_ENABLE();
                if(adc_obj ->Interrupt_priority == INTERRUPT_HIGH_PRIORITY)
                {
                    INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE();
                    ADC_INTERRUPT_HIGH_PRIORITY_ENABLE();
                }
                else if(adc_obj ->Interrupt_priority == INTERRUPT_LOW_PRIORITY)
                {
                    INTERRUPT_GLOPAL_INTERRUPT_LOW_ENABLE();
                    ADC_INTERRUPT_LOW_PRIORITY_ENABLE();
                }
                else
                {
                    /*NOTHING*/
                }
            #else
                INTERRUPT_GLOPAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
            #endif
            ADC_INTERRUPT_HANDELER = adc_obj ->ADC_INTERRUPT_HANDELLER; 
            #endif

        /*CONFIGURE HE OUTPUT FORMATE*/
          select_result_format(adc_obj);
        /*CONFIGURE THE VOLTAGE REFRANCE*/
        select_voltage_refrance(adc_obj);
        /*ENABLE THE ADC*/
        ADC_CONVERTER_ENABLE();
    }
    return(Ret);
}
/**
 @brief :DE_Intialize the ADC Conversion
 * @param adc_obj POINTER TO THE STRUCTURE OF ADC_CONFIGURATUON
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType ADC_De_Init(const adc_config_t * adc_obj)
{
    STD_ReturnType Ret = E_OK;
    if((NULL == adc_obj))
    {
        Ret = E_NOK;
    } 
    else
    {
        /*DISABLE THE ADC*/
        ADC_CONVERTER_DISABLE();
        /*DISABLE THE INTERRUPT*/
        #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            ADC_INTERRUPT_DISABLE();
        #endif
    }
    return(Ret);
}
/**
 * @brief : function to select special function
 * @param adc_obj :POINTER TO THE STRUCTURE OF ADC_CONFIGURATUON
 * @param : have the channel that the ADC will convert the input Voltage that is finding on
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType ADC_Select_Channel(const adc_config_t * adc_obj, adc_channel_select_t channel)
{
    STD_ReturnType Ret = E_OK;
    if((NULL == adc_obj))
    {
        Ret = E_NOK;
    }
    else
    {
        ADCON0bits.CHS = channel;
        adc_input_channel_port_configure(channel);
    }
    return(Ret);
}
/**
 * @brief : function that starting the conversation from analog to digital
 * @param adc_obj:POINTER TO THE STRUCTURE OF ADC_CONFIGURATUON
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType ADC_Start_Conversion(const adc_config_t * adc_obj)
{
    STD_ReturnType Ret = E_OK;
    if((NULL == adc_obj))
    {
        Ret = E_NOK;
    }
    else
    {
        ADC_START_CONVERSION();
    }
    return(Ret);
}
/**
 * brief : function knowing from that the ADC conversation is completed
 * @param adc_obj ::POINTER TO THE STRUCTURE OF ADC_CONFIGURATUON
 * @param conversion_status : pointer for knowing that the adc is done
 *                           TRUE :IF FUNCTION IS COMPLATED
 *                           FALSE : IF FUNCTION IS UNCOMPLATED
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType ADC_IS_Conversion_Done(const adc_config_t * adc_obj,uint8 *conversion_status)
{
    STD_ReturnType Ret = E_OK;
    if((NULL == adc_obj) || (NULL == conversion_status))
    {
        Ret = E_NOK;
    }
    else
    {
       *conversion_status = (uint8)(!(ADCON0bits.GO_nDONE));
    }
    return(Ret);
}
/**
 * @brief : function to know the digital output that coming from convert the input analog voltage
 * @param adc_obj :POINTER TO THE STRUCTURE OF ADC_CONFIGURATUON
 * @param conversion_result : pointer to know the digital output
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType ADC_Get_Conversion_Results(const adc_config_t * adc_obj,uint16 *conversion_result)
{
    STD_ReturnType Ret = E_OK;
    if((NULL == adc_obj) || (NULL == conversion_result))
    {
        Ret = E_NOK;
    }
    else
    {
        if(adc_obj ->result_formate == ADC_RESULT_RIGHT)
        {
            *conversion_result = (uint16)( (ADRESH >> 8) + (ADRESL) ) ;
        }
        else if(adc_obj ->result_formate == ADC_RESULT_LEFT)
        {
             *conversion_result = (uint16)( ( (ADRESH >> 8) + (ADRESL) ) >> 6) ;
        }
        else
        {
             *conversion_result = (uint16)( (ADRESH >> 8) + (ADRESL) ) ;
        }
    }
    return(Ret);
}
/**
 * @brief : function to make the steps of ADC process
 * @param adc_obj : POINTER TO THE STRUCTURE OF ADC_CONFIGURATUON
 * @param conversion_status : pointer for knowing that the adc is done
 * @param conversion_result : pointer to know the digital output
* @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType ADC_Get_Conversion_BLOCKING(const adc_config_t * adc_obj, adc_channel_select_t channel,uint16 *conversion_result)
{
    STD_ReturnType Ret = E_OK;
    uint8 l_conversion_status=0;
    
    if((NULL == adc_obj) || (NULL == conversion_result))
    {
        Ret = E_NOK;
    }
    else
    {
        /*SELECT CHANNEL*/
          Ret = ADC_Select_Channel(adc_obj, channel);
         /*START ADC CONVERSION*/
          Ret = ADC_Start_Conversion(adc_obj);
         /*ADC CONVERSION IS DONE*/
          Ret = ADC_IS_Conversion_Done(adc_obj,& l_conversion_status);
          while(ADCON0bits.GO_nDONE);
         /*GET THE RESULT OF CONVERSATION PROCESS*/
           Ret = ADC_Get_Conversion_Results(adc_obj, conversion_result);
           /*if(CONVERSION_COMPLETED == l_conversion_status )
           {
               Ret = ADC_Get_Conversion_Results(adc_obj, conversion_result);
           } 
           else
           {
               Ret = E_NOK;
           }*/
    
          
    }
    return(Ret);
}
/**
 * 
 * @param channel
 */
static inline void adc_input_channel_port_configure( adc_channel_select_t channel)
{
    switch(channel)
    {
        case ADC_CHANNEL_AN0 :
            SET_BIT(TRISA , _TRISA_RA0_POSN);
            break;
        case ADC_CHANNEL_AN1  :
            SET_BIT(TRISA , _TRISA_RA1_POSN);
            break;
        case ADC_CHANNEL_AN2  :
            SET_BIT(TRISA , _TRISA_RA2_POSN);
            break;
        case ADC_CHANNEL_AN3  :
            SET_BIT(TRISA , _TRISA_RA3_POSN);
            break;
        case ADC_CHANNEL_AN4  :
            SET_BIT(TRISA , _TRISA_RA5_POSN);
            break;
        case ADC_CHANNEL_AN5  :
            SET_BIT(TRISE , _TRISE_RE0_POSN);
            break;
        case ADC_CHANNEL_AN6  :
            SET_BIT(TRISE , _TRISE_RE1_POSN);
            break;
        case ADC_CHANNEL_AN7  :
            SET_BIT(TRISE , _TRISE_RE2_POSN);
            break;
        case ADC_CHANNEL_AN8  :
            SET_BIT(TRISB , _TRISB_RB2_POSN);
            break;
        case ADC_CHANNEL_AN9  :
            SET_BIT(TRISB , _TRISB_RB3_POSN);
            break;
        case ADC_CHANNEL_AN10 :
            SET_BIT(TRISB , _TRISB_RB1_POSN);
            break;
        case ADC_CHANNEL_AN11 :
           SET_BIT(TRISB , _TRISB_RB4_POSN);
            break;
        case ADC_CHANNEL_AN12 :
            SET_BIT(TRISB , _TRISB_RB0_POSN);
            break;
    }
}
/**
 * 
 * @param adc_obj
 */
static inline void select_result_format(const adc_config_t * adc_obj)
{
    switch(adc_obj ->result_formate)
    {
        case ADC_RESULT_RIGHT :
            ADC_RIGHT_FORMATE_ENABLE();
            break;
        case ADC_RESULT_LEFT :
            ADC_LEFT_FORMATE_ENABLE();
            break;
        default :
            ADC_RIGHT_FORMATE_ENABLE();
            break;
    }
}
/**
 * 
 * @param adc_obj
 */
static inline void select_voltage_refrance(const adc_config_t * adc_obj)
{
    switch(adc_obj ->voltage_refrance)
    {
        case VOLTAGE_REFRANCE_ENABLE :
            ADC_VOLTAGE_REFRANCE_ENABLE();
            break;
        case VOLTAGE_REFRANCE_DISABLE :
            ADC_VOLTAGE_REFRANCE_DISABLE();
            break;
        default :
         ADC_VOLTAGE_REFRANCE_DISABLE();
            break;   
    }
}
void ADC_ISR (void)
{
    ADC_INTERRUPT_CLEAR_FLAG();
    if(ADC_INTERRUPT_HANDELER)
    {
        ADC_INTERRUPT_HANDELER();
    }
}
STD_ReturnType ADC_START_Conversion_INTERRUPT(const adc_config_t * adc_obj, adc_channel_select_t channel)
{
STD_ReturnType Ret = E_OK;
    uint8 l_conversion_status=0;
    
    if((NULL == adc_obj))
    {
        Ret = E_NOK;
    }
    else
    {
        /*SELECT CHANNEL*/
          Ret = ADC_Select_Channel(adc_obj, channel);
         /*START ADC CONVERSION*/
          Ret = ADC_Start_Conversion(adc_obj);     
    }
    return(Ret);
}
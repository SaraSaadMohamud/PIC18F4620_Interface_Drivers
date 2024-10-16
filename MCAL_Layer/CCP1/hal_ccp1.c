/* 
 * File:   hal-ccp1.c
 * Author: DELL
 *
 * Created on September 13, 2024, 3:16 AM
 */
#include "hal-ccp1.h"
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void (* CCP1_INTERRUPT_SET_HANDELER)(void);
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void (* CCP2_INTERRUPT_SET_HANDELER)(void);
#endif

static STD_ReturnType CCP_Interrupt_Config(const ccp_t * ccp_obj);
static STD_ReturnType CCP_PWM_Mode_Config(const ccp_t * ccp_obj);
static STD_ReturnType CCP_Capture_Mode_Config(const ccp_t * ccp_obj);
static STD_ReturnType CCP_Compare_Mode_Config(const ccp_t * ccp_obj);
static STD_ReturnType CCP_Capture_Timer_config(const ccp_t * ccp_obj);
static STD_ReturnType CCP_Compare_Timer_config(const ccp_t * ccp_obj);

STD_ReturnType CCP_Init(const ccp_t * ccp_obj)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == ccp_obj)
    {
       Ret = E_NOK; 
    }
    else
    {
        if(ccp_obj ->ccp_init == CCP1_INIT)
        {
            CCP1_CONFIG_SELECTE_MODE(CCP_MODULE_DISABLE);
        }
        else if(ccp_obj ->ccp_init == CCP2_INIT)
        {
            CCP2_CONFIG_SELECTE_MODE(CCP_MODULE_DISABLE);
        }
        CCP_Interrupt_Config(ccp_obj);
        
        switch(ccp_obj->ccp_mode_select)
        {
            /*CCP1 CAPTURE MODE INTIALIZE*/
            #if CCP1_MODULE_SELECT == CCP_CAPTURE_MODULE_ENABLE ||CCP2_MODULE_SELECT == CCP_CAPTURE_MODULE_ENABLE
            case CCP1_CAPTURE_MODE :
                CCP_Capture_Mode_Config(ccp_obj);
                 break;
            #endif
            /*CCP1 COMPARE MODE INTIALIZE*/
            #if CCP1_MODULE_SELECT == CCP_COMPARE_MODULE_ENABLE ||CCP2_MODULE_SELECT == CCP_COMPARE_MODULE_ENABLE
            case CCP1_COMPARE_MODE :
                    CCP_Compare_Mode_Config(ccp_obj);
                break; 
            #endif
            /*CCP1 PWM MODE INTIALIZE*/
            #if CCP_PWM_MODULE_ENABLE == CCP1_MODULE_SELECT || CCP_PWM_MODULE_ENABLE == CCP2_MODULE_SELECT
                case CCP_PWM_MODE :
                    CCP_PWM_Mode_Config(&ccp_obj);
                    break;
            #endif
        }
        Ret = gpio_pin_intializtion(&(ccp_obj->ccp_pin));   
    }   
    return(Ret);
}
STD_ReturnType CCP_De_Init(const ccp_t * ccp_obj)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == ccp_obj)
    {
       Ret = E_NOK; 
    }
    else
    {
        if(ccp_obj ->ccp_init == CCP1_INIT)
        {
            CCP1_CONFIG_SELECTE_MODE(CCP_MODULE_DISABLE);
            #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
                CCP1_INTERRUPT_DISABLE();
            #endif
        }
        else if(ccp_obj ->ccp_init == CCP2_INIT)
        {
            CCP2_CONFIG_SELECTE_MODE(CCP_MODULE_DISABLE);
            #if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
                CCP2_INTERRUPT_DISABLE();
            #endif
        }
       
       
    }
    return(Ret);
}
#if CCP1_MODULE_SELECT == CCP_CAPTURE_MODULE_ENABLE ||CCP2_MODULE_SELECT == CCP_CAPTURE_MODULE_ENABLE
STD_ReturnType CCP1_Is_Capture_Data_Ready(uint8 *capture_status)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == capture_status)
    {
       Ret = E_NOK; 
    }
    else
    {
        if(PIR1bits.CCP1IF == CCP_CAPTURE_READY)
        {
            *capture_status = CCP_CAPTURE_READY;
            CCP1_INTERRUPT_CLEAR_FLAG();
        }
        else
        {
             *capture_status =CCP_CAPTURE_NOT_READY;
        }
    }
    return(Ret);
}
STD_ReturnType CCP1_Capture_Read_Data(uint16 *value)
{
    STD_ReturnType Ret = E_OK;
    ccp_reg_t Capture_temp_value={.ccp_low=0,.ccp_high=0};
    
    if(NULL == value)
    {
       Ret = E_NOK; 
    }
    else
    {
        Capture_temp_value.ccp_low  = CCPR1L;
        Capture_temp_value.ccp_high = CCPR1H;
        
       *value = Capture_temp_value.ccp_16bit;
    }
    return(Ret);
}
#elif CCP1_MODULE_SELECT == CCP_COMPARE_MODULE_ENABLE || CCP2_MODULE_SELECT == CCP_COMPARE_MODULE_ENABLE
STD_ReturnType CCP_Is_Compare_Data_Ready(const ccp_t * ccp_obj,uint8 *compare_status)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == compare_status)
    {
       Ret = E_NOK; 
    }
    else
    {
        if(ccp_obj ->ccp_init ==  CCP1_INIT)
        {
            if(CCP_COMPARE_READY ==PIR1bits.CCP1IF)
            {
                *compare_status = CCP_COMPARE_READY;
            }
            else
            {
                *compare_status = CCP_COMPARE_NOT_READY;
            }
        }
        else if(ccp_obj ->ccp_init ==  CCP2_INIT)
        {
            if(CCP_COMPARE_READY ==PIR2bits.CCP2IF)
            {
                *compare_status = CCP_COMPARE_READY;
            }
            else
            {
                *compare_status = CCP_COMPARE_NOT_READY;
            }
        }   
    }
    return(Ret);
}
    
STD_ReturnType CCP_Compare_Write_Data(const ccp_t * ccp_obj,uint16 value)
{
   STD_ReturnType Ret = E_OK;
   ccp_reg_t Compare_temp_value={.ccp_low=0,.ccp_high=0};
   if (NULL == ccp_obj)
   {
       Ret = E_NOK;
   }
   else
   {
        Compare_temp_value.ccp_16bit = value;
        if(ccp_obj ->ccp_init ==  CCP1_INIT)
        {
            CCPR1L = Compare_temp_value.ccp_low ;
            CCPR1H = Compare_temp_value.ccp_high;
        }
        else if(ccp_obj ->ccp_init ==  CCP2_INIT)
        {
            CCPR2L = Compare_temp_value.ccp_low ;
            CCPR2H = Compare_temp_value.ccp_high;
        }  
   }
    
  
   
   return(Ret);
}
#elif CCP1_MODULE_SELECT == CCP_PWM_MODULE_ENABLE ||CCP2_MODULE_SELECT == CCP_PWM_MODULE_ENABLE
STD_ReturnType CCP_PWM_Set_Duty_Sycle(const ccp_t * ccp_obj,const uint8 duty)
{
   STD_ReturnType Ret = E_OK;
   uint16 l_duty_temp=0;
   if(NULL == ccp_obj)
    {
       Ret = E_NOK; 
    }
    else
    {
        l_duty_temp = (uint16)( (PR2+1) * (duty/100.0) * 4);
        if(ccp_obj ->ccp_init == CCP1_INIT)
        {
            CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003);
            CCPR1L = (uint8)(l_duty_temp >> 2);
        }
        else if(ccp_obj ->ccp_init == CCP2_INIT)
        {
            CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0x0003);
            CCPR2L = (uint8)(l_duty_temp >> 2);
        }
    }

   return(Ret);
}
STD_ReturnType CCP_PWM_Start(const ccp_t * ccp_obj)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == ccp_obj)
    {
       Ret = E_NOK; 
    }
    else
    {
        if(ccp_obj ->ccp_init == CCP1_INIT)
        {
            CCP1CONbits.CCP1M  =  CCP_PWM_MODE_ENABLE;
        }
        else if(ccp_obj ->ccp_init == CCP2_INIT)
        {
            CCP2CONbits.CCP2M  =  CCP_PWM_MODE_ENABLE;
        }
    }
   
    return(Ret);
}
STD_ReturnType CCP_PWM_End(const ccp_t * ccp_obj)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == ccp_obj)
    {
       Ret = E_NOK; 
    }
    else
    {
        if(ccp_obj ->ccp_init == CCP1_INIT)
        {
            CCP1CONbits.CCP1M  =  CCP_MODULE_DISABLE;
        }
        else if(ccp_obj ->ccp_init == CCP2_INIT)
        {
            CCP2CONbits.CCP2M  = CCP_MODULE_DISABLE;
        }
    }
}
#endif
void CCP1_ISR(void)
{
    CCP1_INTERRUPT_CLEAR_FLAG();
    
    if(CCP1_INTERRUPT_SET_HANDELER)
    {
        CCP1_INTERRUPT_SET_HANDELER();
    }
}
void CCP2_ISR(void)
{
    CCP2_INTERRUPT_CLEAR_FLAG();
    
    if(CCP2_INTERRUPT_SET_HANDELER)
    {
        CCP2_INTERRUPT_SET_HANDELER();
    }
}
static STD_ReturnType CCP_Interrupt_Config(const ccp_t * ccp_obj)
{
    STD_ReturnType Ret = E_OK;
    if(ccp_obj ->ccp_init == CCP1_INIT)
    {
        #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        CCP1_INTERRUPT_ENABLE();
        CCP1_INTERRUPT_CLEAR_FLAG();
        CCP1_INTERRUPT_SET_HANDELER = ccp_obj ->CCP1_INTERRUPT_HANDELER;
        #if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PERIORITY_LEVELS_ENABLE();
            if(ccp_obj->CCP1_INTERRUPT_PRIORITY ==  INTERRUPT_HIGH_PRIORITY)
            {
                INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE();
                CCP1_INTERRUPT_HIGH_PRIORITY_ENABLE();
            }
            else if (ccp_obj->CCP1_INTERRUPT_PRIORITY == INTERRUPT_LOW_PRIORITY)
            {
                INTERRUPT_GLOPAL_INTERRUPT_LOW_ENABLE();
                CCP1_INTERRUPT_LOW_PRIORITY_ENABLE();
            }
        #else
            INTERRUPT_GLOPAL_INTERRUPT_ENABLE();
            INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        #endif
                 
#endif
    }
    else if (ccp_obj ->ccp_init == CCP2_INIT)
    {
        #if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        CCP2_INTERRUPT_ENABLE();
        CCP2_INTERRUPT_CLEAR_FLAG();
        CCP2_INTERRUPT_SET_HANDELER = ccp_obj ->CCP2_INTERRUPT_HANDELER;
        #if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PERIORITY_LEVELS_ENABLE();
            if(ccp_obj->CCP2_INTERRUPT_PRIORITY ==  INTERRUPT_HIGH_PRIORITY)
            {
                INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE();
                CCP2_INTERRUPT_HIGH_PRIORITY_ENABLE();
            }
            else if (ccp_obj->CCP2_INTERRUPT_PRIORITY == INTERRUPT_LOW_PRIORITY)
            {
                INTERRUPT_GLOPAL_INTERRUPT_LOW_ENABLE();
                CCP2_INTERRUPT_LOW_PRIORITY_ENABLE();
            }
        #else
                INTERRUPT_GLOPAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        #endif

        #endif   
    }                
}
#if CCP_PWM_MODULE_ENABLE == CCP1_MODULE_SELECT || CCP_PWM_MODULE_ENABLE == CCP2_MODULE_SELECT
static STD_ReturnType CCP_PWM_Mode_Config(const ccp_t * ccp_obj)
{
    STD_ReturnType Ret = E_OK;
    if(ccp_obj ->ccp_init == CCP1_INIT)
    {
        if(ccp_obj->CCP_Mode_Variant == CCP_PWM_MODE_ENABLE)
        {
            CCP1_CONFIG_SELECTE_MODE(CCP_PWM_MODE_ENABLE);
        } 
        else{}
    }
    else if(ccp_obj ->ccp_init == CCP2_INIT)
    {
        if(ccp_obj->CCP_Mode_Variant == CCP_PWM_MODE_ENABLE)
        {
            CCP2_CONFIG_SELECTE_MODE(CCP_PWM_MODE_ENABLE);
        }   
    }
    PR2 = (uint8)(( (_XTAL_FREQ) / 
          ( (ccp_obj ->PWM_Frequancy )*4.0*(ccp_obj ->Timer2_Prescaler_Value)
          *(ccp_obj ->Timer2_postcaler_Value) ) )-1);
}
#endif
#if CCP1_MODULE_SELECT == CCP_CAPTURE_MODULE_ENABLE ||CCP2_MODULE_SELECT == CCP_CAPTURE_MODULE_ENABLE
static STD_ReturnType CCP_Capture_Timer_config(const ccp_t * ccp_obj)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == ccp_obj)
    {
       Ret = E_NOK; 
    }
    else
    {
        switch(ccp_obj ->CCP_Capture_Timer)
        {
            case CCP1_CCP2_TIMER1 :
                T3CONbits.T3CCP1 = 0;
                T3CONbits.T3CCP2 = 0;
                break;
            case CCP2_TIMER3_CCP1_TIMER1 :
                T3CONbits.T3CCP1 = 1;
                T3CONbits.T3CCP2 = 0;
                break;
            case CCP1_CCP2_TIMER3 :
                T3CONbits.T3CCP1 = 0;
                T3CONbits.T3CCP2 = 1;
                break;
            default :
                Ret = E_NOK;
                break;
        }
    }
    return(Ret);
}
static STD_ReturnType CCP_Capture_Mode_Config(const ccp_t * ccp_obj)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == ccp_obj)
    {
       Ret = E_NOK; 
    }
    else
    {
        if(ccp_obj ->ccp_init == CCP1_INIT)
        {
            switch(ccp_obj->CCP_Mode_Variant )
                {
                    case CCP_CAPTURE_MODEL_1_FALLING_EDG :
                        CCP1_CONFIG_SELECTE_MODE(CCP_CAPTURE_MODEL_1_FALLING_EDG);
                        break;
                    case CCP_CAPTURE_MODEL_1_RISING_EDG :
                        CCP1_CONFIG_SELECTE_MODE(CCP_CAPTURE_MODEL_1_RISING_EDG);
                        break;
                    case CCP_CAPTURE_MODEL_4_RISING_EDG :
                        CCP1_CONFIG_SELECTE_MODE(CCP_CAPTURE_MODEL_4_RISING_EDG);
                        break;
                    case CCP_CAPTURE_MODEL_16_RISING_EDG :
                        CCP1_CONFIG_SELECTE_MODE(CCP_CAPTURE_MODEL_16_RISING_EDG);
                        break;
                    default :
                        Ret = E_NOK;
                        break;
                }
        }
        else if(ccp_obj ->ccp_init == CCP2_INIT)
        {
            switch(ccp_obj->CCP_Mode_Variant )
                {
                    case CCP_CAPTURE_MODEL_1_FALLING_EDG :
                        CCP2_CONFIG_SELECTE_MODE(CCP_CAPTURE_MODEL_1_FALLING_EDG);
                        break;
                    case CCP_CAPTURE_MODEL_1_RISING_EDG :
                        CCP2_CONFIG_SELECTE_MODE(CCP_CAPTURE_MODEL_1_RISING_EDG);
                        break;
                    case CCP_CAPTURE_MODEL_4_RISING_EDG :
                        CCP2_CONFIG_SELECTE_MODE(CCP_CAPTURE_MODEL_4_RISING_EDG);
                        break;
                    case CCP_CAPTURE_MODEL_16_RISING_EDG :
                        CCP2_CONFIG_SELECTE_MODE(CCP_CAPTURE_MODEL_16_RISING_EDG);
                        break;
                    default :
                        Ret = E_NOK;
                        break;
                }
        }
    }
    CCP_Capture_Timer_config(ccp_obj);
    return(Ret);
}
#endif
#if CCP1_MODULE_SELECT == CCP_COMPARE_MODULE_ENABLE ||CCP2_MODULE_SELECT == CCP_COMPARE_MODULE_ENABLE
static STD_ReturnType CCP_Compare_Timer_config(const ccp_t * ccp_obj)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == ccp_obj)
    {
       Ret = E_NOK; 
    }
    else
    {
        switch(ccp_obj ->CCP_Compare_Timer)
        {
            case CCP1_CCP2_TIMER1 :
                T3CONbits.T3CCP1 = 0;
                T3CONbits.T3CCP2 = 0;
                break;
            case CCP2_TIMER3_CCP1_TIMER1 :
                T3CONbits.T3CCP1 = 1;
                T3CONbits.T3CCP2 = 0;
                break;
            case CCP1_CCP2_TIMER3 :
                T3CONbits.T3CCP1 = 0;
                T3CONbits.T3CCP2 = 1;
                break;
            default :
                Ret = E_NOK;
                break;
        }
    }
    return(Ret);
}

static STD_ReturnType CCP_Compare_Mode_Config(const ccp_t * ccp_obj)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == ccp_obj)
    {
       Ret = E_NOK; 
    }
    else
    {
        if(ccp_obj ->ccp_init == CCP1_INIT)
        {
             switch(ccp_obj->CCP_Mode_Variant )
                {
                    case CCP_COMPARE_MODEULE_SET_PIN_LOW :
                        CCP1_CONFIG_SELECTE_MODE(CCP_COMPARE_MODEULE_SET_PIN_LOW);
                        break;
                    case CCP_COMPARE_MODEULE_SET_PIN_HIGH  :
                        CCP1_CONFIG_SELECTE_MODE(CCP_COMPARE_MODEULE_SET_PIN_HIGH);
                        break;
                    case CCP_COMPARE_MODEULE_TOGGLE_ON_MATCH :
                        CCP1_CONFIG_SELECTE_MODE(CCP_COMPARE_MODEULE_TOGGLE_ON_MATCH);
                        break;
                    case CCP_COMPARE_MODEULE_GNT_SFT_INTERRUPTR :
                        CCP1_CONFIG_SELECTE_MODE(CCP_COMPARE_MODEULE_GNT_SFT_INTERRUPTR);
                        break;
                    case CCP_COMPARE_MODEULE_GNT_SPECIAL_EVENT :
                        CCP1_CONFIG_SELECTE_MODE(CCP_COMPARE_MODEULE_GNT_SPECIAL_EVENT);
                        break;
                    default :
                        Ret = E_NOK;
                        break;
                }
        }
        else if(ccp_obj ->ccp_init == CCP2_INIT)
        {
             switch(ccp_obj->CCP_Mode_Variant )
                {
                    case CCP_COMPARE_MODEULE_SET_PIN_LOW :
                        CCP2_CONFIG_SELECTE_MODE(CCP_COMPARE_MODEULE_SET_PIN_LOW);
                        break;
                    case CCP_COMPARE_MODEULE_SET_PIN_HIGH  :
                        CCP2_CONFIG_SELECTE_MODE(CCP_COMPARE_MODEULE_SET_PIN_HIGH);
                        break;
                    case CCP_COMPARE_MODEULE_TOGGLE_ON_MATCH :
                        CCP2_CONFIG_SELECTE_MODE(CCP_COMPARE_MODEULE_TOGGLE_ON_MATCH);
                        break;
                    case CCP_COMPARE_MODEULE_GNT_SFT_INTERRUPTR :
                        CCP2_CONFIG_SELECTE_MODE(CCP_COMPARE_MODEULE_GNT_SFT_INTERRUPTR);
                        break;
                    case CCP_COMPARE_MODEULE_GNT_SPECIAL_EVENT :
                        CCP2_CONFIG_SELECTE_MODE(CCP_COMPARE_MODEULE_GNT_SPECIAL_EVENT);
                        break;
                    default :
                        Ret = E_NOK;
                        break;
                }
        }
    }
    CCP_Compare_Timer_config(ccp_obj);
    return(Ret);
}
#endif

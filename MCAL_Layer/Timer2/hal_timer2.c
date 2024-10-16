/* 
 * File:   hal_timer2.c
 * Author: DELL
 *
 * Created on September 11, 2024, 2:09 PM
 */
#include "hal_timer2.h"

#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void(*TIMER2_INTERRUPT_SET_HANDELER)(void);
#endif
        
uint8 Timer2_preloaded_value;

static inline void Timer2_Prescaler_Select(const timer2_config_t * timer);
static inline void Timer2_Postcaler_Select(const timer2_config_t * timer);
void Timer2_ISR(void);

/**
 * @brief: function to intialize the timer2 module
 * @param timer:pointer to the stracture of timer0
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType Timer2_Init(const timer2_config_t * timer)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == timer)
    {
        Ret = E_NOK;
    }
    else
    {
        _TIMER2_MODULE_DISABLE_();
        Timer2_Prescaler_Select(timer);
        Timer2_Postcaler_Select(timer);
        Timer2_preloaded_value = (timer ->Timer2_Preloaded_Value);
        TMR2 = (timer ->Timer2_Preloaded_Value);
        #if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER2_INTERRUPT_ENABLE();
            TIMER2_INTERRUPT_CLEAR_FLAG();
            TIMER2_INTERRUPT_SET_HANDELER = timer->TIMER2_INTERRUPT_HANDELER;
        #if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PERIORITY_LEVELS_ENABLE();
            if(timer->Timer2_priority == INTERRUPT_HIGH_PRIORITY)
            {
                INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE();
                TIMER2_INTERRUPT_HIGH_PRIORITY_ENABLE() ;
            }
            else if (timer ->Timer2_priority == INTERRUPT_LOW_PRIORITY)
            {
                INTERRUPT_GLOPAL_INTERRUPT_LOW_ENABLE();
                TIMER2_INTERRUPT_LOW_PRIORITY_ENABLE();
            }
        #else 
            INTERRUPT_GLOPAL_INTERRUPT_ENABLE();
            INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        #endif

        #endif
        _TIMER2_MODULE_ENABLE_();
    }
    return(Ret);
}
/**
* @brief: function to de intialize the timer2 module
 * @param timer:pointer to the stracture of timer2
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType Timer2_De_Init(const timer2_config_t * timer)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == timer)
    {
        Ret = E_NOK;
    }
    else
    {
        _TIMER2_MODULE_DISABLE_();
        #if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER2_INTERRUPT_DISABLE();
        #endif
    }
    return(Ret);
}
/**
* @brief: function to write a valuein the timer2 register module
 * @param timer:pointer to the stracture of timer2
 * @param value:the value you want to write in the register
  * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType Timer2_Write_Value(const timer2_config_t * timer,uint8 value)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == timer)
    {
        Ret = E_NOK;
    }
    else
    {
        TMR2 = value;
    }
    return(Ret);
}
/**
* @brief: function to read the date store in the timer0 register module
 * @param timer:pointer to the stracture of timer0
 * @param value:pointer to store the red value
  * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType Timer2_Read_Value(const timer2_config_t * timer,uint8 *value)
{
    STD_ReturnType Ret = E_OK;
    if((NULL == timer)&&(NULL == value))
    {
        Ret = E_NOK;
    }
    else
    {
        *value = TMR2;
    }
    return(Ret);
}
static inline void Timer2_Prescaler_Select(const timer2_config_t * timer)
{
    switch(timer->Timer2_Prescaler_Value)
    {
        case TIMER2_PRESCALER_DIV_1 :
            TIMER2_PRESCALER_SELECT_BIT(TIMER2_PRESCALER_DIV_1);
            break;
        case TIMER2_PRESCALER_DIV_4 :
            TIMER2_PRESCALER_SELECT_BIT(TIMER2_PRESCALER_DIV_4);
            break;
        case TIMER2_PRESCALER_DIV_16 :
            TIMER2_PRESCALER_SELECT_BIT(TIMER2_PRESCALER_DIV_16);
            break;        
    }
}
static inline void Timer2_Postcaler_Select(const timer2_config_t * timer)
{
    switch(timer->Timer2_postcaler_Value)
    {
        case TIMER2_POSTCALER_DIV_1 :
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_1);
            break;
        case TIMER2_POSTCALER_DIV_2 :
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_2);
            break;
        case TIMER2_POSTCALER_DIV_3 :
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_3);
            break;
        case TIMER2_POSTCALER_DIV_4 :
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_4);
            break;
        case TIMER2_POSTCALER_DIV_5 :
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_5);
            break;
        case TIMER2_POSTCALER_DIV_6:
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_6);
            break;
        case TIMER2_POSTCALER_DIV_7 :
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_7);
            break;
        case TIMER2_POSTCALER_DIV_8 :
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_8);
            break;
        case TIMER2_POSTCALER_DIV_9 :
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_9);
            break;
        case TIMER2_POSTCALER_DIV_10 :
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_10);
            break;
        case TIMER2_POSTCALER_DIV_11 :
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_11);
            break;
        case TIMER2_POSTCALER_DIV_12 :
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_12);
            break;
        case TIMER2_POSTCALER_DIV_13 :
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_13);
            break;
        case TIMER2_POSTCALER_DIV_14 :
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_14);
            break;
        case TIMER2_POSTCALER_DIV_15 :
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_15);
            break;
        case TIMER2_POSTCALER_DIV_16 :
            TIMER2_POSTCALER_SELECT_BIT(TIMER2_POSTCALER_DIV_16);
            break;
    }
}
void Timer2_ISR(void)
{
     TIMER2_INTERRUPT_CLEAR_FLAG();
     TMR2 = Timer2_preloaded_value;
     if(TIMER2_INTERRUPT_SET_HANDELER)
     {
         TIMER2_INTERRUPT_SET_HANDELER();
     }
}
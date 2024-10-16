/* 
 * File:   hal_timer3.c
 * Author: DELL
 *
 * Created on September 11, 2024, 2:09 PM
 */
#include "hal_timer3.h"

#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*TIMER3_INTERRUPT_SET_HANDELER)(void) = NULL;
#endif
    
uint16 timer3_preloaded_Value;

static inline void Timer3_select_mode(const timer3_config_t * timer);
static inline void Timer3_select_Register_Size(const timer3_config_t * timer);
static inline void Timer3_select_counter_mode(const timer3_config_t * timer);
static inline void Timer3_Prescaler_select(const timer3_config_t * timer);
void TIMER3_ISR(void);
 
/**
 * @brief: function to intialize the timer1 module
 * @param timer:pointer to the stracture of timer1
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType Timer3_Init(const timer3_config_t * timer)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == timer)
    {
        Ret = E_NOK;
    }
    else
    {
        TIMER3_MODULE_DISABLE();
        Timer3_select_mode(timer);
        Timer3_select_Register_Size(timer);
        Timer3_Prescaler_select(timer);
        timer3_preloaded_Value = (uint16)(timer ->Timer3_Preloaded_Value);
        TMR3H = (uint8)((timer ->Timer3_Preloaded_Value) >>8);
        TMR3L = (uint8)(timer ->Timer3_Preloaded_Value);
        
        #if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_ENABLE();
        TIMER3_INTERRUPT_CLEAR_FLAG();
        TIMER3_INTERRUPT_SET_HANDELER = timer ->TIMER3_INTERRUPT_HANDELER;
        #if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PERIORITY_LEVELS_ENABLE();
            if(timer ->TIMER3_INTERRUPT_PRIORITY ==  INTERRUPT_HIGH_PRIORITY)
            {
                INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE();
                TIMER3_INTERRUPT_HIGH_PRIORITY_ENABLE();
            }
            else if (timer ->TIMER3_INTERRUPT_PRIORITY == INTERRUPT_LOW_PRIORITY)
            {
                INTERRUPT_GLOPAL_INTERRUPT_LOW_ENABLE();
                TIMER3_INTERRUPT_LOW_PRIORITY_ENABLE();
            }
        #else
            INTERRUPT_GLOPAL_INTERRUPT_ENABLE();
            INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        #endif

        #endif
        TIMER3_MODULE_ENABLE();
    }
    return(Ret);
}
/**
* @brief: function to de intialize the timer1 module
 * @param timer:pointer to the stracture of timer1
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType Timer3_De_Init(const timer3_config_t * timer)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == timer)
    {
        Ret = E_NOK;
    }
    else
    {
        TIMER3_MODULE_DISABLE();
        #if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER3_INTERRUPT_DISABLE();
        #endif
    }
    return(Ret);
}
/**
* @brief: function to write a valuein the timer1 register module
 * @param timer:pointer to the stracture of timer1
 * @param value:the value you want to write in the register
  * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType Timer3_Write_Value(const timer3_config_t * timer,uint16 value)
{
     STD_ReturnType Ret = E_OK;
    if(NULL == timer)
    {
        Ret = E_NOK;
    }
    else
    {
        TMR3H = (uint8)((value)>> 8);
        TMR3L = (uint8)(value);
    }
    return(Ret);
}
/**
* @brief: function to read the date store in the timer1 register module
 * @param timer:pointer to the stracture of timer1
 * @param value:pointer to store the red value
  * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType Timer3_Read_Value(const timer3_config_t * timer,uint16 *value)
{
    STD_ReturnType Ret = E_OK;
   uint8 l_tmr3_h,l_tmr3_l;
    if((NULL == timer) || (NULL == value))
    {
        Ret = E_NOK;
    }
    else
    {
        l_tmr3_l = TMR3L;
        l_tmr3_h = TMR3H;
        *value = (uint16)(l_tmr3_l + (l_tmr3_h >> 8));
    }
    return(Ret); 
}
static inline void Timer3_select_mode(const timer3_config_t * timer)
{
    switch(timer->Timer3_Mode)
    {
        case TIMER3_TIMER_MODE :
            TIMER3_TIMER_MODE_ENABLE();
            break;
        case TIMER3_COUNTER_MODE :
            TIMER3_COUNTER_MODE_ENABLE();
            Timer3_select_counter_mode(timer);
            break;
    }
}
static inline void Timer3_select_Register_Size(const timer3_config_t * timer)
{
    switch(timer ->Timer3_Register_Read_Write_Mode)
    {
        case TIMER3_16BIT_MODE :
            TIMER3_16BIT_REGISTER_MODE_ENABLE();
            break;
        case TIMER3_8BIT_MODE :
            TIMER3_8BIT_REGISTER_MODE_MODE();
            break;
    }
}
static inline void Timer3_select_counter_mode(const timer3_config_t * timer)
{
     switch(timer->Timer3_Counter_Mode)
    {
        case TIMER3_ASYNC_COUNTER_MODE :
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
            break;
        case TIMER3_SYNC_COUNTER_MODE :
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
            break;
    }
}
static inline void Timer3_Prescaler_select(const timer3_config_t * timer)
{
    switch(timer ->Timer3_prescaler_Value)
    {
        case TIMER3_PRESCALER_DISABLE :
            TIMER3_PRESCALER_VALUE_SELECT(TIMER3_PRESCALER_DISABLE);
            break;
        case TIMER3_PRESCALER_DIV_2 :
            TIMER3_PRESCALER_VALUE_SELECT(TIMER3_PRESCALER_DIV_2);
            break;
        case TIMER3_PRESCALER_DIV_4 :
            TIMER3_PRESCALER_VALUE_SELECT(TIMER3_PRESCALER_DIV_4);
            break;
        case TIMER3_PRESCALER_DIV_8 :
            TIMER3_PRESCALER_VALUE_SELECT(TIMER3_PRESCALER_DIV_8);
            break;
    }
}
void TIMER3_ISR(void)
{
    TIMER3_INTERRUPT_CLEAR_FLAG();
    TMR3H = (uint8)(timer3_preloaded_Value >> 8);
    TMR3L = (uint8) (timer3_preloaded_Value);
    
    if(TIMER3_INTERRUPT_SET_HANDELER)
    {
        TIMER3_INTERRUPT_SET_HANDELER();
    }
}
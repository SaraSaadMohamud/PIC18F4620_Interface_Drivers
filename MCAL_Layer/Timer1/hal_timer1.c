/* 
 * File:   hal_timer1.c
 * Author: DELL
 *
 * Created on September 11, 2024, 7:08 AM
 */
#include "hal_timer1.h"
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*TIMER1_INTERRUPT_SET_HANDELER)(void) = NULL;
#endif
uint16 timer1_preloaded_Value;
static inline void Timer1_select_mode(const timer1_config_t * timer);
static inline void Timer1_select_Register_Size(const timer1_config_t * timer);
static inline void Timer1_select_counter_mode(const timer1_config_t * timer);
static inline void Timer1_oscillator_mode(const timer1_config_t * timer);
static inline void Timer1_Prescaler_select(const timer1_config_t * timer);
 void TIMER1_ISR(void);
/**
 * @brief: function to intialize the timer1 module
 * @param timer:pointer to the stracture of timer1
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType Timer1_Init(const timer1_config_t * timer)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == timer)
    {
        Ret = E_NOK;
    }
    else
    {
        TIMER1_MODULE_DISABLE();
        Timer1_select_mode(timer);
        Timer1_select_Register_Size(timer);
        Timer1_Prescaler_select(timer);
        Timer1_oscillator_mode(timer);
        timer1_preloaded_Value = (uint16)(timer ->Timer1_Preloaded_Value);
        TMR1H = (uint8)((timer ->Timer1_Preloaded_Value) >>8);
        TMR1L = (uint8)(timer ->Timer1_Preloaded_Value);
        
        #if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_INTERRUPT_CLEAR_FLAG();
        TIMER1_INTERRUPT_SET_HANDELER = timer ->TIMER1_INTERRUPT_HANDELER;
        #if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PERIORITY_LEVELS_ENABLE();
            if(timer ->TIMER1_INTERRUPT_PRIORITY ==  INTERRUPT_HIGH_PRIORITY)
            {
                INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE();
                TIMER1_INTERRUPT_HIGH_PRIORITY_ENABLE();
            }
            else if (timer ->TIMER1_INTERRUPT_PRIORITY == INTERRUPT_LOW_PRIORITY)
            {
                INTERRUPT_GLOPAL_INTERRUPT_LOW_ENABLE();
                TIMER1_INTERRUPT_LOW_PRIORITY_ENABLE();
            }
        #else
            INTERRUPT_GLOPAL_INTERRUPT_ENABLE();
            INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        #endif

        #endif
        TIMER1_MODULE_ENABLE();
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
STD_ReturnType Timer1_De_Init(const timer1_config_t * timer)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == timer)
    {
        Ret = E_NOK;
    }
    else
    {
        TIMER1_MODULE_DISABLE();
        #if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER1_INTERRUPT_DISABLE();
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
STD_ReturnType Timer1_Write_Value(const timer1_config_t * timer,uint16 value)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == timer)
    {
        Ret = E_NOK;
    }
    else
    {
        TMR1H = (uint8)((value)>> 8);
        TMR1L = (uint8)(value);
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
STD_ReturnType Timer1_Read_Value(const timer1_config_t * timer,uint16 *value)
{
   STD_ReturnType Ret = E_OK;
   uint8 l_tmr1_h,l_tmr1_l;
    if((NULL == timer) || (NULL == value))
    {
        Ret = E_NOK;
    }
    else
    {
        l_tmr1_l = TMR1L;
        l_tmr1_h = TMR1H;
        *value = (uint16)(l_tmr1_l + (l_tmr1_h >> 8));
    }
    return(Ret); 
}
static inline void Timer1_select_mode(const timer1_config_t * timer)
{
    switch(timer->Timer1_Mode)
    {
        case TIMER1_TIMER_MODE :
            TIMER1_TIMER_MODE_ENABLE();
            break;
        case TIMER1_COUNTER_MODE :
            TIMER1_COUNTER_MODE_ENABLE();
            Timer1_select_counter_mode(timer);
            break;
    }
}
static inline void Timer1_select_Register_Size(const timer1_config_t * timer)
{
    switch(timer ->Timer1_Register_Read_Write_Mode)
    {
        case TIMER1_16BIT_MODE :
            TIMER1_16BIT_REGISTER_MODE_ENABLE();
            break;
        case TIMER1_8BIT_MODE :
            TIMER1_8BIT_REGISTER_MODE_MODE();
            break;
    }
}
static inline void Timer1_select_counter_mode(const timer1_config_t * timer)
{
    switch(timer->Timer1_Counter_Mode)
    {
        case TIMER1_ASYNC_COUNTER_MODE :
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
            break;
        case TIMER1_SYNC_COUNTER_MODE :
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
            break;
    }
}
static inline void Timer1_oscillator_mode(const timer1_config_t * timer)
{
    switch(timer ->Timer1_Oscillator_confige)
    {
        case TIMER1_TIMER_OSCILLATOR_ENABLE :
            TIMER1_EXTERNAL_TIMER_OSILLATOR_ENABLE();
            break;
        case TIMER1_TIMER_OSCILLATOR_DISABLE :
            TIMER1_EXTERNAL_TIMER_OSILLATOR_DISABLE();
            break;
    }
}
static inline void Timer1_Prescaler_select(const timer1_config_t * timer)
{
    switch(timer ->Timer1_prescaler_Value)
    {
        case TIMER1_PRESCALER_DISABLE :
            TIMER1_PRESCALER_VALUE_SELECT(TIMER1_PRESCALER_DISABLE);
            break;
        case TIMER1_PRESCALER_DIV_2 :
            TIMER1_PRESCALER_VALUE_SELECT(TIMER1_PRESCALER_DIV_2);
            break;
        case TIMER1_PRESCALER_DIV_4 :
            TIMER1_PRESCALER_VALUE_SELECT(TIMER1_PRESCALER_DIV_4);
            break;
        case TIMER1_PRESCALER_DIV_8 :
            TIMER1_PRESCALER_VALUE_SELECT(TIMER1_PRESCALER_DIV_8);
            break;
    }
}
void TIMER1_ISR(void)
{
    TIMER1_INTERRUPT_CLEAR_FLAG();
    TMR1H = (uint8)(timer1_preloaded_Value >> 8);
    TMR1L = (uint8) (timer1_preloaded_Value);
    
    if(TIMER1_INTERRUPT_SET_HANDELER)
    {
        TIMER1_INTERRUPT_SET_HANDELER();
    }
}
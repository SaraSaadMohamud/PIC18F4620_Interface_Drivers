/* 
 * File:   hal_timer0.?
 * Author: DELL
 *
 * Created on September 9, 2024, 9:33 AM
 */

#include "hal_timer0.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void (*TIMER0_INTERRUPT_SET_HANDELER)(void) = NULL;
#endif

static uint16 timer0_preload_value=0;

static inline void Timer0_Register_Size(const timer0_config_t * timer);
static inline void Timer0_Mode(const timer0_config_t * timer);
static inline void Timer0_Edge_Mode(const timer0_config_t * timer);
static inline void Timer0_Prescaler_State(const timer0_config_t * timer);

/**
 * @brief: function to intialize the timer0 module
 * @param timer:pointer to the stracture of timer0
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType Timer0_Init(const timer0_config_t * timer)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == timer)
    {
        Ret = E_NOK;
    }
    else
    {
        TIMER0_MODULE_DISABLE();
        Timer0_Register_Size(timer);
        Timer0_Mode(timer);
        Timer0_Prescaler_State(timer);
        timer0_preload_value = timer->timer0_register_preload_value;
        TMR0H = (uint8)((timer ->timer0_register_preload_value)>>8);
        TMR0L = (uint8)(timer ->timer0_register_preload_value);
        
        #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER0_INTERRUPT_ENABLE();
            TIMER0_INTERRUPT_CLEAR_FLAG() ;
            #if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PERIORITY_LEVELS_ENABLE();
                if(timer ->interrupt_priority == INTERRUPT_LOW_PRIORITY)
                {
                    INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE();
                    TIMER0_INTERRUPT_LOW_PRIORITY_ENABLE();
                }
                else if(timer ->interrupt_priority == INTERRUPT_HIGH_PRIORITY)
                {
                    INTERRUPT_GLOPAL_INTERRUPT_LOW_ENABLE();
                    TIMER0_INTERRUPT_HIGH_PRIORITY_ENABLE();
                }
            #else
                INTERRUPT_GLOPAL_INTERRUPT_ENABLE();
                INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
            #endif
            TIMER0_INTERRUPT_SET_HANDELER = timer->timer0_interrupt_handeler;
        #endif
            TIMER0_MODULE_ENABLE();
    }
    return(Ret);
}
/**
* @brief: function to de intialize the timer0 module
 * @param timer:pointer to the stracture of timer0
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType Timer0_De_Init(const timer0_config_t * timer)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == timer)
    {
        Ret = E_NOK;
    }
    else
    {
        TIMER0_MODULE_DISABLE();
        #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            TIMER0_INTERRUPT_DISABLE() ;
        #endif
    }
    return(Ret);
}
/**
* @brief: function to write a valuein the timer0 register module
 * @param timer:pointer to the stracture of timer0
 * @param value:the value you want to write in the register
  * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
STD_ReturnType Timer0_Write_Value(const timer0_config_t * timer,uint16 value)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == timer)
    {
        Ret = E_NOK;
    }
    else
    {
        TMR0H = (uint8)(value>>8);
        TMR0L = (uint8)(value);
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
STD_ReturnType Timer0_Read_Value(const timer0_config_t * timer,uint16 *value)
{
    STD_ReturnType Ret = E_OK;
    uint8 l_tmr0_l,l_tmr0_h;
    
    if((NULL == timer) ||(NULL == value))
    {
        Ret = E_NOK;
    }
    else
    {
        l_tmr0_l = TMR0L;
        l_tmr0_h = TMR0H;
        *value = (uint16)(l_tmr0_l  + ( l_tmr0_h >> 8));
        
    }
    return(Ret);
}

void TIMER0_ISR(void)
{
    TIMER0_INTERRUPT_CLEAR_FLAG();
   TMR0H = (uint8)(timer0_preload_value >> 8);
   TMR0L = (uint8)(timer0_preload_value);
    if(*TIMER0_INTERRUPT_SET_HANDELER)
    {
        TIMER0_INTERRUPT_SET_HANDELER();
    }
}
static inline void Timer0_Register_Size(const timer0_config_t * timer)
{
    switch(timer->timer0_register_size)
        {
            case TIMER0_16BIT_REGISTER_SIZE_CFG:
                TIMER0_16BIT_REGISTER_SIZE();
                break;
            case TIMER0_8BIT_REGISTER_SIZE_CFG:
                TIMER0_8BIT_REGISTER_SIZE();
                break;
            default :
                break;
        }
}
static inline void Timer0_Mode(const timer0_config_t * timer)
{
    switch(timer->timer0_mode)
    {
        case TIMER0_TIMER_MODE:
            TIMER0_TIMER0_MODE_ENABLE();
            break;
        case TIMER0_COUNTER_MODE:
            TIMER0_COUNTER_MODE_ENABLE();
            Timer0_Edge_Mode(timer);
            break;
        default :
            break;
    }
}
static inline void Timer0_Edge_Mode(const timer0_config_t * timer)
{
    switch(timer->timer0_counter_edge)
    {
        case TIMER0_FALLING_EDGE_CFG:
            TIMER0_FALLING_EDGE_ENABLE() ;
            break;
        case TIMER0_RISING_EDGE_CFG:
            TIMER0_RISING_EDGE_ENABLE();
        default :
            break;       
    }
}
static inline void Timer0_Prescaler_State(const timer0_config_t * timer)
{
    switch(timer->timer0_prescaler_enable)
    {
        case TIMER0_PRESCALER_ENABLE_CFG :
            TIMER0_PRESCALER_ENABLE();
            T0CONbits.T0PS = timer->timer0_prescaler_value;
            break;
        case  TIMER0_PRESCALER_DISABLE_CFG:
            TIMER0_PRESCALER_DISABLE();
            break;
        default :
            break;
    }
}

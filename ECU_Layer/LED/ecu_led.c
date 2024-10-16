/* 
 * File:  ecu_led.c
 * Author: DELL
 *
 * Created on July 17, 2024, 7:23 PM
 */
///////////////////////////////////////////
#include "ecu_led.h"

/**
 * @brief  : function to itialize  the led
 * @param  : led pointer point to the led module config
 * @return : statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
STD_ReturnType led_intialize (const led_t *led)
{
    STD_ReturnType Ret=E_OK;
   
    if(NULL == led)
    {
        Ret=E_NOK;
    }
    else
    {
        pin_config_t pin_obj ={.port = led ->port_name,
                           .pin = led ->pin ,
                           .direction = GPIO_DIRECTION_OUTPUT ,
                           .logic = led ->led_state};
    
        
        gpio_pin_intializtion(&pin_obj);
    }
    
    return(Ret);
}
/**
 * @brief  : function to open the led
 * @param  : led pointer point to the led module config
 * @return : statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */

STD_ReturnType led_turn_on (const led_t *led)
{
    STD_ReturnType Ret=E_OK;
    
    if(NULL == led)
    {
        Ret=E_NOK;
    }
    else
    {
        pin_config_t pin_obj ={.port = led ->port_name,
                           .pin = led ->pin ,
                           .direction = GPIO_DIRECTION_OUTPUT ,
                           .logic = led ->led_state};
        
       Ret = gpio_pin_write_logic(&pin_obj , HIGHT);
    }
    
    return(Ret);
}
/**
 * @brief  : function to chose the led
 * @param  : led pointer point to the led module config 
 * @return : statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
STD_ReturnType led_turn_off (const led_t *led)
{
    STD_ReturnType Ret=E_OK;
    
    if(NULL == led)
    {
        Ret=E_NOK;
    }
    else
    {
         pin_config_t pin_obj ={.port = led ->port_name,
                                .pin = led ->pin ,
                                .direction = GPIO_DIRECTION_OUTPUT ,
                                .logic = led ->led_state};
        
        Ret = gpio_pin_write_logic(&pin_obj , LOW);
    }
    
    return(Ret);
}
/**
 * @brief  : function to convert the statues of the led
 * @param  : led pointer point to the led module config
 * @return : statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
STD_ReturnType led_toggle (const led_t *led)
{
    STD_ReturnType Ret=E_OK;
    
    if(NULL == led)
    {
        Ret=E_NOK;
    }
    else
    {
        pin_config_t pin_obj ={.port = led ->port_name,
                           .pin = led ->pin ,
                           .direction = GPIO_DIRECTION_OUTPUT ,
                           .logic = led ->led_state};
        
        gpio_pin_toggle_logic(&pin_obj);
    }
    
    return(Ret);
}
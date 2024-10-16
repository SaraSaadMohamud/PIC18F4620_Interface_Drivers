/* 
 * File:   ecu_button.c
 * Author: Sara.Saad
 *
 * Created on July 29, 2024, 1:12 AM
 */
//////////////////////////////////
#include "ecu_button.h"
/**
 * @breif Read the status of the button
 * @param btn pointer to the button configuration
 * @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
STD_ReturnType button_intialize(button_t *btn)
{
    STD_ReturnType Ret=E_OK;
    
    if(NULL == btn)
    {
        Ret= E_NOK;
    }
    else
    {
        Ret = gpio_pin_direction_intializtion(&(btn ->button_pin));
    }
    return (Ret);
}
/**
 * @breif initialize the assign pin to be an input
 * @param btn pointer to the button configuration
 * @param button_state pointer to read the statues of the pin_buuton
 * @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
STD_ReturnType button_read_state(button_t *btn, button_status_t *button_state)
{
    STD_ReturnType Ret=E_OK;
    logic_t pin_logic_status = LOW;
    
    if(NULL == btn || NULL == button_state)
    {
        Ret=E_NOK;
    }
    else
    {
        Ret = gpio_pin_read_logic (&(btn -> button_pin),&pin_logic_status );
        if(BUTTON_ACTIVE_HIGH == btn ->button_connection)
        {
            if(HIGHT == pin_logic_status)
            {
                *button_state = BUTTON_PREASED;
            }
            else
            {
                *button_state = BUTTON_REREASED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn ->button_connection)
        {
            if(HIGHT == pin_logic_status)
            {
                *button_state = BUTTON_REREASED;
            }
            else
            {
                *button_state = BUTTON_PREASED;
            }
        }
        else
        {
            /*Nothing*/
        }
    }
    return (Ret);
}
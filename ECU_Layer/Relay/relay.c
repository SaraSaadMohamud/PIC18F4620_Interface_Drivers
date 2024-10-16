#include "relay.h"
/**
 * @breif : function to intialize the realy
 * @param _realy pointer point to the realy structure 
 * @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
/////////////////////////////////////
STD_ReturnType relay_intialize(const realy_t *_realy)
{
    STD_ReturnType Ret = E_OK;
    
    if(NULL == _realy)
    {
        Ret = E_NOK;
    }
    else
    {
        pin_config_t pin_obj = {.port = _realy -> realy_port,
                                .pin = _realy -> realy_pin,
                                .direction = GPIO_DIRECTION_OUTPUT,
                                .logic = _realy ->realy_statuse};
        
        gpio_pin_intializtion(&pin_obj);
    }
    
    return(Ret);
}
/**
 * @breif : function to turn on the realy
 * @param _realy pointer point to the realy structure 
 * @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
STD_ReturnType realy_turn_on( const realy_t * _realy)
{
    STD_ReturnType Ret = E_OK;
    
    if(NULL == _realy)
    {
        Ret = E_NOK;
    }
    else
    {
        pin_config_t pin_obj = {.port = _realy -> realy_port,
                                .pin = _realy -> realy_pin,
                                .direction = GPIO_DIRECTION_OUTPUT,
                                .logic = _realy ->realy_statuse};
        
        
        gpio_pin_write_logic(&pin_obj,HIGHT);
    }
    
    return(Ret);
}
/**
 * @breif : function to turn off the realy
 * @param _realy pointer point to the realy structure 
 * @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
STD_ReturnType realy_turn_off( const realy_t *_realy)
{
    STD_ReturnType Ret = E_OK;
    
    if(NULL == _realy)
    {
        Ret = E_NOK;
    }
    else
    {
        pin_config_t pin_obj = {.port = _realy -> realy_port,
                                .pin = _realy -> realy_pin,
                                .direction = GPIO_DIRECTION_OUTPUT,
                                .logic = _realy ->realy_statuse};
        
        
        gpio_pin_write_logic(&pin_obj,LOW);
    }
    
    return(Ret);
}
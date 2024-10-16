#include "DC_Motor.h"
/**
 * @breif : function to intialize the dc_motor
 * @param _realy pointer point to the dc_motor structure 
 * @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
/////////////////////////////////////////////////
STD_ReturnType dc_motor_intialize(const dc_motor_t * _dc_motor)
{
    STD_ReturnType Ret = E_OK;
    
    if(NULL == _dc_motor)
    {
        Ret = E_NOK;
    }
    else
    {
       Ret = gpio_pin_intializtion(&(_dc_motor ->dc_motor_pin[0]));
       Ret = gpio_pin_intializtion(&(_dc_motor ->dc_motor_pin[1]));
    }
    
    return(Ret);
}

/**
 * @breif : function to move_motor_right the realy
 * @param _realy pointer point to the dc_motor structure 
 * @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
STD_ReturnType dc_motor_move_right(const dc_motor_t * _dc_motor)
{
    STD_ReturnType Ret = E_OK;
    
    if(NULL == _dc_motor)
    {
        Ret = E_NOK;
    }
    else
    {
       Ret = gpio_pin_write_logic(&(_dc_motor ->dc_motor_pin[0]) , HIGHT);
       Ret = gpio_pin_write_logic(&(_dc_motor ->dc_motor_pin[1]) , LOW);
    }
    
    return(Ret);
}

/**
 * @breif : function to move_motor_on_left the realy
 * @param _realy pointer point to the dc_motor structure 
 * @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
STD_ReturnType dc_motor_move_left(const dc_motor_t * _dc_motor)
{
    STD_ReturnType Ret = E_OK;
    
    if(NULL == _dc_motor)
    {
        Ret = E_NOK;
    }
    else
    {
       Ret = gpio_pin_write_logic(&(_dc_motor ->dc_motor_pin[0]) , LOW);
       Ret = gpio_pin_write_logic(&(_dc_motor ->dc_motor_pin[1]), HIGHT);
    }
    
    return(Ret);
}

/**
 * @breif : function to turn_off the dc_motor
 * @param _realy pointer point to the dc_motor structure 
 * @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
STD_ReturnType dc_motor_stop(const dc_motor_t * _dc_motor)
{
    STD_ReturnType Ret = E_OK;
    
    if(NULL == _dc_motor)
    {
        Ret = E_NOK;
    }
    else
    {
       Ret=gpio_pin_write_logic(&(_dc_motor ->dc_motor_pin[0]) , LOW);
       Ret=gpio_pin_write_logic(&(_dc_motor ->dc_motor_pin[1]) , LOW);
    }
    
    return(Ret);
}
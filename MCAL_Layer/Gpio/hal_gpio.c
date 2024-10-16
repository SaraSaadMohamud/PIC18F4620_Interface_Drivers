/* 
 * File:  hal_gpio.c
 * Author: DELL
 *
 * Created on July 17, 2024, 7:23 PM
 */

#include"hal_gpio.h"

volatile uint8 *TRIS_Register[5]={&TRISA ,&TRISB ,&TRISC ,&TRISD ,&TRISE};
volatile uint8 *PORT_Register[5]={&PORTA ,&PORTB ,&PORTC ,&PORTD ,&PORTE};
volatile uint8 *LAT_Register[5]={&LATA ,&LATB ,&LATC ,&LATD ,&LATE};
/**
 * @brief : initialize the direction of specific pin @ref direction_t
 * @param _pin_config pointer to the configuration @ref pin_config_t 
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
////////////////////////////////////
#if (PORT_PIN_CONFIG == GPIO_ENABLE )
STD_ReturnType gpio_pin_direction_intializtion(const pin_config_t *_pin_config)
{
    STD_ReturnType Ret = E_OK;
    
    if(NULL == _pin_config  || ((_pin_config ->pin) > (PORT_MAX_PIN_NUMBER -1)))
    {
        Ret=E_NOK;
    }
    else
    {
        switch(_pin_config ->direction)
        {
            case  GPIO_DIRECTION_OUTPUT :
                CLEAR_BIT(*(TRIS_Register[_pin_config ->port]),_pin_config->pin);
                break;
             case GPIO_DIRECTION_INPUT :
                SET_BIT(*(TRIS_Register[_pin_config->port]),_pin_config->pin);
                break;
            default :
                Ret = E_NOK;       
        }
    }
    return(Ret);
}
#endif
/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t 
 * @param direction_status
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action
 *        
 */
#if (PORT_PIN_CONFIG == GPIO_ENABLE )
STD_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config ,direction_t *direction_status)
{
     STD_ReturnType Ret = E_OK;
     
     if((NULL == _pin_config) || (NULL == direction_status) || (((_pin_config -> pin )> (PORT_MAX_PIN_NUMBER -1))))
    {
        Ret=E_NOK;
    }
    else
    {
        *direction_status = READ_BIT(*(TRIS_Register [_pin_config ->port]),_pin_config ->pin);
    }
     
     return(Ret);
}
#endif
/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t 
 * @param logic
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
#if (GPIO_PORT_PIN_CONFIG == GPIO_ENABLE )
STD_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config , logic_t logic)
{
     STD_ReturnType Ret = E_OK;
    
     if(NULL == _pin_config || ((_pin_config ->pin ) > (PORT_MAX_PIN_NUMBER -1)))
    {
        Ret=E_NOK;
    }
    else
    {
         switch(logic)
         {
             case LOW :
                CLEAR_BIT(*(LAT_Register[_pin_config ->port]) , _pin_config ->pin);
                 break;
             case  HIGHT :
                SET_BIT(*(LAT_Register[_pin_config ->port]) , _pin_config ->pin);
                 break;
             default :
                 Ret = E_NOK;
         }
    }
     
     return(Ret);
}
#endif

/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t 
 * @param logic
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
#if (GPIO_PORT_PIN_CONFIG == GPIO_ENABLE )
STD_ReturnType gpio_pin_read_logic (const pin_config_t *_pin_config , logic_t *logic)
{
     STD_ReturnType Ret = E_OK;
     
     if((NULL == _pin_config) ||( NULL == logic) ||(( _pin_config ->pin) > (PORT_MAX_PIN_NUMBER -1)))
    {
        Ret=E_NOK;
    } 
    else
    {
         *logic = READ_BIT(*(PORT_Register[_pin_config ->port]),_pin_config ->pin);
    }
     
     return(Ret);
}
#endif

/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t 
 * @return 
 */

#if (GPIO_PORT_PIN_CONFIG == GPIO_ENABLE )
STD_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config )
{
     STD_ReturnType Ret = E_OK;
     
     if(NULL == _pin_config ||(( _pin_config ->pin) >( PORT_MAX_PIN_NUMBER -1)))
    {
        Ret=E_NOK;
    }
    else
    {
        TOGGLE_BIT(*(LAT_Register [_pin_config ->port]), _pin_config ->pin);
    }
     
     return(Ret);
}
#endif
/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t 
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
#if (GPIO_PORT_CONFIG == GPIO_ENABLE )
STD_ReturnType gpio_pin_intializtion(const pin_config_t *_pin_config)
{
    STD_ReturnType Ret = E_OK;
    if((NULL == _pin_config )||(( _pin_config ->pin) > (PORT_MAX_PIN_NUMBER -1)))
    {
        Ret=E_NOK;
    }
    else
    {
        Ret=gpio_pin_direction_intializtion(_pin_config);
        Ret=gpio_pin_write_logic(_pin_config,_pin_config ->logic);
    }
    
     return(Ret);
}
#endif
/**
 * 
 * @param port
 * @param direction
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */

#if (GPIO_PORT_CONFIG == GPIO_ENABLE )
STD_ReturnType gpio_port_direction_intialize(port_index_t port,uint8 direction)
{
     STD_ReturnType Ret = E_OK;
     if(port > (PORT_MAX_NUMBER-1))
     {
         Ret=E_NOK;
     }
     else
     {
         TRIS_Register[port]=direction;
     }
     return(Ret);
}
#endif

/**
 * 
 * @param port
 * @param direction_status
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action
 */

#if (GPIO_PORT_CONFIG == GPIO_ENABLE )
STD_ReturnType gpio_port_get_direction_status(port_index_t port,uint8 *direction_status)
{
     STD_ReturnType Ret = E_OK;
     
     if((NULL == direction_status )||( port > (PORT_MAX_NUMBER -1)))
    {
        Ret=E_NOK;
    }
    else
    {
        *direction_status =TRIS_Register[port];
    }
     
     return(Ret);
}

#endif
/**
 * 
 * @param port
 * @param logic
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */

#if (GPIO_PORT_CONFIG == GPIO_ENABLE )
STD_ReturnType gpio_port_write_logic(port_index_t port ,uint8 logic)
{
     STD_ReturnType Ret = E_OK;
     
      if(port > (PORT_MAX_NUMBER-1))
     {
         Ret=E_NOK;
     }
     else
     {
        *LAT_Register[port] =logic;
     }
     
     return(Ret);
}

#endif
/**
 * 
 * @param port
 * @param logic
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */

#if (GPIO_PORT_CONFIG == GPIO_ENABLE )
STD_ReturnType gpio_port_read_logic(port_index_t port ,uint8 *logic)
{
    STD_ReturnType Ret = E_OK;
     
    if((NULL == logic )||( port > (PORT_MAX_NUMBER -1)))
    {
        Ret=E_NOK;
    }
    else
    {
        *logic = LAT_Register[port];
    }
    
     return(Ret);
}
#endif

/**
 * 
 * @param port
 * @return status of function
 *        E_OK : function done successfully
 *        E-NOK : the function has issue to perform this action 
 */
#if (GPIO_PORT_CONFIG == GPIO_ENABLE )
STD_ReturnType gpio_port_toggle_logic (port_index_t port)
{
    STD_ReturnType Ret = E_OK;
     
     if(port > (PORT_MAX_NUMBER-1))
     {
         Ret=E_NOK;
     }
     else
     {
         *LAT_Register[port] ^= PORT_MASK;
     }
    
     return(Ret);
}
#endif
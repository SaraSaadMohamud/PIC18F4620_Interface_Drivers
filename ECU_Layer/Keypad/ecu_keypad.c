#include "ecu_keypad.h"

/**
 * @breif function to intialize the keypad
 * @param keypad_obj pointer to keypad structure 
 @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
static const uint8 btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMS]={ {'7','8','9','/'},
                                                                    {'4','5','6','*'},
                                                                    {'1','2','3','-'},
                                                                    {'#','0','=','+'}
                                                                  };
STD_ReturnType keypad_intialize(const keypad_t *keypad_obj)
{
    STD_ReturnType Ret=E_OK;
    uint8 keypad_row_count = ZERO;
    uint8 keypad_colunm_count = ZERO;
    if(NULL == keypad_obj)
    {
        Ret=E_NOK;
    }
    else
    {
        for(keypad_row_count=0 ; keypad_row_count<ECU_KEYPAD_ROWS ; keypad_row_count++)
        {
            Ret=gpio_pin_intializtion(&(keypad_obj->keypad_row_pin[keypad_row_count]));
        }
        for(keypad_colunm_count=0 ; ECU_KEYPAD_COLUMS<ECU_KEYPAD_ROWS ; keypad_colunm_count++)
        {
            Ret=gpio_pin_direction_intializtion(&(keypad_obj->keypad_colum_pin[keypad_colunm_count]));
        }
        
    }
    
    return(Ret);
}
/**
 * @breif function to read the value
 * @param keypad_obj pointer to keypad structure 
 * @param value pointer to the value you want to get 
 @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
STD_ReturnType keypad_get_value(const keypad_t *keypad_obj,uint8 *value)
{
    STD_ReturnType Ret=E_OK;
    uint8 l_keypad_row_count = ZERO;
    uint8 l_keypad_colunm_count = ZERO;
    uint8 l_count = ZERO;
    uint8 colunm_logic = ZERO;
    if((NULL == keypad_obj)|| (NULL == value))
    {
        Ret=E_NOK;
    }
    else
    {
        for( l_keypad_row_count=0 ;  l_keypad_row_count<ECU_KEYPAD_ROWS ; l_keypad_row_count++ )
        {
            for( l_count=0 ;  l_count<ECU_KEYPAD_ROWS ; l_count++ )
            {
                Ret = gpio_pin_write_logic(&(keypad_obj->keypad_row_pin[l_count]),LOW);
            }
            
            Ret = gpio_pin_write_logic(&(keypad_obj->keypad_row_pin[l_keypad_row_count]),HIGHT);
            __delay_ms(10);
            for( l_keypad_colunm_count=0 ; l_keypad_colunm_count<ECU_KEYPAD_COLUMS ; l_keypad_colunm_count++ )
            {
                Ret=gpio_pin_read_logic(&(keypad_obj->keypad_colum_pin[l_keypad_colunm_count]),&colunm_logic);
                if(HIGHT == colunm_logic)
                {
                    *value = btn_values[l_keypad_row_count][l_keypad_colunm_count];
                }
            }
        }
    }
    
    return(Ret);
}

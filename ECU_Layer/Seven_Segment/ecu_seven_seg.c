
#include "ecu_seven_Seg.h"
/**
 * 
 * @param seg pointer to seven_ Segement_ Structure
 * @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */

STD_ReturnType seven_segment_intialize(const segment_t *seg)
{
    STD_ReturnType Ret = E_OK;
    if(NULL == seg)
    {
        Ret = E_NOK;
    }
    else
    {
        Ret = gpio_pin_intializtion(&(seg ->segment_pin[SEGMNT_PIN0]));
        Ret = gpio_pin_intializtion(&(seg ->segment_pin[SEGMNT_PIN1]));
        Ret = gpio_pin_intializtion(&(seg ->segment_pin[SEGMNT_PIN2]));
        Ret = gpio_pin_intializtion(&(seg ->segment_pin[SEGMNT_PIN3]));
    }
    return(Ret);
}
/**
 * @param seg pointer to seven_ Segement_ Structure
 * @param number the VAlue you want to show on the Segement
 * @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
 
STD_ReturnType seven_segment_wite_number(const segment_t *seg,uint8 number)
{
    STD_ReturnType Ret = E_OK;
    if((NULL == seg) &&(number > 9))
    {
        Ret = E_NOK;
    }
    else
    {
        Ret = gpio_pin_write_logic(&(seg ->segment_pin[SEGMNT_PIN0]),(number & 0x01));
        Ret = gpio_pin_write_logic(&(seg ->segment_pin[SEGMNT_PIN1]),((number >> 1) & 0x01));
        Ret = gpio_pin_write_logic(&(seg ->segment_pin[SEGMNT_PIN2]),((number >> 2) & 0x01));
        Ret = gpio_pin_write_logic(&(seg ->segment_pin[SEGMNT_PIN3]),((number >> 3) & 0x01));
    }
    return(Ret);
}
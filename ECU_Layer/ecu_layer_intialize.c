#include "ecu_layer_intialize.h"

chr_lcd_4bit_t lcd1 = {
    .lcd_rs.port =  PORTC_Index,
    .lcd_rs.pin = PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = LOW,
    
    .lcd_en.port =  PORTC_Index,
    .lcd_en.pin = PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = LOW,
    
    .lcd_data[0].port = PORTC_Index,
    .lcd_data[0].pin = PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = LOW,
    
    .lcd_data[1].port = PORTC_Index,
    .lcd_data[1].pin = PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = LOW,
    
    .lcd_data[2].port = PORTC_Index,
    .lcd_data[2].pin = PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = LOW,
    
    .lcd_data[3].port = PORTC_Index,
    .lcd_data[3].pin = PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = LOW,
};

chr_lcd_8bit_t lcd2 = {
    .lcd_rs.port =  PORTC_Index,
    .lcd_rs.pin = PIN6,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = LOW,
    
    .lcd_en.port =  PORTC_Index,
    .lcd_en.pin = PIN7,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = LOW,
    
    .lcd_data[0].port = PORTD_Index,
    .lcd_data[0].pin = PIN0,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = LOW,
    
    .lcd_data[1].port = PORTD_Index,
    .lcd_data[1].pin = PIN1,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = LOW,
    
    .lcd_data[2].port = PORTD_Index,
    .lcd_data[2].pin = PIN2,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = LOW,
    
    .lcd_data[3].port = PORTD_Index,
    .lcd_data[3].pin = PIN3,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = LOW,
    
    .lcd_data[4].port = PORTD_Index,
    .lcd_data[4].pin = PIN4,
    .lcd_data[4].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[4].logic = LOW,
    
    .lcd_data[5].port = PORTD_Index,
    .lcd_data[5].pin = PIN5,
    .lcd_data[5].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[5].logic = LOW,
    
    .lcd_data[6].port = PORTD_Index,
    .lcd_data[6].pin = PIN6,
    .lcd_data[6].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[6].logic = LOW,
    
    .lcd_data[7].port = PORTD_Index,
    .lcd_data[7].pin = PIN7,
    .lcd_data[7].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[7].logic = LOW,
};
void ecu_layer_intialize(void)
{
    STD_ReturnType Ret= E_NOK;
   
    Ret = lcd_4bit_intialize(&lcd1);
    Ret = lcd_8bit_intialize(&lcd2);
}

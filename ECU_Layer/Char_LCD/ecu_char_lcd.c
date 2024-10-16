/* 
 * File:   ecu_char_lcd_cnf.h
 * Author: Sara Saad
 *
 * Created on August 22, 2024, 7:51 AM
 */

#include "ecu_char_lcd.h"
static STD_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd_obj, uint8 data_command);

static STD_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd_obj, uint8 row, uint8 column);
static STD_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd_obj, uint8 row, uint8 column);

static STD_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd_obj);
static STD_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd_obj);

/**
 * 
 * @param lcd_obj
 * @return 
 */
STD_ReturnType lcd_4bit_intialize(const chr_lcd_4bit_t *lcd_obj)
{
    STD_ReturnType Ret = E_OK;
    uint8 lcd_4bit_intialize_count = ZERO;
    if(NULL == lcd_obj)
    {
        Ret = E_NOK;
    }
    else
    {
        Ret = gpio_pin_intializtion(&(lcd_obj ->lcd_rs));
        Ret = gpio_pin_intializtion(&(lcd_obj ->lcd_en));
        
        for(lcd_4bit_intialize_count=0 ; lcd_4bit_intialize_count<4 ; lcd_4bit_intialize_count++)
        {
            Ret = gpio_pin_intializtion(&(lcd_obj ->lcd_data[lcd_4bit_intialize_count]));
        } 
         __delay_ms(20);
        Ret = lcd_4bit_send_command(lcd_obj, _LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
         Ret = lcd_4bit_send_command(lcd_obj, _LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        Ret = lcd_4bit_send_command(lcd_obj, _LCD_8BIT_MODE_2LINE);
        
        Ret = lcd_4bit_send_command(lcd_obj, _LCD_CLEAR );
        Ret = lcd_4bit_send_command(lcd_obj, _LCD_RETURN_HOME  );
        Ret = lcd_4bit_send_command(lcd_obj, _LCD_ENTRY_MODE );
        Ret = lcd_4bit_send_command(lcd_obj, _LCD_CURSOR_OFF_DISPLAY_ON );
        Ret = lcd_4bit_send_command(lcd_obj, _LCD_4BIT_MODE_2LINE); 
        Ret = lcd_4bit_send_command(lcd_obj, _LCD_DDRAM_START );
    }
    
    return(Ret);
}
/**
 * 
 * @param lcd_obj
 * @param command
 * @return 
 */
STD_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd_obj, uint8 command)
{
    STD_ReturnType Ret = E_OK;
    
    if(NULL == lcd_obj)
    {
        Ret = E_NOK;
    }
    else
    {
         Ret = gpio_pin_write_logic(&(lcd_obj ->lcd_rs),LOW);
         Ret = lcd_send_4bits(lcd_obj, command >> 4);
         Ret = lcd_4bit_send_enable_signal(lcd_obj);
         Ret = lcd_send_4bits(lcd_obj, command);
         Ret = lcd_4bit_send_enable_signal(lcd_obj);
         
    }
    
    return(Ret);
}
/**
 * 
 * @param lcd_obj
 * @param data
 * @return 
 */
STD_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd_obj, uint8 data)
{
    STD_ReturnType Ret = E_OK;
    
    if(NULL == lcd_obj)
    {
        Ret = E_NOK;
    }
    else
    {
         Ret = gpio_pin_write_logic(&(lcd_obj ->lcd_rs),HIGHT);
         Ret = lcd_send_4bits(lcd_obj, data >> 4);
         Ret = lcd_4bit_send_enable_signal(lcd_obj);
         Ret = lcd_send_4bits(lcd_obj, data);
         Ret = lcd_4bit_send_enable_signal(lcd_obj);
    }
    
    return(Ret);
}
/**
 * 
 * @param lcd_obj
 * @param row
 * @param column
 * @param data
 * @return 
 */
STD_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd_obj, uint8 row, uint8 column, uint8 data)
{
    STD_ReturnType Ret = E_OK;
    
    if(NULL == lcd_obj)
    {
        Ret = E_NOK;
    }
    else
    {
        Ret = lcd_4bit_set_cursor(lcd_obj, row, column);
        Ret = lcd_4bit_send_char_data(lcd_obj,data);
    }
    
    return(Ret);
}
/**
 * 
 * @param lcd_obj
 * @param str
 * @return 
 */
STD_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd_obj, uint8 *str)
{
    STD_ReturnType Ret = E_OK;
    
    if((NULL == lcd_obj) || (NULL == str))
    {
        Ret = E_NOK;
    }
    else
    {
        while(*str)
        {
            Ret = lcd_4bit_send_char_data(lcd_obj,*str++);
        }
    }
    
    return(Ret);
}
/**
 * 
 * @param lcd_obj
 * @param row
 * @param column
 * @param str
 * @return 
 */
STD_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd_obj, uint8 row, uint8 column, uint8 *str)
{
    STD_ReturnType Ret = E_OK;
    
    if((NULL == lcd_obj) || (NULL == str))
    {
        Ret = E_NOK;
    }
    else
    {
        Ret = lcd_4bit_set_cursor(lcd_obj, row, column);
        while(*str)
        {
            Ret = lcd_4bit_send_char_data(lcd_obj,*str++);
        }
    }
    
    return(Ret);
}
/**
 * 
 * @param lcd_obj
 * @param row
 * @param column
 * @param chr
 * @param mem_pos
 * @return 
 */
STD_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd_obj,uint8 row, uint8 column, const uint8 chr[], uint8 mem_pos)
{
    STD_ReturnType Ret = E_OK;
    uint8 lcd_counter = ZERO;
    
    if(NULL == lcd_obj)
    {
        Ret = E_NOK;
    }
    else
    {
        Ret = lcd_4bit_send_command(lcd_obj, (_LCD_CGGRAM_START + (mem_pos * 8)));
        for(lcd_counter=0 ; lcd_counter<COLUMN_8; lcd_counter++)
        {
            Ret = lcd_4bit_send_char_data(lcd_obj, chr[lcd_counter]);
        }
        Ret = lcd_4bit_send_char_data_pos(lcd_obj, row, column, mem_pos);
    }
    
    return(Ret);
}
/**
 * 
 * @param lcd_obj
 * @return 
 */
STD_ReturnType lcd_8bit_intialize(const chr_lcd_8bit_t *lcd_obj)
{
    STD_ReturnType Ret = E_OK;
    uint8 lcd_4bit_intialize_count = ZERO;
    
    if(NULL == lcd_obj)
    {
        Ret = E_NOK;
    }
    else
    {
        Ret = gpio_pin_intializtion(&(lcd_obj ->lcd_rs));
        Ret = gpio_pin_intializtion(&(lcd_obj ->lcd_en));
        
        for(lcd_4bit_intialize_count=0 ; lcd_4bit_intialize_count<8 ; lcd_4bit_intialize_count++)
        {
            Ret = gpio_pin_intializtion(&(lcd_obj ->lcd_data[lcd_4bit_intialize_count]));
        } 
        
        __delay_ms(20);
        Ret = lcd_8bit_send_command(lcd_obj, _LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
         Ret = lcd_8bit_send_command(lcd_obj, _LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        Ret = lcd_8bit_send_command(lcd_obj, _LCD_8BIT_MODE_2LINE);
         
        Ret = lcd_8bit_send_command(lcd_obj, _LCD_CLEAR );
        Ret = lcd_8bit_send_command(lcd_obj, _LCD_RETURN_HOME  );
        Ret = lcd_8bit_send_command(lcd_obj, _LCD_ENTRY_MODE );
        Ret = lcd_8bit_send_command(lcd_obj, _LCD_CURSOR_OFF_DISPLAY_ON );
        Ret = lcd_8bit_send_command(lcd_obj, _LCD_8BIT_MODE_2LINE); 
        Ret = lcd_8bit_send_command(lcd_obj, _LCD_DDRAM_START );
        
    }
    return(Ret);
}
/**
 * 
 * @param lcd_obj
 * @param command
 * @return 
 */
STD_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd_obj,uint8 command)
{
    STD_ReturnType Ret = E_OK;
    uint8 l_lcd_8bit_command = ZERO;
    
    if(NULL == lcd_obj)
    {
        Ret = E_NOK;
    }
    else
    {
        Ret = gpio_pin_write_logic(&(lcd_obj ->lcd_rs),LOW);
        for(l_lcd_8bit_command; l_lcd_8bit_command<8 ; l_lcd_8bit_command++)
        {
            Ret = gpio_pin_write_logic( &(lcd_obj ->lcd_data[l_lcd_8bit_command]), ( (command >> l_lcd_8bit_command) & (uint8)(0x01) ) );
        }
        Ret = lcd_8bit_send_enable_signal(lcd_obj);
    }
    
    return(Ret);
}
/**
 * 
 * @param lcd_obj
 * @param data
 * @return 
 */
STD_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd_obj,uint8 data)
{
    STD_ReturnType Ret = E_OK;
    uint8 l_lcd_8bit_data = ZERO;
    
    if(NULL == lcd_obj)
    {
        Ret = E_NOK;
    }
    else
    {
        Ret = gpio_pin_write_logic(&(lcd_obj ->lcd_rs),HIGHT);
        
        for(l_lcd_8bit_data ; l_lcd_8bit_data <COLUMN_8 ; l_lcd_8bit_data ++)
        {
            Ret = gpio_pin_write_logic( &(lcd_obj ->lcd_data[l_lcd_8bit_data ]), ( (data >> l_lcd_8bit_data ) & (uint8)(0x01) ) );
        }
        
        Ret = lcd_8bit_send_enable_signal(lcd_obj);
    }
    
    return(Ret);
}
/**
 * 
 * @param lcd_obj
 * @param row
 * @param column
 * @param data
 * @return 
 */
STD_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd_obj,uint8 row,uint8 column,uint8 data)
{
    STD_ReturnType Ret = E_OK;
    
    if((NULL == lcd_obj))
    {
        Ret = E_NOK;
    }
    else
    {
        Ret = lcd_8bit_set_cursor(lcd_obj, row, column);
        Ret = lcd_8bit_send_char_data(lcd_obj,data);
    }
    
    return(Ret);
}
/**
 * 
 * @param lcd_obj
 * @param str
 * @return 
 */
STD_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd_obj,uint8 *str)
{
    STD_ReturnType Ret = E_OK;
    
    if((NULL == lcd_obj) || (NULL == str))
    {
        Ret = E_NOK;
    }
    else
    {
        while(*str)
        {
            Ret = lcd_8bit_send_char_data(lcd_obj, *str++);
        }
    }
    
    return(Ret);
}
/**
 * 
 * @param lcd_obj
 * @param row
 * @param column
 * @param str
 * @return 
 */
STD_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd_obj, uint8 row, uint8 column, uint8 *str)
{
    STD_ReturnType Ret = E_OK;
    
    if((NULL == lcd_obj) || (NULL == str))
    {
        Ret = E_NOK;
    }
    else
    {
        Ret = lcd_8bit_set_cursor(lcd_obj, row, column);
        while(*str)
        {
            Ret = lcd_8bit_send_char_data(lcd_obj, *str++);
        }
    }
    
    return(Ret);
}
/**
 * 
 * @param lcd_obj
 * @param row
 * @param column
 * @param chr
 * @param mem_pos
 * @return 
 */
STD_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd_obj,uint8 row, uint8 column, const uint8 chr[], uint8 mem_pos)
{
    STD_ReturnType Ret = E_OK;
    uint8 lcd_counter = ZERO;
    
    if(NULL == lcd_obj)
    {
        Ret = E_NOK;
    }
    else
    {
        Ret = lcd_8bit_send_command(lcd_obj, (_LCD_CGGRAM_START + (mem_pos * 8)));
        for(lcd_counter=0 ; lcd_counter<COLUMN_8; lcd_counter++)
        {
            Ret = lcd_8bit_send_char_data(lcd_obj, chr[lcd_counter]);
        }
        Ret = lcd_8bit_send_char_data_pos(lcd_obj, row, column, mem_pos);
    }
    
    return(Ret);
}
/**
 * 
 * @param value
 * @param str
 * @return 
 */
STD_ReturnType convert_byte_to_string(uint8 value, uint8 *str)
{
    STD_ReturnType Ret = E_OK;
    
    if((NULL == str))
    {
        Ret = E_NOK;
    }
    else
    {
        memset(str, '\0', 4);
        sprintf(str, "%i", value);
    }
    
    return(Ret);
}
/**
 * 
 * @param value
 * @param str
 * @return 
 */
STD_ReturnType convert_short_to_string(uint16 value, uint8 *str)
{
    STD_ReturnType Ret = E_OK;
    uint8 data_counter=0;
    uint8 Temp[6]={0};
    if((NULL == str))
    {
        Ret = E_NOK;
    }
    else
    {
        memset(str, ' ', 5);
        str[5]='\0';
        sprintf((uint8)Temp,"%i", value);
        while(Temp[data_counter] != '\0')
        {
            str[data_counter] = Temp[data_counter];
            data_counter++;
        }
    }
    
    return(Ret);
}
/**
 * 
 * @param value
 * @param str
 * @return 
 */
STD_ReturnType convert_int_to_string(uint32 value, uint8 *str)
{
    STD_ReturnType Ret = E_OK;
    
    if((NULL == str))
    {
        Ret = E_NOK;
    }
    else
    {
        memset(str, '\0', 11);
        sprintf(str, "%i", value);
    }
    
    return(Ret);
}
/**
 * 
 * @param lcd_obj
 * @param data_command
 * @return 
 */
static STD_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd_obj, uint8 data_command)
{
    STD_ReturnType Ret = E_OK;
    
    if((NULL == lcd_obj))
    {
        Ret = E_NOK;
    }
    else
    {
        Ret = gpio_pin_write_logic( &(lcd_obj ->lcd_data[0]),( (data_command >> 0) & (uint8)(0x01) ) );
        Ret = gpio_pin_write_logic( &(lcd_obj ->lcd_data[1]),( (data_command >> 1) & (uint8)(0x01) ) );
        Ret = gpio_pin_write_logic( &(lcd_obj ->lcd_data[2]),( (data_command >> 2) & (uint8)(0x01) ) );
        Ret = gpio_pin_write_logic( &(lcd_obj ->lcd_data[3]),( (data_command >> 3) & (uint8)(0x01) ) );
    }
}
/**
 * 
 * @param lcd_obj
 * @return 
 */
static STD_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd_obj)
{
     STD_ReturnType Ret = E_OK;
    
    if((NULL == lcd_obj))
    {
        Ret = E_NOK;
    }
    else
    {
        Ret = gpio_pin_write_logic(&(lcd_obj ->lcd_en), HIGHT);
        __delay_us(10);
         Ret = gpio_pin_write_logic(&(lcd_obj ->lcd_en), LOW);
    }
}
/**
 * 
 * @param lcd_obj
 * @return 
 */
static STD_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd_obj)
{
    STD_ReturnType Ret = E_OK;
    
    if((NULL == lcd_obj))
    {
        Ret = E_NOK;
    }
    else
    {
        Ret = gpio_pin_write_logic(&(lcd_obj ->lcd_en), HIGHT);
        __delay_us(10);
         Ret = gpio_pin_write_logic(&(lcd_obj ->lcd_en), LOW);
    }
     return(Ret);
}
static STD_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd_obj, uint8 row, uint8 column)
{
    STD_ReturnType Ret = E_OK;
    
    column--;
    if((NULL == lcd_obj))
    {
        Ret = E_NOK;
    }
    else
    {
        switch(row)
        {
            case ROW1 :
                Ret = lcd_8bit_send_command(lcd_obj,0x80+column);
                break;
            case ROW2 :
                 Ret = lcd_8bit_send_command(lcd_obj,0xc0+column);
                break;
            case ROW3 :
                 Ret = lcd_8bit_send_command(lcd_obj,0x94+column);
                break;
            case ROW4 :
                 Ret = lcd_8bit_send_command(lcd_obj,0xd4+column);
                break;
            default : 
                break;
        }
    }
     return(Ret);
}

static STD_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd_obj, uint8 row, uint8 column)
{
    STD_ReturnType Ret = E_OK;
    
    column--;
    if((NULL == lcd_obj))
    {
        Ret = E_NOK;
    }
    else
    {
        switch(row)
        {
            case ROW1 :
                Ret = lcd_4bit_send_command(lcd_obj,0x80+column);
                break;
            case ROW2 :
                 Ret = lcd_4bit_send_command(lcd_obj,0xc0+column);
                break;
            case ROW3 :
                 Ret = lcd_4bit_send_command(lcd_obj,0x94+column);
                break;
            case ROW4 :
                 Ret = lcd_4bit_send_command(lcd_obj,0xd4+column);
                break;
            default : 
                break;
        }
    }
     return(Ret);
}
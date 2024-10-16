/* 
 * File:   ecu_char_lcd.h
 * Author: DELL
 *
 * Created on August 22, 2024, 7:51 AM
 */

#ifndef ECU_CHAR_LCD_H
#define	ECU_CHAR_LCD_H

/* Section : Includes*/
#include "ecu_char_lcd_cnf.h"
#include "../../MCAL_Layer/Gpio/hal_gpio.h"
/* Section : Macros Declaration */

#define _LCD_CLEAR                 0x01
#define _LCD_RETURN_HOME           0X02
#define _LCD_ENTRY_MODE            0X06
#define _LCD_CURSOR_OFF_DISPLAY_ON 0X0C
#define _LCD_CURSOR_ON_DISPLAY_ON  0X08
#define _LCD_CURSOR_ON_BLINK_ON    0X0F
#define _LCD_CURSOR_ON_BLINK_OFF   0X0E
#define _LCD_DISPLAY_SHIFT_RIGHT   0X1C
#define _LCD_DISPLAY_SHIFT_LEFT    0X18
#define _LCD_8BIT_MODE_2LINE       0X38
#define _LCD_4BIT_MODE_2LINE       0X28
#define _LCD_CGGRAM_START          0X40
#define _LCD_DDRAM_START           0X80

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4

#define COLUMN_1  1
#define COLUMN_2  2
#define COLUMN_3  3
#define COLUMN_4  4
#define COLUMN_5  5
#define COLUMN_6  6
#define COLUMN_7  7
#define COLUMN_8  8
#define COLUMN_9  9
#define COLUMN_10 10
#define COLUMN_11 11
#define COLUMN_12 12
#define COLUMN_13 13
#define COLUMN_14 14
#define COLUMN_15 15
#define COLUMN_16 16
#define COLUMN_17 17
#define COLUMN_18 18
#define COLUMN_19 19
#define COLUMN_20 20



/* Section : Function like Macros Declaration*/

/* Section : User Defined Data Type */
typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}chr_lcd_4bit_t;

typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}chr_lcd_8bit_t;
/* Section : Function Declaration */

STD_ReturnType lcd_4bit_intialize(const chr_lcd_4bit_t *lcd_obj);
STD_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd_obj, uint8 command);
STD_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd_obj, uint8 data);
STD_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd_obj, uint8 row, uint8 column, uint8 data);
STD_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd_obj, uint8 *str);
STD_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd_obj, uint8 row, uint8 column, uint8 *str);
STD_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd_obj,uint8 row, uint8 column, const uint8 chr[], uint8 mem_pos);

STD_ReturnType lcd_8bit_intialize(const chr_lcd_8bit_t *lcd_obj);
STD_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd_obj,uint8 command);
STD_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd_obj,uint8 data);
STD_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd_obj,uint8 row,uint8 column,uint8 data);
STD_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd_obj,uint8 *str);
STD_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd_obj, uint8 row, uint8 column, uint8 *str);
STD_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd_obj,uint8 row, uint8 column, const uint8 chr[], uint8 mem_pos);

STD_ReturnType convert_byte_to_string(uint8 value, uint8 *str);
STD_ReturnType convert_short_to_string(uint16 value, uint8 *str);
STD_ReturnType convert_int_to_string(uint32 value, uint8 *str);
void ecu_layer_intialize(void);
#endif	/* ECU_CHAR_LCD_H */


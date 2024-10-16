/* 
 * File:   hal_usart.h
 * Author: DELL
 *
 * Created on September 23, 2024, 5:54 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/* Section : Includes*/
#include "hal_usart_cfg.h"
#include "../../MCAL_Layer/mcal_std_types.h"
#include "../Gpio/hal_gpio.h"
#include "../../MCAL_Layer/interrupt/mcal_internal_interrupt.h"
#include <pic18f4620.h>
/* Section : Macros Declaration */
#define EUSART_MODULE_ENABLE  1
#define EUSART_MODULE_DISABLE 0

/*EUSART CONFIG*/
#define EUSART_ASYNCRONOUS_MOOD 0
#define EUSART_SYNCRONOUS_MOOD  1

#define EUSART_ASYNCRONOUS_HIGH_SPEED 1
#define EUSART_ASYNCRONOUS_LOW_SPEED  0

#define EUSART_16BIT_BAUDRATE_GEN 1
#define EUSART_8BIT_BAUDRATE_GEN  0

/*Transmetter_part CONFIG*/

#define EUSART_ASYNCRONOUS_TX_ENABLE  1
#define EUSART_ASYNCRONOUS_TX_DISABLE 0

#define EUSART_ASYNCRONOUS_TX_INTERRUPT_ENABLE  1
#define EUSART_ASYNCRONOUS_TX_INTERRUPT_DISABLE 0

#define EUSART_ASYNCRONOUS_TX_9BIT_ENABLE  1
#define EUSART_ASYNCRONOUS_TX_9BIT_DISABLE 0

/*Recever _part CONFIG*/

#define EUSART_ASYNCRONOUS_RX_ENABLE  1
#define EUSART_ASYNCRONOUS_RX_DISABLE 0

#define EUSART_ASYNCRONOUS_RX_INTERRUPT_ENABLE  1
#define EUSART_ASYNCRONOUS_RX_INTERRUPT_DISABLE 0

#define EUSART_ASYNCRONOUS_RX_9BIT_ENABLE  1
#define EUSART_ASYNCRONOUS_RX_9BIT_DISABLE 0

/*EUSART FRAMING ERROR*/
#define EUSART_FRAMING_ERROR_SETTEING 1
#define EUSART_FRAMING_ERROR_CLEARING 0

/*EUSART OVERRUNNING ERROR*/
#define EUSART_OVERRUNNING_ERROR_SETTEING 1
#define EUSART_OVERRUNNING_ERROR_CLEARING 0

/* Section : Function like Macros Declaration*/

/* Section : User Defined Data Type */
typedef enum {
    USART_ASYN_8BIT_LOW_SPEED = 0,
    USART_ASYN_8BIT_HIGH_SPEED,
    USART_ASYN_16BIT_LOW_SPEED,
    USART_ASYN_16BIT_HIGH_SPEED,
    USART_SYN_8BIT,
    USART_SYN_16BIT        
}usart_baudrate_gn_t;

typedef struct{
    uint8 usart_asyn_tx_enable :1;
    uint8 usart_asyn_tx_itrrupt_enable :1 ;
    uint8 usart_asyn_tx_9bit_enable :1 ;
    uint8 :5 ;
}usart_tx_cfg_t;

typedef struct{
    uint8 usart_asyn_rx_enable :1;
    uint8 usart_asyn_rx_itrrupt_enable :1 ;
    uint8 usart_asyn_rx_9bit_enable :1 ;
    uint8 :5 ;
}usart_rx_cfg_t;

typedef union{
    struct{
       uint8 usart_fram_error :1;
       uint8 usart_overrun_error :1;
       uint8 :6;
    };
    uint8 error_status;
}usart_error_status_t;

typedef struct{
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_error_status_t usart_error;
    uint32 baudrate;
    usart_baudrate_gn_t baudrate_gen_cfg;
    void (*EUSART_TX_INTERRUPR_HANDELER)(void);
    void (*EUSART_RX_INTERRUPR_HANDELER)(void);
    void (*EUSART_FRAMING_ERROR_INTERRUPR_HANDELER)(void);
    void (*EUSART_OVERRUN_ERROR_INTERRUPR_HANDELER)(void);
    interrupt_priority_cfg eusart_priority_enable;
}usart_config_t;
/* Section : Function Declaration */
STD_ReturnType EUSART_ASYN_INIT(const usart_config_t * usart_obj);
STD_ReturnType EUSART_ASYN_DE_INIT(const usart_config_t * usart_obj);

STD_ReturnType EUSART_ASYN_WRITE_BYTE_BLOCKING(const usart_config_t * usart_obj,uint8 value);
STD_ReturnType EUSART_ASYN_WRITE_STRING_BLOCKING(const usart_config_t * usart_obj,uint8 *str,uint16 str_lenght);

STD_ReturnType EUSART_ASYN_READ_BYTE_BLOCKING(const usart_config_t * usart_obj,uint8 * value);
STD_ReturnType EUSART_ASYN_READ_BYTE_NON_BLOCKING(const usart_config_t * usart_obj,uint8 * value);

STD_ReturnType EUSART_ASYN_RESTART_RX(void);
#endif	/* HAL_USART_H */


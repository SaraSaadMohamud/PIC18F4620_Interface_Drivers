/* 
 * File:   hal_I2C.h
 * Author: DELL
 *
 * Created on September 29, 2024, 1:14 AM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

/* Section : Includes*/
#include "../../MCAL_Layer/interrupt/mcal_internal_interrupt.h"
#include "../../MCAL_Layer/mcal_std_types.h"
#include <pic18f4620.h>
#include "../Gpio/hal_gpio.h"

/* Section : Macros Declaration */
#define I2C_SLEW_MODE_ENABLE  0 /*400 KHZ*/
#define I2C_SLEW_MODE_DISABLE 1 /*100 KHZ*/

/*ENABLE OR DISABLE THE SMBUS*/
#define I2C_SMPUS_ENABLE  1
#define I2C_SMPUS_DISABLE 0

/*I2C_MASTER_TRANSIMMETED LAST BYTE*/
#define I2C_LAST_BYTE_DATA    1
#define I2C_LAST_BYTE_ADDRESS 0

/*START CONDITION SELECTED*/
#define I2C_START_BIT_DETECTED     1
#define I2C_START_BIT_NOT_DETECTED 0

/*STOP CONDITION SELECTED*/
#define I2C_STOP_BIT_DETECTED     1
#define I2C_STOP_BIT_NOT_DETECTED 0

/*MASTER SYNCROUNES SERIAL PORT MODE SELECT*/
#define I2C_SLAVE_7BIT_ADDRESS_START_STOP_INTERRUPT 0X0E
#define I2C_SLAVE_10BIT_ADRESS_START_STOP_INTERRUPT 0X0F
#define I2C_SLAVE_7BIT_ADDRESS  0X06
#define  I2C_SLAVE_10BIT_ADDRESS 0X07
#define I2C_MASTER_DEFFINED_CLOCK      0X08
#define I2C_MASTER_FRIMWARE_CONTROLLED 0X0B

/*MSSP_I2C_SLAVE_GENERAL_CALL ENABLE OR DISABLE*/
#define I2C_GENERAL_CALL_ADDRESS_ENABLE  1
#define I2C_GENERAL_CALL_ADDRESS_DISABLE 0

/*MASTER MODE RECIVE ENABLE*/
#define I2C_MASTER_RECIVER_MODE_ENABLE  1
#define I2C_MASTER_RECIVER_MODE_DISABLE 0

/*MSSP_I2C_MODE_SELECTED*/
#define MSSP_I2C_MASTER_MODE 1
#define MSSP_I2C_SLAVE_MODE  0

/*ACKNOLEDGE STATE BIT MASTER TRANSMITTE MODE*/
#define I2C_ACKNOLEDGE_BIT_RECIVE_FROM_SLAVE_DETECTED     0
#define I2C_ACKNOLEDGE_BIT_RECIVE_FROM_SLAVE_NOT_DETECTED 1

/*MASTER RECIVE MODE ONLY ACKNOLEDGE BIT DETECTED*/
#define I2C_MASTER_RECIVER_MODE_SEND_ACK     0
#define I2C_MASTER_RECIVER_MODE_SEND_NOT_ACK 1
/* Section : Function like Macros Declaration*/

/*SLEW RATE ENABLE OR DISABLE*/
#define I2C_SLEW_RATE_CFG_ENABLE()  (SSPSTATbits.SMP = 0)
#define I2C_SLEW_RATE_CFG_DISABLE() (SSPSTATbits.SMP = 1)

/*SMBUS ENABLE OR DISABLE*/
#define I2C_SMBUS_ENABLE() (SSPSTATbits.CKE = 1)
#define I2C_SMBUS_DISABLE()(SSPSTATbits.CKE = 0)

/*GENERAL CALL ADRESS ENABLE OR DISABLE*/
#define I2C_GENERAL_CALL_ENABLE() (SSPCON2bits.GCEN = 1)
#define I2C_GENERAL_CALL_DISABLE()(SSPCON2bits.GCEN = 0)

/*ENABLE OR DISABLE MASTER TO BE RECIVER*/
#define I2C_MASTER_RECIVER_ENABLE() (SSPCON2bits.RCEN = 1)
#define I2C_MASTER_RECIVER_ENABLE() (SSPCON2bits.RCEN = 0)

/*ENABLE OR DISABLE MSSP MODULE*/
#define MSSP_MODULE_ENABLE() (SSPCON1bits.SSPEN = 1)
#define MSSP_MODULE_DISABLE()(SSPCON1bits.SSPEN = 0)

/*CLOCK STRECH*/
#define I2C_SLAVE_CLOCK_STRECH_ENABLE()  (SSPCON1bits.CKP = 0)
#define I2C_SLAVE_CLOCK_STRECH_DISABLE() (SSPCON1bits.CKP = 1) 

/* Section : User Defined Data Type */
typedef struct{
    uint8 I2c_mode_config;/*MASTER SYNCROUNES SERIAL PORT mODE SELECT*/
    uint8 Slave_Address;
    
    uint8 I2C_Mode : 1;/*MASTER OR SLAVE*/
    uint8 I2C_slew_rate : 1; /*SLEW RATE ENABLE OR DISABLE*/
    uint8 I2C_SMBUS_Control : 1;/*SMBUS ENABLE OR DISABLE*/
    uint8 I2C_General_Call : 1;/* GENERAL_CALL ENABLE OR DISABLE*/
    uint8 I2c_Master_Recived_Mode : 1;/* MSTER RECIEVER MODE ENABLE OR DISABLE*/
    uint8 : 3;
}i2c_configC_Mode_t;

typedef struct{
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(*I2C_REPORT_WRITE_COLLISION)(void);
    void(*I2C_INTERRUPT_HANDELLER)(void);
    void(*I2C_REPORT_RECIVE_OVERFLOW)(void);
    interrupt_priority_cfg mssp_i2c_priority;
    interrupt_priority_cfg mssp_i2c_bus_collision_priority;
#endif
    uint32 I2C_clock_speed;
    i2c_configC_Mode_t I2c_cfg;
}mssp_i2c_t;

/* Section : Function Declaration */
STD_ReturnType MSSP_I2C_INIT(const mssp_i2c_t* i2c_obj );
STD_ReturnType MSSP_I2C_DE_INIT(const mssp_i2c_t* i2c_obj );

STD_ReturnType MSSP_I2C_MASTER_SEND_START(const mssp_i2c_t* i2c_obj );
STD_ReturnType MSSP_I2C_MASTER_SEND_RESTART(const mssp_i2c_t* i2c_obj );
STD_ReturnType MSSP_I2C_MASTER_SEND_STOP(const mssp_i2c_t* i2c_obj );

STD_ReturnType MSSP_I2C_MASTER_WRITE_BLOKING(const mssp_i2c_t* i2c_obj, uint8 I2C_data,uint8 *ack);
STD_ReturnType MSSP_I2C_MASTER_READ_BLOCKING(const mssp_i2c_t* i2c_obj, uint8 *I2C_data, uint8 ACK);

#endif	/* HAL_I2C_H */


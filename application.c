/* 
 * File:   application.c
 * Author: DELL
 *
 * Created on July 17, 2024, 7:23 PM
 */
#include "application.h"

RealTimeClockDs1307_t Real_Time_Clock_Ds1307_Obj;
mssp_i2c_t i2c_obj = {
    .I2c_cfg.I2C_Mode =  MSSP_I2C_SLAVE_MODE,
    .I2c_cfg.Slave_Address = 0XD0,
    .I2c_cfg.I2c_mode_config = I2C_SLAVE_7BIT_ADDRESS,
    .I2c_cfg.I2C_SMBUS_Control = I2C_SMPUS_DISABLE,
    .I2c_cfg.I2C_slew_rate = I2C_SLEW_MODE_DISABLE,
    .I2c_cfg.I2C_General_Call = I2C_GENERAL_CALL_ADDRESS_DISABLE,
    .I2C_INTERRUPT_HANDELLER =  MSSP_I2C_APP_ISR,
};
int main()
{
   STD_ReturnType Ret = E_NOK;

   while(1)
   {
      Real_Time_Clock_Ds1307_Obj = Real_Time_Clock_Ds1307_Get_Data_Time();
   }
    return(0);
}
void MSSP_I2C_APP_ISR(void)
{
    
}
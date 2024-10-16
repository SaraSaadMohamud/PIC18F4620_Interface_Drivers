/* 
 * File:   RealTimeClockDs1307.?
 * Author: DELL
 *
 * Created on October 2, 2024, 2:20 AM
 */

#include "RealTimeClockDs1307.h"
static RealTimeClockDs1307_t Real_Time_Clock_Ds1307_Obj;
RealTimeClockDs1307_t Real_Time_Clock_Ds1307_Get_Data_Time(void)
{
  
    return(Real_Time_Clock_Ds1307_Obj);
}
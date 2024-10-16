/* 
 * File:   mcal_external_interrupt.c
 * Author: DELL
 *
 * Created on August 28, 2024, 12:31 AM
 */
#include "mcal_external_interrupt.h"

static void (* INT0_Interrupt_Handler)(void)=NULL;
static void (* INT1_Interrupt_Handler)(void)=NULL;
static void (* INT2_Interrupt_Handler)(void)=NULL;

static void (* RB4_INT_Interrupt_Handler_HIGH)(void)=NULL;
static void (* RB4_INT_Interrupt_Handler_LOW)(void)=NULL;
static void (* RB5_INT_Interrupt_Handler_HIGH)(void)=NULL;
static void (* RB5_INT_Interrupt_Handler_LOW)(void)=NULL;
static void (* RB6_INT_Interrupt_Handler_HIGH)(void)=NULL;
static void (* RB6_INT_Interrupt_Handler_LOW)(void)=NULL;
static void (* RB7_INT_Interrupt_Handler_HIGH)(void)=NULL;
static void (* RB7_INT_Interrupt_Handler_LOW)(void)=NULL;

static STD_ReturnType INTERRUPT_INTx_Enable(const interrupt_INTx_t* int_obj);
static STD_ReturnType INTERRUPT_INTx_Disable(const interrupt_INTx_t* int_obj);
static STD_ReturnType INTERRUPT_INTx_Clear_Flag(const interrupt_INTx_t* int_obj);
static STD_ReturnType INTERRUPT_INTx_Priority_init(const interrupt_INTx_t* int_obj);
static STD_ReturnType INTERRUPT_INTx_Edge_init(const interrupt_INTx_t* int_obj);
static STD_ReturnType INTERRUPT_INTx_Pin_Init(const interrupt_INTx_t* int_obj);


static STD_ReturnType INTERRUPT_RBXx_Enable(const interrupt_RBx_t* int_obj);
static STD_ReturnType INTERRUPT_RBXx_Disable(const interrupt_RBx_t* int_obj);
static STD_ReturnType INTERRUPT_RBXx_Clear_Flag(const interrupt_RBx_t* int_obj);
static STD_ReturnType INTERRUPT_RBXx_Priority_init(const interrupt_RBx_t* int_obj);
static STD_ReturnType INTERRUPT_RBx_Pin_Init(const interrupt_RBx_t* int_obj);

static STD_ReturnType INTERRUPT_INTx_SET_INTERRUPT_HABDLER(const interrupt_INTx_t* int_obj);
static STD_ReturnType INT0_SET_INTERRUPT_HABDLER(void (*Interrupt_Handler)(void));
static STD_ReturnType INT1_SET_INTERRUPT_HABDLER(void (*Interrupt_Handler)(void));
static STD_ReturnType INT2_SET_INTERRUPT_HABDLER(void (*Interrupt_Handler)(void));

/**
 * @breif
 * @param int_obj
@return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
STD_ReturnType Inturrupt_INTx_Init(const interrupt_INTx_t* int_obj)
{
    STD_ReturnType Ret=E_OK;
    if(NULL ==  int_obj)
    {
        Ret=E_NOK;
    }
    else
    {
       /*Disable the External interrupt*/
        Ret = INTERRUPT_INTx_Disable(int_obj);
       /*Clear the Flag : External interrupt don't OCCURE*/
        Ret = INTERRUPT_INTx_Clear_Flag(int_obj);
       /*Configure External Interrupt Edge*/
        Ret = INTERRUPT_INTx_Edge_init(int_obj);
        #if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
       /*Configure External Interrupt Priority */
        Ret = INTERRUPT_INTx_Priority_init(int_obj);
        #endif
       /*Configure External Interrupt I/O Pin*/
        Ret = INTERRUPT_INTx_Pin_Init(int_obj);
       /* Configure External Interrupt CallBack*/
        Ret = INTERRUPT_INTx_SET_INTERRUPT_HABDLER(int_obj);
       /*Enable the External interrupt*/
        Ret = INTERRUPT_INTx_Enable(int_obj);
    }
    return(Ret);
}
void INT0_ISR(void)
{
    /*CLEAR THE INT0 INTERRUPT*/
       EXTERNAL_INT0_INTERRUPT_FLAG_CLEAR();
    /*EXECUTE THE CODE*/
       
    /* CALLED CALLBACK FUNCTION*/
       if(INT0_Interrupt_Handler)
       {
           INT0_Interrupt_Handler();
       }
}
void INT1_ISR(void)
{
    /*CLEAR THE INT0 INTERRUPT*/
       EXTERNAL_INT1_INTERRUPT_FLAG_CLEAR();
    /*EXECUTE THE CODE*/
       
    /* CALLED CALLBACK FUNCTION*/
       if(INT1_Interrupt_Handler)
       {
           INT1_Interrupt_Handler();
       }
}
void INT2_ISR(void)
{
    /*CLEAR THE INT0 INTERRUPT*/
       EXTERNAL_INT2_INTERRUPT_FLAG_CLEAR();
    /*EXECUTE THE CODE*/
       
    /* CALLED CALLBACK FUNCTION*/
       if(INT2_Interrupt_Handler)
       {
           INT2_Interrupt_Handler();
       }
}
void RB4_ISR(uint8 RB4_Source)
{
     /*CLEAR THE INT0 INTERRUPT*/
      EXTERNAL_RBI_INTERRUPT_FLAG_CLEAR() ;
    /*EXECUTE THE CODE*/
       
    /* CALLED CALLBACK FUNCTION*/
      if(0 == RB4_Source)
      {
          if(RB4_INT_Interrupt_Handler_LOW)
            {
               RB4_INT_Interrupt_Handler_LOW();
            }
      }
      else if (1 == RB4_Source)
      {
           if(RB4_INT_Interrupt_Handler_HIGH)
            {
                RB4_INT_Interrupt_Handler_HIGH();
            }
      }
}
void RB5_ISR(uint8 RB5_Source)
{
     /*CLEAR THE INT0 INTERRUPT*/
      EXTERNAL_RBI_INTERRUPT_FLAG_CLEAR() ;
    /*EXECUTE THE CODE*/
       
    /* CALLED CALLBACK FUNCTION*/
      if(0 == RB5_Source)
      {
          if(RB5_INT_Interrupt_Handler_LOW)
            {
               RB5_INT_Interrupt_Handler_LOW();
            }
      }
      else if (1 == RB5_Source)
      {
           if(RB5_INT_Interrupt_Handler_HIGH)
            {
                RB5_INT_Interrupt_Handler_HIGH();
            }
      }
}

void RB6_ISR(uint8 RB6_Source)
{
     /*CLEAR THE INT0 INTERRUPT*/
      EXTERNAL_RBI_INTERRUPT_FLAG_CLEAR() ;
    /*EXECUTE THE CODE*/
       
    /* CALLED CALLBACK FUNCTION*/
      if(0 == RB6_Source)
      {
          if(RB6_INT_Interrupt_Handler_LOW)
            {
               RB6_INT_Interrupt_Handler_LOW();
            }
      }
      else if (1 == RB6_Source)
      {
           if(RB6_INT_Interrupt_Handler_HIGH)
            {
                RB6_INT_Interrupt_Handler_HIGH();
            }
      }
}
void RB7_ISR(uint8 RB7_Source)
{
     /*CLEAR THE INT0 INTERRUPT*/
      EXTERNAL_RBI_INTERRUPT_FLAG_CLEAR() ;
    /*EXECUTE THE CODE*/
       
    /* CALLED CALLBACK FUNCTION*/
      if(0 == RB7_Source)
      {
          if(RB7_INT_Interrupt_Handler_LOW)
            {
               RB7_INT_Interrupt_Handler_LOW();
            }
      }
      else if (1 == RB7_Source)
      {
           if(RB7_INT_Interrupt_Handler_HIGH)
            {
                RB7_INT_Interrupt_Handler_HIGH();
            }
      }
}
/**
 * @breif
@return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 * @return 
 */
STD_ReturnType Inturrupt_INTx_De_Init(const interrupt_INTx_t* int_obj)
{
    STD_ReturnType Ret=E_OK;
    if(NULL ==  int_obj)
    {
        Ret=E_NOK;
    }
    else
    {
        Ret = INTERRUPT_INTx_Disable(int_obj);
    }
    return(Ret);
}
/**
 * @breif
 * @param int_obj
 @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
STD_ReturnType Inturrupt_RBx_Init(const interrupt_RBx_t* int_obj)
{
    STD_ReturnType Ret=E_OK;
    if(NULL ==  int_obj)
    {
        Ret=E_NOK;
    }
    else
    {
        /* Macro to Disable Extern_RBI_Interrupt*/
        EXTERNAL_RBI_INTERRUPT_DISABLE() ;
        /* Macro to Clear the flag of Extern_RBI_Interrupt*/
        EXTERNAL_RBI_INTERRUPT_FLAG_CLEAR();
        /* Macro to Enable Extern_RBI_Interrupt*/
        #if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE 
                /*this macro will enable the interrupt priority feature*/
                INTERRUPT_PERIORITY_LEVELS_ENABLE();
                if(int_obj ->Interrupt_priority == INTERRUPT_HIGH_PRIORITY)
                {
                    /*this macro will enable the high priority global interruptS*/
                    INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE();
                    /*MACRO TO ENABLE THE EXTERNAL_RBI_INTERRUPT_HIGH_PERIORITY*/
                     EXTERNAL_RBI_INTERRUPT_HIGH_PRIORITY();
                }
                else if(int_obj ->Interrupt_priority == INTERRUPT_LOW_PRIORITY)
                {
                    /*this macro will enable the LOW priority global interruptS*/
                   INTERRUPT_GLOPAL_INTERRUPT_LOW_ENABLE();
                   /*MACRO TO ENABLE THE EXTERNAL_RBI_INTERRUPT_LOW_PERIORITY*/
                   EXTERNAL_RBI_INTERRUPT_LOW_PRIORITY();
                }
                else 
                {
                    Ret = E_NOK;
                }
               #else
               INTERRUPT_GLOPAL_INTERRUPT_ENABLE();
               INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();         
               #endif
               /*INTITALIZE RBX PIN TO BE INPUT*/
               Ret = gpio_pin_direction_intializtion(&(int_obj->mcu_pin));
               /* INITIALIZE THE CALLBACK FUNCTION*/
               switch(int_obj->mcu_pin.pin)
               {
                   case PIN4:
                       RB4_INT_Interrupt_Handler_HIGH= int_obj->ptr_External_Inturrupt_HIGH;
                       RB4_INT_Interrupt_Handler_LOW = int_obj->ptr_External_Inturrupt_LOW;
                       break;
                    case PIN5:
                       RB5_INT_Interrupt_Handler_HIGH= int_obj->ptr_External_Inturrupt_HIGH;
                       RB5_INT_Interrupt_Handler_LOW = int_obj->ptr_External_Inturrupt_LOW;
                       break;
                    case PIN6:
                       RB6_INT_Interrupt_Handler_HIGH= int_obj->ptr_External_Inturrupt_HIGH;
                       RB6_INT_Interrupt_Handler_LOW= int_obj->ptr_External_Inturrupt_LOW;
                       break;
                    case PIN7:
                       RB7_INT_Interrupt_Handler_HIGH= int_obj->ptr_External_Inturrupt_HIGH;
                       RB7_INT_Interrupt_Handler_LOW= int_obj->ptr_External_Inturrupt_LOW;
                       break;
                   default :
                       Ret =E_NOK;
               }
        EXTERNAL_RBI_INTERRUPT_ENABLE();
    }
    return(Ret);
}
/**
 * @breif
 * @param int_obj
 @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
STD_ReturnType Inturrupt_RBx_De_Init(const interrupt_RBx_t* int_obj)
{
    STD_ReturnType Ret=E_OK;
    if(NULL ==  int_obj)
    {
        Ret=E_NOK;
    }
    else
    {
        /* Macro to Disable Extern_RBI_Interrupt*/
        EXTERNAL_RBI_INTERRUPT_DISABLE() ;
        /* Macro to Clear the flag of Extern_RBI_Interrupt*/
        EXTERNAL_RBI_INTERRUPT_FLAG_CLEAR();
    }
    return(Ret);
}
/**
 * @breif
 * @param int_obj
 @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
static STD_ReturnType INTERRUPT_INTx_Enable(const interrupt_INTx_t* int_obj)
{
    STD_ReturnType Ret=E_OK;
    if(NULL ==  int_obj)
    {
        Ret=E_NOK;
    }
    else
    {
        switch(int_obj ->Interrupt_Source)
        {
            case INTERRUPR_EXTERNAL_INT0 :
                #if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE     
                    INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE();
                #else
                    INTERRUPT_GLOPAL_INTERRUPT_ENABLE();
                    INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();         
                #endif
                EXTERNAL_INT0_INTERRUPT_ENABLE();
                break;
                
            case INTERRUPR_EXTERNAL_INT1 :
               #if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE 
                INTERRUPT_PERIORITY_LEVELS_ENABLE();
                if(int_obj ->Interrupt_priority == INTERRUPT_HIGH_PRIORITY)
                {
                    INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE();
                }
                else if(int_obj ->Interrupt_priority == INTERRUPT_LOW_PRIORITY)
                {
                   INTERRUPT_GLOPAL_INTERRUPT_LOW_ENABLE();
                }
                else 
                {
                    Ret = E_NOK;
                }
               #else
               INTERRUPT_GLOPAL_INTERRUPT_ENABLE();
               INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();         
               #endif
                EXTERNAL_INT1_INTERRUPT_ENABLE();
                break;
                
            case INTERRUPR_EXTERNAL_INT2 :
                #if INTERRUPT_PERIOITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE 
                   INTERRUPT_PERIORITY_LEVELS_ENABLE();
                   if(int_obj ->Interrupt_priority == INTERRUPT_HIGH_PRIORITY)
                    {
                       INTERRUPT_GLOPAL_INTERRUPT_HIGHT_ENABLE();
                    }
                    else if(int_obj ->Interrupt_priority == INTERRUPT_LOW_PRIORITY)
                    {
                       INTERRUPT_GLOPAL_INTERRUPT_LOW_ENABLE();
                    }
                    else 
                    {
                        Ret = E_NOK;
                    }
                #else
                       INTERRUPT_GLOPAL_INTERRUPT_ENABLE();
                       INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();         
                #endif
                EXTERNAL_INT2_INTERRUPT_ENABLE();
                break;
                
            default :
                Ret = E_NOK;
                break;
        }
    }
    return(Ret);
}
/**
 * @breif
 * @param int_obj
 @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
static STD_ReturnType INTERRUPT_INTx_Disable(const interrupt_INTx_t* int_obj)
{
    STD_ReturnType Ret=E_OK;
    if(NULL ==  int_obj)
    {
        Ret=E_NOK;
    }
    else
    {
        switch(int_obj ->Interrupt_Source)
        {
            case INTERRUPR_EXTERNAL_INT0 :
                EXTERNAL_INT0_INTERRUPT_DISABLE();
                break;
            case INTERRUPR_EXTERNAL_INT1 :
                EXTERNAL_INT1_INTERRUPT_DISABLE();
                break;
            case INTERRUPR_EXTERNAL_INT2 :
                EXTERNAL_INT2_INTERRUPT_DISABLE();
                break;
            default :
                Ret = E_NOK;
                break;
        }
    }
    return(Ret);
}
/**
 * @breif
 * @param int_obj
 @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
#if INTERRUPT_PERIOITY_LEVEL_ENABLE  == INTERRUPT_FEATURE_ENABLE
static STD_ReturnType INTERRUPT_INTx_Priority_init(const interrupt_INTx_t* int_obj)
{
    STD_ReturnType Ret=E_OK;
    if(NULL ==  int_obj)
    {
        Ret=E_NOK;
    }
    else
    {
        switch(int_obj ->Interrupt_Source)
        {
            case INTERRUPR_EXTERNAL_INT1 :
                if(int_obj ->Interrupt_priority == INTERRUPT_HIGH_PRIORITY)
                {
                    Ret = EXTERNAL_INT1_INTERRUPT_HIGH_PRIORITY();
                }
                else if(int_obj ->Interrupt_priority == INTERRUPT_LOW_PRIORITY)
                {
                    Ret = EXTERNAL_INT1_INTERRUPT_LOW_PRIORITY();
                }
                else 
                {
                    Ret = E_NOK;
                }
                break;
            case INTERRUPR_EXTERNAL_INT2 :
                if(int_obj ->Interrupt_priority == INTERRUPT_HIGH_PRIORITY)
                {
                    Ret = EXTERNAL_INT2_INTERRUPT_HIGH_PRIORITY();
                }
                else if(int_obj ->Interrupt_priority == INTERRUPT_LOW_PRIORITY)
                {
                    Ret = EXTERNAL_INT2_INTERRUPT_LOW_PRIORITY();
                }
                else 
                {
                    Ret = E_NOK;
                }
                break;
            default :
                Ret = E_NOK;
                break;
        }
    }
    return(Ret);
}
#endif
/**
 * @breif
 * @param int_obj
 @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
static STD_ReturnType INTERRUPT_INTx_Edge_init(const interrupt_INTx_t* int_obj)
{
    STD_ReturnType Ret=E_OK;
    if(NULL ==  int_obj)
    {
        Ret=E_NOK;
    }
    else
    {
        switch(int_obj ->Interrupt_Source)
        {
            case INTERRUPR_EXTERNAL_INT0 :
                if (int_obj ->Interrupt_Edge == INTERRUPR_FALLING_EDGE)
                {
                    Ret = EXTERNAL_INT0_INTERRUPT_FALLING_EDGE_SET();
                }
                else if (int_obj ->Interrupt_Edge == INTERRUPR_RAISING_EDGE)
                {
                    Ret = EXTERNAL_INT0_INTERRUPT_RAISING_EDGE_SET();
                }
                else
                {
                    Ret = E_NOK;
                }
                break;
            case INTERRUPR_EXTERNAL_INT1 :
                 if (int_obj ->Interrupt_Edge == INTERRUPR_FALLING_EDGE)
                {
                    Ret = EXTERNAL_INT1_INTERRUPT_FALLING_EDGE_SET();
                }
                else if (int_obj ->Interrupt_Edge == INTERRUPR_RAISING_EDGE)
                {
                    Ret = EXTERNAL_INT1_INTERRUPT_RAISING_EDGE_SET();
                }
                else
                {
                    Ret = E_NOK;
                }
                break;
            case INTERRUPR_EXTERNAL_INT2 :
                 if (int_obj ->Interrupt_Edge == INTERRUPR_FALLING_EDGE)
                {
                    Ret = EXTERNAL_INT2_INTERRUPT_FALLING_EDGE_SET();
                }
                else if (int_obj ->Interrupt_Edge == INTERRUPR_RAISING_EDGE)
                {
                    Ret = EXTERNAL_INT2_INTERRUPT_RAISING_EDGE_SET();
                }
                else
                {
                    Ret = E_NOK;
                }
                break;
            default :
                Ret = E_NOK;
                break;
        }
    }
    return(Ret);
}
/**
 * @breif
 * @param int_obj
 @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
static STD_ReturnType INTERRUPT_INTx_Pin_Init(const interrupt_INTx_t* int_obj)
{
    STD_ReturnType Ret=E_OK;
    if(NULL ==  int_obj)
    {
        Ret=E_NOK;
    }
    else
    {
        Ret = gpio_pin_intializtion(&(int_obj ->mcu_pin));
    }
    return(Ret);
}
/**
 * @breif
 * @param int_obj
 @return statues of the function
  *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
static STD_ReturnType INTERRUPT_INTx_Clear_Flag(const interrupt_INTx_t* int_obj)
{
    STD_ReturnType Ret=E_OK;
    if(NULL ==  int_obj)
    {
        Ret=E_NOK;
    }
    else
    {
        switch(int_obj ->Interrupt_Source)
        {
             case INTERRUPR_EXTERNAL_INT0 :
                EXTERNAL_INT0_INTERRUPT_FLAG_CLEAR();
                break;
            case INTERRUPR_EXTERNAL_INT1 :
                EXTERNAL_INT1_INTERRUPT_FLAG_CLEAR();
                break;
            case INTERRUPR_EXTERNAL_INT2 :
                EXTERNAL_INT2_INTERRUPT_FLAG_CLEAR();
                break;
            default :
                Ret = E_NOK;
                break;
        }
    }
    return(Ret);
}

/**
 * @breif
 * @param int_obj
 @return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
static STD_ReturnType INTERRUPT_INTx_SET_INTERRUPT_HABDLER(const interrupt_INTx_t* int_obj)
{
    STD_ReturnType Ret=E_OK;
    if(NULL ==  int_obj)
    {
        Ret=E_NOK;
    }
    else
    {
        switch(int_obj->Interrupt_Source)
        {
             case INTERRUPR_EXTERNAL_INT0 :
                 Ret = INT0_SET_INTERRUPT_HABDLER(int_obj->ptr_External_Inturrupt);
                break;
            case INTERRUPR_EXTERNAL_INT1 :
                Ret = INT1_SET_INTERRUPT_HABDLER(int_obj->ptr_External_Inturrupt);
                break;
            case INTERRUPR_EXTERNAL_INT2 :
                Ret = INT2_SET_INTERRUPT_HABDLER(int_obj->ptr_External_Inturrupt);
                break;
            default :
                Ret = E_NOK;
                break;
        }
    }
    return(Ret);
}
/**
 * 
 * @param Interrupt_Handler
@return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
static STD_ReturnType INT0_SET_INTERRUPT_HABDLER(void (*Interrupt_Handler)(void))
{
    STD_ReturnType Ret = E_OK;
    if(NULL == Interrupt_Handler)
    {
        Ret = E_NOK;
    }
    else
    {
        INT0_Interrupt_Handler = Interrupt_Handler;
    }
    return(Ret);
}
/**
 *   
 * @param Interrupt_Handler
@return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
static STD_ReturnType INT1_SET_INTERRUPT_HABDLER(void (*Interrupt_Handler)(void))
{
    STD_ReturnType Ret = E_OK;
    if(NULL == Interrupt_Handler)
    {
        Ret = E_NOK;
    }
    else
    {
        INT1_Interrupt_Handler = Interrupt_Handler;
    }
    return(Ret);
}
/**
 * 
 * @param Interrupt_Handler
@return statues of the function
 *           (E_OK)  : means the function done successfully
 *           (E_Nok) : means the function has issue while perform the action
 */
static STD_ReturnType INT2_SET_INTERRUPT_HABDLER(void (*Interrupt_Handler)(void))
{
    STD_ReturnType Ret = E_OK;
    if(NULL == Interrupt_Handler)
    {
        Ret = E_NOK;
    }
    else
    {
        INT2_Interrupt_Handler = Interrupt_Handler;
    }
    return(Ret);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

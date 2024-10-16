#include <stdio.h>

/*typedef union{
    struct{
        unsigned char SELF_LATC0 : 1 ;
        unsigned char SELF_LATC1 : 1 ;
        unsigned char SELF_LATC2 : 1 ;
        unsigned char SELF_LATC3 : 1 ;
        unsigned char SELF_LATC4 : 1 ;
        unsigned char SELF_LATC5 : 1 ;
        unsigned char SELF_LATC6 : 1 ;
        unsigned char SELF_LATC7 : 1 ;
    };
    unsigned char SELF_LATC_REGISTER;
}SELF_LATC;

typedef union{
    struct{
        unsigned char SELF_SSBMX : 4 ;
        unsigned char SELF_CKP   : 1 ;
        unsigned char SELF_SSPEN : 1 ;
        unsigned char SELF_SSPOV : 1 ;
        unsigned char SELF_WCOL  : 1 ;
    };
    unsigned char SELF_SSBCON1_REGISTER;
}SELF_SSBCON1;

#define SELF_SSBCON1_REG ((volatile SELF_SSBCON1*)0xFC6)
#define D_SELF_SSBCON1_REG (*((volatile SELF_SSBCON1*)0xFC6))

#define SELF_lATC_REG ((volatile SELF_LATC *)0xF8B)
#define D_SELF_lATC_REG (*((volatile SELF_LATC *)0xF8B))

#define HWREG8(X) (*(volatile char *)(X))
#define SARA_LATC (HWREG8 (0XF8B) )
#define SARA_TRISC (HWREG8 (0XF94))
#define Set_Bit(Register_Address,Bit_Position) ((Register_Address) |= (1 << (Bit_Position)))
#define Clear_Bit(Register_Address,Bit_Position) ((Register_Address) &= ~(1 << (Bit_Position)))
#define Toggle_Bit(Register_Address,Bit_Position) ((Register_Address) ^= (1 << (Bit_Position)))
int main()
{
   
}
*/
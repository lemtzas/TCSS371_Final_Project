#include "register.h"


char* register_set(Register* this, unsigned short value)
{
    (*this) = value & 0xFFFF; //mask maximum size
    return 0; //no errors possible
}

char* register_get(Register* this,unsigned short *result)
{
    if(!result) return "Result location not given.";
    (*result) = (*this);
    return 0; //no errors
}

char* register_get_bit(Register* this,int bit,Bit *result)
{
    if(bit<0 || bit>15) return "Bit location out of range.";
    (*result) = ((*this)>>bit)&0x0001;
    return 0; //no errors
}

char* register_set_bit(Register* this, int bit, Bit state)
{
    if(bit<0 || bit>15) return "Bit location out of range.";
    Register mask = 1 << bit;
    if( state )
        (*this) = (*this) | mask;
    else
        (*this) = (*this) & ~mask;
    return 0; //no errors
}

//int main()
//{
//    Register r = 3;
//    unsigned short s = 5;
//    printf("base\t\t%4x = %4x\n\n", r, s);
//    register_get(&r,&s);
//    printf("get\t\t%4x = %4x\n", r, s);
//    register_set(&r,0xBAB5);
//    printf("set BAB5\t%4x = %4x\n", r, s);
//    register_get(&r,&s);
//    printf("get\t\t%4x = %4x\n", r, s);
//    register_get_bit(&r,0,&s);
//    printf("get bit0\t%4x = %4x\n", r, s);
//    register_get_bit(&r,1,&s);
//    printf("get bit1\t%4x = %4x\n", r, s);
//    register_get_bit(&r,2,&s);
//    printf("get bit2\t%4x = %4x\n", r, s);
//    register_get_bit(&r,3,&s);
//    printf("get bit3\t%4x = %4x\n", r, s);
//    register_get_bit(&r,4,&s);
//    printf("get bit4\t%4x = %4x\n", r, s);
//    register_get_bit(&r,15,&s);
//    printf("get bit15\t%4x = %4x\n", r, s);
//    register_set_bit(&r,3,BIT_ON);
//    register_get_bit(&r,3,&s);
//    printf("set3bit1\t%4x = %4x\n", r, s);
//    register_set_bit(&r,3,BIT_OFF);
//    register_get_bit(&r,3,&s);
//    printf("set3bit0\t%4x = %4x\n", r, s);
//    return 0;
//}

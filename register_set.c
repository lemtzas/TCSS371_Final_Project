#include "register_set.h"

int registerSet_set_register(RegisterSet* this, int register_id, Register value)
{
    //TODO: Error detection
    (*this)[register_id] = value;
    return 0;//no errors
}

int registerSet_get_register(RegisterSet* this, int register_id, Register *result)
{
    //TODO: Error detection
    (*result) = (*this)[register_id];
    return 0; //no errors
}


//int main()
//{
//    RegisterSet rs;
//    Register r;
//    unsigned short s;
//    registerSet_get_register(&rs,0,&r);
//    register_get(&r,&s);
//    printf("0\tget\t\t%4x\n",s);
//    registerSet_set_register(&rs,0,0xBABE);
//    registerSet_get_register(&rs,0,&r);
//    register_get(&r,&s);
//    printf("0\tset 0xBABE\t%4x\n",s);
//
//
//    registerSet_get_register(&rs,7,&r);
//    register_get(&r,&s);
//    printf("7\tget\t\t%4x\n",s);
//    registerSet_set_register(&rs,7,0xB0B0);
//    registerSet_get_register(&rs,7,&r);
//    register_get(&r,&s);
//    printf("7\tset 0xB0B0\t%4x\n",s);
//
//
//    registerSet_get_register(&rs,0,&r);
//    register_get(&r,&s);
//    printf("0\tget\t\t%4x\n",s);
//    registerSet_set_register(&rs,0,0xBAB5);
//    registerSet_get_register(&rs,0,&r);
//    register_get(&r,&s);
//    printf("0\tset 0xBAB5\t%4x\n",s);
//    return 0;
//}

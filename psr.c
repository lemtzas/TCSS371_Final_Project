#include "psr.h"

char* PSR_set_n(PSR* this, Bit n){register_set_bit((Register*)this,15,n);return 0;}
char* PSR_get_n(PSR* this, Bit *n){register_get_bit((Register*)this,15,n);return 0;}
char* PSR_set_z(PSR* this, Bit z){register_set_bit((Register*)this,14,z);return 0;}
char* PSR_get_z(PSR* this, Bit *z){register_get_bit((Register*)this,14,z);return 0;}
char* PSR_set_c(PSR* this, Bit c){register_set_bit((Register*)this,13,c);return 0;}
char* PSR_get_c(PSR* this, Bit *c){register_get_bit((Register*)this,13,c);return 0;}
char* PSR_set_o(PSR* this, Bit o){register_set_bit((Register*)this,12,o);return 0;}
char* PSR_get_o(PSR* this, Bit *o){register_get_bit((Register*)this,12,o);return 0;}
char* PSR_set_nzco(PSR* this, Bit n, Bit z, Bit c, Bit o)
{
    PSR_set_n(this,n);
    PSR_set_z(this,z);
    PSR_set_c(this,c);
    PSR_set_o(this,o);
    return 0;
}
char* PSR_get_nzco(PSR* this, Bit *n, Bit *z, Bit *c, Bit *o)
{
    PSR_get_n(this,n);
    PSR_get_z(this,z);
    PSR_get_c(this,c);
    PSR_get_o(this,o);
    return 0;
}

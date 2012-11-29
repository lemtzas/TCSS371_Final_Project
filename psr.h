#ifndef PSR_H
#define PSR_H
#include "register.h"

typedef Register PSR;   // unlike the register in the LC-3, the condition code flags in this register are
                        // PSR[15..12]; PSR[15]=N, PSR[14]=Z, PSR[13]=C, and PSR[12]=O

//sets the registers as named
//does not clear unset registers
char* PSR_set_n(PSR* this, Bit n);
char* PSR_get_n(PSR* this, Bit *n);
char* PSR_set_z(PSR* this, Bit z);
char* PSR_get_z(PSR* this, Bit *z);
char* PSR_set_c(PSR* this, Bit c);
char* PSR_get_c(PSR* this, Bit *c);
char* PSR_set_o(PSR* this, Bit o);
char* PSR_get_o(PSR* this, Bit *o);
char* PSR_set_nzco(PSR* this, Bit n, Bit z, Bit c, Bit o);
char* PSR_get_nzco(PSR* this, Bit *n, Bit *z, Bit *c, Bit *o);

#endif

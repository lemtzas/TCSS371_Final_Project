#ifndef REGISTER_SET_H
#define REGISTER_SET_H

#include "register.h"

typedef Register RegisterSet[8];

//void registerSet_initialize(RegisterSet*); //unnecessary?
int registerSet_set_register(RegisterSet* this, int register_id, Register value);
int registerSet_get_register(RegisterSet* this, int register_id, Register *result);

#endif

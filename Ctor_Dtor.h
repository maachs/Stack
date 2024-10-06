#ifndef CTOR_DTOR_
#define CTOR_DTOR_

#include "Globals.h"
#include "Dump.h"
#include "Verify.h"

ErrorCode StackCtor(Stack_t* stk);

void StackDtor(Stack_t* stk);

void PoisonData(Stack_t* stk);

#endif

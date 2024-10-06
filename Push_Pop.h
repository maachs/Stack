#ifndef PUSH_POP_
#define PUSH_POP_

#include "Globals.h"
#include "Dump.h"
#include "Verify.h"

ErrorCode StackPush(Stack_t* stk, StackElem value);

ErrorCode StackPop(Stack_t* stk, StackElem* pop);

#endif

#ifndef HEADERS_
#define HEADERS_

#include "Globals.h"

ErrorCode StackCtor(Stack_t* stk);

void StackDtor(Stack_t* stk);

void PoisonData(Stack_t* stk);

void StackDump(Stack_t* stk, const char* file, const int line, const char* func);

void PrintError(Stack_t* stk);

ErrorCode StackPush(Stack_t* stk, StackElem value);

ErrorCode StackPop(Stack_t* stk, StackElem* pop);

ErrorCode ReallocPush(Stack_t* stk);

ErrorCode ReallocPop(Stack_t* stk);

#endif

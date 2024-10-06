#ifndef DUMPER_
#define DUMPER_

#include "Globals.h"
#include "Verify.h"

void StackDump(Stack_t* stk, const char* file, const int line, const char* func);

void PrintError(Stack_t* stk);

#endif

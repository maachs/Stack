#ifndef GLOBALS_
#define GLOBALS_

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define DEBUG

typedef double StackElem;

const int CAPACITY_MIN = 10;

StackElem POISON = 666;

struct Stack_t
{
    #ifdef DEBUG
        const char* name;
        const char* file;
        const int   line;
    #endif

    StackElem* data;
    int size;
    int capacity;
    int error_code;
};

enum Step
{
    POP_STEP  = 2,
    PUSH_STEP = 2
};

enum ErrorCode
{
    CTOR_ERROR     = 2,
    STK_ERROR      = 3,
    PUSH_ERROR     = 4,
    POP_ERROR      = 5,
    SUCCESS        = 0,
    SIZE_ERROR     = 6,
    CAPACITY_ERROR = 7
};

#ifdef DEBUG
    #define INIT(var) #var, __FILE__, __LINE__
    #define VERIFY_STACK(var)                              \
        if (VerifyStack(var) != SUCCESS)                   \
        {                                                  \
            StackDump(var, __FILE__, __LINE__, __func__);  \
            assert(0);                                     \
        }
#else
    #define INIT(var)
    #define VERIFY_STACK(var)
#endif

#endif

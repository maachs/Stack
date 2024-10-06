#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <TXlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define DEBUG

typedef double StackElem;

const int CAPACITY_MIN = 10;

const StackElem POISON = -331272.2432;

const StackElem CANARY = 0xDED;

const StackElem EPS = 0.001;

struct Stack_t
{
    #ifdef DEBUG
        StackElem canary1;
        const char* name;
        const char* file;
        const int   line;
    #endif

    StackElem* data;
    int size;
    int capacity;
    int error_code;

    #ifdef DEBUG
        StackElem canary2;
    #endif
};

enum Step
{
    POP_STEP  = 2,
    PUSH_STEP = 2
};

enum ErrorCode
{
    DATA_ERROR        = 1,
    CANARY_ERROR      = 2,
    STK_ERROR         = 3,
    DATA_CANARY_ERROR = 4,
    SUCCESS           = 0,
    SIZE_ERROR        = 6,
    CAPACITY_ERROR    = 7
};

#ifdef DEBUG
    #define INIT(var) CANARY, #var, __FILE__, __LINE__,
    #define ON_DEBUG(...) __VA_ARGS__
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

#ifndef GLOBALS_H_
#define GLOBALS_H_

//#include <TXlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

#define DEBUG

typedef double StackElem;

const int CAPACITY_MIN = 10;

const StackElem POISON = -331272.2;

const StackElem CANARY = 0xDED;

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

    uint64_t struct_hash;
    uint64_t data_hash;
    uint64_t buffer_data_hash;
    uint64_t buffer_struct_hash;

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
    DATA_ERROR          = 1,
    STRUCT_CANARY_ERROR = 2,
    STK_ERROR           = 3,
    DATA_CANARY_ERROR   = 4,
    SUCCESS             = 0,
    SIZE_ERROR          = 6,
    CAPACITY_ERROR      = 7,
    CAPACITY_EQUAL_SIZE = 5,
    DATA_HASH_ERROR     = 8,
    STRUCT_HASH_ERROR   = 9,
    CALLOC_ERROR        = 10
};

#ifdef DEBUG
    #define INIT(var) CANARY, #var, __FILE__, __LINE__,
    #define VERIFY_STACK(var1)                                    \
        if (VerifyStack(var1) != SUCCESS)                         \
        {                                                         \
            StackDump(var1, __FILE__, __LINE__, __func__);        \
            StackDtor(var1);                                      \
            assert(0);                                            \
        }
    #define CALC_HASH                                                                                                                                   \
            stk->buffer_struct_hash = CalcHash((char*) stk + sizeof(StackElem) + sizeof(char*) * 2 + sizeof(int), sizeof(StackElem*) + sizeof(int) * 3);\
            stk->buffer_data_hash   = CalcHash((char*) (stk->data), sizeof(double) * stk->capacity);
#else
    #define INIT(var)
    #define VERIFY_STACK(var1, var2)
    #define CALC_HASH
#endif


uint64_t CalcHash(char* data, int size);

ErrorCode VerifyStack(Stack_t* stk);

#endif

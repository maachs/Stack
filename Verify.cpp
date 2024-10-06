#include "Verify.h"

int VerifyStack(Stack_t* stk)
{
    if (stk == NULL)
    {
        stk->error_code = STK_ERROR;
    }

    if (stk->data == NULL)
    {
        stk->error_code = CTOR_ERROR;
    }

    if (stk->data == NULL)
    {
        stk->error_code = PUSH_ERROR;
    }

    if (stk->data == NULL)
    {
        stk->error_code = POP_ERROR;
    }

    if (stk->size <= 0)
    {
        stk->error_code = SIZE_ERROR;
    }

    if (stk->capacity <= 0)
    {
        stk->error_code = CAPACITY_ERROR;
    }

    return stk->error_code;
}


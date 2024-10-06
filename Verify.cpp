#include "Verify.h"

int VerifyStack(Stack_t* stk)
{
    if (stk == NULL)
    {
        stk->error_code = STK_ERROR;
    }
    else if (stk->data == NULL)
    {
        stk->error_code = DATA_ERROR;
    }
    else if (stk->canary1 - CANARY < EPS || stk->canary2 - CANARY < EPS)
    {
        stk->error_code = CANARY_ERROR;
    }
    else if (stk->data[-1] - CANARY < EPS || stk->data[stk->capacity] - CANARY < EPS)
    {
        stk->error_code = DATA_CANARY_ERROR;
    }
    else
    {
        return SUCCESS;
    }
    /*if (stk->size <= 0)
    {
        stk->error_code = SIZE_ERROR;
    }

    if (stk->capacity <= 0)
    {
        stk->error_code = CAPACITY_ERROR;
    }*/

    return stk->error_code;
}


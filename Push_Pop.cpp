#include "Push_Pop.h"
#include "Ctor_Dtor.h"

ErrorCode StackPush(Stack_t* stk, StackElem value)
{
    assert(stk);
    assert(stk->data);

    if (stk->size == stk->capacity)
    {
        stk->data = (StackElem*) realloc(stk->data, stk->size * PUSH_STEP * sizeof(StackElem)) + 1;

        stk->data[stk->capacity] = POISON;

        PoisonData(stk);

        stk->capacity *= 2;

        stk->data[stk->capacity] = CANARY;
    }

    stk->data[stk->size + 1] = value;
    stk->size++;

    VERIFY_STACK(stk);

    return SUCCESS;
}

ErrorCode StackPop(Stack_t* stk, StackElem* pop)
{
    VERIFY_STACK(stk);

    *pop = stk->data[stk->size];
    stk->size--;

    if (stk->size < 0)
    {
        stk->error_code = SIZE_ERROR;
    }

    VERIFY_STACK(stk);

    stk->data[stk->size + 1] = POISON;

    if (stk->size == stk->capacity / 4)
    {
        stk->data = (StackElem*)realloc(stk->data, (stk->capacity / POP_STEP) * sizeof(StackElem)) + 1;

        stk->capacity /= 2;

        stk->data[stk->capacity] = CANARY;

        if (stk->capacity <= 0)
        {
            stk->error_code = CAPACITY_ERROR;
        }

        VERIFY_STACK(stk);
    }

    return SUCCESS;
}

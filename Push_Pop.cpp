#include "Push_Pop.h"

ErrorCode StackPush(Stack_t* stk, StackElem value)
{
    //VERIFY_STACK(stk);

    if (stk->size == stk->capacity)
    {
        stk->data = (StackElem*) realloc(stk->data, stk->size * PUSH_STEP * sizeof(StackElem));

        VERIFY_STACK(stk);

        stk->capacity *= 2;
    }
    stk->data[stk->size] = value;
    stk->size++;

    //VERIFY_STACK(stk);

    return SUCCESS;
}

ErrorCode StackPop(Stack_t* stk, StackElem* pop)
{
    VERIFY_STACK(stk);

    *pop = stk->data[stk->size];
    stk->size--;

    VERIFY_STACK(stk);

    stk->data[stk->size+1] = POISON;
    if (stk->size == stk->capacity / 4)
    {
        stk->data = (StackElem*)realloc(stk->data, (stk->capacity / POP_STEP) * sizeof(StackElem));

        stk->capacity /= 2;

        VERIFY_STACK(stk);
    }

    VERIFY_STACK(stk);

    return SUCCESS;
}

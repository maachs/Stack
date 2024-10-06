#include "Ctor_Dtor.h"

ErrorCode StackCtor(Stack_t* stk)
{
    assert(stk);
    stk->data = (StackElem*)calloc(CAPACITY_MIN, sizeof(StackElem)) + 1;

    #ifdef DEBUG
        stk->canary2 = CANARY;
    #endif

    stk->size = 0;
    stk->capacity = CAPACITY_MIN;

    PoisonData(stk);

    stk->data[-1] = CANARY;
    stk->data[CAPACITY_MIN] = CANARY;

    VERIFY_STACK(stk);

    return SUCCESS;
}

void StackDtor(Stack_t* stk)
{
    assert(stk);

    free(stk->data);
    stk->data = NULL;

    stk->capacity = CAPACITY_MIN;
    stk->size = 0;
}

void PoisonData(Stack_t* stk)
{
    for (int elem = stk->size; elem < stk->capacity; elem++)
    {
        stk->data[elem] = POISON;
    }
}

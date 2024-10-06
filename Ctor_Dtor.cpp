#include "Ctor_Dtor.h"

ErrorCode StackCtor(Stack_t* stk)
{
    assert(stk);
    stk->data = (StackElem*)calloc(CAPACITY_MIN, sizeof(StackElem));

    stk->size = 0;
    stk->capacity = CAPACITY_MIN;

    PoisonData(stk);

    //VERIFY_STACK(stk);

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
    for (int i = stk->size; i < stk->capacity; i++)
    {
        stk->data[i] = POISON;
    }
}

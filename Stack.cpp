#include <stdio.h>
#include <assert.h>

typedef double StackElem;

const int CAPACITYMIN = 10;

StackElem POISON = 666;

struct Stack_t
{
    StackElem* data;
    int size;
    int capacity;
};

enum ErrorCode
{
    CTOR_ERROR     = 2,
    DTOR_ERROR     = 3,
    PUSH_ERROR     = 4,
    POP_ERROR      = 5,
    SUCCESS        = 0,
    ERR            = 1,
    SIZE_ERROR     = 6,
    CAPACITY_ERROR = 7
};
ErrorCode StackPush(Stack_t* stk, StackElem value);

ErrorCode StackPop(Stack_t* stk, StackElem* pop);

ErrorCode StackCtor(Stack_t* stk);

ErrorCode StackDtor(Stack_t* stk);

void StackDump(Stack_t* stk);

void PoisonData(Stack_t* stk);

int StackAssert(Stack_t* stk);

int main()
{
    Stack_t stk = {};

    StackCtor(&stk);
    StackAssert(&stk);

    StackPush(&stk, 10);
    StackAssert(&stk);

    StackPush(&stk, 20);
    StackAssert(&stk);

    StackElem pop = 0;

    StackPop(&stk, &pop);
    StackAssert(&stk);

    StackDump(&stk);
    StackAssert(&stk);

    StackDtor(&stk);

    return 0;
}

ErrorCode StackCtor(Stack_t* stk)
{
    assert(stk);

    stk->data = (StackElem*)calloc(CAPACITYMIN, sizeof(StackElem));
    stk->size = 0;
    stk->capacity = CAPACITYMIN;

    PoisonData(stk);

    return SUCCESS;
}

ErrorCode StackDtor(Stack_t* stk)
{
    assert(stk);

    free(stk->data);
    stk->data = NULL;

    return SUCCESS;
}

ErrorCode StackPush(Stack_t* stk, StackElem value)
{
    assert(stk);
    assert(stk->data);

    if (stk->size == stk->capacity)
    {
        stk->data = (StackElem*) realloc(stk->data, stk->size * 2 * sizeof(StackElem));
        stk->capacity *= 2;
    }
    stk->data[stk->size] = value;
    stk->size++;

    return SUCCESS;
}

ErrorCode StackPop(Stack_t* stk, StackElem* pop)
{
    assert(stk);
    assert(stk->data);

    *pop = stk->data[stk->size];
    stk->size--;
    stk->data[stk->size+1] = POISON;
    if (stk->size == stk->capacity / 4)
    {
        stk->data = (StackElem*)realloc(stk->data, (stk->capacity / 2) * sizeof(StackElem));
        stk->capacity /= 2;
    }

    return SUCCESS;
}

void StackDump(Stack_t* stk)
{
    assert(stk);
    assert(stk->data);

    printf("data\n");
    for (int elem = 0; elem < stk->size; elem++)
    {
        printf("   %lg\n", stk->data[elem]);
    }

    printf("capacity %d\n", stk->capacity);
    printf("size %d\n", stk->size);
}

void PoisonData(Stack_t* stk)
{
    assert(stk);
    assert(stk->data);

    for (int i = stk->size; i < stk->capacity; i++)
    {
        stk->data[i] = POISON;
    }
}

int StackAssert(Stack_t* stk)
{
    if (stk->size < 0){return SIZE_ERROR;}

    if (stk->capacity < 0){return CAPACITY_ERROR;}
    return SUCCESS;
}

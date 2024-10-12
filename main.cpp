#include "Globals.h"
#include "Headers.h"

int main()
{
    Stack_t stk = {INIT(stk)};

    StackCtor(&stk);

    for (StackElem i = 0; i < 4; i++)
    {
        StackPush(&stk, i);
    }

    StackElem value1 = 0;
    StackElem value2 = 0;
    StackElem value3 = 0;
    StackElem value4 = 0;
    StackElem value5 = 0;
    StackPop(&stk, &value1);
    StackPop(&stk, &value2);
    StackPop(&stk, &value3);
    StackPop(&stk, &value4);
    StackPop(&stk, &value5);

    StackDump(&stk, __FILE__, __LINE__, __func__);

    StackDtor(&stk);

    return 0;
}

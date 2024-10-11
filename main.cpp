#include "Globals.h"
#include "Headers.h"
#include "TXlib.h"

int main()
{
    Stack_t stk = {INIT(stk)};

    StackCtor(&stk);

    for (StackElem i = 0; i < 80; i++)
    {
        StackPush(&stk, i);
    }

    StackElem value = 0;
    StackPop(&stk, &value);

    StackDump(&stk, __FILE__, __LINE__, __func__);

    StackDtor(&stk);

    return 0;
}

#include "Globals.h"
#include "Ctor_Dtor.h"
#include "Push_Pop.h"
#include "Dump.h"
#include "Verify.h"

int main()
{
    Stack_t stk = {INIT(stk)};

    StackCtor(&stk);
    VERIFY_STACK(&stk);

    StackPush(&stk, 10);
    VERIFY_STACK(&stk);

    StackPush(&stk, 20);
    VERIFY_STACK(&stk);

    StackPush(&stk, 30);
    VERIFY_STACK(&stk);

    StackPush(&stk, 40);
    VERIFY_STACK(&stk);

    StackPush(&stk, 50);
    VERIFY_STACK(&stk);

    StackElem pop = 0;

    StackPop(&stk, &pop);
    VERIFY_STACK(&stk);

    StackDump(&stk, __FILE__, __LINE__, __func__);
    VERIFY_STACK(&stk);

    StackDtor(&stk);

    return 0;
}

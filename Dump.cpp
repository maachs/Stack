#include "Dump.h"

void StackDump(Stack_t* stk, const char* file, const int line, const char* func)
{

    printf("\nStk_t [0x%p]\n", stk);

    printf("called from %s : %d (%s)\n", file, line, func);

    printf("named \"%s\" born at %s:%d\n", stk->name, stk->file, stk->line);

    printf("data\n{\n");
    for (int elem = 0; elem < stk->capacity; elem++)
    {
        printf("   [%d] = %lg\n", elem + 1, stk->data[elem]);
    }
    printf("}\n");

    printf("capacity %d\n", stk->capacity);
    printf("size %d\n", stk->size);

    if (stk->error_code != SUCCESS)
    {
        PrintError(stk);
    }
}

void PrintError(Stack_t* stk)
{
    switch (stk->error_code)
    {
        case DATA_ERROR:
            printf("Data == NULL\n");
            break;
        case SIZE_ERROR:
            printf("Size ERROR\n");
            break;
        case CAPACITY_ERROR:
            printf("Capacity ERROR\n");
            break;
        case STK_ERROR:
            printf("Stk = NULL\n");
            break;
        default:
            printf("unspecified error\n");
    }
}


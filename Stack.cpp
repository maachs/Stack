#include "Headers.h"

ErrorCode StackCtor(Stack_t* stk)
{
    assert(stk);

    stk->data = (StackElem*)calloc(CAPACITY_MIN + 2, sizeof(StackElem)) + 1;

    #ifdef DEBUG
        stk->canary2 = CANARY;
    #endif

    stk->size = 0;
    stk->capacity = CAPACITY_MIN;

    PoisonData(stk);

    #ifdef DEBUG
        stk->data[-1] = CANARY;
        stk->data[CAPACITY_MIN] = CANARY;
    #endif

    CALC_HASH;
    stk->data_hash   = stk->buffer_data_hash; //first calc hash
    stk->struct_hash = stk->buffer_struct_hash;

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

ErrorCode StackPush(Stack_t* stk, StackElem value)
{
    CALC_HASH;
    VERIFY_STACK(stk);
    stk->data_hash   = stk->buffer_data_hash;
    stk->struct_hash = stk->buffer_struct_hash;

    if (stk->size == stk->capacity - 1)
    {
        printf("  ");
        ReallocPush(stk);
    }

    stk->data[stk->size] = value;
    stk->size++;

    CALC_HASH;
    stk->data_hash   = stk->buffer_data_hash;
    stk->struct_hash = stk->buffer_struct_hash;

    return SUCCESS;
}
void ReallocPush(Stack_t* stk)
{
    assert(stk);

    stk->data = (StackElem*) realloc(stk->data - 1, stk->capacity * PUSH_STEP * sizeof(StackElem) + 2) + 1;

    if (stk->data == NULL)
    {
        stk->error_code = CALLOC_ERROR;
    }

    stk->data[stk->capacity] = POISON;

    stk->capacity *= 2;

    PoisonData(stk);

    stk->data[stk->capacity] = CANARY;
}

ErrorCode StackPop(Stack_t* stk, StackElem* value)
{
    assert(value);

    CALC_HASH;
    VERIFY_STACK(stk);
    stk->data_hash   = stk->buffer_data_hash;
    stk->struct_hash = stk->buffer_struct_hash;

    *value = stk->data[stk->size];
    stk->size--;

    stk->data[stk->size + 1] = POISON;

    if ((stk->size == stk->capacity / 4) && (stk->size > CAPACITY_MIN))
    {
        printf("%d\n", stk->size);
        printf("%d\n", stk->capacity);
        ReallocPop(stk);
    }

    CALC_HASH;
    stk->data_hash   = stk->buffer_data_hash;
    stk->struct_hash = stk->buffer_struct_hash;
    VERIFY_STACK(stk);

    return SUCCESS;
}

void ReallocPop(Stack_t* stk)
{
    stk->data = (StackElem*)realloc(stk->data - 1, (stk->capacity / POP_STEP) * sizeof(StackElem)) + 1;

    if (stk->data == NULL)
    {
        stk->error_code = CALLOC_ERROR;
    }

    stk->capacity /= 2;

    stk->data[stk->capacity] = CANARY;
}

uint64_t CalcHash (char* data, int size)
{
    uint64_t hash = 5381;

    for (int elem = 0; elem < size; elem++)
    {
        hash += (hash * 33) ^ data[elem];
    }

    return hash;
}

void StackDump(Stack_t* stk, const char* file, const int line, const char* func)
{
    fprintf(stdout, "\nStk_t [0x%p]\n", stk);

    fprintf(stdout, "called from %s : %d (%s)\n", file, line, func);

    fprintf(stdout, "named \"%s\" born at %s:%d\n", stk->name, stk->file, stk->line);

    if (stk == NULL)
    {
        fprintf(stdout, "Dump stk = null");
    }
    else
    {
        printf("____CANARIES____\n");
        fprintf(stdout, "struct canary 1 = %lx\n", (unsigned long int)stk->canary1);
        fprintf(stdout, "struct canary 2 = %lx\n", (unsigned long int)stk->canary2);

        fprintf(stdout, "data canary 1   = %lx\n", (unsigned long int)stk->data[-1]);
        fprintf(stdout, "data canary 2   = %lx\n", (unsigned long int)stk->data[stk->capacity]);

        printf("___HASH___\n");
        fprintf(stdout, "struct hash = %lx\n", (unsigned long int)stk->struct_hash);
        fprintf(stdout, "data hash   = %lx\n", (unsigned long int)stk->data_hash);

        fprintf(stdout, "buffer struct hash = %lx\n", (unsigned long int)stk->buffer_struct_hash);
        fprintf(stdout, "buffer data hash   = %lx\n", (unsigned long int)stk->buffer_data_hash);

        if (stk->data != NULL)
        {
            printf("data\n{\n");
            for (int elem = 0; elem < stk->capacity + 2; elem++)
            {
                fprintf(stdout, "   [%d] = %lg\n", elem - 1, stk->data[elem - 1]);
            }
            printf("}\n");
        }

        printf("capacity %d\n", stk->capacity);
        printf("size %d\n", stk->size);

        stk->error_code = VerifyStack(stk);

        if (stk->error_code != SUCCESS)
        {
            PrintError(stk);
        }
    }
}

void PrintError(Stack_t* stk)
{
    switch (stk->error_code)
    {
        case CAPACITY_EQUAL_SIZE:
            printf("\n<<<<<<<Capacity = size\n\n");
            break;
        case DATA_ERROR:
            printf("\n<<<<<<<Data == NULL\n\n");
            break;
        case SIZE_ERROR:
            printf("\n<<<<<<<Size ERROR\n\n");
            break;
        case CAPACITY_ERROR:
            printf("\n<<<<<<<Capacity ERROR\n\n");
            break;
        case STK_ERROR:
            printf("\n<<<<<<<Stk = NULL\n\n");
            break;
        case STRUCT_CANARY_ERROR:
            printf("\n<<<<<<<Struct canary ERROR\n\n");
            break;
        case DATA_CANARY_ERROR:
            printf("\n<<<<<<<Data canary ERROR\n\n");
            break;
        case DATA_HASH_ERROR:
            printf("\n<<<<<<<Data hash ERROR\n\n");
            break;
        case STRUCT_HASH_ERROR:
            printf("\n<<<<<<<Struct hash ERROR\n\n");
            break;
        default:
            printf("\n<<<<<<<Unspecified ERROR\n\n");
    }
}

ErrorCode VerifyStack(Stack_t* stk)
{
    if (stk->size < 0)
    {
        return SIZE_ERROR;
    }
    else if (stk->capacity <= 0)
    {
        return CAPACITY_ERROR;
    }
    else if (stk->capacity < stk->size)
    {
        return CAPACITY_EQUAL_SIZE;
    }
    else if (stk == NULL)
    {
        return STK_ERROR;
    }
    else if (stk->data == NULL)
    {
        return DATA_ERROR;
    }
    else if ((unsigned long int)stk->canary1 != (unsigned long int)CANARY ||
             (unsigned long int)stk->canary2 != (unsigned long int)CANARY)
    {
        return STRUCT_CANARY_ERROR;
    }
    else if ((unsigned long int)stk->data[-1] != (unsigned long int)CANARY ||
             (unsigned long int)stk->data[stk->capacity] != (unsigned long int)CANARY)
    {
        return DATA_CANARY_ERROR;
    }
    else if (stk->buffer_data_hash != stk->data_hash)
    {
        return DATA_HASH_ERROR;
    }
    else if (stk->buffer_struct_hash != stk->struct_hash)
    {
        return STRUCT_HASH_ERROR;
    }
    else
    {
        return SUCCESS;
    }
}






#include "../header/strix.h"

strix *strix_create(const char *str)
{
    if (!str)
    {
        return NULL;
    }

    strix *string = (strix *)allocate(sizeof(strix));
    if (!string)
    {
        return NULL;
    }

    string->len = strlen(str);
    string->str = (char *)allocate(string->len);
    if (!string->str)
    {
        return NULL;
    }

    if (!memmove(string->str, str, string->len))
    {
        return NULL;
    }

    return string;
}

strix *strix_duplicate(strix *string)
{
    if (!string)
    {
        return NULL;
    }

    if (!string->len)
    {
        return NULL;
    }

    strix *duplicate = (strix *)allocate(sizeof(strix));
    if (!duplicate)
    {
        return NULL;
    }

    duplicate->len = string->len;
    duplicate->str = (char *)allocate(sizeof(duplicate->len));
    if (!duplicate->str)
    {
        return NULL;
    }

    if (!memcpy(duplicate->str, string->str, string->len))
    {
        return NULL;
    }

    return duplicate;
}

void *strix_free(strix *string)
{
    deallocate(string->str);
    deallocate(string);
}

int main(void)
{
    strix *string = strix_create("hello");
    strix *new = strix_duplicate(string);
    fprintf(stdout, STRIX_FORMAT "\n", STRIX_PRINT(string));
}
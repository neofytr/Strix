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

void *strix_free(strix *string)
{
    deallocate(string->str);
    deallocate(string);
}

int main(void)
{
    strix *string = conv_to_strix("hello");
    fprintf(stdout, STRIX_FORMAT "\n", STRIX_PRINT(string));
}
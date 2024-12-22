#ifndef A4921AE8_DB77_42E3_A83E_9D3D0C69BDE0
#define A4921AE8_DB77_42E3_A83E_9D3D0C69BDE0

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../allocator/allocator.h"

typedef struct
{
    char *str;
    size_t len;
} strix;

#define STRIX_FORMAT "%.*s"
#define STRIX_PRINT(string) (int)(string)->len, (string)->str

strix *strix_create(const char *str);
strix *strix_duplicate(strix *string); // returns a null strix if string is of length 0

void *strix_free(strix *string);

#endif /* A4921AE8_DB77_42E3_A83E_9D3D0C69BDE0 */

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
} strix_t;

#define STRIX_FORMAT "%.*s"
#define STRIX_PRINT(string) (int)(string)->len, (string)->str

strix_t *strix_create(const char *str);
strix_t *strix_duplicate(strix_t *strix); // returns a null strix if string is of length 0
bool strix_modify(strix_t *strix, const char *str);
bool strix_clear(strix_t *strix);

void *strix_free(strix_t *string);

#endif /* A4921AE8_DB77_42E3_A83E_9D3D0C69BDE0 */

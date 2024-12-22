#include "../header/strix.h"

static inline bool is_strix_null(const strix_t *strix);
static inline bool is_str_null(const char *str);
static inline bool is_strix_str_null(const strix_t *strix);
static inline bool is_strix_empty(const strix_t *strix);
static inline bool is_strix_empty_or_null(const strix_t *strix);
static inline bool is_ptr_null(const void *ptr);

static inline bool is_ptr_null(const void *ptr)
{
    return !ptr;
}

static inline bool is_strix_null(const strix_t *strix)
{
    return !strix;
}

static inline bool is_str_null(const char *str)
{
    return !str;
}

static inline bool is_strix_str_null(const strix_t *strix)
{
    return !strix->str;
}

static inline bool is_strix_empty(const strix_t *strix)
{
    return !strix->len;
}

static inline bool is_strix_empty_or_null(const strix_t *strix)
{
    return is_strix_null(strix) || is_strix_empty(strix);
}

strix_t *strix_create(const char *str)
{
    if (is_str_null(str))
    {
        return NULL;
    }
    strix_t *strix = (strix_t *)allocate(sizeof(strix_t));
    if (is_strix_null(strix))
    {
        return NULL;
    }
    strix->len = strlen(str);
    strix->str = (char *)allocate(strix->len);
    if (is_strix_str_null(strix))
    {
        return NULL;
    }
    if (!memmove(strix->str, str, strix->len))
    {
        return NULL;
    }
    return strix;
}

strix_t *strix_duplicate(strix_t *strix)
{
    if (is_strix_empty_or_null(strix))
    {
        return NULL;
    }
    strix_t *duplicate = (strix_t *)allocate(sizeof(strix_t));
    if (is_strix_null(duplicate))
    {
        return NULL;
    }
    duplicate->len = strix->len;
    duplicate->str = (char *)allocate(sizeof(duplicate->len));
    if (is_strix_str_null(duplicate))
    {
        return NULL;
    }
    if (!memcpy(duplicate->str, strix->str, strix->len))
    {
        return NULL;
    }
    return duplicate;
}

bool strix_modify(strix_t *strix, const char *str)
{
    if (is_strix_null(strix) || is_str_null(str))
    {
        return false;
    }
    strix_free(strix);
    strix = strix_create(str);
    return true;
}

void *strix_free(strix_t *strix)
{
    deallocate(strix->str);
    deallocate(strix);
}

bool strix_clear(strix_t *strix)
{
    if (is_strix_null(strix))
    {
        return false;
    }
    strix->len = 0;
    deallocate(strix->str);
    return true;
}

int main(void)
{
    strix_t *strix = strix_create("hello");
    strix_modify(strix, "world");
    fprintf(stdout, STRIX_FORMAT "\n", STRIX_PRINT(strix));
}
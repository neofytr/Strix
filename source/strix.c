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

strix_t *strix_duplicate(const strix_t *strix)
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

strix_t *strix_concat(const strix_t *strix_one, const strix_t *strix_two)
{
    if (is_strix_null(strix_one) && !is_strix_null(strix_two))
    {
        return strix_duplicate(strix_two);
    }

    if (is_strix_null(strix_two) && !is_strix_null(strix_one))
    {
        return strix_duplicate(strix_one);
    }

    if (is_strix_null(strix_one) && is_strix_null(strix_two))
    {
        return NULL;
    }

    strix_t *new_strix = (strix_t *)allocate(sizeof(strix_t));
    if (is_strix_null(new_strix))
    {
        return NULL;
    }

    new_strix->len = strix_one->len + strix_two->len;
    new_strix->str = (char *)allocate(sizeof(char) * new_strix->len);

    if (is_strix_str_null(new_strix))
    {
        return NULL;
    }

    if (!memcpy((void *)new_strix->str, (void *)strix_one->str, strix_one->len))
    {
        return NULL;
    }

    if (!memcpy((void *)(new_strix->str + strix_one->len), (void *)strix_two->str, strix_two->len))
    {
        return NULL;
    }

    return new_strix;
}

int main(void)
{
    strix_t *strix = strix_create("hello");
    strix_t *another = strix_create(", world!");
    strix_t *concat = strix_concat(strix, another);
    fprintf(stdout, STRIX_FORMAT "\n", STRIX_PRINT(concat));
}
#include "../header/strix.h"
#include <threads.h>

#include "../header/strix.h"
#include "../header/strix_errno.h"

static inline bool is_strix_null(const strix_t *strix)
{
    if (!strix)
    {
        strix_errno = STRIX_ERR_NULL_STRIX_PTR;
        return true;
    }
    return false;
}

static inline bool is_str_null(const char *str)
{
    if (!str)
    {
        strix_errno = STRIX_ERR_NULL_STRIX_PTR;
        return true;
    }
    return false;
}

static inline bool is_strix_str_null(const strix_t *strix)
{
    if (!strix->str)
    {
        strix_errno = STRIX_ERR_NULL_STRIX_PTR;
        return true;
    }
    return false;
}

static inline bool is_strix_empty(const strix_t *strix)
{
    if (!strix->len)
    {
        strix_errno = STRIX_ERR_EMPTY_STRING;
        return true;
    }
    return false;
}

static inline bool is_strix_empty_or_null(const strix_t *strix)
{
    return is_strix_null(strix) || is_strix_empty(strix);
}

strix_t *strix_create(const char *str)
{
    strix_errno = STRIX_SUCCESS;

    if (is_str_null(str))
    {
        return NULL;
    }

    strix_t *strix = (strix_t *)allocate(sizeof(strix_t));
    if (!strix)
    {
        strix_errno = STRIX_ERR_MALLOC_FAILED;
        return NULL;
    }

    strix->len = strlen(str);
    if (strix->len == 0)
    {
        strix_errno = STRIX_ERR_EMPTY_STRING;
        deallocate(strix);
        return NULL;
    }

    strix->str = (char *)allocate(strix->len);
    if (!strix->str)
    {
        strix_errno = STRIX_ERR_MALLOC_FAILED;
        deallocate(strix);
        return NULL;
    }

    if (!memmove(strix->str, str, strix->len))
    {
        strix_errno = STRIX_ERR_MEMMOVE_FAILED;
        deallocate(strix->str);
        deallocate(strix);
        return NULL;
    }

    return strix;
}

strix_t *strix_duplicate(const strix_t *strix)
{
    strix_errno = STRIX_SUCCESS;

    if (is_strix_empty_or_null(strix))
    {
        return NULL;
    }

    strix_t *duplicate = (strix_t *)allocate(sizeof(strix_t));
    if (!duplicate)
    {
        strix_errno = STRIX_ERR_MALLOC_FAILED;
        return NULL;
    }

    duplicate->len = strix->len;
    duplicate->str = (char *)allocate(sizeof(char) * duplicate->len);
    if (!duplicate->str)
    {
        strix_errno = STRIX_ERR_MALLOC_FAILED;
        deallocate(duplicate);
        return NULL;
    }

    if (!memcpy(duplicate->str, strix->str, strix->len))
    {
        strix_errno = STRIX_ERR_MEMCPY_FAILED;
        deallocate(duplicate->str);
        deallocate(duplicate);
        return NULL;
    }

    return duplicate;
}

bool strix_modify(strix_t *strix, const char *str)
{
    strix_errno = STRIX_SUCCESS;

    if (is_strix_null(strix) || is_str_null(str))
    {
        return false;
    }

    strix_free(strix);
    strix = strix_create(str);
    if (!strix)
    {
        return false;
    }
    return true;
}

void strix_free(strix_t *strix)
{
    if (!strix)
        return;
    if (strix->str)
        deallocate(strix->str);
    deallocate(strix);
}

bool strix_clear(strix_t *strix)
{
    strix_errno = STRIX_SUCCESS;

    if (is_strix_null(strix))
    {
        return false;
    }

    strix->len = 0;
    deallocate(strix->str);
    strix->str = NULL;
    return true;
}

bool strix_concat(strix_t *dest, const strix_t *src)
{
    strix_errno = STRIX_SUCCESS;

    if (is_strix_null(dest))
    {
        return false;
    }

    if (is_strix_null(src))
    {
        return true; // nothing to concatenate, not an error
    }

    size_t new_len = dest->len + src->len;
    char *new_str = (char *)allocate(sizeof(char) * new_len);
    if (!new_str)
    {
        strix_errno = STRIX_ERR_MALLOC_FAILED;
        return false;
    }

    if (!memcpy(new_str, dest->str, dest->len))
    {
        strix_errno = STRIX_ERR_MEMCPY_FAILED;
        deallocate(new_str);
        return false;
    }

    if (!memcpy(new_str + dest->len, src->str, src->len))
    {
        strix_errno = STRIX_ERR_MEMCPY_FAILED;
        deallocate(new_str);
        return false;
    }

    deallocate(dest->str);
    dest->str = new_str;
    dest->len = new_len;

    return true;
}

bool strix_append(strix_t *strix, const char *str)
{
    strix_errno = STRIX_SUCCESS;

    if (is_strix_null(strix) || is_str_null(str))
    {
        return false;
    }

    size_t str_len = strlen(str);
    if (str_len == 0)
    {
        return true; // nothing to append, not an error
    }

    size_t new_len = strix->len + str_len;
    char *new_str = (char *)allocate(sizeof(char) * new_len);
    if (!new_str)
    {
        strix_errno = STRIX_ERR_MALLOC_FAILED;
        return false;
    }

    if (!memcpy(new_str, strix->str, strix->len))
    {
        strix_errno = STRIX_ERR_MEMCPY_FAILED;
        deallocate(new_str);
        return false;
    }

    if (!memcpy(new_str + strix->len, str, str_len))
    {
        strix_errno = STRIX_ERR_MEMCPY_FAILED;
        deallocate(new_str);
        return false;
    }

    deallocate(strix->str);
    strix->str = new_str;
    strix->len = new_len;

    return true;
}

int main(void)
{
    strix_t *strix = strix_create("hello");
    if (!strix)
    {
        strix_perror("Failed to create first string");
        return 1;
    }

    strix_t *world = strix_create(", world!");
    if (!world)
    {
        strix_perror("Failed to create second string");
        strix_free(strix);
        return 1;
    }

    if (!strix_concat(strix, world))
    {
        strix_perror("Failed to concatenate strings");
        strix_free(strix);
        strix_free(world);
        return 1;
    }

    fprintf(stdout, STRIX_FORMAT "\n", STRIX_PRINT(strix));

    if (!strix_append(strix, "!!"))
    {
        strix_perror("Failed to append string");
        strix_free(strix);
        strix_free(world);
        return 1;
    }

    fprintf(stdout, STRIX_FORMAT "\n", STRIX_PRINT(strix));

    strix_free(strix);
    strix_free(world);
    return 0;
}
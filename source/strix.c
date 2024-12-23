#include <threads.h>
#include <stdint.h>

#include "../header/strix.h"
#include "../header/strix_errno.h"

static inline bool is_strix_null(const strix_t *strix)
{
    if (!strix)
    {
        strix_errno = STRIX_ERR_NULL_PTR;
        return true;
    }
    return false;
}

static inline bool is_str_null(const char *str)
{
    if (!str)
    {
        strix_errno = STRIX_ERR_NULL_PTR;
        return true;
    }
    return false;
}

static inline bool is_strix_str_null(const strix_t *strix)
{
    if (!strix->str)
    {
        strix_errno = STRIX_ERR_NULL_PTR;
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

bool strix_insert_str(strix_t *strix, size_t pos, const char *substr)
{
    if (is_strix_null(strix) || is_str_null(substr))
    {
        strix_errno = STRIX_ERR_NULL_PTR;
        return false;
    }

    if (is_strix_str_null(strix))
    {
        strix_errno = STRIX_ERR_STRIX_STR_NULL;
        return false;
    }

    if (strix->len <= pos)
    {
        strix_errno = STRIX_ERR_INVALID_POS;
        return false;
    }

    char *new_str = (char *)allocate(sizeof(char) * (strlen(substr) + strix->len));
    if (is_str_null(new_str))
    {
        strix_errno = STRIX_ERR_MALLOC_FAILED;
        return false;
    }

    if (!memcpy((void *)new_str, (void *)strix->str, pos))
    {
        strix_errno = STRIX_ERR_MEMMOVE_FAILED;
        return false;
    }

    if (!memcpy(((void *)(uint8_t *)new_str + pos), (void *)substr, strlen(substr)))
    {
        strix_errno = STRIX_ERR_MEMMOVE_FAILED;
        return false;
    }

    if (!memcpy(((void *)(uint8_t *)new_str + pos + strlen(substr)), (void *)strix->str, strix->len - pos - 1))
    {
        strix_errno = STRIX_ERR_MEMMOVE_FAILED;
        return false;
    }

    deallocate(strix->str);
    strix->str = new_str;
    strix->len = strix->len + strlen(substr);

    strix_errno = STRIX_SUCCESS;
    return true;
}

bool strix_insert(strix_t *strix_dest, strix_t *strix_src, size_t pos)
{
    if (is_strix_null(strix_dest) || is_strix_null(strix_src))
    {
        strix_errno = STRIX_ERR_NULL_PTR;
        return false;
    }

    if (is_strix_str_null(strix_dest) || is_strix_str_null(strix_src))
    {
        strix_errno = STRIX_ERR_STRIX_STR_NULL;
        return false;
    }

    if (strix_dest->len <= pos)
    {
        strix_errno = STRIX_ERR_INVALID_POS;
        return false;
    }

    char *substr = strix_src->str;
    size_t len = strix_src->len;

    char *new_str = (char *)allocate(sizeof(char) * (len + strix_dest->len));
    if (is_str_null(new_str))
    {
        strix_errno = STRIX_ERR_MALLOC_FAILED;
        return false;
    }

    if (!memcpy((void *)new_str, (void *)strix_dest->str, pos))
    {
        strix_errno = STRIX_ERR_MEMMOVE_FAILED;
        return false;
    }

    if (!memcpy(((void *)(uint8_t *)new_str + pos), (void *)substr, len))
    {
        strix_errno = STRIX_ERR_MEMMOVE_FAILED;
        return false;
    }

    if (!memcpy(((void *)(uint8_t *)new_str + pos + len), (void *)strix_dest->str, strix_dest->len - pos - 1))
    {
        strix_errno = STRIX_ERR_MEMMOVE_FAILED;
        return false;
    }

    deallocate(strix_dest->str);
    strix_dest->str = new_str;
    strix_dest->len = strix_dest->len + len;

    strix_errno = STRIX_SUCCESS;
    return true;
}

bool strix_erase(strix_t *strix, size_t len, size_t pos)
{
    if (is_strix_null(strix))
    {
        strix_errno = STRIX_ERR_NULL_PTR;
        return false;
    }

    if (is_strix_str_null(strix))
    {
        strix_errno = STRIX_ERR_STRIX_STR_NULL;
        return false;
    }

    if (pos >= strix->len)
    {
        strix_errno = STRIX_ERR_INVALID_POS;
        return false;
    }

    if (pos + len > strix->len)
    {
        len = strix->len - pos - 1;
    }

    char *new_str = (char *)allocate(sizeof(char) * (strix->len - len));
    if (is_str_null(new_str))
    {
        strix_errno = STRIX_ERR_MALLOC_FAILED;
        return false;
    }

    if (!memcpy((void *)new_str, (void *)strix->str, pos + 1))
    {
        strix_errno = STRIX_ERR_MEMCPY_FAILED;
        return false;
    }

    if (!memcpy((void *)((uint8_t *)new_str + pos + 1), (void *)((uint8_t *)strix->str) + pos + len + 1, strix->len - pos - len - 1))
    {
        strix_errno = STRIX_ERR_MEMCPY_FAILED;
        return false;
    }

    deallocate(strix->str);
    strix->str = new_str;
    strix->len -= len;

    strix_errno = STRIX_SUCCESS;
    return true;
}

char strix_at(const strix_t *strix, size_t index)
{
    if (is_strix_null(strix))
    {
        strix_errno = STRIX_ERR_NULL_PTR;
        return -1;
    }

    if (index >= strix->len)
    {
        strix_errno = STRIX_ERR_OUT_OF_BOUNDS_ACCESS;
        return -1;
    }

    strix_errno = STRIX_SUCCESS;
    return strix->str[index];
}

int strix_equal(const strix_t *strix_one, const strix_t *strix_two)
{
    if (is_strix_null(strix_one) || is_strix_null(strix_two))
    {
        strix_errno = STRIX_ERR_NULL_PTR;
        return -1;
    }

    if (is_strix_str_null(strix_one) || is_strix_str_null(strix_two))
    {
        strix_errno = STRIX_ERR_STRIX_STR_NULL;
        return -1;
    }

    if (strix_one->len != strix_two->len)
    {
        return 1;
    }

    strix_errno = STRIX_SUCCESS;

    size_t len = strix_one->len;
    if (!strncmp(strix_one->str, strix_two->str, len))
    {
        return 0;
    }

    return 1;
}

int64_t strix_find(const strix_t *strix, const char *substr)
{
    if (is_strix_null(strix) || is_str_null(substr))
    {
        strix_errno = STRIX_ERR_NULL_PTR;
        return -1;
    }

    if (is_strix_str_null(strix))
    {
        strix_errno = STRIX_ERR_STRIX_STR_NULL;
        return -1;
    }

    
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

    strix_insert_str(strix, 0, "no\n");
    strix_insert(strix, strix_create("lets go\n"), 0);
    fprintf(stdout, STRIX_FORMAT "\n", STRIX_PRINT(strix));
    strix_erase(strix, 100, 3);
    fprintf(stdout, STRIX_FORMAT "\n", STRIX_PRINT(strix));
    fprintf(stdout, "%d\n", strix_equal(strix_create("hello"), strix_create("hello\n")));

    strix_free(strix);
    strix_free(world);
    return 0;
}
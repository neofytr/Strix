#include "../header/string_search.h"

int64_t kmp_search(const char *pattern, const char *string, size_t pattern_len, size_t string_len)
{
    size_t lps[pattern_len];

    size_t i = 1, j = 0;
    lps[0] = 0;

    while (i < pattern_len)
    {
        if (pattern[i] == pattern[j])
        {
            j++;
            lps[i] = j;
            i++;
        }
        else
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }

    i = 0;
    j = 0;

    while (i < string_len)
    {
        if (pattern[j] == string[i])
        {
            j++;
            i++;

            if (j == pattern_len)
            {
                j = lps[j - 1]; // the search can be continued using this, but i return after finding the first match
                return (i - j);
            }
        }
        else
        {
            if (j > 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    return -2;
}

position_t *kmp_search_all(const char *pattern, const char *string, size_t pattern_len, size_t string_len)
{
    size_t lps[pattern_len];
    int64_t counter = 0;

    position_t *position = (position_t *)malloc(sizeof(position));
    if (!position)
    {
        strix_errno = STRIX_ERR_MALLOC_FAILED;
        return NULL;
    }

    size_t *pos_arr = (size_t *)malloc(sizeof(size_t) * MAX_POSITIONS);
    if (!pos_arr)
    {
        strix_errno = STRIX_ERR_MALLOC_FAILED;
        return NULL;
    }

    size_t i = 1, j = 0;
    lps[0] = 0;

    while (i < pattern_len)
    {
        if (pattern[i] == pattern[j])
        {
            j++;
            lps[i] = j;
            i++;
        }
        else
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }

    i = 0;
    j = 0;

    while (i < string_len)
    {
        if (pattern[j] == string[i])
        {
            j++;
            i++;

            if (j == pattern_len)
            {
                j = lps[j - 1]; // the search can be continued using this, but i return after finding the first match
                pos_arr[counter++] = i - j;
            }
        }
        else
        {
            if (j > 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    if (!counter)
    {
        position->len = -2;
        return position;
    }

    position->len = counter;
    position->pos = pos_arr;
    return position;
}

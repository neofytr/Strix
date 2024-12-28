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
                return (i - j - 1);
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

int64_t kmp_search_all_len(const char *pattern, const char *string, size_t pattern_len, size_t string_len)
{
    size_t lps[pattern_len];
    int64_t counter = 0;

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
                j = lps[j - 1];
                counter++;
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

    return counter;
}

position_t *kmp_search_all(const char *pattern, const char *string, size_t pattern_len, size_t string_len)
{
    size_t lps[pattern_len];
    int64_t counter = 0;
    size_t current_max_positions = MAX_POSITIONS;

    position_t *position = (position_t *)malloc(sizeof(position_t));
    if (!position)
    {
        strix_errno = STRIX_ERR_MALLOC_FAILED;
        return NULL;
    }

    size_t *pos_arr = (size_t *)malloc(sizeof(size_t) * current_max_positions);
    if (!pos_arr)
    {
        free(position);
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
                if (counter >= current_max_positions)
                {
                    current_max_positions *= 2; // double the size
                    size_t *new_pos_arr = (size_t *)realloc(pos_arr, sizeof(size_t) * current_max_positions);
                    if (!new_pos_arr)
                    {
                        free(pos_arr);
                        free(position);
                        strix_errno = STRIX_ERR_MALLOC_FAILED;
                        return NULL;
                    }
                    pos_arr = new_pos_arr;
                }

                j = lps[j - 1];
                pos_arr[counter++] = i - pattern_len;
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
        free(pos_arr);
        position->len = -2;
        return position;
    }

    if (current_max_positions > counter)
    {
        size_t *new_pos_arr = (size_t *)realloc(pos_arr, sizeof(size_t) * counter);
        if (new_pos_arr)
        {
            pos_arr = new_pos_arr;
        }
    }

    position->len = counter;
    position->pos = pos_arr;
    return position;
}
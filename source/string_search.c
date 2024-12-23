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

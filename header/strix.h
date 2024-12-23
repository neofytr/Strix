#ifndef A4921AE8_DB77_42E3_A83E_9D3D0C69BDE0
#define A4921AE8_DB77_42E3_A83E_9D3D0C69BDE0

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "string_search.h"
#include "../allocator/allocator.h"

/**
 * @brief String handling structure that stores both the string and its length
 *
 * This structure provides a way to handle strings with explicit length tracking,
 * avoiding the need for null-termination and allowing for binary data.
 */
typedef struct
{
    char *str;  // Pointer to the string data
    size_t len; // Length of the string
} strix_t;

/**
 * @brief Format macro for printf-style functions
 *
 * Used to print strix_t strings with proper length handling.
 * Example: printf(STRIX_FORMAT, STRIX_PRINT(my_strix));
 */
#define STRIX_FORMAT "%.*s"

/**
 * @brief Print macro for strix_t structures
 *
 * Expands to the length and string pointer needed by STRIX_FORMAT.
 * Must be used in conjunction with STRIX_FORMAT.
 */
#define STRIX_PRINT(string) (int)(string)->len, (string)->str

/**
 * @brief Creates a new strix_t structure from a C-style string
 *
 * @param str Input string to copy (must be null-terminated)
 * @return strix_t* Pointer to new strix_t structure, or NULL on failure
 *
 * Edge cases:
 * - Returns NULL if input string is NULL
 * - Returns NULL if memory allocation fails for strix_t
 * - Returns NULL if memory allocation fails for internal string
 * - Returns NULL if string copy fails
 */
strix_t *strix_create(const char *str);

/**
 * @brief Creates a deep copy of an existing strix_t structure
 *
 * @param strix Source strix_t to duplicate
 * @return strix_t* Pointer to new strix_t structure, or NULL on failure
 *
 * Edge cases:
 * - Returns NULL if input strix is NULL
 * - Returns NULL if input strix has length 0
 * - Returns NULL if memory allocation fails for new strix_t
 * - Returns NULL if memory allocation fails for internal string
 * - Returns NULL if string copy fails
 */
strix_t *strix_duplicate(const strix_t *strix);

/**
 * @brief Modifies an existing strix_t structure with a new string
 *
 * Frees the existing string and replaces it with a new one.
 *
 * @param strix Target strix_t to modify
 * @param str New string to copy into the structure
 * @return bool true on success, false on failure
 *
 * Edge cases:
 * - Returns false if input strix is NULL
 * - Returns false if input string is NULL
 */
bool strix_modify(strix_t *strix, const char *str);

/**
 * @brief Clears the contents of a strix_t structure
 *
 * Sets length to 0 and frees the internal string.
 *
 * @param strix strix_t structure to clear
 * @return bool true on success, false on failure
 *
 * Edge cases:
 * - Returns false if input strix is NULL
 */
bool strix_clear(strix_t *strix);

/**
 * @brief Concatenates two strix_t structures, modifying the first one
 *
 * Modifies the first strix_t by appending the contents of the second strix_t.
 *
 * @param strix_dest Target strix_t to modify
 * @param strix_src Source strix_t to append
 * @return bool true on success, false on failure
 *
 * Edge cases:
 * - Returns false if either input is NULL
 * - Returns false if memory reallocation fails
 * - Returns false if string copy fails
 */
bool strix_concat(strix_t *strix_dest, const strix_t *strix_src);
/**
 * @brief Appends a C-style string to an existing strix_t structure
 *
 * @param strix Target strix_t structure to modify
 * @param str String to append
 * @return bool true on success, false on failure
 *
 * Edge cases:
 * - Returns false if input strix is NULL
 * - Returns false if input string is NULL
 * - Returns false if append operation fails
 */
bool strix_append(strix_t *strix, const char *str);

/**
 * @brief Inserts the source strix_t structure's string to the destination strix_t structure's string at position pos
 *
 * @param strix_dest Target strix_t structure whose string is being appended to
 * @param strix_src strix_t structure whose string is being appended
 * @return bool true on success, false on failure
 *
 * Edge cases:
 * - Returns false if input strixs are NULL
 * - Returns false if input strix's strings are NULL
 * - Returns false if the destination strix length is less than or equal to pos
 */
bool strix_insert(strix_t *strix_dest, strix_t *strix_src, size_t pos);

bool strix_insert_str(strix_t *strix, size_t pos, const char *substr);

bool strix_erase(strix_t *strix, size_t len, size_t pos); // delete everything starting from position pos + 1; len is truncated to end of strix string if it exceeds it

char strix_at(const strix_t *strix, size_t index);

int strix_equal(const strix_t *strix_one, const strix_t *strix_two); // -1 on error, 0 if equal, 1 if unequal

int64_t strix_find(const strix_t *strix, const char *substr); // index of first detection in the string; -1 on error; -2 on not found

position_t *strix_find_all(const strix_t *strix, const char *substr); // NULL on error, len is -2 on not found; if positive, contains all the positions in pos;

void strix_position_free(position_t *position);

int64_t strix_find_subtrix(const strix_t *strix_one, const strix_t *strix_two);

position_t *strix_find_subtrix_all(const strix_t *strix_one, const strix_t *strix_two);

#define MAX_SUBSTRIX_NUM 2048

typedef struct
{
    strix_t **strix_arr;
    size_t len;
} strix_arr_t;

strix_arr_t *strix_split_by_delim(const strix_t *strix, const char delim);

void strix_free_strix_arr(strix_arr_t *strix_arr);

strix_t *strix_slice(const strix_t *strix, size_t start, size_t end);

void strix_free(strix_t *string);

#endif /* A4921AE8_DB77_42E3_A83E_9D3D0C69BDE0 */
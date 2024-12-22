#ifndef A4921AE8_DB77_42E3_A83E_9D3D0C69BDE0
#define A4921AE8_DB77_42E3_A83E_9D3D0C69BDE0

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
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

void strix_free(strix_t *string);

#endif /* A4921AE8_DB77_42E3_A83E_9D3D0C69BDE0 */
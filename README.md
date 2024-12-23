# Strix String Manipulation Library

The **Strix String Manipulation Library** is a C library designed for efficient and flexible string handling. It introduces a `strix_t` structure to manage strings and their lengths explicitly, allowing for seamless manipulation of binary data and avoiding the pitfalls of null-terminated strings. It also includes a custom memory allocator for allocating `strix_t` structures in memory. Furthermore, support for thread-safe error-handling for strix functions is also provided.

## Data Structures

### `strix_t`
Represents a string with explicit length tracking:
```c
typedef struct {
    char *str;   // Pointer to the string data
    size_t len;  // Length of the string
} strix_t;
```

### `strix_arr_t`
Represents an array of `strix_t` structures:
```c
typedef struct {
    strix_t **strix_arr;
    size_t len;
} strix_arr_t;
```
## Macros

### `STRIX_FORMAT`

Format macro for printf-style functions to print strix_t objects.

### `STRIX_PRINT(strix)`

Expands to length and strix pointer for use with STRIX_FORMAT.

Example usage to print a strix string:

`printf("strix string: "STRIX_FORMAT"\n", STRIX_PRINT(strix));`

### Constants
- `MAX_SUBSTRIX_NUM`: Limits the number of substrings to 2048 during splitting operations.

## API Reference

For detailed core API reference, consult the file:

`/header/strix.h`

### String Creation and Management

#### `strix_t *strix_create(const char *str);`
Creates a new `strix_t` from a C-style string.

#### `strix_t *strix_duplicate(const strix_t *strix);`
Creates a deep copy of an existing `strix_t`.

#### `bool strix_modify(strix_t *strix, const char *str);`
Modifies an existing `strix_t` with a new string.

#### `bool strix_clear(strix_t *strix);`
Clears the contents of a `strix_t` structure.

#### `void strix_free(strix_t *string);`
Frees memory allocated for a `strix_t`.

### Concatenation and Modification

#### `bool strix_concat(strix_t *strix_dest, const strix_t *strix_src);`
Concatenates two `strix_t` structures, modifying the first one.

#### `bool strix_append(strix_t *strix, const char *str);`
Appends a C-style string to a `strix_t`.

#### `bool strix_insert(strix_t *strix_dest, strix_t *strix_src, size_t pos);`
Inserts one `strix_t` into another at a specified position.

#### `bool strix_insert_str(strix_t *strix, size_t pos, const char *substr);`
Appends a substring at a specified position in a `strix_t`.

#### `bool strix_erase(strix_t *strix, size_t len, size_t pos);`
Erases a portion of the string starting from a specified position.

### String Comparison and Search

#### `char strix_at(const strix_t *strix, size_t index);`
Retrieves the character at a specified index in a `strix_t`.

#### `int strix_equal(const strix_t *strix_one, const strix_t *strix_two);`
Compares two `strix_t` structures for equality.

#### `int64_t strix_find(const strix_t *strix, const char *substr);`
Finds the first occurrence of a substring in a `strix_t`.

#### `position_t *strix_find_all(const strix_t *strix, const char *substr);`
Finds all occurrences of a substring in a `strix_t`.

#### `int64_t strix_find_subtrix(const strix_t *strix_one, const strix_t *strix_two);`
Finds the first occurrence of one `strix_t` within another.

#### `position_t *strix_find_subtrix_all(const strix_t *strix_one, const strix_t *strix_two);`
Finds all occurrences of one `strix_t` within another.

### Splitting and Joining

#### `strix_arr_t *strix_split_by_delim(const strix_t *strix, const char delim);`
Splits a `strix_t` into an array of `strix_t` structures using a delimiter.

#### `strix_arr_t *strix_split_by_substr(const strix_t *strix, const char *substr);`
Splits a `strix_t` into an array of `strix_t` structures using a substring.

#### `strix_arr_t *strix_split_by_substrix(const strix_t *strix, const strix_t *substrix);`
Splits a `strix_t` into an array of `strix_t` structures using another `strix_t`.

#### `strix_t *strix_join_via_delim(const strix_t **strix_arr, size_t len, const char delim);`
Joins an array of `strix_t` structures using a delimiter.

#### `strix_t *strix_join_via_substr(const strix_t **strix_arr, size_t len, const char *substr);`
Joins an array of `strix_t` structures using a substring.

#### `strix_t *strix_join_via_substrix(const strix_t **strix_arr, size_t len, const strix_t *substrix);`
Joins an array of `strix_t` structures using another `strix_t`.

### Advanced Operations

#### `strix_t *strix_slice(const strix_t *strix, size_t start, size_t end);`
Creates a new `strix_t` containing a subset of another `strix_t`.

### Array Management

#### `void strix_free_strix_arr(strix_arr_t *strix_arr);`
Frees memory allocated for a `strix_arr_t`.

### Error Handling

The **Strix String Manipulation Library** integrates a robust and thread-safe error-handling system to manage various failure scenarios. 
For detailed reference to the error-handling system, consult the file:

`/header/strix_errno.h`

### Error Codes
The `strix_error_t` enumeration defines all possible error codes that may be returned by the library functions:

| Error Code                        | Description                                    |
|-----------------------------------|------------------------------------------------|
| `STRIX_SUCCESS`                   | Operation completed successfully              |
| `STRIX_ERR_NULL_PTR`              | Null pointer passed as argument               |
| `STRIX_ERR_MALLOC_FAILED`         | Dynamic memory allocation operation failed    |
| `STRIX_ERR_MEMCPY_FAILED`         | Memory copy operation failed                  |
| `STRIX_ERR_MEMMOVE_FAILED`        | Memory move operation failed                  |
| `STRIX_ERR_INVALID_LENGTH`        | Invalid string length specified or computed   |
| `STRIX_ERR_EMPTY_STRING`          | Empty string provided where non-empty required|
| `STRIX_ERR_STRIX_STR_NULL`        | Null string in the strix structure provided   |
| `STRIX_ERR_INVALID_POS`           | Invalid strix string position provided        |
| `STRIX_ERR_OUT_OF_BOUNDS_ACCESS`  | Out of bounds element access                  |
| `STRIX_ERR_INVALID_BOUNDS`        | Invalid bounds given for slicing              |

### Thread-Local Error State
Each thread maintains its own independent error state in the `strix_errno` variable, initialized to `STRIX_SUCCESS`. This ensures thread safety and allows simultaneous operations across multiple threads without interference.

### Error Messages
The library provides a static array of human-readable error messages, indexed by their corresponding error codes:

```c
static const char *strix_error_messages[] = {
    "Success",
    "Null pointer argument",
    "Memory allocation failed",
    "Memory copy operation failed",
    "Memory move operation failed",
    "Invalid string length",
    "Empty string where not allowed",
    "Null string in the strix structure provided",
    "Invalid strix string position provided",
    "Out of bounds element access",
    "Invalid bounds given for slicing",
};
```

### Error Handling API
#### `void strix_perror(const char *prefix)`
Prints a formatted error message to `stderr`, combining the provided prefix and the descriptive error message corresponding to the current `strix_errno` value.

**Example Usage:**
```c
if (!strix_some_function(s)) {
    strix_perror("Failed to process string");
    // Output: "Failed to process string: <error message>"
}
```

#### `strix_error_t strix_get_error(void)`
Retrieves the current error code stored in the thread-local `strix_errno`.

**Example Usage:**
```c
if (strix_get_error() == STRIX_ERR_MALLOC_FAILED) {
    // Handle memory allocation failure
}
```


## Usage Example
```c
#include "strix.h"

int main() {
    strix_t *hello = strix_create("Hello");
    strix_t *world = strix_create("World");

    // Concatenate "Hello" and "World"
    strix_concat(hello, world);
    printf(STRIX_FORMAT, STRIX_PRINT(hello)); // Output: HelloWorld

    strix_free(hello);
    strix_free(world);
    return 0;
}
```

To use the library, explicitly link with the file `strix.o` located in `/binaries/`:

`gcc main.c strix.o -o main`



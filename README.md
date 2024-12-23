# Strix String Manipulation Library 🪢

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

A modern, efficient, and thread-safe C library for string manipulation that goes beyond traditional null-terminated strings. Strix introduces a robust `strix_t` structure for explicit length tracking and safe binary data handling.

## ✨ Features

- 🔒 Thread-safe error handling
- 📏 Explicit length tracking
- 🔄 Binary data support
- 🎯 Custom memory allocation
- 🛡️ Robust error checking
- 🧵 Safe string manipulation

## 📦 Installation

```bash
gcc main.c strix.o -o main
```

The library binary (`strix.o`) can be found in the `/binaries/` directory.

## 🏗️ Core Data Structures

### strix_t
```c
typedef struct {
    char *str;   // Pointer to the string data
    size_t len;  // Length of the string
} strix_t;
```

### strix_arr_t
```c
typedef struct {
    strix_t **strix_arr;
    size_t len;
} strix_arr_t;
```

## 📚 API Reference

### String Creation and Management

| Function | Description | Signature |
|----------|-------------|-----------|
| `strix_create` | Creates a new strix_t from a C-style string | `strix_t *strix_create(const char *str)` |
| `strix_duplicate` | Creates a deep copy of an existing strix_t | `strix_t *strix_duplicate(const strix_t *strix)` |
| `strix_modify` | Modifies an existing strix_t with a new string | `bool strix_modify(strix_t *strix, const char *str)` |
| `strix_clear` | Clears the contents of a strix_t structure | `bool strix_clear(strix_t *strix)` |
| `strix_free` | Frees memory allocated for a strix_t | `void strix_free(strix_t *string)` |

### String Operations

| Function | Description | Signature |
|----------|-------------|-----------|
| `strix_concat` | Concatenates two strix_t structures | `bool strix_concat(strix_t *strix_dest, const strix_t *strix_src)` |
| `strix_append` | Appends a C-style string to a strix_t | `bool strix_append(strix_t *strix, const char *str)` |
| `strix_insert` | Inserts one strix_t into another at a position | `bool strix_insert(strix_t *strix_dest, strix_t *strix_src, size_t pos)` |
| `strix_insert_str` | Inserts a substring at a position | `bool strix_insert_str(strix_t *strix, size_t pos, const char *substr)` |
| `strix_erase` | Erases a portion of the string | `bool strix_erase(strix_t *strix, size_t len, size_t pos)` |

### Search and Comparison

| Function | Description | Signature |
|----------|-------------|-----------|
| `strix_at` | Gets character at specified index | `char strix_at(const strix_t *strix, size_t index)` |
| `strix_equal` | Compares two strix_t structures | `int strix_equal(const strix_t *strix_one, const strix_t *strix_two)` |
| `strix_find` | Finds first occurrence of substring | `int64_t strix_find(const strix_t *strix, const char *substr)` |
| `strix_find_all` | Finds all occurrences of substring | `position_t *strix_find_all(const strix_t *strix, const char *substr)` |
| `strix_find_subtrix` | Finds first occurrence of one strix_t in another | `int64_t strix_find_subtrix(const strix_t *strix_one, const strix_t *strix_two)` |

### Split and Join Operations

| Function | Description | Signature |
|----------|-------------|-----------|
| `strix_split_by_delim` | Splits by delimiter | `strix_arr_t *strix_split_by_delim(const strix_t *strix, const char delim)` |
| `strix_split_by_substr` | Splits by substring | `strix_arr_t *strix_split_by_substr(const strix_t *strix, const char *substr)` |
| `strix_join_via_delim` | Joins with delimiter | `strix_t *strix_join_via_delim(const strix_t **strix_arr, size_t len, const char delim)` |
| `strix_join_via_substr` | Joins with substring | `strix_t *strix_join_via_substr(const strix_t **strix_arr, size_t len, const char *substr)` |

## 🎯 Usage Example

```c
#include "strix.h"

int main() {
    strix_t *hello = strix_create("Hello");
    strix_t *world = strix_create("World");

    // Concatenate strings
    strix_concat(hello, world);
    printf(STRIX_FORMAT, STRIX_PRINT(hello)); // Output: HelloWorld

    strix_free(hello);
    strix_free(world);
    return 0;
}
```

## ⚠️ Error Handling

Strix provides thread-safe error handling through error codes and descriptive messages:

```c
if (!strix_some_function(s)) {
    strix_perror("Failed to process string");
    // Outputs: "Failed to process string: <error message>"
}
```

### Error Codes

| Error Code | Description |
|------------|-------------|
| `STRIX_SUCCESS` | Operation completed successfully |
| `STRIX_ERR_NULL_PTR` | Null pointer passed as argument |
| `STRIX_ERR_MALLOC_FAILED` | Memory allocation failed |
| `STRIX_ERR_MEMCPY_FAILED` | Memory copy operation failed |
| `STRIX_ERR_INVALID_LENGTH` | Invalid string length |
| `STRIX_ERR_EMPTY_STRING` | Empty string provided |

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request
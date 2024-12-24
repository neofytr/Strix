#ifndef B4E8B570_191E_40E7_BFB3_10EB1EAE4545
#define B4E8B570_191E_40E7_BFB3_10EB1EAE4545

#include <stdlib.h>
#include "mem_alloc.h"

typedef void *(*allocator_t)(size_t size);
typedef void (*deallocator_t)(void *ptr);

void change_allocator_to_default();
void change_allocator_to_custom();

void *default_allocator(size_t size);
void default_deallocator(void *ptr);
void *custom_allocator(size_t size);
void custom_deallocator(void *ptr);

extern allocator_t allocate;
extern deallocator_t deallocate;

#endif /* B4E8B570_191E_40E7_BFB3_10EB1EAE4545 */

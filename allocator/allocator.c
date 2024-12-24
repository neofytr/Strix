#include "allocator.h"

allocator_t allocate =
#ifndef CUSTOM_ALLOCATOR
    default_allocator;
#else
    custom_allocator;
#endif

deallocator_t deallocate =
#ifndef CUSTOM_ALLOCATOR
    default_deallocator;
#else
    custom_deallocator;
#endif

// Function definitions
void *default_allocator(size_t size)
{
    return malloc(size);
}

void default_deallocator(void *ptr)
{
    free(ptr);
}

void *custom_allocator(size_t size)
{
    return heap_alloc(size, ALIGN_DEFAULT);
}

void custom_deallocator(void *ptr)
{
    heap_free(ptr);
}

void change_allocator_to_default()
{
    allocate = default_allocator;
    deallocate = default_deallocator;
}

void change_allocator_to_custom()
{
    allocate = custom_allocator;
    deallocate = custom_deallocator;
}

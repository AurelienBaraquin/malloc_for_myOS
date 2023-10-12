#include "my_malloc.h"
#include "bloc.h"
#include <unistd.h>

void my_free(void *ptr);
extern void my_memcpy(void* dest, void* src, size_t size);

void* my_realloc(void* ptr, size_t new_size) {
    if (ptr == NULL) {
        return my_malloc(new_size);
    }

    block_t *ptr_block = PTR_TO_BLOCK(ptr);
    if (ptr_block == NULL) {
        return NULL;
    }

    int size = ptr_block->size;

    if (new_size == 0) {
        return NULL;
    }

    void* new_ptr = my_malloc(new_size);
    if (new_ptr == NULL) {
        return NULL;
    }

    my_memcpy(new_ptr, ptr, size);

    my_free(ptr);

    return new_ptr;
}

#include "my_malloc.h"
#include "bloc.h"
#include <unistd.h>
#include <errno.h>

void* my_aligned_malloc(size_t size, size_t alignment) {
    if (size == 0 || alignment % 2 != 0 || alignment == 0) {
        errno = EINVAL;
        return NULL;
    }

    void* current_address = sbrk(0);
    size_t offset = ((size_t)current_address + sizeof(block_t)) & (alignment - 1);
    size_t adjustment = (alignment - offset) % alignment;

    size_t total_size = size + adjustment;
    void* new_block = my_malloc(total_size);
    if (new_block == NULL)
        return NULL;

    void* aligned_ptr = (void*)((size_t)new_block + adjustment);

    ((void **)aligned_ptr)[-1] = new_block - sizeof(block_t) - ALIGNED_MEM_SIZE;
    #ifdef DEBUG
        printf("Adjust block of size %lu at user side address : %p to %p\n", size, new_block, aligned_ptr);
    #endif
    return aligned_ptr;
}

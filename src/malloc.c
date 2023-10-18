#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>
#include "bloc.h"
#include <errno.h>

void fusion_adjacent_blocks(block_t *first);

static void *alloc_mem(size_t size) {
    void *current_brk;
    void *new_brk;

    current_brk = program_break();
    asm (
        "mov $12, %%rax;"
        "add %1, %0;"
        "mov %0, %%rdi;"
        "syscall;"
        : "=r" (new_brk)
        : "r" (size), "0" (current_brk)
        : "rax", "rdi", "rcx", "r11", "memory"
    );
    if (new_brk == (void *)-1) {
        errno = ENOMEM;
        return NULL;
    }
    return current_brk;
}

static void *alloc_block(size_t size) {
    block_t *block = alloc_mem(size + sizeof(block_t) + ALIGNED_MEM_SIZE);
    if (block == NULL)
        return NULL;
    block->size = size;
    block->free = 1;
    block->next = NULL;
    void *aligned_ptr = (void *)((size_t)block + sizeof(block_t) + ALIGNED_MEM_SIZE);
    ((void **)aligned_ptr)[-1] = block;
    #ifdef DEBUG
        printf("Allocated block of size %lu at %p\n", size, block);
    #endif
    return block;
}

void *my_malloc(size_t size) {
    if (size % 2 != 0)
        ++size;
    static block_t *list = NULL;
    block_t *current = list;
    fusion_adjacent_blocks(list);

    if (list == NULL) {
        if ((list = alloc_block(4096 * 2 - sizeof(block_t) - ALIGNED_MEM_SIZE)) == NULL)
            return NULL;
    }

    if ((current = search_empty_block(list, size)) != NULL)
        return ALLOWED_SPACE_IN_BLOCK(current);

    current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    if ((current->next = alloc_block(4096 * 2 - sizeof(block_t) - ALIGNED_MEM_SIZE)) == NULL)
        return NULL;
    return my_malloc(size);
}

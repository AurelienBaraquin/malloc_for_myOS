#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>
#include "bloc.h"
#include <errno.h>

void fusion_adjacent_blocks(block_t *first);

int program_keeper(size_t size) {
    static int keeper = 0;

    if (size == (size_t)-0x2A)
        return keeper;
    keeper += size;
    return keeper;
}

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
    program_keeper(size);
    return current_brk;
}

static void *alloc_block(size_t size) {
    block_t *block = alloc_mem(size + sizeof(block_t) + ALIGNED_MEM_SIZE);
    if (block == NULL)
        return NULL;
    block->size = size;
    block->free = 0;
    block->next = NULL;
    void *aligned_ptr = (void *)((size_t)block + sizeof(block_t) + ALIGNED_MEM_SIZE);
    ((void **)aligned_ptr)[-1] = block;
    printf("alloc %p\n", block);
    return block;
}

void *my_malloc(size_t size) {
    static block_t *list = NULL;
    block_t *current = list;
    fusion_adjacent_blocks(list);

    if (list == NULL) {
        if ((list = alloc_block(size)) == NULL)
            return NULL;
        return ALLOWED_SPACE_IN_BLOCK(list);
    }

    if ((current = search_empty_block(list, size)) != NULL)
        return ALLOWED_SPACE_IN_BLOCK(current);

    current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    if ((current->next = alloc_block(size)) == NULL)
        return NULL;
    return ALLOWED_SPACE_IN_BLOCK(current->next);
}

__attribute__((destructor)) void reset_program_break(void) {
    sbrk(-program_keeper(-0x2A));
}

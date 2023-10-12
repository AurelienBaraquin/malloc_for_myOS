#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>
#include "bloc.h"
#include <stdio.h>

void fusion_adjacent_blocks(block_t *first);

int program_keeper(size_t size) {
    static int keeper = 0;

    if (size == (size_t)-42)
        return keeper;
    keeper += size;
    // printf("keeper: %d\n", keeper);
    return keeper;
}

static void *alloc_mem(size_t size) {
    void *current_brk, *new_brk;

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
    if (new_brk == (void *)-1)
        return NULL;
    program_keeper(size);
    return current_brk;
}

static void *alloc_block(size_t size) {
    block_t *block = alloc_mem(size + sizeof(block_t));
    block->size = size;
    block->free = 0;
    block->next = NULL;
    return block;
}

void *my_malloc(size_t size) {
    static block_t *list = NULL;
    block_t *current = list;
    fusion_adjacent_blocks(list);

    if (list == NULL) {
        list = alloc_block(size);
        return ALLOWED_SPACE_IN_BLOCK(list);
    }

    while (current->next != NULL)
        current = current->next;
    current->next = alloc_block(size);
    return ALLOWED_SPACE_IN_BLOCK(current->next);
}

__attribute__((destructor)) void reset_program_break(void) {
    sbrk(-program_keeper(-0x2A));
}

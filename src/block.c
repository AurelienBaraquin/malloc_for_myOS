#include "bloc.h"
#define NULL ((void *)0)

int split_block(block_t *block, size_t size) {
    if (block == NULL || block->size < size + sizeof(block_t) + ALIGNED_MEM_SIZE) {
        return -1;
    }

    block_t *new_block = (block_t *)(((char *)block) + size + sizeof(block_t) + ALIGNED_MEM_SIZE);

    #ifdef DEBUG
        printf("Split block of size %lu at %p into %p and %p\n", block->size, block, block, new_block);
    #endif

    new_block->size = block->size - size - sizeof(block_t) - ALIGNED_MEM_SIZE;
    new_block->free = 1;
    new_block->next = block->next;
    ((void **)ALLOWED_SPACE_IN_BLOCK(new_block))[-1] = new_block;

    block->size = size;
    block->free++;
    block->next = new_block;
    ((void **)ALLOWED_SPACE_IN_BLOCK(block))[-1] = block;
    return 0;
}

block_t *search_empty_block(block_t *first, size_t size) {
    block_t *current = first;

    while (current != NULL) {
        if (current->free && split_block(current, size) == 0) {
            #ifdef DEBUG
                printf("Found block of size %lu at %p\n", current->size, current);
            #endif
            return current;
        }
        current = current->next;
    }
    return NULL;
}

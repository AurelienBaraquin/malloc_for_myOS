#include "bloc.h"
#define NULL ((void *)0)

int split_block(block_t *block, size_t size) {
    if (block == NULL || block->size < size + sizeof(block_t) + ALIGNED_MEM_SIZE) {
        return -1;
    }

    block_t *new_block = (block_t *)(((char *)block) + size + sizeof(block_t) + ALIGNED_MEM_SIZE);

    #ifdef DEBUG
        printf("Split block (%lu) %p into %p (%lu) and %p (%lu)\n", block->size, block, block, size, new_block, block->size - size);
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
                printf("Found block (%lu) %p\n", current->size, current);
            #endif
            return current;
        }
        current = current->next;
    }
    return NULL;
}

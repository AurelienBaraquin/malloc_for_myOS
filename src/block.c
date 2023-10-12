#include "bloc.h"
#define NULL ((void *)0)

int split_block(block_t *block, size_t size) {
    if (block == NULL || block->size < size + sizeof(block_t)) {
        return -1;
    }

    block_t *new_block = (block_t *)(((char *)block) + size + sizeof(block_t));

    new_block->size = block->size - size - sizeof(block_t);
    new_block->free = 1;
    new_block->next = block->next;

    block->size = size;
    block->free++;
    block->next = new_block;
    return 0;
}

block_t *search_empty_block(block_t *first, size_t size) {
    block_t *current = first;

    while (current != NULL) {
        if (current->free && split_block(current, size) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

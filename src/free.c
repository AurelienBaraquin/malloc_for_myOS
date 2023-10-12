#include "bloc.h"
#include <unistd.h>

void fusion(block_t *block) {
    if (block == NULL) {
        return;
    }

    block_t *next = block->next;

    if (next != NULL && next->free) {
        block->size += next->size + sizeof(block_t);
        block->next = next->next;
    }
}

void fusion_adjacent_blocks(block_t *first) {
    block_t *current = first;

    if (current == NULL) {
        return;
    }

    while (current->next != NULL) {
        if (current->free && current->next->free) {
            fusion(current);
        } else {
            current = current->next;
        }
    }
}

void my_free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    block_t *block = PTR_TO_BLOCK(ptr);

    if (block == NULL) {
        return;
    }

    block->free++;
}
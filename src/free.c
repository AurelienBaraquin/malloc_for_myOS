#include "bloc.h"
#include <unistd.h>
#include <errno.h>

void fusion(block_t *block) {
    if (block == NULL) {
        return;
    }

    block_t *next = block->next;

    #ifdef DEBUG
        printf("Fusion block (%lu) %p (%lu) with %p (%lu) = %p (%lu)\n", block->size, block, block->size, next, next->size, block, block->size + next->size + sizeof(block_t) + ALIGNED_MEM_SIZE);
    #endif

    if (next != NULL && next->free) {
        block->size += next->size + sizeof(block_t) + ALIGNED_MEM_SIZE;
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
        errno = EINVAL;
        return;
    }

    void *original_address = ((void **)ptr)[-1];

    block_t *block = (block_t *)((void *)original_address);

    if (block == NULL) {
        errno = EINVAL;
        return;
    }

    #ifdef DEBUG
        printf("Freeing block (%lu) %p\n", block->size, block);
    #endif

    block->free++;
}

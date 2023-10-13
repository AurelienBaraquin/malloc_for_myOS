#pragma once

#include <sys/types.h>

#define ORIGINAL_VALUE_KEEPER program_keeper(-0x2A)

#define ALIGNED_MEM_SIZE sizeof(void *)
#define PTR_TO_BLOCK(ptr) (block_t *)((void *)ptr - sizeof(block_t) - ALIGNED_MEM_SIZE)
#define ALLOWED_SPACE_IN_BLOCK(block) (void *)(((void *)block) + sizeof(block_t) + ALIGNED_MEM_SIZE)

typedef struct block_s {
    size_t size;
    char free : 1;
    struct block_s *next;
} block_t;

extern void *program_break(void);
int split_block(block_t *block, size_t size);
block_t *search_empty_block(block_t *first, size_t size);

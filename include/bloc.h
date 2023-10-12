#pragma once

#include <sys/types.h>

#define ALLOWED_SPACE_IN_BLOCK(block) (void *)(((void *)block) + sizeof(block_t))
#define ORIGINAL_VALUE_KEEPER program_keeper(-0x2A)
#define PTR_TO_BLOCK(ptr) (block_t *)((void *)ptr - sizeof(block_t))

typedef struct block_s {
    size_t size;
    char free : 1;
    struct block_s *next;
} block_t;

extern void *program_break(void);

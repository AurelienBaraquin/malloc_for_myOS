#include "my_malloc.h"

#include <unistd.h>
extern void my_memset(void* ptr, int value, size_t num);

void* my_calloc(size_t num_elements, size_t element_size) {
    size_t total_size = num_elements * element_size;

    void* ptr = my_malloc(total_size);
    if (ptr == NULL) {
        return NULL;
    }

    my_memset(ptr, 0, total_size);
    return ptr;
}

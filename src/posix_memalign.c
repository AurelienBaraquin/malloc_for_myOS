#include "my_aligned_alloc.h"
#include <errno.h>
#include <unistd.h>

int my_posix_memalign(void **memptr, size_t alignment, size_t size) {
    if ((alignment & (alignment - 1)) != 0 || alignment % sizeof(void*) != 0) {
        errno = EINVAL;
        return EINVAL;
    }

    *memptr = my_aligned_malloc(size, alignment);

    if (*memptr == NULL) {
        return ENOMEM;
    }

    return 0;
}

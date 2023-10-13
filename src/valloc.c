#include <sys/types.h>
#include "my_aligned_alloc.h"
#include <unistd.h>

size_t get_page_size(void) {
    return sysconf(_SC_PAGESIZE);
}

void* my_valloc(size_t size) {
    int pagesize = get_page_size();
    return my_aligned_malloc(size, pagesize);
}

void *my_pvalloc(size_t size) {
    int pagesize = get_page_size();
    size_t aligned_size = (size + pagesize - 1) & ~(pagesize - 1);
    return my_aligned_malloc(aligned_size, pagesize);
}

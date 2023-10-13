#include <stdarg.h>
#include <unistd.h>
#include "my_malloc.h"

void *recursive_alloc(size_t base_size, size_t dims[], int n, int i) {
    if (i == n - 1) {
        return my_malloc(base_size * dims[i]);
    }

    void **new_ptr = my_malloc(dims[i] * sizeof(void*));
    if (new_ptr == NULL) {
        return NULL;
    }

    for (size_t j = 0; j < dims[i]; ++j) {
        new_ptr[j] = recursive_alloc(base_size, dims, n, i + 1);
        if (new_ptr[j] == NULL) {
            return NULL;
        }
    }

    new_ptr[dims[i]] = NULL;

    return new_ptr;
}

void* ralloc(int n, ...) {
    va_list args;
    va_start(args, n);

    size_t base_size = va_arg(args, size_t);
    size_t dims[n];

    for (int i = 0; i < n; ++i) {
        dims[i] = va_arg(args, size_t);
    }

    va_end(args);

    return recursive_alloc(base_size, dims, n, 0);
}

void *recursive_calloc(size_t base_size, size_t dims[], int n, int i) {
    if (i == n - 1) {
        return my_calloc(base_size * dims[i]);
    }

    void **new_ptr = my_calloc(dims[i] * sizeof(void*));
    if (new_ptr == NULL) {
        return NULL;
    }

    for (size_t j = 0; j < dims[i]; ++j) {
        new_ptr[j] = recursive_calloc(base_size, dims, n, i + 1);
        if (new_ptr[j] == NULL) {
            return NULL;
        }
    }

    new_ptr[dims[i]] = NULL;

    return new_ptr;
}

void* rcalloc(int n, ...) {
    va_list args;
    va_start(args, n);

    size_t base_size = va_arg(args, size_t);
    size_t dims[n];

    for (int i = 0; i < n; ++i) {
        dims[i] = va_arg(args, size_t);
    }

    va_end(args);

    return recursive_calloc(base_size, dims, n, 0);
}

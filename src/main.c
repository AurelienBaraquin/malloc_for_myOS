#include <stdio.h>
#include "my_calloc.h"
#include "my_malloc.h"
#include "my_free.h"
#include "my_realloc.h"
#include "my_aligned_alloc.h"
#include "my_posix_memalign.h"

int main() {
    char *str = my_malloc(1000);
    for (int i = 0; i < 1000; i++) {
        str[i] = 'a';
    }
    str[999] = '\0';
    printf("%s\n", str);
    my_free(str);
    char *a = my_aligned_malloc(10, 16);
    char *b = my_aligned_malloc(10, 32);
    char *c = my_calloc(10, 1);
    my_free(a);
    my_free(b);
    c = my_realloc(c, 20);
    my_free(c);
    return 0;
}

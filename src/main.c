#include <stdio.h>
#include "my_calloc.h"
#include "my_malloc.h"
#include "my_free.h"
#include "my_realloc.h"
#include "my_aligned_alloc.h"

int main() {
    char *str = my_aligned_malloc(16, 4);
    for (int i = 0; i < 16; i++) {
        str[i] = 'a';
    }
    str[15] = '\0';
    printf("%s\n", str);
    my_free(str);

    str = my_malloc(87);
    for (int i = 0; i < 53; i++) {
        str[i] = 'b';
    }
    str[52] = '\0';
    printf("%s\n", str);
    my_free(str);

    str = my_aligned_malloc(8, 64);
    for (int i = 0; i < 8; i++) {
        str[i] = 'c';
    }
    str[7] = '\0';
    printf("%s\n", str);
    my_free(str);

    str = my_calloc(8, 8);
    for (int i = 0; i < 8; i++) {
        str[i] = 'd';
    }
    str[7] = '\0';
    printf("%s\n", str);
    my_free(str);
    return 0;
}

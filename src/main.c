#include <stdio.h>
#include "my_calloc.h"
#include "my_malloc.h"
#include "my_free.h"
#include "my_realloc.h"
#include "my_aligned_alloc.h"
#include "my_posix_memalign.h"
#include "ralloc.h"

int main(void) {
    char **ptr = my_calloc(100, sizeof(char *));
    for (int i = 0; i < 100; ++i) {
        ptr[i] = my_malloc(999);
        for (int j = 0; j < 999; ++j) {
            ptr[i][j] = 'a';
        }
        ptr[i][998] = '\0';
    }
    // for (int i = 0; i < 100; ++i) {
    //     printf("%s\n", ptr[i]);
    // }
    for (int i = 0; i < 100; ++i) {
        my_free(ptr[i]);
    }
    my_free(ptr);
    return 0;
}

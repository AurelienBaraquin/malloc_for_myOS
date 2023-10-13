#include <stdio.h>
#include "my_calloc.h"
#include "my_malloc.h"
#include "my_free.h"
#include "my_realloc.h"
#include "my_aligned_alloc.h"
#include "my_posix_memalign.h"
#include <ralloc.h>

int main() {
    char **array = (char**) ralloc(2, sizeof(char), 5, 10);
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            array[i][j] = 'a' + i * 2 + j;
        }
        array[i][9] = '\0';
    }
    for (int i = 0; array[i] != NULL; ++i) {
        printf("%s\n", array[i]);
    }
    for (int i = 0; i < 5; ++i) {
        my_free(array[i]);
    }
    my_free(array);
    return 0;
}

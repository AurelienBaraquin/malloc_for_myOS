#include <stdio.h>
#include "my_calloc.h"
#include "my_malloc.h"
#include "my_free.h"
#include "my_realloc.h"
#include "my_aligned_alloc.h"
#include "my_posix_memalign.h"
#include "ralloc.h"

int main(void) {
    char *str = my_calloc(10, sizeof(char));
    for (int i = 0; i < 10; i++) {
        str[i] = 'a';
    }
    printf("%s\n", str);
    my_free(str);
    return 0;
}

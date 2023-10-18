#include <stdio.h>
#include "my_calloc.h"
#include "my_malloc.h"
#include "my_free.h"
#include "my_realloc.h"
#include "my_aligned_alloc.h"
#include "my_posix_memalign.h"
#include "ralloc.h"

int main(void) {
    char *str = my_aligned_malloc(3, 16);
    str[0] = 'a';
    str[1] = 'b';
    str[2] = '\0';
    printf("%s\n", str);
    char *str2 = my_malloc(3);
    str2[0] = 'c';
    str2[1] = 'd';
    str2[2] = '\0';
    printf("%s\n", str2);
    my_free(str2);
    my_free(str);
    return 0;
}

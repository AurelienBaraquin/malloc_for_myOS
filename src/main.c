#include <stdio.h>
#include "my_calloc.h"
#include "my_malloc.h"
#include "my_free.h"
#include "my_realloc.h"

int main() {
    int *ptr = my_calloc(10, sizeof(int));
    for (int i = 0; i < 10; i++) {
        printf("%d\n", ptr[i]);
    }
    my_free(ptr);

    char *str = my_malloc(12);
    str[0] = 'H';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';
    str[5] = ' ';
    str[6] = 'W';
    str[7] = 'o';
    str[8] = 'r';
    str[9] = 'l';
    str[10] = 'd';
    str[11] = '\0';
    printf("%s\n", str);

    my_free(str);

    return 0;
}

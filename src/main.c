void *my_malloc(int size);
void my_free(void *ptr);
void* my_realloc(void* ptr, int new_size);

#include <stdio.h>

int main() {
    char *str = my_malloc(5);

    for (int i = 0; i < 5; i++)
        str[i] = 'a';
    str[4] = '\0';

    printf("%s", str);

    str = my_realloc(str, 10);

    for (int i = 4; i < 10; i++)
        str[i] = 'b';
    str[9] = '\0';

    printf("%s", str);

    my_free(str);

    return 0;
}

void *my_malloc(int size);
void my_free(void *ptr);

#include <stdio.h>

int main() {
    char *str = my_malloc(5);

    str[0] = 'h';
    str[1] = 'i';
    str[2] = '!';
    str[3] = '\n';
    str[4] = '\0';

    char *str2 = my_malloc(5);

    str2[0] = 'b';
    str2[1] = 'y';
    str2[2] = 'e';
    str2[3] = '\n';
    str2[4] = '\0';

    printf("%s", str);
    printf("%s", str2);

    char *str3 = my_malloc(20);

    for (int i = 0; i < 20; i++)
        str3[i] = 'a';
    str3[18] = '\n';
    str3[19] = '\0';

    printf("%s", str3);

    my_free(str);
    my_free(str2);
    my_free(str3);

    char *str4 = my_malloc(20);
    str = my_malloc(5);

    str[0] = 'h';
    str[1] = 'i';
    str[2] = '!';
    str[3] = '\n';
    str[4] = '\0';

    for (int i = 0; i < 15; i++)
        str4[i] = 'b';
    str4[13] = '\n';
    str4[14] = '\0';

    printf("%s", str4);
    printf("%s", str);

    my_free(str4);
    my_free(str);

    return 0;
}

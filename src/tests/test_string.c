#include <stdio.h>

#include "adt.h"

int main() {
    printf("--- Driver Test String ---");
    printf("\n");
    printf("\n");
    char src[] = "halo";
    String dest = StringFrom(src);
    dest = concat_string(dest, StringFrom(" dunia"));
    printf("%s\n", STR_VALUE(dest));
    dest = concat_string(dest, StringFrom("       \n\t"));
    printf("Concatenation before trimming: %s\n", STR_VALUE(concat_string(dest, StringFrom("abc"))));
    dest = trim_end(dest);
    printf("Concatenation after trimming: %s\n", STR_VALUE(concat_string(dest, StringFrom("abc"))));
    printf("dest value after concatenation: %s\n", STR_VALUE(dest));
    String dunia = substring(dest, 5, 10);
    printf("%s\n", STR_VALUE(dunia));
    printf("%d\n", length(dunia));
    printf("\n");
    printf("--------------------------");
    printf("\n");
    printf("\n");
    return 0;
}

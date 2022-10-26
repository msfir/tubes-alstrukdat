#include "cstring.h"
#include <stdio.h>

int main() {
    char src[] = "halo";
    String dest = StringFrom(src);
    dest = concat_string(dest, StringFrom(" dunia"));
    printf("%s\n", STR_VALUE(dest));
}

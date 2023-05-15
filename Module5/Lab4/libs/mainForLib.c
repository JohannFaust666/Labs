#include <stdio.h>
#include "arithmetics.h"

int main() {
    int a = 5;
    int b = 3;

    printf("%d + %d = %d\n", a, b, add(a, b));
    printf("%d - %d = %d\n", a, b, subtract(a, b));

    return 0;
}

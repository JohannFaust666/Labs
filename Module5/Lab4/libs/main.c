#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *handle;
    int (*add)(int, int), (*subtract)(int, int);
    char *error;

    handle = dlopen("./libarithmetics.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    dlerror();    /* Clear any existing error */

    add = dlsym(handle, "add");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        return 1;
    }

    subtract = dlsym(handle, "subtract");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        return 1;
    }

    int a = 5;
    int b = 3;

    printf("%d + %d = %d\n", a, b, (*add)(a, b));
    printf("%d - %d = %d\n", a, b, (*subtract)(a, b));

    dlclose(handle);

    return 0;
}

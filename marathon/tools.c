#include "tools.h"

void * mallocSafe(size_t size) {
    void *result = malloc(size);
    if (result != NULL) 
        return result;
    else 
        exit(1);
}
int max(int x, int y) {
    if (x >= y)
        return x;
    else 
        return y;
}

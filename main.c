#include "hashmap.h"
#include <stdio.h>

int main() {
    hash_map* map = malloc(sizeof(hash_map));
    constructor(map, 10);
    printf("%p\n", (void*)map);

    free(map);
    return 0;
}
#include "hashmap.h"


int main() {
    hash_map* map = malloc(sizeof(hash_map));
    constructor(map, 10);

    int p = 10;
    int *q = &p;

    int p2 = 20;
    int *q2 = &p2;

    printf("running set\n");
    set(map, "a1", q);
    set(map, "a6", q2);

    printf("running get\n");
    int* w1 = (int*)get(map, "a1");
    int* w2 = (int*)get(map, "a6");
    printf("%d :: %d\n", *w1, *w2);
    free(map);
    return 0;
}
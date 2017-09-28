#include "hashmap.h"

void constructor(hash_map* map, int size) {
    bucket *arr = calloc(size, sizeof(bucket));
    map->size = size;
    map->count = 0;
    map->items = arr;
}
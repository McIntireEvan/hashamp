#include "hashmap.h"
#include <string.h>

/* Naive string hashing function */
int hash_string(hash_map* map, char *str) {
    unsigned long val = 0;

    while(*str++) {
        val = (val << 4) + *str;
    }

    return val % map->size;
}

void constructor(hash_map* map, int size) {
    map->size = size;
    map->count = 0;
    map->items = calloc(size, sizeof(bucket*));
}

int set(hash_map* map, char *key, void *value) {
    int bucket_num = hash_string(map, key);
    bucket *item = map->items[bucket_num];
    bucket *next;

    next = malloc(sizeof(bucket));
    next->ptr = (void*)value;
    next->key = malloc(strlen(key) + 1);
    strcpy(next->key, key);
    next->next = NULL;

    if(item) {
        while(item->next) {
            item = item->next;
        }
        item->next = next;
    } else {
        map->items[bucket_num] = next;
    }
    return 0;
}

void *get(hash_map* map, char *key) {
    int bucket_num = hash_string(map, key);
    bucket *item = map->items[bucket_num];

    if(item) {
        while(item->next && strcmp(item->key, key)) {
            item = item->next;
        }
        return item->ptr;
    } else {
        return NULL;
    }
}
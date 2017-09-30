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
    if(map->count == map->size) {
        return 0;
    }

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

    map->count++;
    return 1;
}

void *get(hash_map* map, char *key) {
    int bucket_num = hash_string(map, key);
    bucket *item = map->items[bucket_num];

    if(item) {
        while(item->next && strcmp(item->key, key)) {
            item = item->next;
        }
        if(!strcmp(item->key, key)) {
            return item->ptr;
        }
    }

    return NULL;
}

void *delete(hash_map *map, char* key) {
    int bucket_num = hash_string(map, key);
    bucket *item = map->items[bucket_num];
    bucket *prev = item;
    bucket *new;
    void* ret;

    if(item) {
        while(item->next && strcmp(item->key, key)) {
            prev = item;
            item = item->next;
        }

        if(strcmp(item->key, key)) {
            return NULL;
        }

        new = item->next;
        ret = item->ptr;

        if(item == map->items[bucket_num]) {
            map->items[bucket_num] = new;
        } else {
            prev->next = new;
        }

        free(item->key);
        free(item);
    }

    return NULL;
}

float load(hash_map *map) {
    return (1.0) * (map->count / map->count);
}

void free_bucket(bucket *buck) {
    if(!buck) {
        return;
    }
    free_bucket(buck->next);
    free(buck->key);
    free(buck);
}

void destructor(hash_map *map) {
    for(int i = 0; i < map->size; i++) {
        free_bucket(map->items[i]);
    }
    free(map);
}
#include <stdlib.h>
#include <stdio.h>

/*  Each bucket acts as a linked list */
typedef struct bucket_t {
    void *ptr;
    char *key;
    struct bucket_t *next;
} bucket;

typedef struct hash_map_t {
    int size;
    int count;
    bucket **items;
} hash_map;

void constructor(hash_map *map, int size);
int set(hash_map *map, char *key, void *value);
void *get(hash_map *map, char *key);
void *delete(hash_map *map, char* key);
float load(hash_map *map);
void destructor(hash_map *map);
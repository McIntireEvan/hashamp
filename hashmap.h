#include <stdlib.h>

/*  Each bucket acts as a linked list */
typedef struct bucket_t {
    void *ptr;
    char **key;
    struct bucket_t *next;
} bucket;

typedef struct hash_map_t {
    int size;
    int count;
    bucket *items;
} hash_map;

void constructor(hash_map* map, int size);

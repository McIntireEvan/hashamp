#include "hashmap.h"

/* Naive string hashing function */
int hash_string(hash_map *map, char *str) {
    unsigned long val = 0;

    while(*str++) {
        val = (val << 4) + *str;
    }

    return val % map->size;
}

/* Constructs a hash_map by allocating all the needed memory */
void constructor(hash_map **map, int size) {
    *map = malloc(sizeof(hash_map));
    (*map)->size = size;
    (*map)->count = 0;
    (*map)->items = calloc(size, sizeof(bucket*));
}

/* Adds a key-value pair to the given map, or updates the value */
int set(hash_map *map, char *key, void *value) {
    /* Auto-fail if we've hit the max and we're not updating */
    if(!get(map, key) && map->count == map->size) {
        return 0;
    }

    /* Go to the correct bucket */
    int bucket_num = hash_string(map, key);
    bucket *item = map->items[bucket_num];
    bucket *next;

    /* If the value exists, we just find it and update */
    if(get(map, key)) {
        /* Traverse the list */
        while(item->next && strcmp(item->key, key)) {
            item = item->next;
        }
        /* Update value, return success */
        item->val = value;
        return 1;
    }

    /* Create new bucket*/
    next = malloc(sizeof(bucket));
    next->val = (void*)value;

    /* Copy the key */
    next->key = malloc(strlen(key) + 1);
    strcpy(next->key, key);

    next->next = NULL;

    /* Check if the list has a head */
    if(item) {
        /* It does, we find the end and add next to there*/
        while(item->next) {
            item = item->next;
        }
        item->next = next;
    } else {
        /* No head, so next is the head */
        map->items[bucket_num] = next;
    }

    /* Update count, return success */
    map->count++;
    return 1;
}

/* Retrieves a value given a key or NULL if not in the map*/
void *get(hash_map *map, char *key) {
    /* Find the correct bucket */
    int bucket_num = hash_string(map, key);
    bucket *item = map->items[bucket_num];
    if(item) {
        /* Traverse to item or end of list */
        while(item->next && strcmp(item->key, key)) {
            item = item->next;
        }
        /* Check if we actually found the item */
        if(!strcmp(item->key, key)) {
            return item->val;
        }
    }
    /* Couldn't find it */
    return NULL;
}

/* Deletes a key-value pair and returns the value or NULL if not in the map */
void *delete(hash_map *map, char *key) {
    /* Find the bucket, create some variables to keep track of our position */
    int bucket_num = hash_string(map, key);
    bucket *item = map->items[bucket_num];
    bucket *prev = item;
    bucket *new;
    void* ret;

    /* We can only delete something if there are entries in the bucket */
    if(item) {
        /* Traverse to the correct item, keeping track of the previous item */
        while(item->next && strcmp(item->key, key)) {
            prev = item;
            item = item->next;
        }

        /* We didn't find anything */
        if(strcmp(item->key, key)) {
            return NULL;
        }

        /* Get the values we need (next item and return value) */
        new = item->next;
        ret = item->val;

        if(item == map->items[bucket_num]) {
            /* If item was the head of its list, make the new item the head */
            map->items[bucket_num] = new;
        } else {
            /* Just have the previous item point to the new one */
            prev->next = new;
        }

        /* Free memory */
        free(item->key);
        free(item);

        /* Update item count */
        map->count--;
        return ret;
    }

    return NULL;
}

/* Returns a float value representing the load factor of the hashmap*/
float load(hash_map *map) {
    return (1.0 * map->count) / map->size;
}

/* Frees all the dynamically allocated memory for a bucket
 * Uses recursion to traverse to the end of the list, and free as it backs out
 */
void free_bucket(bucket *buck) {
    if(!buck) {
        return;
    }
    free_bucket(buck->next);
    free(buck->key);
    free(buck);
}

/* Frees all the dynamically allocated memory for a hash_map and destroys it */
void destructor(hash_map *map) {
    for(int i = 0; i < map->size; i++) {
        free_bucket(map->items[i]);
    }
    free(map);
}
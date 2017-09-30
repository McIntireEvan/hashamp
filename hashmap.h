#include <stdlib.h>
#include <string.h>

/* bucket type that holds key-value pairs as a linked list */
typedef struct bucket_t {
    /* Value; can be a pointer to any type */
    void *val;

    /* Key that the value is associated with */
    char *key;

    /* The next bucket in the list */
    struct bucket_t *next;
} bucket;

/* hash_map type that associates a string key with a generic pointer */
typedef struct hash_map_t {
    /* Max number of elements */
    int size;

    /* Current number of elements */
    int count;

    /* Array of pointers to buckets */
    bucket **items;
} hash_map;

/* Constructs a hash_map by allocating all the needed memory */
void constructor(hash_map **map, int size);

/* Adds a key-value pair to the given map, or updates the value */
int set(hash_map *map, char *key, void *value);

/* Retrieves a value given a key or NULL if not in the map*/
void *get(hash_map *map, char *key);

/* Deletes a key-value pair and returns the value or NULL if not in the map */
void *delete(hash_map *map, char* key);

/* Returns a float value representing the load factor of the hashmap*/
float load(hash_map *map);

/* Frees all the dynamically allocated memory for a hash_map and destroys it */
void destructor(hash_map *map);
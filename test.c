#include <stdio.h>
#include "hashmap.h"

void test_empty() {
    printf("Testing empty map");
    hash_map *map;

    printf("Creating map\n");
    constructor(&map, 5);
    if(!map) {
        printf("constructor failed; map is null\n");
        exit(0);
    }

    printf("Checking map size\n");
    if(!(map->size == 5)) {
        printf("constructor failed; size is wrong\n");
        exit(0);
    }

    printf("Checking map count\n");
    if(!(map->count == 0)) {
        printf("constructor failed; count is wrong\n");
        exit(0);
    }

    printf("Checking get on non-existent value\n");
    if(get(map, "test")) {
        printf("constructor failed; unexpected entry\n");
        exit(0);
    }

    printf("Checking delete on non-existent value\n");
    if(delete(map, "test")) {
        printf("constructor failed; unexpected entry\n");
        exit(0);
    }

    printf("Checking load\n");
    if(load(map) != 0.0) {
        printf("constructor failed; load is non-zero\n");
        exit(0);
    }
    destructor(map);
    printf("All empty map tests passed\n");
}

void test_get_help(hash_map *map, char *key, int expected,char* fail) {
    int *p = (int*)get(map, key);
    if(!p || *p != expected) {
        printf("%s\n", fail);
        exit(0);
    }
}

void test_non_empty() {
    printf("Testing non-empty map\n");

    hash_map *map;
    printf("Creating map\n");
    constructor(&map, 6);

    /*
     * We're going to add 6 elements, and retrive all of them.
     * The hash of "a1" and "a6" collide, but the test shows they work
     */
    int a = 0, b = 10, c = 10, d = 30, e = 500, f = -12, g = 42;
    printf("Checking set\n");
    if(!set(map, "a1", &a)) {
        printf("Failed set a1:%d\n", a);
        exit(0);
    }

    if(!set(map, "a2", &b)) {
        printf("Failed set a2:%d\n", b);
        exit(0);
    }

    if(!set(map, "a3", &c)) {
        printf("Failed set a3:%d\n", c);
        exit(0);
    }

    if(!set(map, "a4", &d)) {
        printf("Failed set a4:%d\n", d);
        exit(0);
    }

    if(!set(map, "a5", &e)) {
        printf("Failed set a5:%d\n", e);
        exit(0);
    }

    if(!set(map, "a6", &f)) {
        printf("Failed set a6:%d\n", f);
        exit(0);
    }

    if(set(map, "fail", &g)) {
        printf("exceeded maximum size without failing\n");
        exit(0);
    }

    if(!set(map, "a6", &g)) {
        printf("Failed set(update) a6:%d\n", g);
        exit(0);
    }

    printf("Check get\n");

    test_get_help(map, "a1", a, "get mismatch for a1");
    test_get_help(map, "a2", b, "get mismatch for a2");
    test_get_help(map, "a3", c, "get mismatch for a3");
    test_get_help(map, "a4", d, "get mismatch for a4");
    test_get_help(map, "a5", e, "get mismatch for a5");
    test_get_help(map, "a6", g, "get mismatch for a6");

    /* Testing load at max */
    printf("Testing max load\n");
    if ((load(map) - 1.0) != 0) {
        printf("Invalid load: expected 1.0; got %.1f\n", load(map));
        exit(0);
    }

    /* Testing delete */
    printf("Checking delete\n");

    int *p = (int*)delete(map, "a6");
    if(!p || *p != g) {
        printf("delete mismatch for a6:%d\n", g);
        exit(0);
    }

    if(get(map, "a6")) {
        printf("got non-null for deleted value\n");
        exit(0);
    }

    destructor(map);
    printf("All non-empty map test passed\n");
}

int main() {
    test_empty();
    test_non_empty();
    printf("All tests passed!\n");
    return 0;
}
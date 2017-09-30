# hashmap

An implementation of a hashmap in C

## Running
To build, just run `make`
To run the test cases, `./build/test`

## Details
This implementation uses seperate chaining with linked lists for the buckets.
That is, the main `hash_map` type has an array of `bucket`s, and each `bucket`
is a linked list.

When an element is set, the hash of the key becomes the index in the array, and
the pair is added to that linked list.

## Improvements
The `hash_string` function isn't amazing - it could probably be swapped out with
the `djb2` algorithm by Dan Bernstein for a lower amount of collisions

Other methods of bucketing, i.e. linear probing, can be more effecient, but
seperate chaining is good enough, and ofter more clear for demonstration purposes.
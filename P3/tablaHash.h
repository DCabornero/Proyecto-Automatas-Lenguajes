#ifndef TABLAHASH_H
#define TABLAHASH_H
#define MAX_LINE 256
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

typedef struct entry_s entry_t;

typedef struct hashtable_s hashtable_t;

hashtable_t *ht_create( int size );

/* Hash a string for a particular hash table. */
int ht_hash( hashtable_t *hashtable, char *key );

/* Create a key-value pair. */
entry_t *ht_newpair( char *key, int value );

/* Insert a key-value pair into a hash table. */
void ht_set( hashtable_t *hashtable, char *key, int value );

/* Retrieve a key-value pair from a hash table. */
int ht_get( hashtable_t *hashtable, char *key );

void ht_destroy(hashtable_t *hashtable);

#endif

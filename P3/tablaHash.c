#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux.  See feature_test_macros(7) */
#define MAX_LINE 256

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <math.h>

struct entry_s {
	char *key;
	int value;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

struct hashtable_s {
	int size;
	struct entry_s **table;
};

typedef struct hashtable_s hashtable_t;


/* Create a new hashtable. */
hashtable_t *ht_create( int size ) {

	hashtable_t *hashtable = NULL;
	int i;

	if( size < 1 ) return NULL;

	/* Allocate the table itself. */
	if( ( hashtable = malloc( sizeof( hashtable_t ) ) ) == NULL ) {
		return NULL;
	}

	/* Allocate pointers to the head nodes. */
	if( ( hashtable->table = malloc( sizeof( entry_t * ) * size ) ) == NULL ) {
		return NULL;
	}
	for( i = 0; i < size; i++ ) {
		hashtable->table[i] = NULL;
	}

	hashtable->size = size;

	return hashtable;
}

/* Hash a string for a particular hash table. */
int ht_hash( hashtable_t *hashtable, char *key ) {

	unsigned long int hashval;
	int i = 0;

	/* Convert our string to an integer */
	while( hashval < ULONG_MAX && i < strlen( key ) ) {
		hashval = hashval << 8;
		hashval += key[ i ];
		i++;
	}

	return hashval % hashtable->size;
}

/* Create a key-value pair. */
entry_t *ht_newpair( char *key, int value ) {
	entry_t *newpair;

	if( ( newpair = malloc( sizeof( entry_t ) ) ) == NULL ) {
		return NULL;
	}

	if( ( newpair->key = strdup( key ) ) == NULL ) {
		return NULL;
	}

	newpair->value = value;

	newpair->next = NULL;

	return newpair;
}

/* Insert a key-value pair into a hash table. */
void ht_set( hashtable_t *hashtable, char *key, int value ) {
	int bin = 0;
	entry_t *newpair = NULL;
	entry_t *next = NULL;
	entry_t *last = NULL;

	bin = ht_hash( hashtable, key );

	next = hashtable->table[ bin ];

	while( next != NULL && next->key != NULL && strcmp( key, next->key ) > 0 ) {
		last = next;
		next = next->next;
	}

	/* There's already a pair.  Let's replace that string. */
	if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 ) {

		next->value = value;

	/* Nope, could't find it.  Time to grow a pair. */
	} else {
		newpair = ht_newpair( key, value );

		/* We're at the start of the linked list in this bin. */
		if( next == hashtable->table[ bin ] ) {
			newpair->next = next;
			hashtable->table[ bin ] = newpair;

		/* We're at the end of the linked list in this bin. */
		} else if ( next == NULL ) {
			last->next = newpair;

		/* We're in the middle of the list. */
		} else  {
			newpair->next = next;
			last->next = newpair;
		}
	}
}

/* Retrieve a key-value pair from a hash table. */
int ht_get( hashtable_t *hashtable, char *key ) {
	int bin = 0;
	entry_t *pair;

	bin = ht_hash( hashtable, key );

	/* Step through the bin, looking for our value. */
	pair = hashtable->table[ bin ];
	while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 ) {
		pair = pair->next;
	}

	/* Did we actually find anything? */
	if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ) {
		return (int) NAN;

	} else {
		return pair->value;
	}

}


int main( int argc, char **argv ) {

  char* key;
  char* val;
  int i, flag, value;
  char buf[MAX_LINE];
  FILE* fin = NULL;
  FILE* fout = NULL;

	hashtable_t *hashtable = ht_create(65536);

  if(argc != 3){
    printf("Usage is ./prueba_tabla fichero_entrada fichero_salida\n");
  }

  fin = fopen(argv[1], "r");
  if(!fin){
    printf("El fichero de entrada es inválido\n");
    return 0;
  }

  fout = fopen(argv[2], "w");
  if(!fout){
    printf("El fichero de salida no se ha podido crear\n");
    fclose(fin);
    return 0;
  }

  while(fgets(buf, MAX_LINE, fin) != NULL){
    flag = 0;
    for(i=0; i<strlen(buf)+1; i++){
      if(buf[i] == ' '){
        buf[i] = 0;
        flag = 1;
        break;
      }
    }
    key = buf;
    if(flag){
      val = buf+i+1;
      value = ht_get(hashtable, key);
      if(value == (int)NAN){
        ht_set(hashtable, key, atoi(val));
        fprintf(fout, "%s\n", key);
      }
      else{
        fprintf(fout, "-1 %s\n", key);
      }
    }
    if(!flag){
      value = ht_get(hashtable, key);
      if(value == (int)NAN){
        value = -1;
      }
      fprintf(fout, "%s %d\n", val, value);
    }
  }
  fclose(fin);
  fclose(fout);

	return 0;
}

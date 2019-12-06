#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux.  See feature_test_macros(7) */


#include "tablaHash.h"

struct entry_s {
	char *key;
	struct SIMBOLO* value;
	struct entry_s *next;
};



struct hashtable_s {
	int size;
	struct entry_s **table;
};


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

	unsigned long int hashval = 0;
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
entry_t *ht_newpair( char *key, CATEGORIA_SIMBOLO cat_simbolo, TIPO tipo, CATEGORIA categoria, int valor, int longitud, int num_parametros, int posicion, int num_var_locales ) {
	entry_t *newpair;

	if( ( newpair = malloc( sizeof( entry_t ) ) ) == NULL ) {
		return NULL;
	}

	if( ( newpair->key = strdup( key ) ) == NULL ) {
		return NULL;
	}

	newpair->value = malloc(sizeof(SIMBOLO));

	newpair->value->cat_simbolo = cat_simbolo;
	newpair->value->tipo = tipo;
	newpair->value->categoria = categoria;
	newpair->value->valor = valor;
	newpair->value->longitud = longitud;
	newpair->value->num_parametros = num_parametros;
	newpair->value->posicion = posicion;
	newpair->value->num_var_locales = num_var_locales;

	newpair->next = NULL;

	return newpair;
}

/* Insert a key-value pair into a hash table. */
void ht_set( hashtable_t *hashtable, char *key, CATEGORIA_SIMBOLO cat_simbolo, TIPO tipo, CATEGORIA categoria, int valor, int longitud, int num_parametros, int posicion, int num_var_locales) {
	int bin = 0;
	entry_t *newpair = NULL;
	entry_t *next = NULL;
	entry_t *last = NULL;

	bin = ht_hash( hashtable, key);

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
		newpair = ht_newpair( hashtable, key, cat_simbolo, tipo, categoria, valor, longitud, num_parametros, posicion, num_var_locales);

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
SIMBOLO* ht_get( hashtable_t *hashtable, char *key ) {
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

void ht_destroy(hashtable_t *hashtable){
	int i;
	entry_t *curr, *next;
	if(!hashtable){
		return;
	}
	for(i=0;i<hashtable->size;i++){
		curr = hashtable->table[i];
		if(!curr){
			continue;
		}
		while(curr->next){
			next = curr->next;
			free(curr->value);
			free(curr->key);
			free(curr);
			curr = next;
		}
		free(curr->key);
		free(curr);
	}
	free(hashtable->table);
	free(hashtable);
	return;
}

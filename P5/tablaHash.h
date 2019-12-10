#ifndef TABLAHASH_H
#define TABLAHASH_H
#define MAX_LINE 256
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

/* Categoría de un símbolo: variable, parámetro de función o función */
typedef enum { VARIABLE, PARAMETRO, FUNCION } CATEGORIA_SIMBOLO;

/* Tipo de un símbolo: sólo se trabajará con enteros y booleanos */
typedef enum { ENTERO, BOOLEANO } TIPO;

/* Categoría de la variable: puede ser variable atómicas (escalar) o lista/array (vector) */
typedef enum { ESCALAR, VECTOR } CATEGORIA;

typedef struct SIMBOLO_{
	CATEGORIA_SIMBOLO cat_simbolo;      /* categoría del simbolo */
	TIPO tipo;                          /* tipo */
  CATEGORIA categoria;                /* categoria de la variable */
  int valor;                          /* valor si escalar */
  int longitud;                       /* longitud si vector */
  int num_parametros;                 /* número de parámetros si función */
  int posicion;                       /* posición en llamada a función si parámetro, posición de declaración si variable local de función */
  int num_var_locales;                /* número de variables locales si función */
} SIMBOLO;

typedef struct entry_s entry_t;

typedef struct hashtable_s hashtable_t;

hashtable_t *ht_create( int size );

/* Hash a string for a particular hash table. */
int ht_hash( hashtable_t *hashtable, char *key );

/* Create a key-value pair. */
entry_t *ht_newpair( char *key, CATEGORIA_SIMBOLO cat_simbolo, TIPO tipo, CATEGORIA categoria, int valor, int longitud, int num_parametros, int posicion, int num_var_locales );

/* Insert a key-value pair into a hash table. */
void ht_set( hashtable_t *hashtable, char *key, CATEGORIA_SIMBOLO cat_simbolo, TIPO tipo, CATEGORIA categoria, int valor, int longitud, int num_parametros, int posicion, int num_var_locales);

/* Retrieve a key-value pair from a hash table. */
SIMBOLO* ht_get( hashtable_t *hashtable, char *key );

void ht_destroy(hashtable_t *hashtable);

#endif

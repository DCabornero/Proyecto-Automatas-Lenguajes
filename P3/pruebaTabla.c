#include "tablaHash.h"

int main( int argc, char **argv ) {

  char* key;
  char* val;
  int i, flag, value, intval;
  char buf[MAX_LINE];
  FILE* fin = NULL;
  FILE* fout = NULL;

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
	hashtable_t *target_table = NULL;
	hashtable_t *hashtable_g = ht_create(65536);
	hashtable_t *hashtable_l = NULL;

  while(fgets(buf, MAX_LINE, fin) != NULL){
    flag = 0;
    for(i=0; i<strlen(buf)-1; i++){
      if(buf[i] == '\t'){
        buf[i] = 0;
        flag = 1;
        break;
      }
    }
    key = buf;
		// Descartamos el \n
		if(!flag){
			key[strlen(key)-1] = 0;
		}
		// Inserción o función
    if(flag){
      val = buf+i+1;
			intval = atoi(val);
			// Inserción
			if(intval >= 0){
				// Intentamos insertar en la local si hay
				if(hashtable_l){
					target_table = hashtable_l;
				}
				// Si no intentaremos insertar en la global
				else{
					target_table = hashtable_g;
				}
      	value = ht_get(target_table, key);
      	if(value == (int)NAN){
        	ht_set(target_table, key, intval);
        	fprintf(fout, "%s\n", key);
      	}
				// Si no, no se ha podido insertar
      	else{
          fprintf(fout, "-1\t%s\n", key);
      	}
    	}
			// Función
			else{
				// Cierre
				if(!strcmp(key, "cierre") && intval == -999){
					ht_destroy(hashtable_l);
					hashtable_l = NULL;
					fprintf(fout, "cierre\n");
				}
				else{
					// Suponemos que no se va a abrir otro ámbito sin cerrar el anterior
          // Parece ser que no se puede suponer lo jodidamente evidente, pero bueno
          if(hashtable_l){
            fprintf(fout, "-1\t%s\n", key);
          }
          else{
					    hashtable_l = ht_create(65536);
				    	ht_set(hashtable_g, key, intval);
				    	ht_set(hashtable_l, key, intval);
				    	fprintf(fout, "%s\n", key);
        }
				}
			}
		}
		// Búsqueda
    if(!flag){
			// Primero intentamos buscar en la local
			if(hashtable_l){
				value = ht_get(hashtable_l, key);
				// Encontrado en la local
				if(value != (int)NAN){
					fprintf(fout, "%s\t%d\n", key, value);
					continue;
				}
			}
			// Si no hay local o no se ha encontrado, buscamos en la global
      value = ht_get(hashtable_g, key);
      if(value == (int)NAN){
        value = -1;
      }
      fprintf(fout, "%s\t%d\n", key, value);
    }
  }
	if(hashtable_l){
		ht_destroy(hashtable_l);
	}
	ht_destroy(hashtable_g);
  fclose(fin);
  fclose(fout);

	return 0;
}

#include "tablaSimbolos.h"

hashtable_t * tablaGlobal = NULL;
hashtable_t * tablaLocal = NULL;

STATUS declarar(char* id, SIMBOLO* desc_id){
  if(tablaLocal != NULL){
    if(ht_get(tablaLocal, id)){
      return ERROR;
    }
    else{
      ht_set(tablaLocal, id, desc_id->cat_simbolo, desc_id->tipo, desc_id->categoria, desc_id->valor, desc_id->longitud, desc_id->num_parametros, desc_id->posicion, desc_id->num_var_locales);
      return OK;
    }
  }
  else{
    if(tablaGlobal == NULL){
      tablaGlobal = ht_create(MAX_TABLA_SIMBOLOS);
    }
    if(ht_get(tablaGlobal, id)){
      return ERROR;
    }
    else{
      ht_set(tablaGlobal, id, desc_id->cat_simbolo, desc_id->tipo, desc_id->categoria, desc_id->valor, desc_id->longitud, desc_id->num_parametros, desc_id->posicion, desc_id->num_var_locales);
      return OK;
    }
  }
  return ERROR;
}

SIMBOLO* usoGlobal(char* id){
  if(tablaGlobal == NULL){
    return NULL;
  }
  return ht_get(tablaGlobal, id);
}

SIMBOLO* usoLocal(char* id){
  if(tablaLocal == NULL){
    return NULL;
  }
  return ht_get(tablaLocal, id);
}

STATUS declararFuncionTS(char* id, SIMBOLO* desc_id){
  if(ht_get(tablaGlobal, id) != NULL){
    return ERROR;
  }
  tablaLocal = ht_create(MAX_TABLA_SIMBOLOS);
  ht_set(tablaGlobal, id, desc_id->cat_simbolo, desc_id->tipo, desc_id->categoria, desc_id->valor, desc_id->longitud, desc_id->num_parametros, desc_id->posicion, desc_id->num_var_locales);
  ht_set(tablaLocal, id, desc_id->cat_simbolo, desc_id->tipo, desc_id->categoria, desc_id->valor, desc_id->longitud, desc_id->num_parametros, desc_id->posicion, desc_id->num_var_locales);
  return OK;
}

STATUS cerrarFuncion(){
  if(tablaLocal == NULL){
    return ERROR;
  }
  ht_destroy(tablaLocal);
  return OK;
}

void eliminar(){
  if(tablaGlobal){
    ht_destroy(tablaGlobal);
  }
  if(tablaLocal){
    ht_destroy(tablaLocal);
  }
}

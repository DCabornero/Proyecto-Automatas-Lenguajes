%{
#include "alfa.h"
extern long ncol;
extern long nlin;
extern int is_morpho;
extern int yyleng;
int yylex();
int tipo_actual;
int clase_actual;
int ambito_actual = GLOBAL;
int tamanio_vector;
int etiquetas = 1;
int retornado = 0;
int posicion_parametro = 0;
int num_variables_locales = 0;
int num_parametros = 0;
int call_params = 0;
int calling = 0;
char aux_itoa[32];
SIMBOLO* simbolo_actual = NULL;
SIMBOLO* simbolo_creado = NULL;
void yyerror(const char *s);
extern FILE* out;
%}

%union{
  tipo_atributos atributos;
}

/* Palabras reservadas */
%token TOK_MAIN
%token TOK_INT
%token TOK_BOOLEAN
%token TOK_ARRAY
%token TOK_FUNCTION
%token TOK_IF
%token TOK_ELSE
%token TOK_WHILE
%token TOK_SCANF
%token TOK_PRINTF
%token TOK_RETURN
%token TOK_PUNTOYCOMA
%token TOK_COMA
%token TOK_PARENTESISIZQUIERDO
%token TOK_PARENTESISDERECHO
%token TOK_CORCHETEIZQUIERDO
%token TOK_CORCHETEDERECHO
%token TOK_LLAVEIZQUIERDA
%token TOK_LLAVEDERECHA
%token TOK_ASIGNACION
%token TOK_MAS
%token TOK_MENOS
%token TOK_DIVISION
%token TOK_ASTERISCO
%token TOK_AND
%token TOK_OR
%token TOK_NOT
%token TOK_IGUAL
%token TOK_DISTINTO
%token TOK_MENORIGUAL
%token TOK_MAYORIGUAL
%token TOK_MENOR
%token TOK_MAYOR
%token <atributos> TOK_CONSTANTE_ENTERA
%token <atributos> TOK_IDENTIFICADOR
%token TOK_TRUE
%token TOK_FALSE
%token TOK_ERROR
%token TOK_IDENTIFICADORERROR

%type <atributos> constante
%type <atributos> constante_entera
%type <atributos> constante_logica
%type <atributos> exp
%type <atributos> condicional
%type <atributos> elemento_vector
%type <atributos> identificador
%type <atributos> comparacion
%type <atributos> if_exp
%type <atributos> if_exp_sentencias
%type <atributos> while
%type <atributos> while_exp
%type <atributos> fun_call
%type <atributos> fn_declaration
%type <atributos> fn_name


%right TOK_ASIGNACION
%left TOK_OR
%left TOK_AND
%left TOK_IGUAL TOK_DISTINTO
%left TOK_MENOR TOK_MENORIGUAL TOK_MAYOR TOK_MAYORIGUAL
%left TOK_MAS TOK_MENOS
%left TOK_DIVISION TOK_ASTERISCO
%right TOK_NOT
%left TOK_PARENTESISIZQUIERDO TOK_PARENTESISDERECHO
%%

programa: TOK_MAIN TOK_LLAVEIZQUIERDA escritura1 declaraciones escritura2 funciones escritura3 sentencias TOK_LLAVEDERECHA {
  escribir_fin(out);
  fprintf(out, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> }\n");
};
escritura1: %empty{
  escribir_subseccion_data(out);
  escribir_cabecera_bss(out);
};
escritura2: %empty{
  escribir_segmento_codigo(out);
}
escritura3: %empty{
  escribir_inicio_main(out);
};
declaraciones: declaracion {fprintf(out, ";R2:\t<declaraciones> ::= <declaracion>\n");}
               | declaracion declaraciones {fprintf(out, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones>\n");};
declaracion: clase identificadores TOK_PUNTOYCOMA {fprintf(out, ";R4:\t<declaracion> ::= <clase> <identificadores> ;\n");};
clase: clase_escalar {clase_actual=ESCALAR; fprintf(out, ";R5:\t<clase> ::= <clase_escalar>\n");}
       | clase_vector {clase_actual=VECTOR; fprintf(out, ";R7:\t<clase> ::= <clase_vector>\n");};
clase_escalar: tipo {
  fprintf(out, ";R9:\t<clase_escalar> ::= <tipo>\n");
};
tipo: TOK_INT {tipo_actual=ENTERO; fprintf(out, ";R10:\t<tipo> ::= int\n");}
      | TOK_BOOLEAN {tipo_actual=BOOLEANO; fprintf(out, ";R11:\t<tipo> ::= boolean\n");};
clase_vector: TOK_ARRAY tipo TOK_CORCHETEIZQUIERDO TOK_CONSTANTE_ENTERA TOK_CORCHETEDERECHO {
  tamanio_vector = $4.valor_entero;
  fprintf(out, ";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ]\n");
};
identificadores: identificador {fprintf(out, ";R18:\t<identificadores> ::= <identificador>\n");}
                 | identificador TOK_COMA identificadores {fprintf(out, ";R19:\t<identificadores> ::= <identificador> , <identificadores>\n");};
funciones: funcion funciones {fprintf(out, ";R20:\t<funciones> ::= <funcion> <funciones>\n");}
           | %empty {fprintf(out, ";R21:\t<funciones> ::=\n");};
funcion: fn_declaration sentencias TOK_LLAVEDERECHA {
  if(retornado == 0){
    printf("****Error semantico en lin %ld: Funcion %s sin sentencia de retorno.\n", nlin, $1.lexema);
    return -1;
  }
  if($1.tipo != tipo_actual){
    printf("****Error semantico en lin %ld: Retorno de funcion %s incompatible.\n", nlin, $1.lexema);
    return -1;
  }
  cerrarFuncion();
  ambito_actual = GLOBAL;
  simbolo_actual = usoGlobal($1.lexema);
  simbolo_actual->cat_simbolo = FUNCION;
  fprintf(out, ";R22:\t<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }\n");
};

fn_declaration: fn_name TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA declaraciones_funcion {
  simbolo_actual = usoGlobal($1.lexema);
  simbolo_actual->num_parametros = num_parametros;
  strcpy($$.lexema, $1.lexema);
  $$.tipo = $1.tipo;
  declararFuncion(out, $1.lexema, num_variables_locales);
};

fn_name: TOK_FUNCTION tipo TOK_IDENTIFICADOR{
  retornado = 0;
  ambito_actual = LOCAL;
  simbolo_actual = usoGlobal($3.lexema);
  if(simbolo_actual != NULL){
    printf("****Error semantico en lin %ld: Declaracion duplicada.\n", nlin);
    return -1;
  }
  simbolo_creado = (SIMBOLO*)calloc(1, sizeof(SIMBOLO));
  simbolo_creado->cat_simbolo = FUNCION;
  simbolo_creado->tipo = tipo_actual;
  declararFuncionTS($3.lexema, simbolo_creado);
  free(simbolo_creado);
  $$.tipo = tipo_actual;
  strcpy($$.lexema, $3.lexema);
  num_variables_locales = 0;
  posicion_parametro = 0;
  num_parametros = 0;
};

parametros_funcion: parametro_funcion resto_parametros_funcion
                    | %empty;

resto_parametros_funcion: TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion
                          | %empty;

parametro_funcion: tipo idpf {
  num_parametros++;
  posicion_parametro++;
};

idpf: TOK_IDENTIFICADOR{
  simbolo_actual = usoLocal($1.lexema);
  if(simbolo_actual != NULL){
    printf("****Error semantico en lin %ld: Declaracion duplicada.\n", nlin);
    return -1;
  }
  simbolo_creado = (SIMBOLO*)calloc(1, sizeof(SIMBOLO));
  simbolo_creado->cat_simbolo = PARAMETRO;
  simbolo_creado->tipo = tipo_actual;
  simbolo_creado->categoria = ESCALAR;
  simbolo_creado->posicion = posicion_parametro;
  declarar($1.lexema, simbolo_creado);
  free(simbolo_creado);
};
declaraciones_funcion: declaraciones {fprintf(out, ";R28:\t<declaraciones_funcion> ::= <declaraciones>\n");}
                       | %empty {fprintf(out, ";R29:\t<declaraciones_funcion> ::=\n");};
sentencias: sentencia {fprintf(out, ";R30:\t<sentencias> ::= <sentencia>\n");}
            | sentencia sentencias {fprintf(out, ";R31:\t<sentencias> ::= <sentencia> <sentencias>\n");};
sentencia: sentencia_simple TOK_PUNTOYCOMA {fprintf(out, ";R32:\t<sentencia> ::= <sentencia_simple> ;\n");}
           | bloque {fprintf(out, ";R33:\t<sentencia> ::= <bloque>\n");};
sentencia_simple: asignacion {fprintf(out, ";R34:\t<sentencia_simple> ::= <asignacion>\n");}
                  | lectura {fprintf(out, ";R35:\t<sentencia_simple> ::= <lectura>\n");}
                  | escritura {fprintf(out, ";R36:\t<sentencia_simple> ::= <escritura>\n");}
                  | retorno_funcion {fprintf(out, ";R38:\t<sentencia_simple> ::= <retorno_funcion>\n");};
bloque: condicional {fprintf(out, ";R40:\t<bloque> ::= <condicional>\n");}
        | bucle {fprintf(out, ";R41:\t<bloque> ::= bucle\n");};
asignacion: TOK_IDENTIFICADOR TOK_ASIGNACION exp {
              if(ambito_actual == GLOBAL){
                simbolo_actual = usoGlobal($1.lexema);
              }
              else{
                simbolo_actual = usoLocal($1.lexema);
                if(simbolo_actual == NULL){
                  simbolo_actual = usoGlobal($1.lexema);
                }
              }
              if(simbolo_actual == NULL){
                printf("****Error semantico en lin %ld: Acceso a variable no declarada(<%s>).\n", nlin, $1.lexema);
                return -1;
              }
              if(simbolo_actual->cat_simbolo == FUNCION){
                printf("****Error semantico en lin %ld: Asignacion incompatible.\n", nlin);
                return -1;
              }
              if(simbolo_actual->categoria == VECTOR){
                printf("****Error semantico en lin %ld: Asignacion incompatible.\n", nlin);
                return -1;
              }
              if(simbolo_actual->tipo != $3.tipo){
                printf("****Error semantico en lin %ld: Asignacion incompatible.\n", nlin);
                return -1;
              }
              if(ambito_actual == LOCAL){
                if(simbolo_actual->cat_simbolo == PARAMETRO){
                  escribirParametro(out, simbolo_actual->posicion, num_parametros);
                  asignarDestinoEnPila(out, $3.es_direccion);
                }
                else if(simbolo_actual->cat_simbolo == VARIABLE){
                  escribirVariableLocal(out, simbolo_actual->posicion);
                  asignarDestinoEnPila(out, $3.es_direccion);
                }
              }
              else{
                asignar(out, $1.lexema, $3.es_direccion);
                fprintf(out, ";R43:\t<asignacion> ::= <identificador> = <exp>\n");
              }
            }
            | elemento_vector TOK_ASIGNACION exp {
              if($1.tipo != $3.tipo){
                printf("****Error semantico en lin %ld: Asignacion incompatible.\n", nlin);
                return -1;
              }
              sprintf(aux_itoa, "%d", $1.valor_entero);
              escribir_operando(out, aux_itoa, 0);
              escribir_elemento_vector(out, $1.lexema, simbolo_actual->longitud, $3.es_direccion);
              asignarDestinoEnPila(out, $3.es_direccion);
              fprintf(out, ";R44:\t<asignacion> ::= <elemento_vector> = <exp>\n");
            };
elemento_vector: TOK_IDENTIFICADOR TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO {
  if(ambito_actual == LOCAL){
    simbolo_actual = usoLocal($1.lexema);
    if(simbolo_actual == NULL){
      simbolo_actual = usoGlobal($1.lexema);
    }
  }
  else{
    simbolo_actual = usoGlobal($1.lexema);
  }
  if(simbolo_actual == NULL){
    printf("****Error semantico en lin %ld: Acceso a variable no declarada (<%s>).\n", nlin, $1.lexema);
    return -1;
  }
  if(simbolo_actual->categoria != VECTOR){
    printf("****Error semantico en lin %ld: Intento de indexacion de una variable que no es de tipo vector.\n", nlin);
    return -1;
  }
  if($3.tipo != ENTERO){
    printf("****Error semantico en lin %ld: El indice en una operacion de indexacion tiene que ser de tipo entero.\n", nlin);
    return -1;
  }
  $$.tipo = simbolo_actual->tipo;
  $$.es_direccion = 1;
  $$.valor_entero = $3.valor_entero;
  strcpy($$.lexema, $1.lexema);
  escribir_elemento_vector(out, $1.lexema, simbolo_actual->longitud, $3.es_direccion);
  fprintf(out, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ]\n");
};
condicional: if_exp_sentencias {
              ifthenelse_fin(out, $1.etiqueta);
              fprintf(out, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> }\n");
            }
             | if_exp_sentencias TOK_ELSE TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {
              ifthenelse_fin(out, $1.etiqueta);
              fprintf(out, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }\n");
            };
if_exp_sentencias: if_exp sentencias TOK_LLAVEDERECHA {
  $$.etiqueta = $1.etiqueta;
  ifthenelse_fin_then(out, $$.etiqueta);
}
if_exp: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA {
  if($3.tipo != BOOLEANO){
    printf("****Error semantico en lin %ld: Condicional con condicion de tipo int.\n", nlin);
  }
  $$.etiqueta = etiquetas++;
  ifthen_inicio(out, $3.es_direccion, $$.etiqueta);
}
bucle: while_exp sentencias TOK_LLAVEDERECHA {
  while_fin(out, $1.etiqueta);
  fprintf(out, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> }\n");
};
while: TOK_WHILE TOK_PARENTESISIZQUIERDO {
  $$.etiqueta = etiquetas++;
  while_inicio(out, $$.etiqueta);
};
while_exp: while exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA {
  if($2.tipo != BOOLEANO){
    printf("****Error semantico en lin %ld: Bucle con condicion de tipo int.\n", nlin);
    return -1;
  }
  $$.etiqueta = $1.etiqueta;
  while_exp_pila(out, $2.es_direccion, $$.etiqueta);
}
lectura: TOK_SCANF TOK_IDENTIFICADOR {
  if(ambito_actual == GLOBAL){
    simbolo_actual = usoGlobal($2.lexema);
  }
  else{
    simbolo_actual = usoLocal($2.lexema);
    if(simbolo_actual == NULL){
      simbolo_actual = usoGlobal($2.lexema);
    }
  }
  if(simbolo_actual == NULL){
    printf("****Error semantico en lin %ld: Acceso a variable no declarada(<%s>).\n", nlin, $2.lexema);
  }
  if(simbolo_actual->cat_simbolo == FUNCION){
    printf("****Error semantico en lin %ld: Asignacion incompatible.\n", nlin);
    return -1;
  }
  if(simbolo_actual->categoria == VECTOR){
    printf("****Error semantico en lin %ld: Asignacion incompatible.\n", nlin);
    return -1;
  }
  leer(out, $2.lexema, simbolo_actual->tipo);
  fprintf(out, ";R54:\t<lectura> ::= scanf <identificador>\n");
};
escritura: TOK_PRINTF exp {
  escribir(out, $2.es_direccion, $2.tipo);
  fprintf(out, ";R56:\t<escritura> ::= printf <exp>\n");
};
retorno_funcion: TOK_RETURN exp {
  if(ambito_actual != LOCAL){
    printf("****Error semantico en lin %ld: Sentencia de retorno fuera del cuerpo de una funcion.\n", nlin);
    return -1;
  }
  retornado = 1;
  tipo_actual = $2.tipo;
  retornarFuncion(out, $2.es_direccion);
  fprintf(out, ";R61:\t<retorno_funcion> ::= return <exp>\n");
};
exp: exp TOK_MAS exp {
  if($1.tipo == BOOLEANO || $3.tipo == BOOLEANO){
    printf("****Error semantico en lin %ld: Operacion aritmetica con operandos boolean.\n", nlin);
    return -1;
  }
  if(($1.tipo == ENTERO) && ($3.tipo == ENTERO)){
    sumar(out, $1.es_direccion, $3.es_direccion);
    $$.tipo = ENTERO;
    $$.es_direccion = 0;
  }
  fprintf(out, ";R72:\t<exp> ::= <exp> + <exp>\n");
}
     | exp TOK_MENOS exp {
     if($1.tipo == BOOLEANO || $3.tipo == BOOLEANO){
       printf("****Error semantico en lin %ld: Operacion aritmetica con operandos boolean.\n", nlin);
       return -1;
     }
     if(($1.tipo == ENTERO) && ($3.tipo == ENTERO)){
       restar(out, $1.es_direccion, $3.es_direccion);
       $$.tipo = ENTERO;
       $$.es_direccion = 0;
     }
      fprintf(out, ";R73:\t<exp> ::= <exp> - <exp>\n");
    }
     | exp TOK_DIVISION exp {
     if($1.tipo == BOOLEANO || $3.tipo == BOOLEANO){
       printf("****Error semantico en lin %ld: Operacion aritmetica con operandos boolean.\n", nlin);
       return -1;
     }
     if(($1.tipo == ENTERO) && ($3.tipo == ENTERO)){
       dividir(out, $1.es_direccion, $3.es_direccion);
       $$.tipo = ENTERO;
       $$.es_direccion = 0;
     }
      fprintf(out, ";R74:\t<exp> ::= <exp> / <exp>\n");
     }
     | exp TOK_ASTERISCO exp {
     if($1.tipo == BOOLEANO || $3.tipo == BOOLEANO){
       printf("****Error semantico en lin %ld: Operacion aritmetica con operandos boolean.\n", nlin);
       return -1;
     }
     if(($1.tipo == ENTERO) && ($3.tipo == ENTERO)){
       multiplicar(out, $1.es_direccion, $3.es_direccion);
       $$.tipo = ENTERO;
       $$.es_direccion = 0;
     }
      fprintf(out, ";R75:\t<exp> ::= <exp> * <exp>\n");
    }
     | TOK_MENOS exp {
      if($2.tipo == BOOLEANO){
        printf("****Error semantico en lin %ld: Operacion aritmetica con operandos boolean.\n", nlin);
        return -1;
      }
      if($2.tipo == ENTERO){
        cambiar_signo(out, $2.es_direccion);
        $$.tipo = ENTERO;
        $$.es_direccion = 0;
      }
      fprintf(out, ";R76:\t<exp> ::= - <exp>\n");
     }
     | exp TOK_AND exp {
       if($1.tipo == ENTERO || $3.tipo == ENTERO){
         printf("****Error semantico en lin %ld: Operacion logica con operandos int.\n", nlin);
         return -1;
       }
       if(($1.tipo == BOOLEANO) && ($3.tipo == BOOLEANO)){
         y(out, $1.es_direccion, $3.es_direccion);
         $$.tipo = BOOLEANO;
         $$.es_direccion = 0;
       }
        fprintf(out, ";R77:\t<exp> ::= <exp> && <exp>\n");
     }
     | exp TOK_OR exp {
     if($1.tipo == ENTERO || $3.tipo == ENTERO){
       printf("****Error semantico en lin %ld: Operacion logica con operandos int.\n", nlin);
       return -1;
     }
     if(($1.tipo == BOOLEANO) && ($3.tipo == BOOLEANO)){
       o(out, $1.es_direccion, $3.es_direccion);
       $$.tipo = BOOLEANO;
       $$.es_direccion = 0;
     }
      fprintf(out, ";R78:\t<exp> ::= <exp> || <exp>\n");
}
     | TOK_NOT exp {
      if($2.tipo == ENTERO){
        printf("****Error semantico en lin %ld: Operacion logica con operandos int.\n", nlin);
        return -1;
      }
      if($2.tipo == BOOLEANO){
       no(out, $2.es_direccion, $2.etiqueta);
       $$.tipo = BOOLEANO;
       $$.es_direccion = 0;
      }
      fprintf(out, ";R79:\t<exp> ::= ! <exp>\n");
     }
     | TOK_IDENTIFICADOR {
         if(ambito_actual == GLOBAL){
           simbolo_actual = usoGlobal($1.lexema);
         }
         else{
           simbolo_actual = usoLocal($1.lexema);
           if(simbolo_actual == NULL){
             simbolo_actual = usoGlobal($1.lexema);
           }
         }
         if(simbolo_actual == NULL){
           printf("****Error semantico en lin %ld: Acceso a variable no declarada(%s).\n", nlin, $1.lexema);
           return -1;
         }
         if(simbolo_actual->cat_simbolo == FUNCION){
           printf("****Error semantico en lin %ld: Funcion no puede ser exp.\n", nlin);
           return -1;
         }
         if(simbolo_actual->categoria == VECTOR){
           printf("****Error semantico en lin %ld: Vector no puede ser exp.\n", nlin);
           return -1;
         }
         if(ambito_actual == LOCAL && usoLocal($1.lexema)){
          simbolo_actual = usoLocal($1.lexema);
          if(simbolo_actual->cat_simbolo == PARAMETRO){
            escribirParametro(out, simbolo_actual->posicion, num_parametros);
          }
          else if(simbolo_actual->cat_simbolo == VARIABLE){
            escribirVariableLocal(out, simbolo_actual->posicion);
          }
          if(simbolo_actual->cat_simbolo == FUNCION){
            printf("****Error semantico en lin %ld: Funcion no puede ser exp.\n", nlin);
          }
         }
         $$.tipo=simbolo_actual->tipo;
         $$.es_direccion=1;
         if(ambito_actual == GLOBAL || (!usoLocal($1.lexema) && usoGlobal($1.lexema))){
          escribir_operando(out, $1.lexema, 1);
         }
         fprintf(out, ";R80:\t<exp> ::= <identificador>\n");
      }
     | constante {
     $$.tipo = $1.tipo;
     $$.es_direccion = $1.es_direccion;
     fprintf(out, ";R81:\t<exp> ::= <constante>\n");
    }
     | TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO {
       $$.tipo = $2.tipo;
       $$.es_direccion = $2.es_direccion;
       fprintf(out, ";R82:\t<exp> ::= ( <exp> )\n");
     }
     | TOK_PARENTESISIZQUIERDO comparacion TOK_PARENTESISDERECHO {
      $$.tipo = $2.tipo;
      $$.es_direccion = $2.es_direccion;
      fprintf(out, ";R83:\t<exp> ::= ( <comparacion> )\n");
     }
     | elemento_vector {fprintf(out, ";R85:\t<exp> ::= <elemento_vector>\n");}
     | fun_call lista_expresiones TOK_PARENTESISDERECHO {
      simbolo_actual = usoGlobal($1.lexema);
      if(simbolo_actual == NULL || simbolo_actual->cat_simbolo != FUNCION){
        printf("****Error semantico en lin %ld: Llamada a funcion no declarada %s.\n", nlin, $1.lexema);
        return -1;
      }
      if(simbolo_actual->num_parametros != call_params){
        printf("****Error semantico en lin %ld: Numero incorrecto de parametros en llamada a funcion.\n", nlin);
        return -1;
      }
      calling = 0;
      call_params = 0;
      $$.tipo = simbolo_actual->tipo;
      llamarFuncion(out, $1.lexema, simbolo_actual->num_parametros);
      fprintf(out, ";R88:\t<exp> ::= <identificador> ( <lista_expresiones> )\n");
    };

fun_call: TOK_IDENTIFICADOR TOK_PARENTESISIZQUIERDO{
  if(calling){
    printf("****Error semantico en lin %ld: No está permitido el uso de llamadas a funciones como parametros de otras funciones.\n", nlin);
    return -1;
  }
  simbolo_actual = usoGlobal($1.lexema);
  if(simbolo_actual == NULL){
    printf("****Error semantico en lin %ld: Llamada a funcion no declarada %s", nlin, $1.lexema);
  }

  strcpy($$.lexema, $1.lexema);
  call_params = 0;
  calling = 1;
}

lista_expresiones: exp_call resto_lista_expresiones {
                    call_params++;
                    fprintf(out, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones>\n");
                  }
                   | %empty {fprintf(out, ";R90:\t<lista_expresiones> ::=\n");};
resto_lista_expresiones: TOK_COMA exp_call resto_lista_expresiones {
                          call_params++;
                          fprintf(out, ";R91:\t<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>\n");
                        }
                         | %empty {fprintf(out, ";R92:\t<resto_lista_expresiones> ::=\n");};
exp_call: exp {
  operandoEnPilaAArgumento(out, $1.es_direccion);
}
comparacion: exp TOK_IGUAL exp {
  if($1.tipo == BOOLEANO || $3.tipo == BOOLEANO){
    printf("****Error semantico en lin %ld: Comparacion con operandos boolean.\n", nlin);
    return -1;
  }
  if(($1.tipo == ENTERO) && ($3.tipo == ENTERO)){
    igual(out, $1.es_direccion, $3.es_direccion, etiquetas);
    etiquetas += 1;
    $$.tipo = BOOLEANO;
    $$.es_direccion = 0;
  }
  fprintf(out, ";R93:\t<comparacion> ::= <exp> == <exp>\n");
}
             | exp TOK_DISTINTO exp {
               if($1.tipo == BOOLEANO || $3.tipo == BOOLEANO){
                 printf("****Error semantico en lin %ld: Comparacion con operandos boolean.\n", nlin);
                 return -1;
               }
               if(($1.tipo == ENTERO) && ($3.tipo == ENTERO)){
                 distinto(out, $1.es_direccion, $3.es_direccion, etiquetas);
                 etiquetas += 1;
                 $$.tipo = BOOLEANO;
                 $$.es_direccion = 0;
               }
               fprintf(out, ";R94:\t<comparacion> ::= <exp> != <exp>\n");
             }

             | exp TOK_MENORIGUAL exp {
               if($1.tipo == BOOLEANO || $3.tipo == BOOLEANO){
                 printf("****Error semantico en lin %ld: Comparacion con operandos boolean.\n", nlin);
                 return -1;
               }
               if(($1.tipo == ENTERO) && ($3.tipo == ENTERO)){
                 menor_igual(out, $1.es_direccion, $3.es_direccion, etiquetas);
                 etiquetas += 1;
                 $$.tipo = BOOLEANO;
                 $$.es_direccion = 0;
               }
               fprintf(out, ";R96:\t<comparacion> ::= <exp> <= <exp>\n");
             }

             | exp TOK_MAYORIGUAL exp {
               if($1.tipo == BOOLEANO || $3.tipo == BOOLEANO){
                 printf("****Error semantico en lin %ld: Comparacion con operandos boolean.\n", nlin);
                 return -1;
               }
               if(($1.tipo == ENTERO) && ($3.tipo == ENTERO)){
                 mayor_igual(out, $1.es_direccion, $3.es_direccion, etiquetas);
                 etiquetas += 1;
                 $$.tipo = BOOLEANO;
                 $$.es_direccion = 0;
               }
               fprintf(out, ";R97:\t<comparacion> ::= <exp> >= <exp>\n");
              }

             | exp TOK_MENOR exp {
              if($1.tipo == BOOLEANO || $3.tipo == BOOLEANO){
                printf("****Error semantico en lin %ld: Comparacion con operandos boolean.\n", nlin);
                return -1;
              }
              if(($1.tipo == ENTERO) && ($3.tipo == ENTERO)){
                menor(out, $1.es_direccion, $3.es_direccion, etiquetas);
                etiquetas += 1;
                $$.tipo = BOOLEANO;
                $$.es_direccion = 0;
              }
              fprintf(out, ";R98:\t<comparacion> ::= <exp> < <exp>\n");
             }

             | exp TOK_MAYOR exp {
             if($1.tipo == BOOLEANO || $3.tipo == BOOLEANO){
               printf("****Error semantico en lin %ld: Comparacion con operandos boolean.\n", nlin);
               return -1;
             }
             if(($1.tipo == ENTERO) && ($3.tipo == ENTERO)){
               mayor(out, $1.es_direccion, $3.es_direccion, etiquetas);
               etiquetas += 1;
               $$.tipo = BOOLEANO;
               $$.es_direccion = 0;
             }
              fprintf(out, ";R98:\t<comparacion> ::= <exp> > <exp>\n");
            };
constante: constante_logica {
            $$.tipo = $1.tipo;
            $$.es_direccion = $1.es_direccion;
            fprintf(out, ";R99:\t<constante> ::= <constante_logica>\n");}
           | constante_entera {
            $$.tipo = $1.tipo;
            $$.es_direccion = $1.es_direccion;
            fprintf(out, ";R100:\t<constante> ::= <constante_entera>\n");
           };
constante_logica: TOK_TRUE {
  $$.tipo = BOOLEANO;
  $$.es_direccion = 0;
  escribir_operando(out, "1", 0);
  fprintf(out, ";R102:\t<constante_logica> ::= true\n");
}
                  | TOK_FALSE {
  $$.tipo = BOOLEANO;
  $$.es_direccion = 0;
  escribir_operando(out, "0", 0);
  fprintf(out, ";R103:\t<constante_logica> ::= false\n");
};
constante_entera: TOK_CONSTANTE_ENTERA {
  $$.tipo = ENTERO;
  $$.es_direccion = 0;
  $$.valor_entero = $1.valor_entero;
  escribir_operando(out, $1.lexema, 0);
  fprintf(out, ";R104:\t<constante_entera> ::= TOK_CONSTANTE_ENTERA\n");
};
identificador: TOK_IDENTIFICADOR {
  if(clase_actual == VECTOR && (tamanio_vector <= 0 || tamanio_vector > 64)){
    printf("****Error semantico en lin %ld: El tamanyo del vector <%s> excede los limites permitidos (1,64).\n", nlin, $1.lexema);
    return -1;
  }
  simbolo_creado = (SIMBOLO*)calloc(1, sizeof(SIMBOLO));
  simbolo_creado->cat_simbolo = VARIABLE;
  simbolo_creado->tipo = tipo_actual;
  simbolo_creado->categoria = clase_actual;
  if(clase_actual == VECTOR){
    simbolo_creado->longitud = tamanio_vector;
  }
  if(ambito_actual == LOCAL){
    if(clase_actual == VECTOR){
      printf("****Error semantico en lin %ld: Variable local de tipo no escalar.\n", nlin);
      free(simbolo_creado);
      return -1;
    }
    num_variables_locales++;
    simbolo_creado->posicion = num_variables_locales;
  }
  else{
    if(clase_actual == VECTOR){
      declarar_variable(out, $1.lexema, tipo_actual, tamanio_vector);
    }
    else{
      declarar_variable(out, $1.lexema, tipo_actual, 1);
    }
  }
  if(declarar($1.lexema, simbolo_creado) == ERROR){
    printf("****Error semantico en lin %ld: Declaracion duplicada.\n", nlin);
    free(simbolo_creado);
    simbolo_creado = NULL;
    return -1;
  }
  free(simbolo_creado);
  simbolo_creado = NULL;
  fprintf(out, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n");
};
%%

void yyerror(const char * s) {
    if(!is_morpho) {
        printf("****Error sintactico en [lin %ld, col %ld]\n", nlin, ncol-yyleng);
    }
}

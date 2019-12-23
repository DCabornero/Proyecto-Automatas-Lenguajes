#include "generacion.h"
#define VARIABLE 1
#define INMEDIATO 0

void escribir_cabecera_bss(FILE* fpasm){
  fprintf(fpasm, "segment .bss\n");
  fprintf(fpasm, "__esp resd 1\n");
}

void escribir_subseccion_data(FILE* fpasm){
  fprintf(fpasm, "segment .data\n");
  fprintf(fpasm, "mensaje_0 db \"****Error de ejecucion: Division por cero.\", 0\n");
  fprintf(fpasm, "mensaje_1 db \"****Error de ejecucion: Indice fuera de rango.\", 0\n");
}

void declarar_variable(FILE* fpasm, char * nombre, int tipo, int tamano){
  fprintf(fpasm, "_%s ", nombre);
  if(tipo == ENTERO){
    fprintf(fpasm, "resd %d", tamano);
  }
  else if(tipo == BOOLEANO){
    fprintf(fpasm, "resd %d", tamano);
  }
  fprintf(fpasm, "\n");
}

void escribir_segmento_codigo(FILE* fpasm){
  fprintf(fpasm, "segment .text\n");
  fprintf(fpasm, "global main\n");
  fprintf(fpasm, "extern scan_int, scan_boolean\n");
  fprintf(fpasm, "extern print_int, print_boolean, print_string, print_blank, print_endofline\n");
}

void escribir_inicio_main(FILE* fpasm){
  fprintf(fpasm, "main:\n");
  fprintf(fpasm, "mov dword [__esp], esp\n");
}

void escribir_fin(FILE* fpasm){
  fprintf(fpasm, "jmp fin\n");
  fprintf(fpasm, "div0: push dword mensaje_0\n");
  fprintf(fpasm, "    call print_string\n");
  fprintf(fpasm, "    call print_endofline\n");
  fprintf(fpasm, "    add esp, 4\n");
  fprintf(fpasm, "    jmp near fin\n");
  fprintf(fpasm, "fin_indice_fuera_rango: push dword mensaje_1\n");
  fprintf(fpasm, "    call print_string\n");
  fprintf(fpasm, "    call print_endofline\n");
  fprintf(fpasm, "    add esp, 4\n");
  fprintf(fpasm, "    jmp near fin\n");
  fprintf(fpasm, "fin: mov dword esp, [__esp]\n");
  fprintf(fpasm, "ret\n");
}

void escribir_operando(FILE* fpasm, char* nombre, int es_variable){
  fprintf(fpasm, "push dword ");
  if(es_variable == VARIABLE){
    fprintf(fpasm, "_%s\n", nombre);
  }
  else if(es_variable == INMEDIATO){
    fprintf(fpasm, "%s\n", nombre);
  }
}

void asignar(FILE* fpasm, char* nombre, int es_variable){
  fprintf(fpasm, "pop dword ebx\n");
  if(es_variable == INMEDIATO){
    fprintf(fpasm, "mov [_%s], ebx\n", nombre);
  }
  else if(es_variable == VARIABLE){
    fprintf(fpasm, "mov ebx, [ebx]\n");
    fprintf(fpasm, "mov [_%s], ebx\n", nombre);
  }
}

void sumar(FILE* fpasm, int es_variable_1, int es_variable_2){
  if(es_variable_2 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword edx, [ebx]\n");
  }
  else if(es_variable_2 == INMEDIATO){
    fprintf(fpasm, "pop dword edx\n");
  }
  if(es_variable_1 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword eax, [ebx]\n");
  }
  else if(es_variable_1 == INMEDIATO){
    fprintf(fpasm, "pop dword eax\n");
  }
  fprintf(fpasm, "add eax, edx\n");
  fprintf(fpasm, "push dword eax\n");
}

void restar(FILE* fpasm, int es_variable_1, int es_variable_2){
  if(es_variable_2 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword edx, [ebx]\n");
  }
  else if(es_variable_2 == INMEDIATO){
    fprintf(fpasm, "pop dword edx\n");
  }
  if(es_variable_1 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword eax, [ebx]\n");
  }
  else if(es_variable_1 == INMEDIATO){
    fprintf(fpasm, "pop dword eax\n");
  }
  fprintf(fpasm, "sub eax, edx\n");
  fprintf(fpasm, "push dword eax\n");
}

void multiplicar(FILE* fpasm, int es_variable_1, int es_variable_2){
  if(es_variable_2 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword edx, [ebx]\n");
  }
  else if(es_variable_2 == INMEDIATO){
    fprintf(fpasm, "pop dword edx\n");
  }
  if(es_variable_1 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword eax, [ebx]\n");
  }
  else if(es_variable_1 == INMEDIATO){
    fprintf(fpasm, "pop dword eax\n");
  }
  fprintf(fpasm, "imul edx\n");
  fprintf(fpasm, "push dword eax\n");
}

void dividir(FILE* fpasm, int es_variable_1, int es_variable_2){
  if(es_variable_2 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword ecx, [ebx]\n");
  }
  else if(es_variable_2 == INMEDIATO){
    fprintf(fpasm, "pop dword ecx\n");
  }
  if(es_variable_1 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword eax, [ebx]\n");
  }
  else if(es_variable_1 == INMEDIATO){
    fprintf(fpasm, "pop dword eax\n");
  }
  fprintf(fpasm, "cmp ecx, 0\n");
  fprintf(fpasm, "je div0\n");
  fprintf(fpasm, "cdq\n");
  fprintf(fpasm, "idiv ecx\n");
  fprintf(fpasm, "push dword eax\n");
}

void o(FILE* fpasm, int es_variable_1, int es_variable_2){
  if(es_variable_2 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword edx, [ebx]\n");
  }
  else if(es_variable_2 == INMEDIATO){
    fprintf(fpasm, "pop dword edx\n");
  }
  if(es_variable_1 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword eax, [ebx]\n");
  }
  else if(es_variable_1 == INMEDIATO){
    fprintf(fpasm, "pop dword eax\n");
  }
  fprintf(fpasm, "or eax, edx\n");
  fprintf(fpasm, "push dword eax\n");
}

void y(FILE* fpasm, int es_variable_1, int es_variable_2){
  if(es_variable_2 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword edx, [ebx]\n");
  }
  else if(es_variable_2 == INMEDIATO){
    fprintf(fpasm, "pop dword edx\n");
  }
  if(es_variable_1 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword eax, [ebx]\n");
  }
  else if(es_variable_1 == INMEDIATO){
    fprintf(fpasm, "pop dword eax\n");
  }
  fprintf(fpasm, "and eax, edx\n");
  fprintf(fpasm, "push dword eax\n");
}

void cambiar_signo(FILE* fpasm, int es_variable){
  if(es_variable == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword eax, [ebx]\n");
  }
  else if(es_variable == INMEDIATO){
    fprintf(fpasm, "pop dword eax\n");
  }
  fprintf(fpasm, "neg eax\n");
  fprintf(fpasm, "push dword eax\n");
}

void no(FILE* fpasm, int es_variable, int cuantos_no){
  if(es_variable == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword eax, [ebx]\n");
  }
  else if(es_variable == INMEDIATO){
    fprintf(fpasm, "pop dword eax\n");
  }
  fprintf(fpasm, "cmp eax, 0\n");
  fprintf(fpasm, "jne no%d\n", cuantos_no); /*Salta en caso de que eax sea 1*/
  fprintf(fpasm, "inc eax\n");
  fprintf(fpasm, "jmp nofin%d\n", cuantos_no);
  fprintf(fpasm, "no%d: dec eax\n", cuantos_no);
  fprintf(fpasm, "nofin%d: push dword eax\n", cuantos_no);
}

void igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
  if(es_variable2 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword edx, [ebx]\n");
  }
  else if(es_variable2 == INMEDIATO){
    fprintf(fpasm, "pop dword edx\n");
  }
  if(es_variable1 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword eax, [ebx]\n");
  }
  else if(es_variable1 == INMEDIATO){
    fprintf(fpasm, "pop dword eax\n");
  }
  fprintf(fpasm, "cmp eax, edx\n");
  fprintf(fpasm, "jne op%d\n", etiqueta);
  fprintf(fpasm, "push dword 1\n");
  fprintf(fpasm, "jmp fin%d\n", etiqueta);
  fprintf(fpasm, "op%d: push dword 0\n", etiqueta);
  fprintf(fpasm, "fin%d:\n", etiqueta);
}

void distinto(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
  if(es_variable2 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword edx, [ebx]\n");
  }
  else if(es_variable2 == INMEDIATO){
    fprintf(fpasm, "pop dword edx\n");
  }
  if(es_variable1 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword eax, [ebx]\n");
  }
  else if(es_variable1 == INMEDIATO){
    fprintf(fpasm, "pop dword eax\n");
  }
  fprintf(fpasm, "cmp eax, edx\n");
  fprintf(fpasm, "je op%d\n", etiqueta);
  fprintf(fpasm, "push dword 1\n");
  fprintf(fpasm, "jmp fin%d\n", etiqueta);
  fprintf(fpasm, "op%d: push dword 0\n", etiqueta);
  fprintf(fpasm, "fin%d:\n", etiqueta);
}

void menor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
  if(es_variable2 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword edx, [ebx]\n");
  }
  else if(es_variable2 == INMEDIATO){
    fprintf(fpasm, "pop dword edx\n");
  }
  if(es_variable1 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword eax, [ebx]\n");
  }
  else if(es_variable1 == INMEDIATO){
    fprintf(fpasm, "pop dword eax\n");
  }
  fprintf(fpasm, "cmp eax, edx\n");
  fprintf(fpasm, "jg op%d\n", etiqueta);
  fprintf(fpasm, "push dword 1\n");
  fprintf(fpasm, "jmp fin%d\n", etiqueta);
  fprintf(fpasm, "op%d: push dword 0\n", etiqueta);
  fprintf(fpasm, "fin%d:\n", etiqueta);
}

void mayor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
  if(es_variable2 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword edx, [ebx]\n");
  }
  else if(es_variable2 == INMEDIATO){
    fprintf(fpasm, "pop dword edx\n");
  }
  if(es_variable1 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword eax, [ebx]\n");
  }
  else if(es_variable1 == INMEDIATO){
    fprintf(fpasm, "pop dword eax\n");
  }
  fprintf(fpasm, "cmp eax, edx\n");
  fprintf(fpasm, "jl op%d\n", etiqueta);
  fprintf(fpasm, "push dword 1\n");
  fprintf(fpasm, "jmp fin%d\n", etiqueta);
  fprintf(fpasm, "op%d: push dword 0\n", etiqueta);
  fprintf(fpasm, "fin%d:\n", etiqueta);
}

void menor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
  if(es_variable2 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword edx, [ebx]\n");
  }
  else if(es_variable2 == INMEDIATO){
    fprintf(fpasm, "pop dword edx\n");
  }
  if(es_variable1 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword eax, [ebx]\n");
  }
  else if(es_variable1 == INMEDIATO){
    fprintf(fpasm, "pop dword eax\n");
  }
  fprintf(fpasm, "cmp eax, edx\n");
  fprintf(fpasm, "jge op%d\n", etiqueta);
  fprintf(fpasm, "push dword 1\n");
  fprintf(fpasm, "jmp fin%d\n", etiqueta);
  fprintf(fpasm, "op%d: push dword 0\n", etiqueta);
  fprintf(fpasm, "fin%d:\n", etiqueta);
}

void mayor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
  if(es_variable2 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword edx, [ebx]\n");
  }
  else if(es_variable2 == INMEDIATO){
    fprintf(fpasm, "pop dword edx\n");
  }
  if(es_variable1 == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword eax, [ebx]\n");
  }
  else if(es_variable1 == INMEDIATO){
    fprintf(fpasm, "pop dword eax\n");
  }
  fprintf(fpasm, "cmp eax, edx\n");
  fprintf(fpasm, "jle op%d\n", etiqueta);
  fprintf(fpasm, "push dword 1\n");
  fprintf(fpasm, "jmp fin%d\n", etiqueta);
  fprintf(fpasm, "op%d: push dword 0\n", etiqueta);
  fprintf(fpasm, "fin%d:\n", etiqueta);
}

void leer(FILE* fpasm, char* nombre, int tipo){
  fprintf(fpasm, "push dword _%s\n", nombre);
  if(tipo == ENTERO){
    fprintf(fpasm, "call scan_int\n");
  }
  else if(tipo == BOOLEANO){
    fprintf(fpasm, "call scan_boolean\n");
  }
  fprintf(fpasm, "add esp, 4\n");
}

void escribir(FILE* fpasm, int es_variable, int tipo){
  if(es_variable == VARIABLE){
    fprintf(fpasm, "pop dword ebx\n");
    fprintf(fpasm, "mov dword eax, [ebx]\n");
    fprintf(fpasm, "push dword eax\n");
  }
  if(tipo == ENTERO){
    fprintf(fpasm, "call print_int\n");
  }
  else if(tipo == BOOLEANO){
    fprintf(fpasm, "call print_boolean\n");
  }
  fprintf(fpasm, "call print_endofline\n");
  fprintf(fpasm, "add esp, 4\n");
}

void ifthenelse_inicio(FILE* fpasm, int exp_es_variable, int etiqueta){
  fprintf(fpasm, "pop dword eax\n");
  if(exp_es_variable == VARIABLE){
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "cmp eax, 0\n");
  fprintf(fpasm, "je near fin_then_%d\n", etiqueta);
}

void ifthen_inicio(FILE* fpasm, int exp_es_variable, int etiqueta){
  ifthenelse_inicio(fpasm, exp_es_variable, etiqueta);
}

void ifthen_fin(FILE* fpasm, int etiqueta){
  fprintf(fpasm, "fin_then_%d:\n", etiqueta);
}

void ifthenelse_fin_then(FILE* fpasm, int etiqueta){
  fprintf(fpasm, "jmp near fin_ifelse_%d\n", etiqueta);
  fprintf(fpasm, "fin_then_%d:\n", etiqueta);
}

void ifthenelse_fin(FILE* fpasm, int etiqueta){
  fprintf(fpasm, "fin_ifelse_%d:\n", etiqueta);
}

void while_inicio(FILE* fpasm, int etiqueta){
  fprintf(fpasm, "inicio_while_%d:\n", etiqueta);
}

void while_exp_pila(FILE* fpasm, int exp_es_variable, int etiqueta){
  fprintf(fpasm, "pop eax\n");
  if(exp_es_variable > 0){
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "cmp eax, 0\n");
  fprintf(fpasm, "je near fin_while_%d\n", etiqueta);
}

void while_fin(FILE* fpasm, int etiqueta){
  fprintf(fpasm, "jmp near inicio_while_%d\n", etiqueta);
  fprintf(fpasm, "fin_while_%d:\n", etiqueta);
}

void escribir_elemento_vector(FILE* fpasm, char* nombre_vector, int tam_max, int exp_es_direccion){
  fprintf(fpasm, "pop eax\n");
  if(exp_es_direccion == VARIABLE){
    fprintf(fpasm, "mov eax, [eax]\n");
  }
  fprintf(fpasm, "cmp eax, 0\n");
  fprintf(fpasm, "jl near fin_indice_fuera_rango\n");
  fprintf(fpasm, "cmp eax, %d\n", tam_max-1);
  fprintf(fpasm, "jg near fin_indice_fuera_rango\n");
  fprintf(fpasm, "mov dword edx, _%s\n", nombre_vector);
  fprintf(fpasm, "lea eax, [edx + eax*4]\n");
  fprintf(fpasm, "push dword eax\n");
}

void declararFuncion(FILE* fpasm, char* nombre_funcion, int num_var_loc){
  fprintf(fpasm, "_%s:\n", nombre_funcion);
  fprintf(fpasm, "push dword ebp\n");
  fprintf(fpasm, "mov ebp, esp\n");
  fprintf(fpasm, "sub esp, %d*4\n", num_var_loc);
}

void retornarFuncion(FILE* fpasm, int es_variable){
  fprintf(fpasm, "pop eax\n");
  if(es_variable == VARIABLE){
    fprintf(fpasm, "mov dword eax, [eax]\n");
  }
  fprintf(fpasm, "mov esp, ebp\n");
  fprintf(fpasm, "pop ebp\n");
  fprintf(fpasm, "ret\n");
}

void escribirParametro(FILE* fpasm, int pos_parametro, int num_total_parametros){
  int d_ebp;
  d_ebp = 4*(1+(num_total_parametros-pos_parametro));
  fprintf(fpasm, "lea eax, [ebp + %d]\n", d_ebp);
  fprintf(fpasm, "push dword eax\n");
}

void escribirVariableLocal(FILE* fpasm, int posicion_variable_local){
  int d_ebp;
  d_ebp = 4*posicion_variable_local;
  fprintf(fpasm, "lea eax, [ebp - %d]\n", d_ebp);
  fprintf(fpasm, "push dword eax\n");
}

void asignarDestinoEnPila(FILE* fpasm, int es_variable){
  fprintf(fpasm, "pop dword ebx\n");
  fprintf(fpasm, "pop dword eax\n");
  if(es_variable){
    fprintf(fpasm, "mov dword eax, [eax]\n");
  }
  fprintf(fpasm, "mov dword [ebx], eax\n");
}

void operandoEnPilaAArgumento(FILE* fpasm, int es_variable){
  if(es_variable == VARIABLE){
    fprintf(fpasm, "pop dword eax\n");
    fprintf(fpasm, "mov eax, [eax]\n");
    fprintf(fpasm, "push dword eax\n");
  }
}

void llamarFuncion(FILE* fpasm, char* nombre_funcion, int num_argumentos){
  fprintf(fpasm, "call _%s\n", nombre_funcion);
  fprintf(fpasm, "add esp, %d*4\n", num_argumentos);
  fprintf(fpasm, "push dword eax\n");
}

void limpiarPila(FILE* fpasm, int num_argumentos){
  fprintf(fpasm, "add esp, %d", 4*num_argumentos);
}

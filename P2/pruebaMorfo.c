#include <stdio.h>
#include "tokens.h"

int yylex();

int main(int argc, char** argv){
  extern FILE* yyin;
  extern char* yytext;
  extern int yyleng;
  extern long nlin, ncol;
  int tok;
  FILE* fout;

  if(argc != 3){
    printf("Usage is pruebaMorfo fichEntrada fichSalida\n");
  }

  yyin = fopen(argv[1], "r");
  fout = fopen(argv[2], "w");

  while(tok = yylex()){
    switch(tok){
      case TOK_MAIN:
        fprintf(fout, "TOK_MAIN\t%d main\n", TOK_MAIN);
        break;
      case TOK_INT:
        fprintf(fout, "TOK_INT\t%d int\n", TOK_INT);
        break;
      case TOK_BOOLEAN:
        fprintf(fout, "TOK_BOOLEAN\t%d boolean\n", TOK_BOOLEAN);
        break;
      case TOK_ARRAY:
        fprintf(fout, "TOK_ARRAY\t%d array\n", TOK_ARRAY);
        break;
      case TOK_FUNCTION:
        fprintf(fout, "TOK_FUNCTION\t%d function\n", TOK_FUNCTION);
        break;
      case TOK_IF:
        fprintf(fout, "TOK_IF\t%d if\n", TOK_IF);
        break;
      case TOK_ELSE:
        fprintf(fout, "TOK_ELSE\t%d else\n", TOK_ELSE);
        break;
      case TOK_WHILE:
        fprintf(fout, "TOK_WHILE\t%d while\n", TOK_WHILE);
        break;
      case TOK_SCANF:
        fprintf(fout, "TOK_SCANF\t%d scanf\n", TOK_SCANF);
        break;
      case TOK_PRINTF:
        fprintf(fout, "TOK_PRINTF\t%d printf\n", TOK_PRINTF);
        break;
      case TOK_RETURN:
        fprintf(fout, "TOK_RETURN\t%d return\n", TOK_RETURN);
        break;
      case TOK_PUNTOYCOMA:
        fprintf(fout, "TOK_PUNTOYCOMA\t%d ;\n", TOK_PUNTOYCOMA);
        break;
      case TOK_COMA:
        fprintf(fout, "TOK_COMA\t%d ,\n", TOK_COMA);
        break;
      case TOK_PARENTESISIZQUIERDO:
        fprintf(fout, "TOK_PARENTESISIZQUIERDO\t%d (\n", TOK_PARENTESISIZQUIERDO);
        break;
      case TOK_PARENTESISDERECHO:
        fprintf(fout, "TOK_PARENTESISDERECHO\t%d )\n", TOK_PARENTESISDERECHO);
        break;
      case TOK_CORCHETEIZQUIERDO:
        fprintf(fout, "TOK_CORCHETEIZQUIERDO\t%d [\n", TOK_CORCHETEIZQUIERDO);
        break;
      case TOK_CORCHETEDERECHO:
        fprintf(fout, "TOK_CORCHETEDERECHO\t%d ]\n", TOK_CORCHETEDERECHO);
        break;
      case TOK_LLAVEIZQUIERDA:
        fprintf(fout, "TOK_LLAVEIZQUIERDA\t%d {\n", TOK_LLAVEIZQUIERDA);
        break;
      case TOK_LLAVEDERECHA:
        fprintf(fout, "TOK_LLAVEDERECHA\t%d }\n", TOK_LLAVEDERECHA);
        break;
      case TOK_ASIGNACION:
        fprintf(fout, "TOK_ASIGNACION\t%d =\n", TOK_ASIGNACION);
        break;
      case TOK_MAS:
        fprintf(fout, "TOK_MAS\t%d +\n", TOK_MAS);
        break;
      case TOK_MENOS:
        fprintf(fout, "TOK_MENOS\t%d -\n", TOK_MENOS);
        break;
      case TOK_DIVISION:
        fprintf(fout, "TOK_DIVISION\t%d /\n", TOK_DIVISION);
        break;
      case TOK_ASTERISCO:
        fprintf(fout, "TOK_ASTERISCO\t%d *\n", TOK_ASTERISCO);
        break;
      case TOK_AND:
        fprintf(fout, "TOK_AND\t%d &&\n", TOK_AND);
        break;
      case TOK_OR:
        fprintf(fout, "TOK_OR\t%d ||\n", TOK_OR);
        break;
      case TOK_NOT:
        fprintf(fout, "TOK_NOT\t%d !\n", TOK_NOT);
        break;
      case TOK_IGUAL:
        fprintf(fout, "TOK_IGUAL\t%d ==\n", TOK_IGUAL);
        break;
      case TOK_DISTINTO:
        fprintf(fout, "TOK_DISTINTO\t%d !=\n", TOK_DISTINTO);
        break;
      case TOK_MENORIGUAL:
        fprintf(fout, "TOK_MENORIGUAL\t%d <=\n", TOK_MENORIGUAL);
        break;
      case TOK_MAYORIGUAL:
        fprintf(fout, "TOK_MAYORIGUAL\t%d >=\n", TOK_MAYORIGUAL);
        break;
      case TOK_MENOR:
        fprintf(fout, "TOK_MENOR\t%d <\n", TOK_MENOR);
        break;
      case TOK_MAYOR:
        fprintf(fout, "TOK_MAYOR\t%d >\n", TOK_MAYOR);
        break;
      case TOK_IDENTIFICADOR:
        fprintf(fout, "TOK_IDENTIFICADOR\t%d %s\n", TOK_IDENTIFICADOR, yytext);
        break;
      case TOK_CONSTANTE_ENTERA:
        fprintf(fout, "TOK_CONSTANTE_ENTERA\t%d %s\n", TOK_CONSTANTE_ENTERA, yytext);
        break;
      case TOK_TRUE:
        fprintf(fout, "TOK_TRUE\t%d true\n", TOK_TRUE);
        break;
      case TOK_FALSE:
        fprintf(fout, "TOK_FALSE\t%d false\n", TOK_FALSE);
        break;
      case TOK_ERROR:
        //fprintf(fout, "TOK_ERROR\t%d %s\n", TOK_ERROR, yytext);
        printf("****Error en [lin %ld, col %ld]: simbolo no permitido (%s)\n", nlin, ncol, yytext);
        fclose(yyin);
        fclose(fout);
        return 0;
        break;
      case TOK_IDENTIFICADORERROR:
        //fprintf(fout, "TOK_IDENTIFICADORERROR\t%d %s\n", TOK_IDENTIFICADORERROR, yytext);
        printf("****Error en [lin %ld, col %ld]: identificador demasiado largo (%s)\n", nlin, ncol, yytext);
        fclose(yyin);
        fclose(fout);
        return 0;
        break;
      default:
        fprintf(fout, "TOKEN NO ESPERADO\n");
    }
  }
  fclose(yyin);
  fclose(fout);
  return 0;
}

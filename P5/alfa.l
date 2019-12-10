%{
#include <stdio.h>
#include "alfa.h"
#include "y.tab.h"
long ncol = 1;
long nlin = 1;
FILE* out;
int is_morpho = 0;
%}

%option noyywrap

%%
main {ncol += yyleng; fprintf(out, ";D:\tmain\n"); return TOK_MAIN;}
int {ncol += yyleng; fprintf(out, ";D:\tint\n"); return TOK_INT;}
boolean {ncol += yyleng; fprintf(out, ";D:\tboolean\n");return TOK_BOOLEAN;}
array {ncol += yyleng; fprintf(out, ";D:\tarray\n"); return TOK_ARRAY;}
function {ncol += yyleng; fprintf(out, ";D:\tfunction\n"); return TOK_FUNCTION;}
if {ncol += yyleng; fprintf(out, ";D:\tif\n"); return TOK_IF;}
else {ncol += yyleng; fprintf(out, ";D:\telse\n"); return TOK_ELSE;}
while {ncol += yyleng; fprintf(out, ";D:\twhile\n"); return TOK_WHILE;}
scanf {ncol += yyleng; fprintf(out, ";D:\tscanf\n"); return TOK_SCANF;}
printf {ncol += yyleng; fprintf(out, ";D:\tprintf\n"); return TOK_PRINTF;}
return {ncol += yyleng; fprintf(out, ";D:\treturn\n"); return TOK_RETURN;}

; {ncol += yyleng; fprintf(out, ";D:\t;\n"); return TOK_PUNTOYCOMA;}
"," {ncol += yyleng; fprintf(out, ";D:\t,\n"); return TOK_COMA;}
"(" {ncol += yyleng; fprintf(out, ";D:\t(\n"); return TOK_PARENTESISIZQUIERDO;}
")" {ncol += yyleng; fprintf(out, ";D:\t)\n"); return TOK_PARENTESISDERECHO;}
"[" {ncol += yyleng; fprintf(out, ";D:\t[\n"); return TOK_CORCHETEIZQUIERDO;}
"]" {ncol += yyleng; fprintf(out, ";D:\t]\n"); return TOK_CORCHETEDERECHO;}
"{" {ncol += yyleng; fprintf(out, ";D:\t{\n"); return TOK_LLAVEIZQUIERDA;}
"}" {ncol += yyleng; fprintf(out, ";D:\t}\n"); return TOK_LLAVEDERECHA;}
"=" {ncol += yyleng; fprintf(out, ";D:\t=\n"); return TOK_ASIGNACION;}
"+" {ncol += yyleng; fprintf(out, ";D:\t+\n"); return TOK_MAS;}
"-" {ncol += yyleng; fprintf(out, ";D:\t-\n"); return TOK_MENOS;}
"/" {ncol += yyleng; fprintf(out, ";D:\t/\n"); return TOK_DIVISION;}
"*" {ncol += yyleng; fprintf(out, ";D:\t*\n"); return TOK_ASTERISCO;}
"&&" {ncol += yyleng; fprintf(out, ";D:\t&&\n"); return TOK_AND;}
"||" {ncol += yyleng; fprintf(out, ";D:\t||\n"); return TOK_OR;}
! {ncol += yyleng; fprintf(out, ";D:\t!\n"); return TOK_NOT;}
"==" {ncol += yyleng; fprintf(out, ";D:\t==\n"); return TOK_IGUAL;}
"!=" {ncol += yyleng; fprintf(out, ";D:\t!=\n"); return TOK_DISTINTO;}
"<=" {ncol += yyleng; fprintf(out, ";D:\t<=\n"); return TOK_MENORIGUAL;}
">=" {ncol += yyleng; fprintf(out, ";D:\t>=\n"); return TOK_MAYORIGUAL;}
"<" {ncol += yyleng; fprintf(out, ";D:\t<\n"); return TOK_MENOR;}
">" {ncol += yyleng; fprintf(out, ";D:\t>\n"); return TOK_MAYOR;}

true {ncol += yyleng; fprintf(out, ";D:\ttrue\n"); return TOK_TRUE;}
false {ncol += yyleng; fprintf(out, ";D:\tfalse\n"); return TOK_FALSE;}

[a-zA-Z]([a-zA-Z0-9]){0,99} {strcpy(yylval.atributos.lexema, yytext); yylval.atributos.es_direccion = ES_VARIABLE; ncol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_IDENTIFICADOR;}
[0-9][0-9]* {yylval.atributos.valor_entero = atoi(yytext); yylval.atributos.tipo = TIPO_ENTERO; yylval.atributos.es_direccion = ES_INMEDIATO; ncol += yyleng; fprintf(out, ";D:\t%s\n", yytext); return TOK_CONSTANTE_ENTERA;}

[ \t]+ {ncol += yyleng;}
[\n] {nlin++; ncol = 1;}
"//"(.)*[\n] {nlin++; ncol = 1;}

[a-zA-Z]([a-zA-Z0-9])* {printf("****Error en [lin %ld, col %ld]: identificador demasiado largo (%s)\n", nlin, ncol, yytext); is_morpho = 1; return TOK_IDENTIFICADORERROR;}
. {printf("****Error en [lin %ld, col %ld]: simbolo no permitido (%s)\n", nlin, ncol, yytext); is_morpho = 1; return TOK_ERROR;}

%%

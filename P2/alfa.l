%{
#include <stdio.h>
#include "tokens.h"
%}

%option noyywrap

%%
main {printf("TOK_MAIN %d main \n", TOK_MAIN);}
int {printf("TOK_INT %d int \n", TOK_INT);}
boolean {printf("TOK_BOOLEAN %d boolean \n", TOK_BOOLEAN);}
array {printf("TOK_ARRAY %d array \n", TOK_ARRAY);}
function {printf("TOK_FUNCTION %d function \n", TOK_FUNCTION);}
if {printf("TOK_IF %d if \n", TOK_IF);}
else {printf("TOK_ELSE %d else \n", TOK_ELSE);}
while {printf("TOK_WHILE %d while \n", TOK_WHILE);}
scanf {printf("TOK_SCANF %d scanf \n", TOK_SCANF);}
printf {printf("TOK_PRINTF %d printf \n", TOK_PRINTF);}
return {printf("TOK_RETURN %d return \n", TOK_RETURN);}

; {printf("TOK_PUNTOYCOMA %d ; \n", TOK_PUNTOYCOMA);}
"," {printf("TOK_COMA %d , \n", TOK_COMA);}
"(" {printf("TOK_PARENTESISIZQUIERDO %d ( \n", TOK_PARENTESISIZQUIERDO);}
")" {printf("TOK_PARENTESISDERECHO %d ) \n", TOK_PARENTESISDERECHO);}
"[" {printf("TOK_CORCHETEIZQUIERDO %d [ \n", TOK_CORCHETEIZQUIERDO);}
"]" {printf("TOK_CORCHETEDERECHO %d ] \n", TOK_CORCHETEDERECHO);}
"{" {printf("TOK_LLAVEIZQUIERDA %d { \n", TOK_LLAVEIZQUIERDA);}
"}" {printf("TOK_LLAVEDERECHA %d } \n", TOK_LLAVEDERECHA);}
"=" {printf("TOK_ASIGNACION %d = \n", TOK_ASIGNACION);}
"+" {printf("TOK_MAS %d + \n", TOK_MAS);}
"-" {printf("TOK_MENOS %d - \n", TOK_MENOS);}
"/" {printf("TOK_DIVISION %d / \n", TOK_DIVISION);}
"*" {printf("TOK_ASTERISCO %d * \n", TOK_ASTERISCO);}
"&&" {printf("TOK_AND %d && \n", TOK_AND);}
"||" {printf("TOK_OR %d || \n", TOK_OR);}
! {printf("TOK_NOT %d ! \n", TOK_NOT);}
"==" {printf("TOK_IGUAL %d == \n", TOK_IGUAL);}
"!=" {printf("TOK_DISTINTO %d != \n", TOK_DISTINTO);}
"<=" {printf("TOK_MENORIGUAL %d <= \n", TOK_MENORIGUAL);}
">=" {printf("TOK_MAYORIGUAL %d >= \n", TOK_MAYORIGUAL);}
"<" {printf("TOK_MENOR %d < \n", TOK_MENOR);}
">" {printf("TOK_MAYOR %d > \n", TOK_MAYOR);}

true {printf("TOK_TRUE %d true \n", TOK_TRUE);}
false {printf("TOK_FALSE %d false \n", TOK_FALSE);}

[a-zA-Z]([a-zA-Z0-9]){0,99} {printf("TOK_IDENTIFICADOR %d %s \n", TOK_IDENTIFICADOR, yytext);}
[0-9][0-9]* {printf("TOK_CONSTANTE_ENTERA %d %s \n", TOK_CONSTANTE_ENTERA, yytext);}

[ \n\t]+ {printf("");}
"//"(.)*[\n] {printf("");}

[a-zA-Z]([a-zA-Z0-9])* {printf("TOK_IDENTIFICADORERROR %d %s \n", TOK_IDENTIFICADORERROR, yytext);}
. {printf("TOK_ERROR %d %s \n", TOK_ERROR, yytext);}

%%

int main(){
  return yylex();
}

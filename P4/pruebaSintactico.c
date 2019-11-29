#include <stdio.h>
#include "y.tab.h"

int yylex();
int yyparse();

int main(int argc, char** argv){
  extern FILE* yyin;
  extern FILE* out;
  int ret;

  if(argc != 3){
    printf("Usage is pruebaSintactico fichEntrada fichSalida\n");
    return 0;
  }

  yyin = fopen(argv[1], "r");
  out = fopen(argv[2], "w");

  while((ret = yyparse())){
    if(ret){
      break;
    }
  }
  fclose(yyin);
  fclose(out);
  return 0;
}

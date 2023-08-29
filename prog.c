#include <stdlib.h>
#include <stdio.h>
#include "progb.h"

int main(int argc, char *argv[])
{	
  EXPRESSAO expressao;
  /*
  int resultado;
  struct Pilha pilha;  
  */

	argc = argc;
	argv = argv;
  oi();
/* 
  ler_expressao(&expressao);
  
  if (!validar_expressao(&expressao)) {
    printf("Expressão inválida!\n");
    return 1;
  }

  
  converter_expressao_posfixa(&expressao, &pilha);


  resultado = calcular_expressao_posfixa(&pilha);

 
  printf("Resultado: %d\n", resultado);
  */
 printf("%s",expressao.string);
 

  return 0;
}
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
  int *dados;
  int topo;
  int tamanho;
} PILHA;

typedef struct
{
  char *string;
  int tamanho;
}EXPRESSAO;
void oi();
void ler_expressao(EXPRESSAO *expressao);
int calcular_expressao_posfixa(PILHA *pilha);
PILHA *criar_pilha(int tamanho);
int desempilhar(PILHA *pilha);
void empilhar(PILHA *pilha, int valor);
void converter_expressao_posfixa(EXPRESSAO *expressao, PILHA *pilha);
int precedencia(char operador);
int validar_expressao(EXPRESSAO *expressao);

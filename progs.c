#include <stdlib.h>
#include <stdio.h>
#include "progb.h"

void oi()
{
  printf("Hello world");
}

void ler_expressao(EXPRESSAO *expressao){
  char *string = malloc(100 * sizeof(char));
  int tamanho = 0;

  printf("Digite uma expressão: ");
  fgets(string, 100, stdin);

  tamanho = strlen(string);

  expressao->string = malloc((tamanho + 1) * sizeof(char));
  strcpy(expressao->string, string);

  expressao->tamanho = tamanho;
}

int calcular_expressao_posfixa(PILHA *pilha) {
  int resultado = 0;

  while (pilha->topo > 0) {
    int operando = desempilhar(pilha);

    if (operando >= '0' && operando <= '9') {
      resultado = operando - '0';
    } else {
      int operando_2 = desempilhar(pilha);

      switch (operando) {
        case '+':
          resultado += operando_2;
          break;
        case '-':
          resultado -= operando_2;
          break;
        case '*':
          resultado *= operando_2;
          break;
        case '/':
          resultado /= operando_2;
          break;
        case '$':
          resultado ^= operando_2;
          break;
      }
    }
  }

  return resultado;
}

PILHA *criar_pilha(int tamanho) {
  PILHA *pilha = malloc(sizeof(PILHA));
  pilha->dados = malloc(sizeof(int) * tamanho);
  pilha->topo = 0;
  pilha->tamanho = tamanho;

  return pilha;
}

int desempilhar(PILHA *pilha) {
  if (pilha->topo == 0) {
    printf("Erro: Pilha vazia!\n");
    return -1;
  }

  return pilha->dados[--pilha->topo];
}

void empilhar(PILHA *pilha, int valor) {
  if (pilha->topo == pilha->tamanho) {
    printf("Erro: Pilha cheia!\n");
    return;
  }

  pilha->dados[pilha->topo++] = valor;
}


void converter_expressao_posfixa( EXPRESSAO *expressao, PILHA *pilha) {
  char *c = expressao->string;
  char operador_atual;

  while (*c != '\0') {
    if (*c >= '0' && *c <= '9') {
      empilhar(pilha, *c - '0');
    } else if (*c == '(') {
      empilhar(pilha, *c);
    } else if (*c == ')') {
      while (pilha->topo > 0 && pilha->dados[pilha->topo - 1] != '(') {
        int operando_2 = desempilhar(pilha);
        int operando_1 = desempilhar(pilha);

        switch (pilha->dados[pilha->topo - 1]) {
          case '+':
            empilhar(pilha, operando_1 + operando_2);
            break;
          case '-':
            empilhar(pilha, operando_1 - operando_2);
            break;
          case '*':
            empilhar(pilha, operando_1 * operando_2);
            break;
          case '/':
            empilhar(pilha, operando_1 / operando_2);
            break;
          case '$':
            empilhar(pilha, operando_1 ^ operando_2);
            break;
        }
      }

      if (pilha->topo == 0) {
        printf("Erro: Parenteses incorretos!\n");
        return;
      }
      pilha->topo--;
    } else if (*c == '+' || *c == '-' || *c == '*' || *c == '/' || *c == '$') {
      operador_atual = *c;

      while (pilha->topo > 0 && precedencia(operador_atual) <= precedencia(pilha->dados[pilha->topo - 1])) {
        int operando_2 = desempilhar(pilha);
        int operando_1 = desempilhar(pilha);

        switch (pilha->dados[pilha->topo - 1]) {
          case '+':
            empilhar(pilha, operando_1 + operando_2);
            break;
          case '-':
            empilhar(pilha, operando_1 - operando_2);
            break;
          case '*':
            empilhar(pilha, operando_1 * operando_2);
            break;
          case '/':
            empilhar(pilha, operando_1 / operando_2);
            break;
          case '$':
            empilhar(pilha, operando_1 ^ operando_2);
            break;
        }
      }

      empilhar(pilha, operador_atual);
    }
  }
}


int precedencia(char operador) 
{
  switch (operador) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
    case '$':
      return 3;
    default:
      return 0;
  }
}
int validar_expressao(EXPRESSAO *expressao) {
  char *c = expressao->string;

  while (*c != '\0') {
    if (*c >= '0' && *c <= '9') {
      c++;
    } else if (*c == '(') {
      c++;
    } else if (*c == ')') {
      c++;
    } else if (*c == '+' || *c == '-' || *c == '*' || *c == '/' || *c == '$') {
      c++;
    } else {
      return 0;
    }
  }

  return 1;
}
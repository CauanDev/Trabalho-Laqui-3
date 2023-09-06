#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_ELEMENTOS 1000
#define SIMBOLO_DESCONHECIDO 1
#define VAZIA ' '    
typedef char vetor[MAX_ELEMENTOS];
typedef int vetor1[MAX_ELEMENTOS];
typedef struct 
{
    int topo;
    vetor Elementos;
    vetor1 Numbers;
               
} Pilha;



int validar_expressao(char str1[]);
void transFixa(Pilha P, char str1[], char str2[]);
void Push(Pilha *pilha, char elemento);
char Pop(Pilha *pilha);
void PushInt(Pilha *pilha, int elemento);
int PopInt(Pilha *pilha);
char StackTopElement(Pilha P);
int Comp(char Elem1, char Elem2);
void Limpar(char *str);
int Calcula(char str[]);

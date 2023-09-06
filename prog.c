#include<stdio.h> /* printf() */
#include <stdlib.h>
#include <string.h>
#include "progb.h"
/*
    gcc prog.c -o prog.exe progs.c
*/

int main(int argc, char **argv)
{
    Pilha P;
    char str1[MAX_ELEMENTOS];            
    char str2[MAX_ELEMENTOS+(MAX_ELEMENTOS/2)];

    int i = 0, j = 0;

    printf("Digite a string a ser analisada (ex. 3+5*2+1*7): ");
    gets(str1);    
    Limpar(str1);
    if(!(validar_expressao(str1)))
    {
        printf("Expressao Invalida!!!");
        return 0;
    }    

    transFixa(P, str1, str2);
    printf("Ficou assim: %s\n",str2); 
    printf("Resultado = %d",Calcula(str2));
    return 0;
}



#include <stdio.h>
#include <stdbool.h>

#define MAX_ELEMENTOS 20 /* Aumentei o tamanho máximo da expressão para permitir mais caracteres */
#define VAZIA ' '
#define SIMBOLO_DESCONHECIDO 1

typedef char vetor[MAX_ELEMENTOS];
typedef struct {
    int topo;
    vetor Elementos;
} PILHA;

void Push(PILHA *, char);
char Pop(PILHA *);
char StackTopElement(PILHA);
int Comp(char, char);
bool verificaParenteses(char *str);
bool verificaExpressao(char *str);
bool isOperador(char c);

int main(int argc, char **argv) {
    PILHA P;
    char str1[20];
    char str2[20];
    char symbol_pilha, symbol_str;

    int i = 0, j = 0;

    printf("Digite a string a ser analisada (ex. 3+5*2+1*7): ");
    scanf("%s", str1);

    if (!verificaParenteses(str1)) 
    {
        printf("Erro: a contagem de parênteses está incorreta.\n");
        return 0;
    }

    P.topo = 0;
    int l = 0;
    
    //
    while (str1[i] != '\0') 
    {
       
        if (str1[i] >= '0' && str1[i] <= '9') 
        {
            char numero[20]; // Supomos que não haverá números com mais de 20 dígitos
            int k = 0;
            l=i;
            while (str1[l] >= '0' && str1[l] <= '9') 
            {                
                printf("Analisado = %c\nIndice = %d\n",str1[l],l);
                numero[l] = str1[l];
               /*
                printf("%c\n",numero[l]);
                getchar(); 
               */ 
                
                Push(&P,numero[l]);
                
                str2[l] = numero[l];               
                l++;
               
            }

                str2[l] = ','; 
                      
                
            
            i++;
            
            
        } 
        else 
        {
            symbol_pilha = StackTopElement(P);
            symbol_str = str1[i];
            while (symbol_pilha != VAZIA && !Comp(StackTopElement(P), symbol_str)) 
            {
                symbol_pilha = Pop(&P);
                str2[j++] = symbol_pilha;
            }
            Push(&P, symbol_str);
            i++;
        }
    }

    do 
    {
        symbol_pilha = Pop(&P);
        str2[j] = symbol_pilha;
        j++;
    } while (symbol_pilha != VAZIA);
    str2[j] = '\0';

    printf("\n");
    printf("String de entrada (infixa): %s\n", str1);
    printf("String de saida (posfixa): %s\n",str2);
   

    if (verificaExpressao(str2))
        printf("A expressão está correta.\n");
    else
        printf("Erro: a expressão está incorreta.\n");

    return 0;
}

void Push(PILHA *pilha, char elemento) {
    if (pilha->topo < MAX_ELEMENTOS) 
    {
        pilha->Elementos[pilha->topo] = elemento;
        pilha->topo++;
    }
}

char Pop(PILHA *pilha) {
    char elemento = VAZIA;
    if (pilha->topo != 0) {
        pilha->topo--;
        elemento = pilha->Elementos[pilha->topo];
    }
    return elemento;
}

char StackTopElement(PILHA P) {
    int topo;
    topo = P.topo - 1;
    return (P.Elementos[topo]);
}

int Comp(char Elem1, char Elem2) {
    switch (Elem1) {
        case VAZIA:
            switch (Elem2) {
                case '+':
                case '-':
                case '*':
                case '/':
                    return 1;
            }
        case '+':
            switch (Elem2) {
                case '+':
                case '-':
                    return 0;
                case '*':
                case '/':
                    return 1;
            }
        case '-':
            switch (Elem2) {
                case '+':
                case '-':
                    return 0;
                case '*':
                case '/':
                    return 1;
            }
        case '*':
            switch (Elem2) {
                case '+':
                case '-':
                case '*':
                case '/':
                    return 0;
            }
        case '/':
            switch (Elem2) {
                case '+':
                case '-':
                case '*':
                case '/':
                    return 0;
            }
    }
    return SIMBOLO_DESCONHECIDO;
}

bool verificaParenteses(char *str) {
    PILHA parenteses;
    int i;
    parenteses.topo = 0;
    for (i = 0; str[i]; i++) {
        if (str[i] == '(')
            Push(&parenteses, '(');
        else if (str[i] == ')') {
            if (Pop(&parenteses) != '(')
                return false; // Houve um fechamento de parêntese sem correspondência
        }
    }
    return parenteses.topo == 0; // Deve estar vazia se a contagem for correta
}

bool verificaExpressao(char *str) {
    PILHA operandos;
    int i;
    operandos.topo = 0;
    for (i = 0; str[i]; i++) {
        if (isdigit(str[i]))
            Push(&operandos, '0'); // Empilhe dígitos
        else if (isOperador(str[i])) {
            if (operandos.topo < 2)
                return false; // Não há operandos suficientes para operação
            Pop(&operandos); // Desempilhe dois operandos
            Pop(&operandos);
            Push(&operandos, '0'); // Empilhe um operando fictício
        }
    }
    return operandos.topo == 1; // Deve ter exatamente um operando no final
}

bool isOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

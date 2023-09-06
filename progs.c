#include "progb.h"

/*
    ARRUMAR A FUNCAO ResolverParenteses
*/

void transFixa(Pilha P, char str1[], char str2[])
{
    int i=0;
    int j=0;
    char symbol_pilha, symbol_str;
    P.topo = 0; /* Inicializar a pilha */
    while (str1[i]) /* varrer a string de entrada enquanto for diferente de '\0' */
    {
        if (str1[i] >= '0' && str1[i] <= '9')
        {
            
            /*
            
            */
            str2[j] = str1[i];
            j++;
            /* se o caracter for um dígito, então colocar ele na string de saída 
            i++; 
            while(str1[i] >= '0' && str1[i] <= '9')
            {
                str2[j] = str1[i];
                j++;/* se o caracter for um dígito, então colocar ele na string de saída 
                i++;
            }
            printf("\nFoi colocado isso: %c na pilha\n",str1[i]);
            Push(&P,str1[i]);
            str2[i] = ',';
            printf("\nbct = %s\n",str2);
            j++;
            i++;
            */
            
            
        }
        else
        {
            str2[i] = ',';
            symbol_pilha = StackTopElement(P);
            /*  Pegar operador do topo da pilha 
            printf("O que ta vindo aqui: %c",symbol_pilha);*/
            symbol_str = str1[i];   
            j++;    /* Pegar operador da string de entrada */
            /* 
                comparar operadores: se operador da string tiver menor precedência que um operador que já estiver no topo da pilha, 
                então COLOCAR NA STRING DE SAÍDA, TODOS OS OPERADORES ARMAZENADOS NA PILHA, CUJA PRECEDÊNCIA SEJA MAIOR QUE O OPERADOR 
                ATUAL QUE TENHO EM MÃOS DA STRING 
            */
            while (symbol_pilha != VAZIA && !Comp(StackTopElement(P), symbol_str)) 
            {
                symbol_pilha = Pop(&P); /* desempilhar operador da pilha que tem maior precedência que o operador atual que está sendo analisado da string de entrada */
                str2[j] = symbol_pilha; /* colocar esse operador na string de saída */
                j++;
            }
            Push(&P, symbol_str); /* Empilhar operador atual, que tenho em mãos, da string */
        }
        i++; /* "andar" na string de entrada */
    } /* fim do while */


    /* Colocar na string de saída todos os operadores que porventura ainda estejam empilhados na pilha */
    do
    {
        symbol_pilha = Pop(&P);
        str2[j] = symbol_pilha;      
        j++;
    } while (symbol_pilha != VAZIA);
    str2[j] = '\0';


}


void Push(Pilha *pilha, char elemento)
{
    if (pilha->topo < MAX_ELEMENTOS)
    { 
        pilha->Elementos[pilha->topo] = elemento;
        pilha->topo++;
    }

}
char Pop(Pilha *pilha)
{
    char elemento = VAZIA;
    if (pilha->topo != 0)
    {
        pilha->topo--;
        elemento = pilha->Elementos[pilha->topo];
    }
    return elemento;
}
void PushInt(Pilha *pilha, int elemento)
{
    if (pilha->topo < MAX_ELEMENTOS)
    {
        pilha->Numbers[pilha->topo] = elemento;
        pilha->topo++;
    }

}
int PopInt(Pilha *pilha)
{
    int elemento = VAZIA;
    if (pilha->topo != 0)
    {
        pilha->topo--;
        elemento = pilha->Numbers[pilha->topo];
    }
    return elemento;
}


char StackTopElement(Pilha P)
{
    int topo;
    topo = P.topo - 1;
    return(P.Elementos[topo]);
}


int Comp(char Elem1, char Elem2)
{
    switch (Elem1)
    {
        case VAZIA:
            switch (Elem2)
            { 
                case '+':
                case '-':
                case '*':
                case '$':
                case '/': return 1;
            }
        case '+':
            switch (Elem2)
            { 
                case '+':
                case '-': return 0; /* '+' e '-' à direita tem menor precedência que o '+' à esquerda */
                case '*':
                case '$':
                case '/': return 1; /* '*' e '/' tem maior precedência que o '+' à esquerda */
            }
        case '-':
            switch (Elem2)
            { 
                case '+':
                case '-': return 0; /* '+' e '-' à direita tem menor precedência que o '-' à esquerda */ 
                case '*':
                case '$':
                case '/': return 1; /* '*' e '/' tem maior precedência que o '-' à esquerda */
            }
        case '$':            
            switch (Elem2)
            { 
                case '+':
                case '-': 
                case '*':
                case '$':
                case '/': return 0; /* '+' e '-' e '*' e '/' tem menor precedência que o '*' à esquerda */
            }                      
        case '*':
            switch (Elem2)
            { 
                case '+':
                case '-': 
                case '*':
                case '$':
                case '/': return 0; /* '+' e '-' e '*' e '/' tem menor precedência que o '*' à esquerda */
            }
        case '/':
            switch (Elem2)
            { 
                case '+':
                case '-': 
                case '*':
                case '$':
                case '/': return 0; /* '+' e '-' e '*' e '/' tem menor precedência que o '/' à esquerda */
            }
    }
	return SIMBOLO_DESCONHECIDO;
}



void Limpar(char str[])
{
    char *nova_string = malloc(strlen(str) + 1);
    // Percorre a string original, caracter por caracter.
    int i = 0, j = 0;
    while (str[i] != '\0') 
    {
        // Se o caracter não for um espaço, adiciona-o à nova string.
        if (str[i] != ' ') 
        {
            nova_string[j++] = str[i];
        }
        i++;
    }
    // Adiciona um caractere nulo ao final da nova string.
    nova_string[j] = '\0';
    strcpy(str,nova_string);

    
}
/*
void SepararDigitos(char str[],char str2[])
{
    Pilha operadores;
    int i,j;
    i = 0;
    while(str[i]!= " \0")
    {
        while(str[i] >= '0' && str[i] <= '9')
        {
            str2[i] = str[i];
            i++;
        }
        Push(&operadores, str[i]);
        str2[i] = ',';
    }
    
}
*/

int Calcula(char str[]) 
{   
    Pilha operandos;
    int i;
    int j;
    int a, b, r=0;
    int aux;
    operandos.topo = 0;
    for (i = 0; str[i] != '\0'; i++) 
    {
        
            // Leitura de um número
            aux = 0;
            while (str[i] >= '0' && str[i] <= '9') 
            {
                aux = aux * 10 + (str[i] - '0');
                i++;
            }
            // Empilhe o número
            
            PushInt(&operandos, aux);            

            if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'|| str[i] == '$') 
            {

                a = PopInt(&operandos); // Desempilhe dois operandos
                b = PopInt(&operandos);

                switch (str[i]) 
                {
                    case '+':
                        r = a + b;
                    break;
                    case '-':
                        r = a - b;
                    break;
                    case '*':
                        r = a * b;
                    break;
                    case '/':
                        r = a / b;
                    break;
                    case '$':
                        r = 1;
                        // Calcula a exponenciação
                        for (j = 0; j < b; j++) 
                        {
                            r *= a;
                        }
                    break;
                }
                return r; // Empilhe o resultado da operação
            } 
            else 
            {
                if(str[i] != ',')
                {
                    return -1; // Caractere inválido  
                }
                
            }
        
        
    }
    

}

int validar_expressao(char str1[]) 
{
    char expressao[strlen(str1)];
    int i = 0;
    int veredito;
    int qtd_parenteses_abertos = 0;
    int qtd_parenteses_fechados = 0;
    veredito = 1;
    strcpy(expressao,str1);
    while (expressao[i] != '\0') 
    {
        if (expressao[i] == '(') 
        {
            qtd_parenteses_abertos++;
        } 
        else
        {
            if (expressao[i] == ')') 
            {
                qtd_parenteses_fechados++;
            } 
            else
            {
                if (expressao[i] == '+' || expressao[i] == '-' || expressao[i] == '*' || expressao[i] == '/' || expressao[i] == '$') 
                {
                    /*Verifica se o operador está entre dois operandos*/
                    if (i == 0 || (expressao[i - 1] < '0' || expressao[i - 1] > '9') || (expressao[i + 1] < '0' || expressao[i + 1] > '9')) 
                    {
                        return 0;
                    }
                    /*Verifica se o operador não está adjacente a outro operador*/
                    if (i > 0 && expressao[i - 1] == '+' || expressao[i - 1] == '-' || expressao[i - 1] == '*' || expressao[i - 1] == '/' || expressao[i - 1] == '$') 
                    {
                        return 0;
                    }
                } 
                else
                {
                    if (expressao[i] == ')') 
                    {
                        /*Verifica se a quantidade de parênteses está correta*/
                        if (qtd_parenteses_fechados > qtd_parenteses_abertos) 
                        {
                            return 0;
                        }
    
                    }
                }
            
            }    
        }    
        i++;
    }
    /*Verifica se a expressão não termina em um operador*/
    if (expressao[i - 1] == '+' || expressao[i - 1] == '-' || expressao[i - 1] == '*' || expressao[i - 1] == '/' || expressao[i - 1] == '$') 
    {
        veredito =  0;
    }

    /*Verifica se a quantidade de parênteses está correta*/
    if (qtd_parenteses_abertos != qtd_parenteses_fechados) 
    {
        veredito = 0;
    }
    return veredito;
}

int ResolverParenteses(char string[],int i,int j)
{
    char aux[i+j];
    int j = 0;
    while(string[i])
    {
        if(string[i] == '(')
        {
            i++;
            while(string[i] != ')')
            {
                aux[j] = string[i];
                j++;
                i++;
            }
        }
        i++;
    }
    return Calcula(aux);
}

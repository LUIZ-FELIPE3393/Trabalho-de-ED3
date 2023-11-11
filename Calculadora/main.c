#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

typedef struct Pilha Pilha;
typedef struct Algarismo Algarismo;

struct Algarismo
{
    char valor;
    Algarismo *next;
};

struct Pilha
{
    //Pilha de algarismos que formam um número
    Algarismo *topEl;
};

//Pilha.Controller
Algarismo* new_algarismo(char valor);
Pilha* new_pilha();

void clear(Pilha* p);
int isEmpty(Pilha* p);
void push(Pilha* p, Algarismo* alg);
void pop(Pilha* p);
Algarismo* topEl(Pilha* p);

void listarAlgarismos(Pilha* p);

void numero_para_algarismos(Pilha* p, int num);
Pilha soma_numeros(Pilha* op1, Pilha* op2); // Retorna pilha do numero resultante

//===============

int main()
{
    setlocale(LC_ALL, "");

    Pilha op1, op2, res;
    op1.topEl = NULL;
    op2.topEl = NULL;

    int num;

    printf("Operando 1: ");
    scanf("%d", &num);
    numero_para_algarismos(&op1, num);

    printf("Operando 2: ");
    scanf("%d", &num);
    numero_para_algarismos(&op2, num);

    printf("Resultado: \n");
    res = soma_numeros(&op1, &op2);
    listarAlgarismos(&res);

    return 0;
}

Algarismo* new_algarismo(char valor)
{
    Algarismo* n = (Algarismo*) malloc(sizeof(Algarismo));

    n->valor = valor;

    return n;
}

void clear(Pilha* p)
{
    if (!p) return;

    while (p->topEl != NULL)
    {
        Algarismo* temp = topEl(p);
        p->topEl = temp->next;
        free(temp);
    }

    p->topEl = NULL;
}

void push(Pilha* p, Algarismo* alg)
{
    alg->next = p->topEl;
    p->topEl = alg;
}

void pop(Pilha* p)
{
    if (isEmpty(p))
        return;
    Algarismo* temp = topEl(p);
    p->topEl = temp->next;
    free(temp);
}

Algarismo* topEl(Pilha* p)
{
    if (p->topEl)
        return p->topEl;
    else
    {
        printf("ERRO - Não foi possível retornar o elemento do topo da pilha\n");
        return NULL;
    }
}

int isEmpty(Pilha* p)
{
    if (!p) return -1;

    if (p->topEl == NULL)
        return 1;
    else return 0;
}

void listarAlgarismos(Pilha* p)
{
    Algarismo* pAux = p->topEl;
    while (pAux)
    {
        printf("> %d <\n", pAux->valor);

        pAux = pAux->next;
    }
}

void numero_para_algarismos(Pilha* p, int num)
{
    int tam = 0, temp = num, dec, div;

    while (temp > 0)
    {
        tam++;
        temp = temp / 10;
    }

    int i;
    for (i = tam; i > 0; i--)
    {
        int j = 0;
        div = 1;
        for (j = 1; j < i; j++)
            div *= 10;

        dec = num / div;

        push(p, new_algarismo(dec));

        num = num % div;
    }

    listarAlgarismos(p);
}

Pilha soma_numeros(Pilha* op1, Pilha* op2) // Retorna pilha do numero resultante
{
    Pilha res;
    res.topEl = NULL;

    char soma = 0;
    while (op1->topEl || op2->topEl)
    {
        int operando1 = 0, operando2 = 0;

        if (!isEmpty(op1)) operando1 = op1->topEl->valor;
        if (!isEmpty(op2)) operando2 = op2->topEl->valor;

        soma = soma + operando1 + operando2;

        pop(op1);
        pop(op2);

        push(&res, new_algarismo(soma % 10));

        soma = soma / 10;
    }

    return res;
}

/*push(&p, new_numero(2560));
    listarNumeros(&p);
    printf("\nINSERE\n");
    Sleep(400);

    push(&p, new_numero(2890));
    listarNumeros(&p);
    printf("\nINSERE\n");
    Sleep(400);

    push(&p, new_numero(5127));
    listarNumeros(&p);
    printf("\nINSERE\n");
    Sleep(400);

    pop(&p);
    listarNumeros(&p);
    printf("\nREMOVE\n");
    Sleep(400);

    pop(&p);
    listarNumeros(&p);
    printf("\nREMOVE\n");
    Sleep(400);

    pop(&p);
    listarNumeros(&p);
    printf("\nREMOVE\n");
    Sleep(400);

    system("cls");
    printf("\nFIM\n");*/





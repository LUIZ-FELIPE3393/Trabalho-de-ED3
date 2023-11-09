#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Pilha Pilha;
typedef struct Numero Numero;

struct Numero
{
    int num;
    Numero *next;
};

struct Pilha
{
    Numero LNumInicio, *LNumAux, *LNumTop;
    Pilha *next;
};

//Pilha.Controller
Pilha LPilInicio, *LPilAux;

Numero* new_numero(int num);
Pilha* new_pilha();

void clear(Pilha* p);
int isEmpty(Pilha* p);
void push(Pilha* p, Numero* num);
void pop(Pilha* p);
Numero* topEl(Pilha* p);

void listarNumeros(Pilha* p);

//===============

int main()
{
    setlocale(LC_ALL, "");

    Pilha* p = new_pilha();

    printf("Pilha inicializada!\n");

    Numero* n = new_numero(2560);
    Numero* n1 = new_numero(2890);
    Numero* n2 = new_numero(5127);

    printf("Numeros inicializados!\n");

    push(p, n);
    push(p, n1);
    push(p, n2);

    printf("Numeros empilhados!\n");

    listarNumeros(p);

    printf("Lista vazia? :%d\n", isEmpty(p));
    printf("Elemento do topo é: %d\n", topEl(p)->num);

    pop(p);
    printf("Elemento do topo é: %d\n", topEl(p)->num);

    clear(p);

    listarNumeros(p);

    printf("Lista vazia? :%d\n", isEmpty(p));

    return 0;
}

Pilha* new_pilha()
{
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));

    p->LNumAux = &p->LNumInicio;
    p->LNumTop = p->LNumAux;
    p->LNumTop->next = NULL;

    return p;
}

Numero* new_numero(int num)
{
    Numero* n = (Numero*) malloc(sizeof(Numero));

    n->num = num;

    return n;
}

void clear(Pilha* p)
{
    if (!p) return;

    p->LNumAux = p->LNumInicio.next;
    while(p->LNumAux)
    {
        Numero* temp = p->LNumAux;
        p->LNumAux = p->LNumAux->next;
        free(temp);
    }

    p->LNumInicio.next = NULL;
}

void push(Pilha* p, Numero* num)
{
    if (!p) return;

    //p->LNumAux = p->LNumInicio.next;
    while (p->LNumTop->next != NULL)
    {
        // Manda Top para o fim da pilha
        p->LNumTop = p->LNumTop->next;
    }

    //Insere na pilha
    p->LNumTop->next = num;
    p->LNumTop = p->LNumTop->next;
    p->LNumTop->next = NULL;
}

void pop(Pilha* p)
{
    p->LNumAux = p->LNumInicio.next;

    while (p->LNumAux->next != p->LNumTop)
    {
        // Manda Aux para para antes de Top
        p->LNumAux = p->LNumAux->next;
    }

    //Top é liberado
    free(p->LNumTop);

    //Top torna-se Aux
    p->LNumAux->next = NULL;
    p->LNumTop = p->LNumAux;

}

Numero* topEl(Pilha* p)
{
    if (p->LNumTop)
        return p->LNumTop;
    else
    {
        printf("Não foi possível retornar o elemento do topo da pilha");
        return NULL;
    }
}

int isEmpty(Pilha* p)
{
    if (!p) return -1;

    if (p->LNumInicio.next == NULL)
        return 1;
    else return 0;
}

void listarNumeros(Pilha* p)
{
    p->LNumAux = p->LNumInicio.next;
    while (p->LNumAux)
    {
        printf("Num: %d\n", p->LNumAux->num);

        p->LNumAux = p->LNumAux->next;
    }
}





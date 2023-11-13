#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int TAM_PACOTE = 16; // Em bytes

typedef struct Fila Fila;
typedef struct Elemento Elemento;

struct Fila
{
    int capacidade, quant_elementos;
    Elemento *lastEl, *firstEl;
};

struct Elemento
{
    char dado[TAM_PACOTE];
    Elemento *next;
};

void converte_dados_em_pacotes(Fila*, char* dados);

void clear(Fila*);
char isEmpty(Fila*);
char isFull(Fila*);
void enqueue(Fila*, Elemento*);
void dequeue(Fila*);
Elemento* firstEl(Fila*);

Fila* new_fila(int capacidade);
Elemento* new_elemento(char* dados, int offset);

int main()
{
    Fila* f = new_fila(8);
    

    return 0;
}

void converte_dados_em_pacotes(Fila* fila, char* dados)
{

}

void clear(Fila* fila)
{
    while(!isEmpty)
        dequeue(fila);
}

char isEmpty(Fila* fila)
{
    if (!fila->firstEl)
        return 1;
    return 0;
}

char isFull(Fila* fila)
{
    if (fila->quant_elementos == fila->capacidade)
        return 1;
    return 0;
}

void enqueue(Fila* fila, Elemento* el)
{
    if (isEmpty(fila))
    {
        fila->firstEl = el;
        fila->lastEl = el;
    }
    else
    {
        fila->lastEl->next = el;
        fila->lastEl = el;
    }
}

void dequeue(Fila* fila)
{
    if (isEmpty(fila))
        return;
    Elemento* temp = fila->firstEl;
    fila->firstEl = temp->next;
    free(temp);
}

Elemento* firstEl(Fila* fila)
{
    return fila->firstEl;
}

Fila* new_fila(int capacidade)
{
    Fila* new_fila = (Fila*) malloc(sizeof(Fila));
    new_fila->capacidade = capacidade;
    new_fila->lastEl = NULL;
    new_fila->firstEl = NULL;
    return new_fila;
}

Elemento* new_elemento(char* dado, int offset)
{
    Elemento* new_el = (Elemento*) malloc(sizeof(Elemento));
    memcpy(new_el->dado, dado[offset], sizeof(char)*TAM_PACOTE);
    new_el->next = NULL;
    return new_el; 
}

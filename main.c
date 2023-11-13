#include <stdio.h>
#include <stdlib.h>

//const int TAM_PACOTE;

typedef struct Fila Fila;
typedef struct Elemento Elemento;

struct Fila
{
    int capacidade;
    Elemento* topEl;
};

struct Elemento
{
    char dado;
    Elemento* next;
};

void clear();
char isEmpty();
char isFull();
void enqueue(Elemento* el);
Elemento* dequeue();
Elemento* firstEl();

int main()
{
    

    return 0;
}

void clear()
{

}

char isEmpty()
{

}

char isFull()
{

}

void enqueue(Elemento* el)
{

}

Elemento* dequeue()
{

}

Elemento* firstEl()
{

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define TAM_PACOTE 8 // Em bytes

typedef struct Fila Fila;
typedef struct Elemento Elemento;

struct Fila
{
    int capacidade, quant_elementos;
    Elemento *lastEl, *firstEl;
};

struct Elemento
{
    Elemento *next;
    char dado[TAM_PACOTE];
};

void converte_dados_em_pacotes(Fila*, char* dados);

void clear(Fila*);
char isEmpty(Fila*);
char isFull(Fila*);
void enqueue(Fila*, Elemento*);
void dequeue(Fila*);
Elemento* firstEl(Fila*);

void visualizar_pacotes(Fila* f1, Fila* f2);
void visualizar_transf();
void envia_pacotes(Fila* f1, Fila* f2);

Fila* new_fila(int capacidade);
Elemento* new_elemento(char* dados, int offset);

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

int main()
{
    Fila* f1 = new_fila(12);
    Fila* f2 = new_fila(12);

    char str[1024];

    fflush(stdin);
    printf("Digite o dado (string) a ser enviado:\n");
    scanf("%[^\n]", str);
    converte_dados_em_pacotes(f1, str);

    envia_pacotes(f1, f2);

    gotoxy(1, 18);

    fflush(stdin);
    system("pause");

    return 0;
}

void envia_pacotes(Fila* f1, Fila* f2)
{
    while(!isEmpty(f1))
    {
        Elemento* temp = new_elemento(firstEl(f1)->dado, 0);
        dequeue(f1);

        visualizar_pacotes(f1, f2);
        visualizar_transf();

        enqueue(f2, new_elemento(temp->dado, 0));
    }
}

void converte_dados_em_pacotes(Fila* fila, char* dados)
{
    int num_pacotes = 1 + strlen(dados) / (TAM_PACOTE-1);
    int memcpy_offset = 0;

    for (int i = 0; i < num_pacotes; i++)
    {
        enqueue(fila, new_elemento(dados, memcpy_offset));
        memcpy_offset += TAM_PACOTE-1;
    }
}

void visualizar_transf()
{
    gotoxy(12, 2);
    printf("======================");
    gotoxy(12, 6);
    printf("======================");

    int i;
    for (i = 0; i < 20; i++)
    {
        gotoxy((13 + i) - 1, 4);
        printf(" ");
        gotoxy(13 + i, 4);
        printf("*");
        Sleep(20);
    }
}

void visualizar_pacotes(Fila* f1, Fila* f2)
{
    system("cls");
    Elemento* el1 = f1->firstEl;
    Elemento* el2 = f2->firstEl;
    if (isEmpty(f1)) printf("*VAZIO*\n");
    gotoxy(48, 1);
    if (isEmpty(f2)) printf("*VAZIO*\n");

    int i = 1;

    while(el1 || el2)
    {
        if (el1)
        {
            gotoxy(1, i);
            printf(">%s<", el1->dado);
            el1 = el1->next;
        }
        if (el2)
        {
            gotoxy(48, i);
            printf(">%s<", el2->dado);
            el2 = el2->next;
        }

        i++;
    }

    if (isEmpty(f1)) printf("*CHEIO*\n");
    gotoxy(48, 1);
    if (isEmpty(f2)) printf("*CHEIO*\n");
}

void clear(Fila* fila)
{
    while(!isEmpty(fila))
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
    if (isFull(fila)) return;

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
    fila->quant_elementos++;
}

void dequeue(Fila* fila)
{
    if (isEmpty(fila))
        return;
    Elemento* temp = fila->firstEl;
    fila->firstEl = temp->next;
    free(temp);
    fila->quant_elementos--;
}

Elemento* firstEl(Fila* fila)
{
    return fila->firstEl;
}

Fila* new_fila(int capacidade)
{
    Fila* new_fila = (Fila*) malloc(sizeof(Fila));
    new_fila->capacidade = capacidade;
    new_fila->quant_elementos = 0;
    new_fila->lastEl = NULL;
    new_fila->firstEl = NULL;
    return new_fila;
}

Elemento* new_elemento(char* dado, int offset)
{
    char str[TAM_PACOTE] = "";

    for (int i = 0; i < TAM_PACOTE; i++)
    {
        str[i] = dado[offset+i];
    }
    str[TAM_PACOTE-1] = '\0';

    Elemento* new_el = (Elemento*) malloc(sizeof(Elemento));
    strcpy(new_el->dado, str);
    new_el->next = NULL;
    return new_el;
}

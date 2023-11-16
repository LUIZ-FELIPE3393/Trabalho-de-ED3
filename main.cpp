#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

FILE *arq_ptr;

int algSizeMax  = 3;
int algSize = 0;
int arqSize = 1;


typedef struct Algoritimo Algoritimo;

struct Algoritimo {
    char algo;
    Algoritimo *pAnt;
};

Algoritimo *pAlgIni = NULL;
Algoritimo *pAlgFim = NULL;

//Funções de fila (FIFO)
void clearAlg();
int isEmpity();
void enqueue(int num);
int dequeue();
Algoritimo * firstEl();
char isFull();
Algoritimo * newAlg(int num);

void visualizar_fila();

//Funções de Arquivos para pacotes
void put_arq(Algoritimo *alg);


int main() {
    setlocale(LC_ALL,"");

    

    system("pause");
    return 0;
}

void clearAlg(){
    int i;

    for(i = 1; i <= algSize; i++){
        dequeue();
    }

}

int isEmpity(){
    setlocale(LC_ALL,"");
    if(pAlgIni == NULL){
       //printf("\nFila está vazia");
        return 1;
    }
    else{
       //printf("\nFila não está vazia");
        return 0;
    }

}

void enqueue(int num){
    if(isEmpity()){
        Algoritimo *pAlg;
        pAlg = newAlg(num);
        pAlg->pAnt = NULL;
        pAlgIni = pAlg;
        pAlgFim = pAlg;
        algSize++;
    }
    else{
        Algoritimo *pAlg;
        pAlg = newAlg(num);
        pAlgFim->pAnt = pAlg;
        pAlgFim = pAlg;
        pAlg->pAnt = NULL;

        algSize++;
    }

}

int dequeue(){
    setlocale(LC_ALL,"");
    if(isEmpity()){
        return 1;
    }

    Algoritimo *pAux = pAlgIni;
    pAlgIni = pAux->pAnt;
    free(pAux);

    algSize--;

    return 0;
}

Algoritimo * firstEl (){
    setlocale(LC_ALL,"");

    if(isEmpity()){
        return NULL;
    }

    Algoritimo *pAux = pAlgIni;

    //printf("\nPrimeiro da fila:%c", pAux->algo);

    return pAux;
}

char isFull(){
    setlocale(LC_ALL,"");

    if(algSize == algSizeMax){
        //printf("\nFila está cheia");
        return 1;
    }
    else{
        //printf("\nFila não está cheia");
        return 0;
    }
}

Algoritimo * newAlg(int num){

    Algoritimo * alg = new Algoritimo;
    alg->algo = num;

    return alg;
}

void visualizar_fila()
{
    Algoritimo* alg = pAlgIni;

    printf("FILA { ");

    while (alg)
    {
        printf("%d", alg->algo);
        if(alg->pAnt)
            printf(" - ", alg->algo);
        alg = alg->pAnt;
    }
    printf(" }\n");
}
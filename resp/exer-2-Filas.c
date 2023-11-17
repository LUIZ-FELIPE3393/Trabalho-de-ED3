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
void isFull();
Algoritimo * newAlg(int num);

void visualizar_fila();

//Funções de Arquivos para pacotes
void put_arq(Algoritimo *alg);


int main() {
    enqueue(2);
    enqueue(3);

    dequeue();

    enqueue(1);

    dequeue();

    enqueue(4);
    enqueue(5);

    dequeue();
    dequeue();

    visualizar_fila();

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
    put_arq(pAux);//Envia o pacote(nó) pro arquivo;
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

void isFull(){
    setlocale(LC_ALL,"");

    if(algSize == algSizeMax){
        printf("\nFila está cheia");
    }
    else{
        printf("\nFila não está cheia");
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
            printf(" - ");
        alg = alg->pAnt;
    }
    printf(" }\n");
}

void put_arq(Algoritimo *alg){
    arq_ptr = fopen("pacotes.txt", "a");

    fprintf(arq_ptr, "%d{%d}\n", arqSize, alg->algo);//envia pros arquivos os pacotes com dados numericos mais o indice de numeros de pacotes enviados

    fclose(arq_ptr);
    arqSize++;
}
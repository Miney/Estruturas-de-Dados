#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//contar ocorrencias de cada operador
/*Sera montada uma lista encadeada com os operadores na ordem que aparecem no arquivo*/

struct operador {
    char operador;
    struct operador *prox;
}


void adicionaoperador (struct operador *head, int op){
    struct operador *aux, *novo;

    novo->op;

    aux=head;

    while(aux->prox != NULL){
        aux=aux->prox;
    }

    novo->prox = NULL;
    aux->prox=novo;
}


int main(){

    FILE *f2;

    char op;
    int i=0;
    char cmp[]={'#','<','>','(',')','/','+','-','*','{','}','[',']','=','\0'};

    struct operador listaop;
    listaop.prox = NULL;

    f2=fopen("PT1.txt","r");
    fscanf("f2","%c","&op");

    while(!feof(f2)){
            while(i<15){
                if(cmp[i]==op){
                    adicionaoperador(&listaop, op);
                }
                else i++;
            }
        fscanf("f2","%c","&op");
    }

    system("PAUSE");
    return 0;
}


/*

Yasmin Pimentel -- 11/0144341
Projeto 6 - Estrutura de Dados

Algoritmo Amigos Viajantes

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*VARIAVEIS GLOBAIS*/
///declaracao dos ponteiros para arquivo para permitir acesso pelas funcoes mais facilmente



/*  DECLARACAO DE ESTRUTURAS  */


struct aresta{
    int distancia;
    int identificadorDestino; ///Referente ao identificador da lista de nos
    struct aresta *prox;
};
typedef struct aresta Aresta;

struct no {
    int identificador; ///Referente ao vertice
    char *nome_cidade;
    struct no *prox;
    struct aresta *ListaAdj;
};
typedef struct no No;


/*  DECLARACAO DE FUNCOES   */
void editaArquivo();
No* inicializaGrafo();
int procuraCidade(No*, char*);
No* adicionaNos(No*);
//Adjacencias* adiciona_adjacencia(char[], int);
//Grafo* preenche_grafo(Grafo*);


/*  FUNCAO PRINCIPAL  */

int main(){
    editaArquivo();
    printf("editou o arquivo\n");
    No *Cidades, *x;

    Cidades=inicializaGrafo();
    Cidades=adicionaNos(Cidades);
    //printf("preencheu o grafo\n");

    ///funcao de impressao do grafo(teoricamente)
    while(Cidades->prox!=NULL){
        printf("entrou no for\n");
        printf("%s ", x->nome_cidade);
        Cidades=Cidades->prox;
        /*for(Cidades->adj ; Cidades->adj->prox!=NULL ; Cidades->adj->prox){
            printf("\t%s %d \n", Cidades->adj->nome_cidade, Cidades->adj->distancia);
        }*/
    }


}

/*  EXPLICITACAO DE FUNCOES   */


/*Funcao que edita o arquivo original para que em cada linha se leia apenas uma informacao, e sempre na ordem
cidade de origem, cidade destino, distancia. Esta funcionando perfeitamente, debug em 26 de setembro*/

void editaArquivo(){
    FILE* fp;
    FILE* n_fp;
    char cidade_aux[20], char_aux;
    int distancia_aux;
    int i;

    fp=fopen("entradaProj6","r");

    if(fp==NULL){
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }

    n_fp=fopen("EDT.txt","w");

    if(n_fp==NULL){
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }


    while(!feof(fp)){
         fscanf(fp,"%s",&cidade_aux);

         if(strcmp(cidade_aux, "para")==0){
            fprintf(n_fp,"\n");
            fscanf(fp,"%s",&cidade_aux);
         }

         if(strcmp(cidade_aux,"Km")==0){
            fprintf(n_fp,"\n");
            fscanf(fp,"%s",&cidade_aux);
         }

         for(i=0;i<20;i++){
            if(cidade_aux[i]==':'){
                cidade_aux[i]=cidade_aux[i+1];

                fprintf(n_fp,"%s\n", cidade_aux);
                fscanf(fp,"%d",&distancia_aux);
                fprintf(n_fp, "%d\n", distancia_aux);
                fscanf(fp, "%s", &cidade_aux);
            }
         }

         if(strcmp(cidade_aux,"para")!=0&&strcmp(cidade_aux,"Km")!=0){
            fprintf(n_fp,"%s", cidade_aux);
         }

    }
    fcloseall();
}

No* inicializaGrafo(){
    No *G;
    G=NULL;
    printf("Inicializou Grafo\n");
    return G;
}

No* adicionaNos(No* G){
    FILE *fp;
    //Grafo aux;
    char ch, cidade_org[20], cidade_dest[20];
    int distancia, i, contadorIdentificador=0, retornoBusca;
    No *temp, *percorre;

    temp = (No*) malloc(sizeof(No));
    percorre=(No*) malloc(sizeof(No));

    fp=fopen("EDT.txt", "r");
    if(fp==NULL){
        printf("nao abriu o arquivo\n");
    }

    while(!feof(fp)){
    printf("Entrou no while\n");
        fscanf(fp, "%s", &cidade_org);
        puts(cidade_org);
        fscanf(fp, "%s", &cidade_dest);
        puts(cidade_dest);
        fscanf(fp, "%d", &distancia);
        printf("%d\n", distancia);

        if(procuraCidade(G, cidade_org)==0){
            printf("Nao achou a cidade\n");
            if(G==NULL){
                printf("Encontrou NULL\n");
                G=temp;
            }
            percorre=G;
            while(percorre->prox!=NULL){
                percorre=percorre->prox;
            }
            percorre->prox=temp;
            temp->prox=NULL;
            strcpy(temp->nome_cidade, cidade_org);
            temp->ListaAdj->prox=NULL;
            temp->identificador=contadorIdentificador;
            contadorIdentificador++;
            printf("Adicionou a cidade\n");
        }


        if(procuraCidade(G, cidade_dest)==0){
            printf("Nao achou a cidade\n");
            if(G==NULL){
                G=temp;
            }
            percorre=G;
            while(percorre->prox!=NULL){
                percorre=percorre->prox;
            }
            percorre->prox=temp;
            temp->prox=NULL;
            strcpy(temp->nome_cidade, cidade_dest);
            temp->ListaAdj->prox=NULL;
            temp->identificador=contadorIdentificador;
            contadorIdentificador++;
        }

        else{
            printf("Achou a cidade\n");
        }
    }
    fclose(fp);

    return G;
}

///funcao que retorna 0 se nao encontrar a cidade
int procuraCidade(No* percorre, char *cidade){
    int retorno=0;
    if(percorre==NULL){
        retorno=0;
    }
    else{
        while(percorre->prox!=NULL){
            if(strcmp(percorre->nome_cidade, cidade)==0){
                retorno=1;
            }
            percorre=percorre->prox;
        }
    }
    return retorno;
}

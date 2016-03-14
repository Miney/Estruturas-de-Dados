#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define bool int
#define true 0
#define false 1

/*      VARIAVEIS GLOBAIS     */
int contadorIdentificador=0;

/*  DEFINICAO DAS ESTRUTURAS    */
struct no{
    char nome_cidade[20];
    int identificador;
    struct no *prox;
    struct aresta *listaArestas;
};
typedef struct no No;

struct aresta{
    char cidade_destino[20];
    int distancia;
    struct aresta *prox;
};
typedef struct aresta Aresta;


/*  DECLARACAO DE FUNCOES   */
void editaArquivo();
No* inicializaNo();
No* preencheGrafo(No*);
bool procuraCidade(No*, char[20]);
No* adicionaNo(No*, char[20]);
No* preencheAdjacencias(No*);
Aresta* adicionaAdjacencias(No*, char[20], int);


/*  FUNCAO PRINCIPAL   */
int main(){
    No *Grafo;
    Aresta *Arestas;
    bool paraDeImprimirCaminhos=false, paraDeImprimirCidades=false;

    Arestas=(Aresta*)malloc(sizeof(Aresta));

    editaArquivo();
    Grafo=inicializaNo();
    Grafo=preencheGrafo(Grafo);
    Grafo=preencheAdjacencias(Grafo);
    //printf("\n\n\n\n\n\n");

    //while(Grafo->prox!=NULL)
    while (false==paraDeImprimirCidades) {
        printf("cidade %d = %s\n", Grafo->identificador, Grafo->nome_cidade);

        Arestas=Grafo->listaArestas;
        if (Arestas!=NULL) {
            while(false==paraDeImprimirCaminhos) {
                printf("\t%s\t%d Km\n", Arestas->cidade_destino, Arestas->distancia);
                if(Arestas->prox!=NULL){
                    Arestas=Arestas->prox;
                } else {
                    paraDeImprimirCaminhos=true;
                }
            }
            paraDeImprimirCaminhos=false;
        }

        if (Grafo->prox!=NULL) {
            Grafo=Grafo->prox;
        } else {
            paraDeImprimirCidades=true;
        }
    }
    return 0;
}

/*      EXPLICITACAO DE FUNCOES     */

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

/*  Funcao simples de inicializacao de nos  */

No* inicializaNo(){
    No *N;
    N=NULL;
    return N;
}

/*funcao que adiciona um no na lista recebida*/

No* adicionaNo(No* listaNos, char *cidade_nova){
    No *novo, *percorre;

    novo=(No*)malloc(sizeof(No));
    novo->prox=listaNos;
    strcpy(novo->nome_cidade, cidade_nova);
    novo->listaArestas=NULL;
    novo->identificador=contadorIdentificador;
    printf("Adicionou a cidade %s na posicao %d\n", novo->nome_cidade, novo->identificador);
    contadorIdentificador++;
    return novo;
}

/*    funcao que retorna verdadeiro quando um no especifico esta na lista e falso quando ele nao esta     */

bool procuraCidade (No  *listaNos, char *cidade_buscada){
    No *temp, *percorre;
    percorre=(No*)malloc(sizeof(No));
    if(listaNos==NULL){
        printf("Nao encontrou %s\n", cidade_buscada);
        return false;
    }

    else{
        percorre=listaNos;

        while (1) {
            if(strcmp(cidade_buscada, percorre->nome_cidade)==0){
                printf("Encontrou %s na posicao %d\n", percorre->nome_cidade, percorre->identificador);
                return true;
            }

            else{
                printf("Passou por %s na posicao %d\n", percorre->nome_cidade, percorre->identificador);
                if(percorre->prox!=NULL){
                    percorre=percorre->prox;
                } else {
                    printf("Nao encontrou %s\n", cidade_buscada);
                    return false;
                }

            }
        }
    }
}

/* funcao principal de preenchimento do grafo, que fara uso de duas funcoes auxiliares que serao uteis para outros pontos do codigo
   os nos sao adicionados no inicio ao inves de serem adicionados no final(mais comum) o que nao vai influenciar o resultado final
*/

No* preencheGrafo(No* G){
    FILE *fp;
    char cidade_org[20], cidade_dest[20];
    int distancia;
    No* aux;
    aux=(No*)malloc(sizeof(No));

    fp=fopen("EDT.txt","r");

    while(!feof(fp)){
        fscanf(fp, "%s", &cidade_org);
        fscanf(fp, "%s", &cidade_dest);
        fscanf(fp, "%d", &distancia);


        if(procuraCidade(G, cidade_org)==false){
            G=adicionaNo(G, cidade_org);
        }

        if(procuraCidade(G, cidade_dest)==false){
            G=adicionaNo(G, cidade_dest);
        }
    }
    fclose(fp);
    return G;
}


/*  funcao de preenchimento de adjacencias para completar o grafo. Usa apenas uma funcao auxiliar, que adiciona o novo "no"
adjacente. Ela preenche as vias duplamente ( origem-destino e destino-origem) para uso posterior na funcao de busca de caminhos
ja que o grafo nao e dirigido   */

No* preencheAdjacencias(No* listaPrincipal){
    FILE *fp;
    char cidade_org[20], cidade_dest[20];
    int distancia, contador_achou_cidade;

    No* percorre;
    percorre=(No*)malloc(sizeof(No));

    Aresta *percorre_arestas;
    percorre_arestas=(Aresta*)malloc(sizeof(Aresta));
    fp=fopen("EDT.txt", "r");
    if(fp==NULL){
        printf("Nao pode abrir o arquivo\n");
        exit(1);
    }

    while(!feof(fp)){
        fscanf(fp, "%s", &cidade_org);
        fscanf(fp, "%s", &cidade_dest);
        fscanf(fp, "%d", &distancia);

        percorre=listaPrincipal;
        contador_achou_cidade=0;
        while(contador_achou_cidade!=2){
            if(strcmp(percorre->nome_cidade, cidade_org)==0){
                printf("achou a cidade %s\n", percorre->nome_cidade);
                percorre->listaArestas=adicionaAdjacencias(percorre, cidade_dest, distancia);
                printf("Adicionou %s como adjacencia de %s\n", percorre->listaArestas->cidade_destino, percorre->nome_cidade);
                contador_achou_cidade++;
            }
            if(strcmp(percorre->nome_cidade, cidade_dest)==0){
                printf("achou a cidade %s\n", percorre->nome_cidade);
                percorre->listaArestas=adicionaAdjacencias(percorre, cidade_org, distancia);
                printf("Adicionou %s como adjacencia de %s\n", percorre->listaArestas->cidade_destino, percorre->nome_cidade);
                contador_achou_cidade++;
            }
            percorre=percorre->prox;
        }
    }

    return listaPrincipal;
}

/*  funcao auxiliar de preenchimento das listas de adjacencias      */

Aresta* adicionaAdjacencias(No *cidade, char *cidade_dest, int distancia){
    Aresta *novo, *temp;

    novo=(Aresta*) malloc(sizeof(Aresta));
    temp=(Aresta*)malloc(sizeof(Aresta));

    temp=cidade->listaArestas;
    novo->prox=temp;
    novo->distancia=distancia;
    strcpy(novo->cidade_destino,cidade_dest);

    return novo;
}



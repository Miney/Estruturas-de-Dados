#include <stdlib.h>
#include <stdio.h>
#include <string.h>
///definicoes para insercao do tipo bool
#define bool int
#define true 0
#define false 1
///definicao do maximo de caminhos alternativos possiveis( questao de alocacao de memoria para uso de um vetor de listas)
#define MAX_CAMINHOS 1000

/*      VARIAVEIS GLOBAIS     */
int contadorIdentificador=0;
///numero absurdo para ir armazenando as menores distancias encontradas;
int contadorMenorDistancia=1000000;
int contadorListaCaminhos=0;
int contadorVetorJaPreenchido=0;




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
/*  ESTRUTURAS GLOBAIS   */
Aresta *listaCaminhos[MAX_CAMINHOS];
Aresta *listaFinal;
/*
struct listaCaminhos{
    char nome_cidade[20];
    int distancia;
    struct listaCaminhos *listaCaminho;
    struct listaCaminhos *prox;

};
typedef struct listaCaminhos ListaCaminhos;
*/

/*  DECLARACAO DE FUNCOES   */

void editaArquivo();
No* inicializaNo();
No* preencheGrafo(No*);
bool procuraCidade(No*, char[20]);
No* adicionaNo(No*, char[20]);
No* preencheAdjacencias(No*);
Aresta* adicionaAdjacencias(No*, char[20], int);


No* retornaNoNome(No*, char[20]);
No* retornaNoId(No*, int);
void imprimeLista(Aresta*);
//void iniciaBuscaCaminho(No*, int);
//void preencheCaminhos(No* , Aresta* , Aresta* );
void achaMenorCaminho(No*, int);
bool encontrar_todas_cidades(No* , Aresta*);

/*  FUNCAO PRINCIPAL   */
int main(){
    No *Grafo, *aux_impressao;
    Aresta *Arestas;
    char listaFinalOrganizada[50][20];
    bool paraDeImprimirCaminhos=false, paraDeImprimirCidades=false;
    int escolha_cidade_partida, cidade_partida, contadorListaFinalOrganizada=0, i;


    Arestas=(Aresta*)malloc(sizeof(Aresta));
    aux_impressao=(No*)malloc(sizeof(No));
    ///inicializacao da lista final que vai armazenar o menor caminho
    //listaFinal=(Aresta*)malloc(sizeof(Aresta));

    editaArquivo();
    Grafo=inicializaNo();
    Grafo=preencheGrafo(Grafo);
    Grafo=preencheAdjacencias(Grafo);
    aux_impressao=Grafo;
    printf("\t\t\t  Busca do menor caminho \t\t\t\n");
    printf("Digite o numero da cidade de partida:\n");
    //while(Grafo->prox!=NULL)
    while (false==paraDeImprimirCidades) {
        printf("cidade %d = %s\n", aux_impressao->identificador, aux_impressao->nome_cidade);

        //Arestas=aux_impressao->listaArestas;
        //imprimeLista(Arestas);
        Arestas=aux_impressao->listaArestas;
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
        if (aux_impressao->prox!=NULL) {
            aux_impressao=aux_impressao->prox;
        } else {
            paraDeImprimirCidades=true;
        }
    }
    scanf("%d", &escolha_cidade_partida);

inicio:

    switch(escolha_cidade_partida){
        case 0:
            cidade_partida=0;
            //strcpy(cidade_partida,"Brasília");
            break;
        case 1:
            cidade_partida=1;
            //strcpy(cidade_partida,"Goiânia");
            break;
        case 2:
            cidade_partida=2;
            //strcpy(cidade_partida,"CampinaGrande");
            break;
        case 3:
            cidade_partida=3;
            //strcpy(cidade_partida,"Blumenau");
            break;
        case 4:
            cidade_partida=4;
            //strcpy(cidade_partida,"BeloHorizonte");
            break;
        case 5:
            cidade_partida=5;
            //strcpy(cidade_partida,"CampoGrande");
            break;
        case 6:
            cidade_partida=6;
            //strcpy(cidade_partida,"Belém");
            break;
        case 7:
            cidade_partida=7;
            //strcpy(cidade_partida,"BoaVista");
            break;
        case 8:
            cidade_partida=8;
            //strcpy(cidade_partida,"Curitiba");
            break;
        case 9:
            cidade_partida=9;
            //strcpy(cidade_partida,"Florianópolis");
            break;
        case 10:
            cidade_partida=10;
            //strcpy(cidade_partida,"Santos");
            break;
        case 11:
            cidade_partida=11;
            //strcpy(cidade_partida,"RiodeJaneiro");
            break;
        case 12:
            cidade_partida=12;
            //strcpy(cidade_partida,"Petrópolis");
            break;
        case 13:
            cidade_partida=13;
            //strcpy(cidade_partida,"JoãoPessoa");
            break;
        default:
            printf("A cidade escolhida nao foi valida, digite uma cidade valida:\n");
            scanf("%d", &escolha_cidade_partida);
            ///o uso do goto foi so para simplificar o processo de loop, unicamente nesse caso
            goto inicio;
    }

    achaMenorCaminho(Grafo, cidade_partida);

    i=50;
    while(listaFinal!=NULL){
        strcpy(listaFinalOrganizada[i],listaFinal->cidade_destino);
        i--;
        contadorListaFinalOrganizada++;
        listaFinal=listaFinal->prox;
    }
    printf("Menor Caminho:\n");
    for(i=50;i>contadorListaFinalOrganizada;i--){
        printf("%s -> ", listaFinalOrganizada[i]);
    }
    printf("\nDistancia total: %d\n", contadorMenorDistancia);

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
    contadorIdentificador++;
    return novo;
}

/*    funcao que retorna verdadeiro quando um no especifico esta na lista e falso quando ele nao esta     */

bool procuraCidade (No  *listaNos, char *cidade_buscada){
    No *temp, *percorre;
    percorre=(No*)malloc(sizeof(No));
    if(listaNos==NULL){
        return false;
    }

    else{
        percorre=listaNos;

        while (1) {
            if(strcmp(cidade_buscada, percorre->nome_cidade)==0){
                return true;
            }

            else{
                if(percorre->prox!=NULL){
                    percorre=percorre->prox;
                } else {
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
        /*  como o preenchimento tem que ser uma vida de duas maos, o contador achou cidade tem que ser maior que dois(achou tanto a
            cidade destino quanto a cidade origem para mutuamente se adicionarem como adjacencias       */
        while(contador_achou_cidade!=2){
            if(strcmp(percorre->nome_cidade, cidade_org)==0){
                percorre->listaArestas=adicionaAdjacencias(percorre, cidade_dest, distancia);
                contador_achou_cidade++;
            }
            if(strcmp(percorre->nome_cidade, cidade_dest)==0){
                percorre->listaArestas=adicionaAdjacencias(percorre, cidade_org, distancia);
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

No* retornaNoNome(No* Grafo_final, char *cidade_buscada){
    No *percorre;
    percorre=(No*)malloc(sizeof(No));

    percorre=Grafo_final;
    while(percorre!=NULL){
        if(strcmp(cidade_buscada, percorre->nome_cidade)==0){
            //printf("Encontrou %s pelo nome\n", cidade_buscada);
            return percorre;
        }
        else{
            percorre=percorre->prox;
        }
        //printf("Nao encontrou %s pelo nome\n", cidade_buscada);
    }

}

No* retornaNoId(No* Grafo_final, int cidade_buscada){

    No *percorre;
    percorre=(No*)malloc(sizeof(No));

    percorre=Grafo_final;

    while (percorre!=NULL) {
        //printf("id buscado %d, id atual %d\n", cidade_buscada, percorre->identificador);
        if(cidade_buscada == percorre->identificador){
            //printf("Encontrou %s pela id\n", percorre->nome_cidade);
            return percorre;
        }

        else{
            //if(percorre->prox!=NULL){
                percorre=percorre->prox;
            //} else {
              //  printf("\nFATAL ERROR\n");
            //}
        }
    }
    printf("Nao encontrou a cidade buscada pela id %d\n", cidade_buscada);
}
/*
void iniciaBuscaCaminho(No* Grafo_final,int cidade_inicial){
    No *aux;
    aux=(No*) malloc(sizeof(No));
    printf("Alocou para o no auxiliar\n");
    aux=retornaNoId(Grafo_final, cidade_inicial);
    printf("retornou no pela Id\n");
    //Aresta novaLista[contadorListaCaminhos];

    while(aux->listaArestas!=NULL){
        printf("dentro do while busca caminho\n");
        listaCaminhos[contadorListaCaminhos]=(Aresta*)malloc(sizeof(Aresta));

        strcpy(listaCaminhos[contadorListaCaminhos]->cidade_destino, aux->nome_cidade);
        listaCaminhos[contadorListaCaminhos]->distancia=0;

        listaCaminhos[contadorListaCaminhos]->prox=NULL;

        preencheCaminhos(Grafo_final, aux->listaArestas, listaCaminhos[contadorListaCaminhos]);
        aux->listaArestas=aux->listaArestas->prox;
        contadorListaCaminhos++;
        sleep(1);
    }
}
*/
/*
void preencheCaminhos(No* Grafo_final, Aresta* novo_elemento, Aresta* listaCaminho){
    No* aux;

    //Aresta* novaLista[contadorListaCaminhos];
    //listaCaminhos[contadorListaCaminhos]=(Aresta*)malloc(sizeof(Aresta));

    aux=(No*)malloc(sizeof(No));
    aux=retornaNoNome(Grafo_final, novo_elemento->cidade_destino);

    novo_elemento->prox=listaCaminho;

    while(aux->listaArestas!=NULL){

        listaCaminhos[contadorListaCaminhos]=(Aresta*)malloc(sizeof(Aresta));
        listaCaminhos[contadorListaCaminhos]=novo_elemento;
        strcpy(novo_elemento->cidade_destino, aux->listaArestas->cidade_destino);
        novo_elemento->distancia=aux->listaArestas->distancia + listaCaminho->distancia;

        if(encontrar_todas_cidades(Grafo_final, novo_elemento)==true){
            if(novo_elemento->distancia<contadorMenorDistancia){
                listaFinal=novo_elemento;
                contadorMenorDistancia=novo_elemento->distancia;
            }
        }

        else{
                printf("Nao encontrou todas cidades na lista %d\n", contadorListaCaminhos);
        }

        ///para ele nao preencher listas indefinidamente

        if(novo_elemento->distancia < contadorMenorDistancia && contadorListaCaminhos<MAX_CAMINHOS){
            printf("Inicia nova lista\n");
            preencheCaminhos(Grafo_final, aux->listaArestas, novo_elemento);
        }

        else if(contadorListaCaminhos==MAX_CAMINHOS){
            printf("Atingiu o maximo de caminhos\n");
        }
        aux->listaArestas=aux->listaArestas->prox;
        contadorListaCaminhos++;
    }
}
*/
bool encontrar_todas_cidades(No* Grafo_final, Aresta* listaCidadesTeste){
    No *percorre_grafo;
    Aresta *percorre_lista;

    Aresta *temporariaParaImpressao;

    percorre_grafo=(No*)malloc(sizeof(No));
    percorre_lista=(Aresta*)malloc(sizeof(Aresta));

    temporariaParaImpressao=(Aresta*)malloc(sizeof(Aresta));

    ///a base do calculo sera o proprio grafo, porque nele so existe uma ocorrencia de cada cidade, enquanto na lista podem haver mais
    int contador_cidades=0;
    temporariaParaImpressao=listaCidadesTeste;
    //imprimeLista(temporariaParaImpressao);
    //sleep(2);

    percorre_grafo=Grafo_final;

    while(percorre_grafo!=NULL){
        //printf("1\n");
        percorre_lista=listaCidadesTeste;
        //printf("cidade sendo procurada: %s\n", percorre_grafo->nome_cidade);
        while(percorre_lista!=NULL){

            //printf("2\tcidade= %s\tdestino= %s\n",percorre_grafo->nome_cidade,percorre_lista->cidade_destino);

            if(strcmp(percorre_grafo->nome_cidade, percorre_lista->cidade_destino)==0){
                //percorre_grafo=percorre_grafo->prox;
                //printf("Achou %s\n", percorre_lista->cidade_destino);
                contador_cidades++;
                //break;
            }

            //else{
            percorre_lista=percorre_lista->prox;
            //printf("4\tcidade_prox= %s\n",percorre_lista->cidade_destino);
            //}
            //sleep(1);
        }
        if(contador_cidades==14){
            //printf("Encontrou todas cidades na lista\n");
            return true;
        }
        else{
            //printf("Ainda nao encontrou todas as cidades na lista, procurando prox elemento\n");
            percorre_grafo=percorre_grafo->prox;
        }
        //printf("7\n");
    }
    //printf("Nao encontrou todas as cidades na lista\n");
    return false;
}

void imprimeLista(Aresta* listaParaImprimir){
    //printf("[imprimeLista] entrou ");
    Aresta *aux_impressao;
    aux_impressao=(Aresta*)malloc(sizeof(Aresta));
    aux_impressao=listaParaImprimir;
    //printf(":%s:  |", listaParaImprimir->cidade_destino);
    //if (listaParaImprimir->prox!=NULL) {
    //    imprimeLista(listaParaImprimir->prox);
    //}
    while(aux_impressao!=NULL){
        printf(":%s:  |", aux_impressao->cidade_destino);
        aux_impressao=aux_impressao->prox;
        //sleep(1);
    }
    //printf("[imprimeLista] saiu\n");
}

int retornaNumeroAdjacencias(Aresta* listaArestas){
    int retorno;
    Aresta* aux;
    aux=listaArestas;
    while(aux!=NULL){
        retorno++;
        aux=aux->prox;
    }
    return retorno;
}


void achaMenorCaminho(No* Grafo_final, int cidade_inicial){
    No *aux;
    Aresta *lista_aux;
    bool encontrou_novos_caminhos;
    int i, j;

    aux=(No*)malloc(sizeof(No));
    lista_aux=(Aresta*)malloc(sizeof(Aresta));

    aux=retornaNoId(Grafo_final, cidade_inicial);

    //printf("retornou no auxiliar da cidade inicial pela Id\n");

    ///aterra, da um nome e atribui uma distancia ao no 0
    listaCaminhos[contadorListaCaminhos]=(Aresta*)malloc(sizeof(Aresta));


    strcpy(listaCaminhos[contadorListaCaminhos]->cidade_destino, aux->nome_cidade);
    listaCaminhos[contadorListaCaminhos]->distancia=0;
    listaCaminhos[contadorListaCaminhos]->prox=NULL;

    printf("vetor iniciado, entra no loop principal\n");

    do{
        encontrou_novos_caminhos=false;

        for(i=0 ; i<=contadorVetorJaPreenchido ; i++){
            if(listaCaminhos[i]->distancia < contadorMenorDistancia && encontrar_todas_cidades(Grafo_final, listaCaminhos[i])==false){
                encontrou_novos_caminhos=true;

                aux=retornaNoNome(Grafo_final, listaCaminhos[i]->cidade_destino);
                imprimeLista(aux->listaArestas);
                //sleep(2);

                while(aux->listaArestas!=NULL){
                    if( aux->listaArestas->prox == NULL ){
                        lista_aux->prox=listaCaminhos[i];
                        strcpy(lista_aux->cidade_destino, aux->listaArestas->cidade_destino);
                        lista_aux->distancia = aux->listaArestas->distancia + listaCaminhos[i]->distancia;
                        listaCaminhos[i]=lista_aux;
                        printf("\nImpressao velha lista %d\n", i);
                        //imprimeLista(listaCaminhos[i]);
                        //sleep(2);

                    }
                    else{
                        contadorListaCaminhos++;
                        listaCaminhos[contadorListaCaminhos]=(Aresta*)malloc(sizeof(Aresta));
                        //listaCaminhos[contadorListaCaminhos]=listaCaminhos[i];
                        lista_aux->prox=listaCaminhos[i];

                        strcpy(lista_aux->cidade_destino, aux->listaArestas->cidade_destino);
                        printf("\nAdicionando %s\n", lista_aux->cidade_destino);
                        lista_aux->distancia = aux->listaArestas->distancia + listaCaminhos[i]->distancia;
                        listaCaminhos[contadorListaCaminhos]=lista_aux;
                        printf("\nImpressao nova lista %d\n", contadorListaCaminhos);
                        //sleep(2);
                        //imprimeLista(listaCaminhos[contadorListaCaminhos]);
                        //sleep(2);
                    }
                    aux->listaArestas=aux->listaArestas->prox;
                    printf("###############");
                    imprimeLista(aux->listaArestas);
                    //sleep(2);
                }

            }
        }

        contadorVetorJaPreenchido=contadorListaCaminhos;
        printf("Terminou alteracoes, %d locais do vetor preenchidos, verificando caminhos\n", contadorVetorJaPreenchido);
        sleep(2);

        for(i=0;i<contadorVetorJaPreenchido;i++){
            if(listaCaminhos[i]->distancia < contadorMenorDistancia){
                if(encontrar_todas_cidades(Grafo_final, listaCaminhos[i])==true){
                    listaFinal=listaCaminhos[i];
                    contadorMenorDistancia=listaCaminhos[i]->distancia;
                }
            }
        }

        printf("Terminou verificacao, reiniciando?\n");
        sleep(2);


    }while(encontrou_novos_caminhos==true);

}

/*Universidade de Brasilia
  Projeto 3 Estruturas de Dados - Desenvolvimento de codificador
  Helena Schubert 10/0012311
  Yasmin Pimentel 11/0144341
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
///Definicao das variaveis globais
///Variavel global de contagem para preenchimento no vetor caminho da folha
int posicao=0;
///frase a ser codificada
char frase[80];
///Definicao de estruturas

struct caminho
{
    int binario;
    struct caminho *prox;
};
typedef struct caminho Caminho;

struct lista
{
    char caractere;
    int freq;
    int tamanho_caminho;
    ///o caminho eh estrutura propria
    struct caminho *cam;
    struct lista *pro;
    struct lista *ant;
};
typedef struct lista Lista;



///Variavel global de lista
Lista *fr;
struct fila
{
    struct lista *pri;
    struct lista *ult;
};
typedef struct fila Fila;

///Declaracao de funcoes

Lista* cria_lista(void);
Lista* busca_na_lista(Lista *, char );
Lista* incrementa_lista(Lista *, char );
Lista* aloca_carct_lista(Lista *, char [80]);
void imprime_lista(Lista *);
Lista* procura_menor_freq (Lista *);
Lista* compara (Lista *, Lista *);
Lista* retira (Lista*, Lista *);
Fila* cria_fila(void);
Fila* insere_na_fila(Fila *, Lista *);
Fila* enfilera (Lista *);
void imprime_fila(Fila *);
Fila* insere_ordenadamente_na_fila(Fila *, Lista *);
Fila*  meristema (Fila *);
Caminho* insere_binario(Caminho *, int);
void imprime_caminho(void);
void imprime_compressao(void);
///Funcao principal

int main()
{

    Lista *aux;
    Fila *fla;

    printf("Digite uma frase de ate 80 caracteres a ser codificada:\n");
    gets(frase);
    printf("\n%s\n", frase);
    fr=cria_lista();
    fr=aloca_carct_lista(fr, frase);
    imprime_lista(fr);
    printf("\n\n");
    fla=enfilera(fr);
    printf("............. \n\n");
    //imprime_fila(fla);
    fla=insere_ordenadamente_na_fila(fla, fla->ult);
    printf("............. \n\n");
    imprime_fila(fla);
    imprime_caminho();
    imprime_compressao();
    return 0;
}

///Definicao de funcoes

Lista* aloca_carct_lista(Lista *l, char frase[80])
{
    int i;
    i=0;
    while(frase[i]!='\0')
    {
        l=incrementa_lista(l, frase[i]);
        i++;
    }
    return l;
}

Lista* cria_lista(void)
{
    return NULL;
}

Lista* incrementa_lista(Lista *l, char c)
{
    Lista *novo, *aux;
    if(l==NULL)
    {
        novo=(Lista*)malloc(sizeof(Lista));
        novo->pro=NULL;
        novo->ant=NULL;
        novo->tamanho_caminho=0;
        novo->caractere=c;
        novo->freq=1;
        return novo;
    }
    else
    {
        aux=busca_na_lista(l, c);
        if(aux==NULL)
        {
            novo=(Lista*)malloc(sizeof(Lista));
            novo->pro=NULL;
            novo->ant=l;
            l->pro=novo;
            novo->caractere=c;
            novo->freq=1;
            novo->tamanho_caminho=0;
            return novo;
        }
        else
        {
            aux->freq++;
            return l;
        }
    }
}

Lista* busca_na_lista(Lista *l, char c)
{
    Lista *p;
    while(l!=NULL)
    {
        if(l->caractere==c)
            return l;
        else
            l=l->ant;
    }
    if(l==NULL)
        return NULL;
}

void imprime_lista(Lista *l)
{
    Lista *p;
    for(p=l; p!=NULL; p=p->ant)
    {
        printf("%c\t%d\n", p->caractere, p->freq);
    }
}

Lista* compara (Lista *um, Lista *dois)
{
    if(um->freq < dois->freq)
        return um;
    else
        return dois;
}

Lista* procura_menor_freq(Lista *l)
{
    Lista *aux=l, *p=l;
    if(l==NULL)
        return NULL;
    while(p!=NULL)
    {
        aux=compara(aux,p);
        p=p->ant;
    }
    return aux;
}

Fila* cria_fila(void)
{
    Fila *f=(Fila*)malloc(sizeof(Fila));
    f->pri=NULL;
    f->ult=NULL;
    return f;
}

Lista* retira (Lista*l, Lista *elem)
{
    if(l==NULL)
        return NULL;

    if(elem->ant==NULL && elem->pro==NULL)
    {
        return NULL;
    }
    if(elem->ant==NULL && elem->pro!=NULL)
    {
        elem->pro->ant=NULL;
        return l;
    }
    if(elem->ant!=NULL && elem->pro!=NULL)
    {
        elem->pro->ant=elem->ant;
        elem->ant->pro=elem->pro;
        return l;
    }
    if(elem->ant!=NULL && elem->pro==NULL)
    {
        elem->ant->pro=NULL;
        return elem->ant;
    }
}

Fila* insere_na_fila(Fila *f, Lista *no)
{
    if(f->pri==NULL)
    {
        f->pri=no;
        f->ult=no;
        no->ant=NULL;
        no->pro=NULL;
        return f;
    }
    else
    {
        no->ant=f->ult;
        f->ult->pro=no;
        no->pro=NULL;
        f->ult=no;
        return f;
    }
}

Fila* enfilera (Lista *l)
{
    Fila *f;
    Lista *aux, *novo, *a2;
    f=cria_fila();
    novo=l;
    while(novo!=NULL)
    {
        aux=procura_menor_freq(novo);
        a2=aux;
        novo=retira(novo, aux);
        f=insere_na_fila(f, a2);
    }
    return f;
}

void imprime_fila(Fila *f)
{
    Lista *p;
    p=(Lista*)malloc(sizeof(Lista));
    p=f->pri;
    while(p!=NULL)
    {
        printf("%c\t%d", p->caractere, p->freq);
        while(p->cam!=NULL){
            printf("%d",p->cam->binario);
            p->cam=p->cam->prox;
        }
        printf("\n");
        p=p->pro;
    }
}

Fila*  meristema (Fila *f)
{
    /* nessa função resolvi criar novas interpretações e funcionalidades às estrutura já existentes,
    ou básicamente à lista. Como uma lista tem q ter no mínino um ponteiro em cada nó que se ligue ao nó
    seguinte para ser segmentada, e como uma fila vai do primeiro para o último, pensei na seguinte estruturação:
             uma fila com lista simples.
             cada nó pro aponta para o próximo
             -resta um ponteiro
             um ponteiro ant aponta para um nó paralelo
             o nó paralelo é a raiz de uma árvore
             o ponteiro ant da raiz equivale ao esq
             o ponteiro pro da raiz equivale ao dir
    tentarei realizar com sucesso as próximas funções com base nessa nova colocação descrita.*/

    Lista *raiz=(Lista*)malloc(sizeof(Lista));
    if(f->pri!=f->ult)
    {
        raiz->freq=f->pri->freq;
        raiz->freq=raiz->freq+f->pri->pro->freq;
        raiz->ant=f->pri;
        raiz->pro=f->pri->pro;
        f->pri=raiz->pro->pro;
        f=insere_ordenadamente_na_fila(f, raiz);
        meristema(f);
    }
    else
        return f;
}
///na lista da arvore ant seria a esquerda (equivalente a 0) e prox seria a direita (equivalente a 1)
Fila* insere_ordenadamente_na_fila(Fila *f, Lista *raiz)
{
    Lista *prl, *aux=f->pri;
    prl=(Lista*)malloc(sizeof(Lista));
    prl->tamanho_caminho=0;
    prl->caractere='0';
    prl->ant=raiz;
    prl->cam=insere_binario(prl->cam,0);
    prl->tamanho_caminho++;
    //posicao++;
    prl->freq=raiz->freq;
    if(raiz->freq < aux->freq && aux!=NULL)  //a nova raiz é menor q o primeiro da lista
    {
        prl->pro=aux;
        prl->cam=insere_binario(prl->cam, 1);
        prl->tamanho_caminho++;
        //posicao++;
        f->pri=prl;
    }
    if(raiz->freq >= f->ult->freq)
    {
        f->ult->pro=prl;
        prl->cam=insere_binario(prl->cam, 1);
        prl->tamanho_caminho++;
        //posicao++;
        prl->pro=NULL;
        f->ult=prl;
    }
    else
    {
        while(raiz->freq >=aux->pro->freq && aux->pro!=NULL)
        {
            aux=aux->pro;
        }
        prl->pro=aux->pro;
        aux->pro=prl;
    }
    return f;
}

Caminho* insere_binario(Caminho* cam, int info){
    Caminho* novo= (Caminho*) malloc(sizeof(Caminho));
    novo->binario=info;
    novo->prox=cam;
    return novo;
}

void imprime_caminho(void)
{
    int i=0;//, tamanho_frase, tamanho_caminho;
    Lista* aux;
    aux=(Lista*)malloc(sizeof(Lista));
    //tamanho_frase=sizeof(frase);

    printf("Mensagem condificada:");
    while(frase[i]!='\0'){
        aux=busca_na_lista(fr,frase[i]);
        while(aux->cam!=NULL){
            printf("%d", fr->cam->binario);
            aux->cam=aux->cam->prox;
            //tamanho_caminho++;
        }
        i++;
        printf("\n");
    }
}

void imprime_compressao(void){
    int tamanho_frase,tamanho_original=0, tamanho_final=0, i=0;
    Lista *aux;
    aux=(Lista*)malloc(sizeof(Lista));
    while(frase[i]!='\0'){
        tamanho_frase++;
        i++;
    }

    tamanho_original=tamanho_frase*8;

    for(i=0;i<tamanho_frase;i++){
      aux=busca_na_lista(fr,frase[i]);
      while(aux->tamanho_caminho)
      tamanho_final+=sizeof(aux->cam);
    }
    printf("Tamanho original:%d\tTamanho final:%d\t", tamanho_original, tamanho_final);
    tamanho_final=(tamanho_final/tamanho_original);
    printf("Taxa de compressao: %d\n", tamanho_final);
}

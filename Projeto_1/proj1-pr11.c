/****************************************************
Departamento de Ciência da Computação
Instituto de Ciências Exatas
Universidade de Brasília
Estrutura de Dados 
Alunos(a): 
Descrição: 
****************************************************/

/*INCLUDE*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

/*DEFINICOES*/
#define MIN_VOOS 0
#define MAX_VOOS 64
#define MIN_P 0
#define MAX_P 12
#define MIN_D 24
#define MAX_D 48
#define N_PISTAS 3
#define CHAR_P 'P'
#define CHAR_D 'D'
 
/*estruturas*/
typedef struct listaVoos{
	struct listaVoos *ant;
	struct listaVoos *prox;
	char cod[7];
	char tipo;
	int comb;
}tipo_lista;

typedef struct dado{
	char cod[7];
        char tipo;
        int comb;
	struct dado *prox;
}tipo_dado;

typedef struct fila{
	tipo_dado *ini;
	tipo_dado *fim;	
}tipo_fila;

/*enumeracoes*/
enum{P = 0, D};

enum{PISTA_1 = 0, PISTA_2, PISTA_3};

enum{EMERGENCIA = 0, POUSO, DECOLAGEM};

/*PROTOTIPOS*/
int geraRand(int min, int max, int T);
tipo_lista* insereElemento(tipo_lista *lista, char codigo[], int tipo, int combustivel);
void imprimeLista(tipo_lista *lista);
tipo_lista* processaLista(tipo_lista *lista, int pista);
tipo_lista* procuraVoo(tipo_lista *lista, int tipo);
tipo_lista* retiraItem(tipo_lista *item);
tipo_fila* criaFila(void);
void insereNaFila(tipo_lista *item, tipo_fila *fila);
void imprimeFila(tipo_fila *fila);
tipo_fila* esvaziaFila(tipo_fila *fila);
int filaVazia(tipo_fila *fila);

/*PRINCIPAL*/
int main()
{
	/*constantes*/
	char codigos[][7] = {"VG3001", "JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009", "AZ1008", 
			     "AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880", "AL0012", "TT4544", 
			     "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002", "AZ1002", "AZ1007", "GL7604", 
			     "AZ1006", "TG1503", "AZ1003", "JJ4403", "AZ1001", "LN7003", "AZ1004", "TG1504", 
			     "AZ1005", "TG1502", "GL7601", "TT4500", "RL7801", "JJ4410", "GL7607", "AL0029",
			     "VV3390", "VV3392", "GF4681", "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", 
			     "AZ1065", "LF0978", "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510", 
			     "TT1020", "AZ1098", "BA2312", "VG3030", "BA2304", "KL5609", "KL5610", "KL5611"};
	/*variaveis*/
	int NVoos, NPousos = 0, NDecolagens = 0;
	int CombP, CombD;
	int i, pista = 0;
	tipo_lista *listaVoos, *item;
	tipo_fila *filaP1, *filaP2, *filaP3;
	/*programa*/
	/*gera lista de voos aleatoria*/
	NVoos = geraRand(MIN_VOOS, MAX_VOOS, 1);
	listaVoos = NULL;
	for(i = 0; i < NVoos; i++){
		switch(geraRand(P, D, 0)){
			/*gera infos de pouso aleatoria*/
			case P:
				CombP = geraRand(MIN_P, MAX_P, 0);
				listaVoos = insereElemento(listaVoos, codigos[i], P, CombP);
				NPousos++;
				break;
			/*gera infos de decolagens aletoria*/
			case D:
				CombD = geraRand(MIN_D, MAX_D, 0);
				listaVoos = insereElemento(listaVoos, codigos[i], D, CombD);
				NDecolagens++;
				break;
		}
	}
	/*imprime primeira parte do programa*/
	printf("\n   FILA DE PEDIDOS DE VOOS DE UM AEROPORTO\n---------------------------------------------");
	printf("\n * Hora Atual: %s", __TIME__); 
	printf("\n * Numero de Voos: %i (%i pousos, %i decolagens)", NVoos, NPousos, NDecolagens);
	printf("\n * Lista de Pedidos: "); imprimeLista(listaVoos);
	/*cria e inicializa as filas das pistas*/
       	filaP1 = criaFila();
	filaP2 = criaFila();
	filaP3 = criaFila();
	/*loop que processa a lista, coloca na devida fila e remove elemento da lista ate estar vazia*/ 
	while(listaVoos != NULL){
		/*retorna o item da lista q deve ser enfileirado para a dada pista*/
		item = processaLista(listaVoos, pista);
                if(item != NULL){
			/*enfileira item para a dada pista*/
			switch(pista){
				case PISTA_1: insereNaFila(item, filaP1); break;
				case PISTA_2: insereNaFila(item, filaP2); break;
				case PISTA_3: insereNaFila(item, filaP3); break;
			}
			/*retira item da lista*/
                        listaVoos = retiraItem(item);
                }	
                /*proxima pista a ser processada - varia de 0, 1, 2, 0, 1, 2, 0, ...*/
		pista = (pista + 1) % N_PISTAS;
	}
	/*imprime os voos de cada pista*/
	printf("\n\n * Filas Designadas por Pista");
	printf("\n     	- Pista 1: "); imprimeFila(filaP1);
	printf("\n\n	- Pista 2: "); imprimeFila(filaP2);
	printf("\n\n	- Pista 3: "); imprimeFila(filaP3);
	/*finaliza programa - esvazia as filas (obs: lista ja esvaziada no loop acima)*/
	filaP1 = esvaziaFila(filaP1);
	filaP2 = esvaziaFila(filaP2);
	filaP3 = esvaziaFila(filaP3);
	printf("\n\nTecle ENTER para finalizar programa.");
	getchar();
	return 0;
}

/*FUNCOES*/
/*gera numero aleatorio dentro dos limites*/
int geraRand(int min, int max, int T)
{
	/*variaveis locais*/
	int r;
	/*subprograma*/
	if(T == 1)
		/*planta semente de tempo - apenas na primeira chamada*/
		srand(time(NULL));
	r = min+rand() % (max-min+1);
	return r;
}

/*insere elementos em uma lista DEC*/
tipo_lista* insereElemento(tipo_lista *lista, char codigo[], int tipo, int combustivel)
{
	/*variaveis*/
	tipo_lista *novo = (tipo_lista*) malloc(sizeof(tipo_lista));
	/*subprograma*/
	if(novo == NULL){
		printf("Falha na alocação de memoria. Tecle ENTER para sair");
		getchar(); exit(1);
	}
	/*insere novo elemento*/
	strcpy(novo->cod, codigo);
	novo->comb = combustivel;
	switch(tipo){
		case P: novo->tipo = CHAR_P; break;
		case D: novo->tipo = CHAR_D; break;
	}
	/*insere e atualiza nos*/
	if(lista == NULL){
		novo->prox = novo->ant = novo;
	}else{
		novo->prox = lista;
		novo->ant = lista->ant;
		lista->ant->prox = novo;
		lista->ant = novo;
	}
	return novo;	
}

/*imprime elementos de um lista DEC*/
void imprimeLista(tipo_lista *lista)
{
	/*variaveis locais*/
	tipo_lista *p = lista;
	/*subprograma*/
	if(lista != NULL) do{
		p = p->ant;
		printf("%s(%c%i)   ", p->cod,  p->tipo, p->comb);
	}while(p != lista);
}

/*processa a lista de voo para a pista adequqda (pista 1, 2 ou 3)*/
tipo_lista* processaLista(tipo_lista *lista, int pista)
{
	/*variaveis locais*/
	tipo_lista *item;
	/*subprograma*/
	switch(pista){
		/*para a pista 1*/
		case PISTA_1:
			/*procura emergencias*/
			item = procuraVoo(lista, EMERGENCIA);
			/*se nao tiver emergencias*/
			if(item == NULL){
				/*procura decolagens*/
				item = procuraVoo(lista, DECOLAGEM);
			}
			return item;
		/*para pistas 2 e 3*/
		default:
			/*procura pousos*/
			item = procuraVoo(lista, POUSO);
			/*se nao tiver pousos*/
                        if(item == NULL){
				/*procura decolagens*/
                                item = procuraVoo(lista, DECOLAGEM);
                        }
                        return item;
	}
}

/*procura o tipo desejado de voo (emergencia, pouso ou decolagem)*/
tipo_lista* procuraVoo(tipo_lista *lista, int tipo)
{
	/*variaveis locais*/
	tipo_lista *item = lista, *aux = NULL;
	int flag = 0;
	/*subprograma*/
	switch(tipo){
		/*procura casos de emergencia*/
		case EMERGENCIA:
			/*percorre toda lista*/
			if(lista != NULL) do{
				item = item->ant;
				/*caso encontre Pouso com 0 Combustivel retorna item*/
				if(item->tipo == CHAR_P && item->comb == 0)
					return item;
			}while(item != lista);
			return NULL;
		/*procura casos de pouso*/
		case POUSO:
			/*percorre toda lista*/
			if(lista != NULL) do{
                                item = item->ant;
				/*caso encontre pouso*/
                                if(item->tipo == CHAR_P){
					/*primeiro caso inicializa*/
					if(flag == 0){
                                                aux = item;
                                                flag = 1;
                                        }else{
						/*se combustivel do item atual e menor, seleciona item*/
                                                if(item->comb < aux->comb)
                                                        aux = item;
                                        }	
				}
                        }while(item != lista);
			/*retorna vazio ou item*/
                        return aux;
		/*procura casos de decolagem*/
		case DECOLAGEM:
			/*percorre toda lista*/
			if(lista != NULL) do{
                                item = item->ant;
				/*caso encontre decolagem*/
                                if(item->tipo == CHAR_D){
					/*primeira ocorrecia inicializa*/
					if(flag == 0){
						aux = item;
						flag = 1;
					}else{
						/*se combustivel do item atual e menor, seleciona item*/
                                        	if(item->comb < aux->comb)
                                        	        aux = item;
					}
                                }
                        }while(item != lista);
			/*retorna vazio ou itemf*/
                        return aux;
	}
	/*return necessario para nao dar warning*/
	return NULL;
}

/*retira elemento da lista de voos*/
tipo_lista* retiraItem(tipo_lista *item)
{
	/*variaveis locais*/
	tipo_lista *p;
	/*subprograma*/
	/*se existe apenas mais um item na lista DEC*/
	if(item->prox != item){
		item->prox->ant = item->ant;
		item->ant->prox = item->prox;
		p = item->prox;
		free(item);
		return p;
	}else{
		free(item);
		return NULL;
	}
}

/*cria fila*/
tipo_fila* criaFila(void)
{
	/*variaveis*/
	tipo_fila *f = (tipo_fila*) malloc(sizeof(tipo_fila));
	/*subprograma*/
	f->ini = f->fim = NULL;
	return f;

}

/*insere elemento da lista na respectiva fila*/
void insereNaFila(tipo_lista *item, tipo_fila *fila)
{
	/*variaveis*/
	tipo_dado *d = (tipo_dado*) malloc(sizeof(tipo_dado));
	/*subprograma*/
	/*copia infos para novo dado da fila*/
	strcpy(d->cod, item->cod);
	d->tipo = item->tipo;
	d->comb = item->comb;
	d->prox = NULL;
	/*verifica se fila nao estava vazia*/
	if(fila->fim != NULL)
		fila->fim->prox = d;
	fila->fim = d;
	/*caso de a fila estar inicialmente vazia*/
	if(filaVazia(fila))
		fila->ini = fila->fim;
		
}

/*imprime a fila desejada*/
void imprimeFila(tipo_fila *fila)
{
	/*variaveis*/
	tipo_dado *dado; 
	/*subprograma*/
	if(!filaVazia(fila)){
		for(dado = fila->ini; dado != NULL; dado = dado->prox)
			printf("%s(%c%i)  ", dado->cod, dado->tipo, dado->comb);
	}else{
		printf("A fila está vazia.");
	}
}

/*esvazia completamente a fila dada - recursivo*/
tipo_fila* esvaziaFila(tipo_fila *fila)
{
	/*subprograma*/
	/*se fila nao esta vazia*/
	if(!filaVazia(fila)){
		/*novo comeco da fila eh o proximo elemento*/
		fila->ini = fila->ini->prox;
		/*libera memoria do comeco antigo*/
		free(fila->ini);
		/*esvazia nova fila*/
		fila = esvaziaFila(fila);
	/*caso fila vazia*/
	}else{
		/*inicializa fila vazia*/
		fila->ini = fila->fim = NULL;
	}
	return fila;
}

/*verifica se fila esta vazia*/
int filaVazia(tipo_fila *fila)
{
	/*retorna 1 se fila vazia ou 0 caso contrario*/
	return(fila->ini == NULL);
}

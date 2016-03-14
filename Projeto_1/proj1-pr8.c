/*Alunos:   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Lista {
	char palavra[30];
	int f1,f2;
	struct Lista *next,*prev;
}lista;

void cria(lista**); /* cria a lista */
void separa(FILE *, int, lista **); /* le os arquivos e separa as palavras */
void ordena(int, lista **, char *); /* localiza o lugar da palavra na lista, que eh ordenada     em ordem alfabetica */
void verifica(int, lista *, int); /* verifica a localizaçao do elemento (primeiro ou segundo arquivo) e incrementa no contador*/
void remove_texto(lista **); /* remove os elementos inseridos na lista que só se encontram em um dos arquivos */
void remove_elemento(lista *n); /* remove elemento da lista */
void imprime(lista*); /* imprime a lista */
int insere_1(int, char *, lista **); /* insere o primeiro elemento da lista */
int insere_fim(lista *, int, char *, lista **); /* insere o elemento no fim da lista */
int insere(lista *, int, char *, lista **); /* insere o elemento no comeco ou no meio da lista */

int main () {
    
	FILE *fp1, *fp2;
    char arquivo1[30], arquivo2[30];
	lista *n;
    
	cria(&n);
	
	printf("insira o caminho do arquivo 1: ");
	gets(arquivo1);
	printf("insira o caminho do arquivo 2: ");
	gets(arquivo2);
	fp1 = fopen(arquivo1, "r");
	fp2 = fopen(arquivo2, "r");

	separa(fp1,1, &n);
	separa(fp2,2, &n);
	
	remove_texto(&n);
	imprime(n);
	
	return 0;
}

void cria(lista **n) {
	lista *p ;
	p = malloc(sizeof(lista));

	p->next = NULL;
	p->prev = NULL;
	p->f1 = 0;
	p->f2 = 0;
	p->palavra[0] = '\0';
	*n = p;
}

void separa(FILE *fp, int fn, lista **n){
	char p[30],c;
	int i=0,y;
	
	fscanf(fp, "%c", &c);
	while (!feof(fp)) {
		
		if ((c >64 && c<91) || (c>96 && c<123)) { /*intervalo das letras na tabela ASCII */
			p[i] = c;
			i++; y=0;
		} else {
			if (y == 0) {
			    p[i] = '\0';
			    ordena(fn, &(*n), p);
			    i = 0; y = 1;
			}
		}
		fscanf(fp, "%c", &c);
	}

	p[i] = '\0';
	ordena(fn, &(*n), p);
			    
	fclose(fp);

}
	
void ordena(int fn,lista **n, char *p) {
	lista *d;
	int i=0,s=0;
	d=*n;
	
	do {
		if (d->palavra[i] == p[i]) { /* caso a letra seja igual */
			if (p[i] == '\0') {	/* se o \0 eh igual quer dizer que jah tem essa palavra, soh incrementa o contador */
				verifica(fn, d,0);
				s = 1;
			}
			i++;
		} else if (d->f1 == 0 && d->f2 == 0) /* primeiro elemento da lista */
			s = insere_1(fn, p, &(*n));
		else if (p[i] < d->palavra[i]) /* novo elemento, no inicio ou no meio */
			s = insere(d, fn, p, &(*n));
		else if (d->next==NULL) /* novo elemento no final */
			s = insere_fim(d, fn, p, &(*n));
		else /* nao eh inserido nesse elemento, chama o proximo */
			d = d->next;
	} while (s == 0);
	
}

void verifica(int fn, lista *b, int g) {
	if (fn == 1) {
		if (g == 1) {
			b->f1 = 1;
			b->f2 = 0;
		} else
			b->f1 = b->f1 + 1;
	} else {
		if (g == 1){
			b->f2 = 1;
			b->f1 = 0;
		} else
			b->f2 = b->f2 + 1;
	}
}

void remove_texto(lista **n) {
	lista *h;
	h = *n;
	
	while (h->next != NULL) {
		if (h->f1 == 0 || h->f2 == 0)
			remove_elemento(h);
		h = h->next;
	}
	
	if (h->next == NULL) {
		if (h->f1 == 0 || h->f2 == 0)
			remove_elemento(h);
	}
}

void remove_elemento(lista *h) {
	
	if (h->next == NULL)
		 h->prev->next = h->next;
	else {
		h->next->prev = h->prev;
		h->prev->next = h->next;
	}
    
	free(h);
	
}


void imprime(lista *o) {
	printf("\n\nLista\n\n");
	while (o->next != NULL) {
	    printf("%s\t%d\t%d\n", o->palavra, o->f1, o->f2);
	    o = o->next;
	}
	if (o->next == NULL)
		printf("%s\t%d\t%d\n", o->palavra, o->f1, o->f2);
}

int insere_1(int fn, char *p,lista **n) {
	strcpy ((*n)->palavra,p);
	verifica(fn, (*n),1);
	
	return 1;
}

int insere_fim(lista *d, int fn, char *p, lista **n) {
	lista *b;
	b = malloc(sizeof(lista));

	strcpy (b->palavra,p);

	b->next = NULL;
	b->prev = d;
	d->next = b;

	verifica(fn,b,1);
	return 1;
}

int insere(lista *d, int fn, char *p,lista **n) {
	lista *b;
	b = malloc(sizeof(lista));

	strcpy (b->palavra,p);
	
	if (d->prev == NULL) 
		*n = b;
	
	b->next = d;
	b->prev = d->prev;
	d->prev = b;
	d = b->prev;
	d->next = b;
	
	verifica(fn, b,1);
	return 1;
}

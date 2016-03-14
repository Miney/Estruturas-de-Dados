///Projeto 2 - Simulador de Voo - Edicao Final
///Helena Schubert  ???
///Yasmin Pimentel  11/0144341

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//define state 0 e 1

///Para fins praticos, um minuto equivalera a 5 na simulacao

///Definicao das variaveis globais

int contadorCodigos, contadorId; ///sera utilizado para armazenar os codigos e as identidades dos voos

///Os codigos de voo serao estaticos, ja que todas as outras informacoes sao aleatorias
char matrizCodigos[64][6]={{"VG3001"}, {"JJ4404"}, {"LN7001"}, {"TG1501"},
{"GL7602"}, {"TT1010"}, {"AZ1009"}, {"AZ1008"}, {"AZ1010"}, {"TG1506"}, {"VG3002"}, {"JJ4402"}, {"GL7603"},
{"RL7880"}, {"AL0012"}, {"TT4544"}, {"TG1505"}, {"VG3003"}, {"JJ4403"}, {"JJ4401"}, {"LN7002"}, {"AZ1002"},
{"AZ1007"}, {"GL7604"}, {"AZ1006"}, {"TG1503"}, {"AZ1003"}, {"JJ4403"}, {"AZ1001"}, {"LN7003"}, {"AZ1004"},
{"TG1504"}, {"AZ1005"}, {"TG1502"}, {"GL7601"}, {"TT4500"}, {"RL7801"}, {"JJ4410"}, {"GL7607"}, {"AL0029"},
{"VV3390"}, {"VV3392"}, {"GF4681"}, {"GF4690"}, {"AZ1020"}, {"JJ4435"}, {"VG3010"}, {"LF0920"}, {"AZ1065"},
{"LF0978"}, {"RL7867"}, {"TT4502"}, {"GL7645"}, {"LF0932"}, {"JJ4434"}, {"TG1510"}, {"TT1020"}, {"AZ1098"},
{"BA2312"}, {"VG3030"}, {"BA2304"}, {"KL5609"}, {"KL5610"}, {"KL5611"}};


///Definicao dos TADs

struct voo {
  //clock_t cl;     ///horário de chegada ou partida do voo
  int horario;    ///horario de decolagem ou pouso (0-23*5 minutos)
  int estado;     ///aterrisagem = 0, decolagem =1
  char codigo[6]; ///codigo do voo
  int combustivel;///varia de 0-12*5 minutos restantes
  int id;
};

typedef struct voo Voo;

struct fila{
  Voo *primeiro;
  Voo *ultimo;
};

typedef struct fila Fila;

struct pista{
  int estado;  //1 se há avião na pista, 0 se não há
  Fila *espera;  //fila de voos que aguarda para usar a pista
  int avioesEspera; //quantos avioes estão na fila de espera
};

typedef struct pista Pista;

struct aeroporto{
  Pista *pista1; //pouso
  Pista *pista2; //pouso 2
  Pista *pista3; //decolagem e pouso de emergencia
};

typedef struct aeroporto Aeroporto;

/*
///essa estrutura eu pensei para armazenar os voos na ordem de clock

struct lista{
  struct lista *anterior;
  struct lista *proximo;
};
*/
///Declaracao das Funcoes

Voo* criaVoo();
Fila* criaFila();
Voo* geraVoo (Voo*);
int geraRand(int, int);

/*
///Funcoes para insercao na fila
Voo* auxInsereInicio(Voo*, int);///aqui int vale como o que for ser inserido no inicio da fila, provavelmente vai ser o endereco do voo
void insereInicioFila(Fila*, int);///aqui int vale como o que for ser inserido no inicio da fila
Voo* auxInsereFinal(Voo*, int);///idem
void insreFinalFila)(Fila*, int);///idem

///Funcoes para retirada da fila
Voo* auxRetiraInicio(Voo*);///aqui tanto faz qual o elemento
void retiraInicioFila(Fila*);///aqui tanto faz qual o elemento
Voo* auxRetiraFinal(Fila*);///aqui tanto faz qual o elemento
void retiraFinalFila(Fila*);///aqui tanto faz qual o elemento
*/

///Inicio do main

int main(){

  srand(time(NULL));

  int i, h, nVoos, listaVoos[64], indiceLista, j, limiteInferiorLista, ntroca, temp;



  nVoos=geraRand(10, 64);

  struct Voo nVoo[64];

  ///Aqui no main eu tratei os voos como vetor porque pareceu o que a funcao tava considerando, mas eu nao tenho certeza =P
  ///As filas, de qualquer forma vao ter que ser listas.

  for(i=0;i<nVoos;i++){
    nVoo[i]=criaVoo;
    nVoo[i]=geraVoo(nVoo[i]);

  }


  indiceLista=0;
  limiteInferiorLista=0;

  for(h=0;h<24;h++){
    for(i=0;i<nVoos;i++){
      if(nVoo[i].horario==h){
        listaVoos[indiceLista]=nVoo[i].id;
        indiceLista++;
      }
    }
    while(ntroca!=0){
      for(j=limiteInferiorLista;j<indiceLista;j++){
        if(j>j+1){
          temp=listaVoos[j];
          listaVoos[j]=listaVoos[j+1];
          listaVoos[j+1]=temp;
          ntroca++;
        }
      }
    }
    limiteInferiorLista=indiceLista;
  }

  printf("\t\tAEROPORTO INTERNACIONAL DO PARAISO\t\t");

/*
  for(i=0;i<nVoos;i++){
    printf("horario: %d combustivel: %d  codigo: %c%c%c%c%c%c \n", nVoo[listaVoos[i]].horario, nVoo[listaVoos[i]].combustivel, nVoo[listaVoos[i]].codigo[0],nVoo[listaVoos[i]].codigo[1],nVoo[listaVoos[i]].codigo[2],nVoo[listaVoos[i]].codigo[3],nVoo[listaVoos[i]].codigo[4],nVoo[listaVoos[i]].codigo[5]);
  }*/


  return 0;
}

///Definicao das funcoes

Voo* criaVoo(){
  return NULL;
}

Fila* criaFila(){
  Fila* f = (Fila*)malloc(sizeof(Fila));
  f->primeiro=f->ultimo=NULL;
  return f;
}



Voo* geraVoo (Voo* v){
  int i, j;
  //v->cl=rand()%1440*CLOCKS_PER_SEC;  //1440 segundos equivalem a 2h no tempo do simulador (2*60*60/5)

  i=contadorCodigos;
  contadorId=i;
  v->id=contadorId;

  for(j=0;j<6;j++){
    v->codigo[j]=matrizCodigos[i][j];
  }

  contadorCodigos++;
  v->horario=geraRand(0,24); ///periodos em que o voo pode aparecer
  v->estado=geraRand(0,2);

  if(v->estado==0){
    v->combustivel=geraRand(0,12);///caso decolagem, define-se combustivel
  }

  else{
    v->combustivel=100;///Caso decolagem o combustivel e irrelevante
  }
  return v;
}

int geraRand(int min, int max){
  int r;
  r=min+rand()%(max-min+1);
  return r;
}

/*
///A funcao auxiliar trabalha a estrutura a ser inserida na fila
Voo* auxInsereInicio(Voo* inicio){
  Voo* v = malloc(sizeof(Voo));
  ///aqui seria feita a insercao de informacao relevante?
  v->proximo=inicio;
  v->anterior=NULL;
  if(inicio!=NULL){
    inicio->anterior=p;
  }
  return v;
}

void insereInicioFila(Fila* f, int i){
  f->primeiro= auxInsereInicio(f->Inicio);
  if(f->final)==NULL{
    f->inicio=f->ultimo;
  }
}

Voo* auxInsereFinal(Voo*, int){

}
void insreFinalFila)(Fila*, int);///idem

///Funcoes para retirada da fila
Voo* auxRetiraInicio(Voo*);///aqui tanto faz qual o elemento
void retiraInicioFila(Fila*);///aqui tanto faz qual o elemento
Voo* auxRetiraFinal(Fila*);///aqui tanto faz qual o elemento
void retiraFinalFila(Fila*);///aqui tanto faz qual o elemento
*/

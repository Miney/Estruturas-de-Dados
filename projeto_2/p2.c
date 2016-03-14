

//SIMULADOR DE CONTROLADOR DE VOO

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

//para fim práticos, 1 minuto na vida real equilaverá a 5 minutos no simulador

struct voo {

       clock_t cl;   //horário de chegada/partida do voo
       int estado;  //aterrisagem = 0; decolagem =1
       char numero[6];   //numero do voo
       int prioridade; //de 0 a 12, 0 é a maior prioridade, 12 a menor
       struct voo *pro;
       struct voo *ant;
       };

struct fila{
       voo *pri;
       voo *ult;
       };

struct pista{
       int napista;  //1 se há avião na pista, 0 se não há
       fila *espera;  //fila de voos que aguarda para usar a pista
       int mod; //quantos avioes estão na fila de espera
       };

struct aeroporto{
       pista *p1; //pouso
       pista *p2; //pouso 2
       pista *p3; //decolagem e pouso de emergencia
       };

typedef struct pista pista;
typedef struct aeroporto aeroporto;
typedef struct voo voo;
typedef struct fila fila;

voo* cria_voo();
voo* randomizador (voo *);
voo* busca_localizacao (voo *, clock_t );
voo* incrementa_ran (voo *);
voo* gerador (voo *);

int main (){

srand(time(NULL));

voo *v;
v=cria_voo();
v=incrementa_ran(v);
printf("%d, %s\n", v->cl, v->numero);
v=incrementa_ran(v);
printf("%d, %s\n", v->cl, v->numero);
v=incrementa_ran(v);
printf("%d, %s\n", v->cl, v->numero);
v=incrementa_ran(v);
printf("%d, %s\n", v->cl, v->numero);


system("PAUSE");
return 0;
}
voo* cria_voo(){
       voo *v;
       v=NULL;
       return v;
       }

fila* cria_fila(){
      fila* f=(fila*)malloc(sizeof(fila));
      f->pri=NULL;
      f->ult=NULL;
      return f;
      }

voo* randomizador (voo *v){
     char let[2], num[4], aux[6];
     int i;
     v->cl=rand()%1440*CLOCKS_PER_SEC;  //1440 segundos equivalem a 2h no tempo do simulador (2*60*60/5)
     let[0]=rand()%25+65;
     let[1]=rand()%25+65; //numero do voo será gerado automaticamente, facilitando o trabalho
     for(i=0;i<4;i++){
                      num[i]=rand()%10+48;
                      }
     strcpy(aux, let);
     strcat(aux, num);
     strcpy(v->numero, aux);
     v->estado=rand()%2;
     v->prioridade=rand()%13;
     v->pro=NULL;
     return v;
     }

voo* busca_localizacao (voo *v, clock_t c){
     if(v->cl>=c && v->pro==NULL)
                                 return v;
     if(v->cl<c)
                return NULL;
     if(v->cl>=c && v->pro->cl>=c)
                              busca_localizacao(v->pro, c);
     if(v->cl>=c && v->pro->cl<c)
                             return v;
     }


voo* incrementa_ran (voo *ini){
      voo *aux, *v=(voo*)malloc(sizeof(voo));
      v=randomizador(v);
      if(ini==NULL){
                    v->pro=NULL;
                    return v;
                    }
      else{
           aux=busca_localizacao(ini, v->cl);
           if(aux==NULL){
                         v->pro=ini;
                         return v;
                         }
           else{
                v->pro=aux->pro;
                aux->pro=v;
                return ini;
                }
           }
      }

voo* gerador (voo *v){
      int i;
      for(i=0;i<64;i++){
                        v=incrementa_ran(v);
                        }
      return v;
      }


/* oq falta, ainda é organizar a lista dos voos gerados randomicamente  para ordenar eles em ordem crescente do menor clock
pro maior. Após ter essa ordem, o meu pensamento é criar a função organizadora. Elas funcionará mais ou menos assim:

    fila* organizodora (voo *v){
          quando o v->cl for igual ao clock(), q é afunção q contem o tempo do programa, o voo será posto na fila
          i.e.:
               espera até clock()==v->cl;
               então, de acordo com seu estado, ela será ordenada nas pista 1 e 2 (pouso), ou 3(decolagem)
               será alocado em ordem de crescente de prioridade
               aas demais considerações do programa devem ser lembradas
               cada pista tem uma fila própria

    existirão 3 estruturas desse modelo:
              struct pista{
                     fila *fila;
                     int ocupada;
                     }
              onde ocupada mostra o estado da fila
    uma função pega o primeiro da fila e poe na pista, e atualiza ocupado = 1;
    a cada 5min em tempo de programa, ou 1 min. em tempo real, essa função deve imprimir na tela
    os voos em espera e os voos em pista. Quando a pista->ocupada tiver valor 0, o prófixo da fila será chamado

    basicamente, o plano é esse! oq acha?
    */
aeroporto* cria_aer (){
           aeroporto *aer=(aeroporto*)malloc(sizeof(aeroporto));
           aer->p1->espera=NULL;
           aer->p1->napista=0;
           aer->p1->mod=0;

           aer->p2->espera=NULL;
           aer->p2->napista=0;
           aer->p2->mod=0;

           aer->p3->espera=NULL;
           aer->p3->napista=0;
           aer->p3->mod=0;
           return aer;
           }

int aguarda (clock_t cl){
    if(cl>=clock())
                   return 1;
    else
        aguarda(cl);
        }
aeroporto* organizadora (aeroporto *aer, voo *v){
           if(aguarda(v->cl)){
           if(v->estado==0){ //isto é, v esperaa pra aterrisar
                            if(aer->p1->napista==0)
                                             aer->p1->napista=1;
                            else{
                                 if(aer->p2->napista==0){
                                                   aer->p2->napista=1;
                                                   }
                                                   }
                                 else
                                     organiza_fila(aer, v)
                            atualiza(aer);
                            }
           if(v->estado==1){ //v espera pra decolar voo
                             if(aer->p3->napista==0)
                                              aer->p3->napista=1;

fila* organiza_fila (aeroporto *aer, voo *v){
              fila *aux1, *aux2;
              aux1=aer->p1->espera;
              aux2=aer->p2->espera;
              if(aux1==NULL){    //se ainda não há nenhum avião na fila de espera da pista 1
                             aux1->pri=v;
                             aux1->ult=v;
                             aer->p1->mod=aer->p1->mod+1;
                             }
              else{
                   if(aux2==NULL){ //se ainda não há nenhum avião na fila de espera da pista 2
                                  aux2->pri=v;
                                  aux2->ult=v;
                                  aer->p2->mod=aer->p2->mod+1;
                                  }
              else{
                   if(aer->p1->mod >= aer->p2->mod){
                                   aer->p1->mod=aer->p1->mod+1;
                                   aux1=ordena(aux1);
                                   }
                   if(aer->p1->mod < aer->p2->mod){
                                   aer->p2->mod=aer->p2->mod+1;
                                   aux2=ordena(aux2);
                                   }
                   }
              }
/*a próxima função funciona, teoricamente, dessse modo:
    o novo voo a ser incrementado percorre a lista e onde ele achar o primeiro numero (de prioridade) maior que ele,
    ele será alocado em frente a esse numero. Se esse numero em questão for o inicio da fila, o novo voo será agora o
    primeiro da fila. Se ele não achar nenhum numero maior que ele, ele será o último.
    */

pista* ordena (fila *f, voo *v){
      fila *aux=f;
      voo *contador;
      for(contador=aux->pri; contador=aux->ult; contador=aux->pri->pro){
                             if(contador->prioridade > v->prioridade){
                                                     v->pro=contador->pro;
                                                     contador->pro=v;
                                                     if(aux->pri==contador)
                                                                           aux->pri=v;
                                                     }
                             else
                             if(contador=aux->ult){
                                                   aux->ult->pro=v;
                                                   aux->ult=v;
                                                   }
                             }
      f=aux;
      return p;
      }



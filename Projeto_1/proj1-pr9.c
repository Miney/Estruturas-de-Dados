/*
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

struct lista{ //Struct
        char pal[50];
        int i;
        struct lista *prox;
        };
typedef struct lista lis;

lis* lst_cria(void){ //Cria lista
     return NULL;
     }
     
lis* lst_busca(lis* l, char* v){ //Busca elemento
     lis *p;
     char var[50];
     for (p=l; p!=NULL; p = p->prox) {
         strcpy(var, v);
         if(strcmp(p->pal,var)==0)
         return p;
     }
     return NULL ;
}
     
lis* lst_insere(lis* l, char *v){ //Insere elemento
     lis* novo = (lis*) malloc (sizeof(lis));
     int i;
     novo->prox = l;
     novo->i = 1;
     strcpy(novo->pal, v);
     /*for(i=0; i <= strlen(v); i++)
      novo->pal[i] = v[i];
     */
     /*for(i=0; v[i] != NULL; i++)
       novo->pal[i] = v[i];
     novo->pal[i] = NULL;
     */
     return novo;
}

void lst_imprime (lis* l){ //Imprime lista
     lis* p;
     for (p = l; p != NULL; p = p->prox){
         printf ("Palavra = %s -- %d\n", p->pal, p->i);
     }

}


/*lis* lst_ordena (lis* l){
     int o;
     lis *p, *j, *k, *m;
     o=0;
     for (p = l; p != NULL; p = p->prox, o++){
         if(p->prox != NULL){
                if(p->i < (p->prox)->i){
                        m = p->prox;
                        j->prox = m;
                        m->prox = p;
                        p->prox = (j->prox)->prox;
                        if(o == 0){
                            k->prox = p->prox;
                        } 
                }
         }              
     }
                        
     return ;
}*/

lis* lst_ordena (lis* l){
     int i;
     lis *p, *j, *g;
     for (p = l; p != NULL; p = p->prox){
         
         if(p->prox != NULL){
         
                    if ((p->i) > ((p->prox)->i)){
                    j = p;
                    g = (p->prox)->prox;
                    p->prox = g;
                 //   (p->prox)->prox = p->prox;
                    } 
         }
         }
         //printf ("a");
         return l;
}



int main(){
    //declaração de variáveis
    FILE *fo, *ft;
    char *rand,arq1[15],arq2[15], pall[50];
    lis *L1, *L2, *L3, *busca;
    int D,F,Z=0,C=0;

    
    //Programa

    printf ("Digite o nome do arquivo: ");
    gets(arq1);
    printf("Digite o nome do arquivo2: ");
    gets(arq2);
    
    if ((fo = fopen (arq1, "r")) == NULL){
            printf("Arquivo 1 nao encontrado.\n");
            system("pause");
            exit(1);
            }       
    if ((ft = fopen (arq2, "r")) == NULL){
            printf("Arquivo 2 nao encontrado.\n");
            system("pause");
            exit(2);
            }
    //printf("Abriu arquivos\n");
    
    L1 = lst_cria();
    L2 = lst_cria();
    L3 = lst_cria();
    
    //printf("Criou lista\n");
    
    while(!feof(fo)){
    
            fscanf (fo, "%s", pall);
            strcpy(rand,pall);
            busca = lst_busca(L1, rand);
            
            if(busca == NULL)
                     L1 = lst_insere(L1, rand);
            else{
                 busca->i++;
                 }
                 
    
    }
    
        while(!feof(ft)){
    
            fscanf (ft, "%s", pall);
            strcpy(rand,pall);
            busca = lst_busca(L2, rand);
            
            if(busca == NULL)
                     L2 = lst_insere(L2, rand);
            else{
                 busca->i++;
                 busca = NULL;
                 }
                 
    
    }
    
    lis *p1, *p2;
    FILE *gh;
    gh = fopen("Comparar.txt" , "w");
    fprintf(gh,"palavra\t\tfreq1\tfreq2\n");
    
    for( p1 = L1 ; p1!=NULL; p1=p1->prox){
            for( p2 = L2 ; p2 !=  NULL; p2 = p2->prox){
                  if(strcmp(p1->pal,p2->pal)==0){
                             fprintf(gh,"%s\t\t%d\t%d\n",p1->pal,p1->i,p2->i);
                             D = (p1->i + p2->i)/2;
                             F = (p1->i - p2->i);
                             C++;
                             printf("C1 - %d\n", C);
                             if(F < D){
                                  Z++;
                                  printf("Z1 - %d\n", Z);
                             }
                  }
           }          
    }
    printf("C- %d   Z- %d",C,Z);
    fprintf(gh,"\nArquivos analisados %s e %s\n",arq1, arq2);
    fprintf(gh,"Numero de palavras iguais %d\nNumero de palavras iguais que aparecem muito repetidas %d\n", C, Z);
    
    if(Z > C/2)
         fprintf(gh,"Esse arquivo é uma copia!!!!!!!\n");
    else
        fprintf(gh,"Arquivo naum eh copia");




    
    fclose(gh);
    fclose(ft);
    fclose(fo);
    
    system("pause");
    return 0;
    }

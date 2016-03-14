#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    char v1[]="//", v2[]="\0", v3[]="/*", v4[]="*/", vt[3];
    vt[2]='\0';

    //abre os arquivos para teste

    FILE *f1, *f2;

    f1=fopen("proj1-pr1.c","r");
    f2=fopen("proj1-edt.txt","a");

    /*inicia a retirada de comentarios e contrucao de arquivo*/

    while(!feof(f1)){
        fscanf(f1,"%c",&vt[0]);
        fscanf(f1,"%c",&vt[1]);

        if(strcmp(v1,vt)==0){
            do{
                vt[0]=vt[1];
                fscanf(f1,"%c",&vt[1]);
            }while(strcmp(v2,vt)!=0);

            fscanf(f1,"%c",&vt[0]);
            fscanf(f1,"%c",&vt[1]);
        }

        if(strcmp(v3,vt)==0){
            do{
                vt[0]=vt[1];
                fscanf(f1,"%c",&vt[1]);
            }while(strcmp(v4,vt)!=0);

            fscanf(f1,"%c",&vt[0]);
            fscanf(f1,"%c",&vt[1]);
        }


        else{
            fprintf(f2,"%c",vt[0]);
            fprintf(f2,"%c",vt[1]);
        }
    }
    /*termina de gerar o arquivo para teste*/

    system("PAUSE");
    return 0;
}

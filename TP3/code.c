#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int estMiniscule(char c) {return (c>='a'&& c<='z') ? 1 : 0;}
int estMajuscule(char c) {return (c>='A'&& c<='Z') ? 1 : 0;}

char *codage(char *text, char *passWord){
    int i = 0;
    int j=0;
    int taille = strlen(text);
    do{
            if (estMiniscule(text[i])){
                 text[i]= (text[i]-'a' +(passWord[(int)j%(strlen(passWord))]-'a'+1))%26 + 'a';
                 j++;
            }    
            else if (estMajuscule(text[i])){
                text[i]= (text[i]-'A' +(passWord[(int)j%(strlen(passWord))]-'a'+1))%26 + 'A';
                j++;
            }
            else
                text[i]= text[i];
            i++;
    }while(i < taille);
    return text;
}


void normaliserTexte(FILE *in, FILE *out){
    char c;
    int eof= fscanf(in,"%c",&c);
    do {
        printf("\n-->%d",eof);
        if(estMajuscule(c) || estMiniscule(c))
            fprintf(out,"%c",c);
        eof= fscanf(in,"%c",&c);
    }while (eof != EOF);
}

void decouperFichier(FILE *in, FILE *out, int longueur, int debut){
    char c;
    int i=0;
    int s = debut;
    int eof= fscanf(in,"%c",&c);
    do {
        if (i>debut || i == s+longueur){
             fprintf(out,"%c",c);
             s+=longueur;
        }
        eof= fscanf(in,"%c",&c);
        i++;
    }while (eof != EOF);
}

int main(int argc, char *argv[]){
    //1
    char *text = (char *)malloc(sizeof(char));
    char *passWord = (char *)malloc(sizeof(char));
    passWord = "java";
    printf("\nEnter your text here : ");
    fgets(text, 1000*sizeof(text), stdin);
    printf("\nCodage : %s",codage(text, passWord));
    //2
    FILE *fileIn,*fileOut;
    fileIn = fopen(argv[1],"rb");
    fileOut = fopen(argv[2],"wb");
    decouperFichier(fileIn,fileOut, 5, 0);

    
    return EXIT_SUCCESS;
}
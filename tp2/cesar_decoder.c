#include <stdio.h>
#include <stdlib.h>


int estLettre(char c){return ((c>='a' && c <= 'z') || (c>='A' && c<= 'Z')) ? 1 :0;}
int estMinuscule(char c) { return (c >= 'a' && c <= 'z') ? 1 : 0; }
int estMajuscule(char c) { return (c >= 'A' && c <= 'Z') ? 1 : 0; }

char prochaineLettre(FILE* in){
    
    int eof;
    char c;

    eof = fscanf(in, "%c", &c);

    if (in != NULL){
        if (eof != EOF){    
            if (estLettre(c)){
                return c;
            } else {
                //fprintf(stderr, "Warning : Ce n'est par une lettre\n");
                return '2'; // caractaire speciaux
            }
            eof = fscanf(in, "%c", &c); // on passe au caractaire suivant;
        } else {
            fprintf(stderr, "Erreur : la fin de fichier\n");
            return '1'; // la fin de la fichier
        }
    } else {
        fprintf(stderr, "Erreur : fichier mon_fichier.txt introuvable dans le repertoire courant\n");
    }
    return '0'; // error
    
}

char lettreLaPlusFrequente(FILE *in){
    int tab[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char c = prochaineLettre(in) ;
    int max=0;
    int indice=0;
    int i=0;

    if (c!='0')
        while(c!='1'){
            if (c != '2')
                tab[c-'a']++;
            c=prochaineLettre(in);
        }
    
    max = tab[0];

    for ( i=0; i<26; i++)
        if (max<tab[i]){
            max = tab[i];
            indice = i;
        }
    return indice+'a';
}



void decodageCesar(FILE *in, FILE *out) {
    char LettrePlusFrequente = lettreLaPlusFrequente(in);
    int decalage = 'e' - LettrePlusFrequente ; // le decalage a appliquer

    int eof;
    char c;

    rewind(in);
    eof = fscanf(in, "%c", &c);

     printf("\ndecalage qu\'on doit appliquer = %d\n", decalage);

    do {

        if (estMinuscule(c)){
            (decalage<=0) 
                ?   fprintf(out, "%c", (c-'a'+26+decalage)%26+'a')
                :   fprintf(out, "%c", (c-'a'+decalage+((-1*decalage/26)+1)*26)%26 +'a');
        } else if (estMajuscule(c)){
            (decalage<=0) 
                ?   fprintf(out, "%c", (c-'A'+26+decalage)%26+'A')
                :   fprintf(out, "%c", (c-'A'+decalage+((-1*decalage/26)+1)*26)%26 +'A');
        }
        else 
             fprintf(out,"%c",c);
        eof = fscanf(in, "%c", &c);

    } while(eof != EOF);

   
}

int main(int argc, char *argv[]){

   
    FILE *file;
    FILE *fileOut;

    file = fopen(argv[1], "rb");
    fileOut = fopen(argv[2], "wb");
    decodageCesar(file, fileOut);
    return EXIT_SUCCESS;
}
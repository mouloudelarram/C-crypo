/*
EL ARRAM Mouloud
TANASOV Vlad Alexandru
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int estLettre(char c){ return ((c>='a' && c <= 'z') || (c>='A' && c<= 'Z'));}
int estMinuscule(char c) { return (c >= 'a' && c <= 'z'); }
int estMajuscule(char c) { return (c >= 'A' && c <= 'Z'); }

char prochaineLettre(FILE* in){
    int status;
    char c;
    status = fscanf(in, "%c", &c);

    if (in != NULL){
        if (status != EOF){    
            if (estLettre(c)){
                return c;
            } else {
                return '2';
            }
            status = fscanf(in, "%c", &c); 
        } else {
            return '1'; 
        }
    } else {
        fprintf(stderr, "Erreur : fichier mon_fichier.txt introuvable dans le repertoire courant\n");
    }
    return '0'; 
    
}

char lettreLaPlusFrequente(FILE *in){
    rewind(in);
    int tab[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char c = prochaineLettre(in) ;
    int indice=0;
    int i=0;
   
    if (c!='0'){
        while(c!='1'){
            if (c != '2')
                tab[c-'a']++;
            c=prochaineLettre(in);
        }
    }

    for ( i=0; i<26; i++)
        if (tab[indice]<tab[i]){
            indice = i;
        }
    return indice+'a';
}

char majToMin(char l) {
    return (l-'A')+'a';
} 

void normaliserFichier(FILE* in, FILE* out)
{
    char c;
    int status = fscanf(in, "%c", &c);
    while (status != EOF)
    {
        if(estMajuscule(c)) 
            fprintf(out, "%c", majToMin(c));
        else if (estMinuscule(c))
            fprintf(out, "%c", c);
        status = fscanf(in, "%c", &c);
    } 
}

void decouperFichier(FILE *in, FILE *out, int longueur, int debut)
{
    rewind(in);
    char c;
    int status;
    status = fscanf(in, "%c", &c);

    if (fseek(in,debut, SEEK_SET) == 0)
        while(status != EOF){
            fprintf(out,"%c", c);
            fseek(in,longueur-1, SEEK_CUR);
            status = fscanf(in,"%c", &c);
        }

}

void decrypte(FILE* in, FILE* out, char *password, int taille) {
    rewind(in);

    char c;
    int status = fscanf(in,"%c", &c) ;
    int i=0;
    while(status != EOF) {
       int decalage;
       if(estMajuscule(c))
       {
        decalage = password[i%taille]-'a';
        fprintf(out,"%c", (c-'A'+26-decalage)%26+'A');
        i++;
       }
       else if (estMinuscule(c))
       {
        decalage = password[i%taille]-'a';
        fprintf(out,"%c", (c-'a'+26-decalage)%26+'a');
        i++;
       }
       else {
        fprintf(out,"%c", c);
       }
       status = fscanf(in,"%c", &c) ;
   }
}

int main(int argc, char *argv[])
{
    FILE* in;
    FILE* out;
    FILE* textDecoupe;
    FILE* textNormalise;
    int taille = atoi(argv[2]);
    char pwd[taille];
    in = fopen(argv[1], "rb");
    out = fopen(argv[3], "wb");
    textDecoupe = fopen("fileDecouper.txt", "w+");
    textNormalise = fopen("textNormalise.txt", "wb");

    normaliserFichier(in,textNormalise);
    fclose(textNormalise);

    textNormalise = fopen("textNormalise.txt", "rb");

    if (textNormalise == NULL){
        return 0;
    }

    rewind(textDecoupe);
  
    for (int i =1; i<= taille;i++){
        rewind(textNormalise);
        rewind(textDecoupe);
        decouperFichier(textNormalise, textDecoupe, taille, i); 
        rewind(textDecoupe);
        pwd[i-1]= lettreLaPlusFrequente(textDecoupe);
    }

    int decalage = 0 ;

    int i;
    for (i=0;i<taille;i++){
        decalage = 'e' -pwd[i];
        if (decalage <= 0) 
            pwd[i] =   -1*decalage +'a';
        else 
            pwd[i] = 'z'-decalage +1 ;
    }

    printf("\nLe mot de passe est : ");

     for (i=0;i<taille;i++){
        printf("%c", pwd[i]);
     }

    decrypte(in, out, pwd, taille);
    printf("\n");


    return EXIT_SUCCESS;
}

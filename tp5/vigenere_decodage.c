/*
    EL ARRAM Mouloud
    TANASOV Vlad Alexandru
    TP5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define IDEAL_NBR_ITER 100
#define DEBUT_INDICE_COINCI 0.065
#define FIN_INDICE_COINCI 0.095

int estMinuscule(char c) { return (c >= 'a' && c <= 'z'); }
int estMajuscule(char c) { return (c >= 'A' && c <= 'Z'); }
char majToMin(char l) { return (l-'A')+'a';} 

char prochaineLettre(FILE* in){
    int status;
    char c;
    status = fscanf(in, "%c", &c);
    if (in != NULL){
        if (status != EOF){    
            if ((c>='a' && c <= 'z') || (c>='A' && c<= 'Z')){
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
    int tab[26] = {0};
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


int TotalCharCompter(FILE * file){
    int compteur = 0;
    rewind(file);
    while(fgetc(file) != EOF)
        compteur ++;
    return compteur;
}

int CharCompter(FILE * file, char c){
    int compteur = 0;
    rewind(file);
    char temp = fgetc(file);
    while(temp != EOF){
        if (temp == c)
            compteur ++;
        temp = fgetc(file);
    }
    return compteur;
}

double IndiceCoincidence(FILE *in) {
    long NombreTotalLettres = TotalCharCompter(in);
    long NombreChaqueLettre = 0;
    double IndiceCoincidence = 0.0;
    for (int i=0; i<26;i++){
        NombreChaqueLettre = CharCompter(in, i+'a');
        IndiceCoincidence += NombreChaqueLettre*(NombreChaqueLettre-1.0);
    }
    return IndiceCoincidence / (NombreTotalLettres*(NombreTotalLettres-1.0));
}

int longueurMotDePasseVigenere(FILE *in)
{
    FILE *textDecoupe;
    textDecoupe = fopen("fileDecouper.txt", "w+"); 
    rewind(in);
    double indiceCoin = 0.0;
    indiceCoin = IndiceCoincidence(in);
    for (int i=1;i<IDEAL_NBR_ITER;i++){
        textDecoupe = fopen("fileDecouper.txt", "w+");
        decouperFichier(in, textDecoupe, i,0);
        fclose(textDecoupe);
        textDecoupe = fopen("fileDecouper.txt", "r+");
        indiceCoin = IndiceCoincidence(textDecoupe);
        printf("indice : %f\n",indiceCoin);
        if (indiceCoin > DEBUT_INDICE_COINCI && indiceCoin < FIN_INDICE_COINCI)
            return i;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    FILE* in;
    FILE* out;
    FILE* textDecoupe;
    FILE* textNormalise;
    int taille;
    char pwd[IDEAL_NBR_ITER];
    int decalage = 0;
    int i;

    in = fopen(argv[1], "rb");
    out = fopen(argv[2], "wb");
    textDecoupe = fopen("fileDecouper.txt", "w+");
    textNormalise = fopen("textNormalise.txt", "wb");
    normaliserFichier(in,textNormalise);
    fclose(textNormalise);
    textNormalise = fopen("textNormalise.txt", "rb");
    taille = longueurMotDePasseVigenere(textNormalise);
    rewind(textDecoupe);

    for (i=1; i<=taille;i++){
        rewind(textNormalise);
        rewind(textDecoupe);
        decouperFichier(textNormalise, textDecoupe, taille, i); 
        rewind(textDecoupe);
        pwd[i-1]= lettreLaPlusFrequente(textDecoupe);
    }

    for (i=0;i<taille;i++){
        decalage = 'e'-pwd[i];
        if (decalage <= 0) 
            pwd[i] = -1*decalage+'a';
        else 
            pwd[i] = 'z'-decalage+1 ;
    }

    printf("\nLa longueur de mot de passe est : %d et le mot de passe est : ",taille);
    for (i=0;i<taille;i++){
        printf("%c", pwd[i]);
    }
    printf("\n\n");
    decrypte(in, out, pwd, taille);

    return EXIT_SUCCESS;
}

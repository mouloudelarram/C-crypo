#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int estMiniscule(char c){ return (c>='a'&&c<='z') ? 1 : 0;}
int estMajiscule(char c){ return (c>='A'&&c<='Z') ? 1 : 0;}

int main(int argc, char *argv[]) {

    /* declaration des variables */
    FILE *fileInput;
    FILE *fileOutput;
    char c='\0';
    int eof = 1;
    int decalage = 0;
    
    /* Fin declaration des variables */

    fileInput = fopen(argv[1], "rb");
    fileOutput = fopen(argv[3], "wb");
    eof= fscanf(fileInput, "%c", &c); /* on initialise le eof*/
    decalage = atoi(argv[2]); /* recuperer le decalage */

    if (fileInput != NULL)
        do {
            if (estMiniscule(c)){
                (decalage >= 0) 
                    ?   fprintf(fileOutput,"%c", (c-'a'+decalage)%26 +'a' )
                    :   fprintf(fileOutput,"%c", (c-'z'+decalage)%26 +'z' );   /*(c-'a'+decalage+((-1*decalage/26)+1)*26)%26 +'a' */
            } else if (estMajiscule(c)){
                (decalage >= 0) 
                    ?   fprintf(fileOutput,"%c", (c-'A'+decalage)%26 +'A' )
                    :   fprintf(fileOutput,"%c", (c-'Z'+decalage)%26 +'Z' );  /* (c-'Z'+decalage+((-1*decalage/26)+1)*26)%26 +'Z' */
            } else {
                fprintf(fileOutput,"%c", c);
            }
            eof = fscanf(fileInput, "%c", &c);
                        
        } while(eof != EOF);
    return EXIT_SUCCESS;
}
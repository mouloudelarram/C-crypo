#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE *file;
    int eof = 1;
    char c='\0';

    file = fopen("mon_fichier.txt", "rd");
    if (file != NULL)
        do {
            printf("%c", c);
            eof = fscanf(file, "%c", &c);

        }while(eof != EOF);

    printf("\n");

    return EXIT_SUCCESS;
}
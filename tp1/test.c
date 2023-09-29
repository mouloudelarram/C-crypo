#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i=0;
    printf("Nombre d’options : %d\n", argc);
    for (i=0; i<argc; i++)
        printf("Option num %d : %s\n", i, argv[i]);
    
    return EXIT_SUCCESS;
}
/*
TANASOV Vlad Alexandru
EL ARRAM Mouloud
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int estMiniscule(char c) {return (c>='a' && c<='z');}
int estMajuscule(char c) {return (c>='A' && c<='Z');}

char *majToMin(char pwd[]) {
    int i;
    for (i=0; i<strlen(pwd); i++)
    {
        if(estMajuscule(pwd[i])) pwd[i] = (pwd[i]-'A')+'a';
    }
    return pwd;
} 

void codage(FILE *in, char pwd[], FILE *out) {
    char c;
    int status = fscanf(in, "%c", &c);
    int i=0;

    do 
    {
        if (estMiniscule(c))
        {
            c = (c-'a' +(pwd[(int)i%(strlen(pwd))]-'a'+1))%26 + 'a';
            i++;
        }    
        else if (estMajuscule(c))
        {
            c = (c-'A' +(pwd[(int)i%(strlen(pwd))]-'a'+1))%26 + 'A';
            i++;
        }

        fprintf(out,"%c",c);
        status = fscanf(in, "%c", &c);
    } while(status != EOF);

} 



int main(int argc, char *argv[])
{
    FILE *in;
    FILE *out;

    in = fopen(argv[1], "rb");
    out = fopen(argv[3], "wb");

    codage(in, majToMin(argv[2]), out);

    return EXIT_SUCCESS;
}

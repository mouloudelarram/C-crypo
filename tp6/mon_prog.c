#include <stdio.h>
#include <stdlib.h>
#include "lodepng.h"

struct myImage {
    int HEIGHT;
    int WIDTH;
    unsigned char* RED;
    unsigned char* GREEN;
    unsigned char* BLUE;
    unsigned char* OPACITY;
};

struct myImage LireImage(char* nom_fichier)
{
    struct myImage Img;
    unsigned error;
    unsigned char* image;
    unsigned width, height;

    error = lodepng_decode32_file(&image, &width, &height, nom_fichier);
    if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

    free(image);

    int taille = strlen(image);

    Img.HEIGHT = height;
    Img.WIDTH = width;
    Img.RED = (unsigned char *) malloc((taille/4)*size_of((unsigned char)));
    Img.GREEN = (unsigned char *) malloc((taille/4)*size_of((unsigned char)));
    Img.BLUE = (unsigned char *) malloc((taille/4)*size_of((unsigned char)));
    Img.OPACITY = (unsigned char *) malloc((taille/4)*size_of((unsigned char)));


    for(int i=0; i<taille; i += 4)
    {
        Img.RED[i] = image[i];
        Img.GREEN[i+1] = image[i+1];
        Img.BLUE[i+2] = image[i+2];
        Img.OPACITY[i+3] = image[i+3];
    }

    return Img;
}

int main(int argc, char *argv[])
{
    struct myImage Image = LireImage("chat.png");
    printf("%d", Image.HEIGHT);

    return EXIT_SUCCESS;
}
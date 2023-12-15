#include "offre.h"

int main(void){
    printf("Hello world!\n");
    return 0;
}

void test(void)
{
    FILE *flot;
    flot=fopen("précedences.txt","r");
    if(flot==NULL)
    {
        printf("Erreur dans l'ouverture de : précedences.txt !\n");
        exit(1);
    }
    Offre **tOffre;
    int tMax=5, taille=0;
    tOffre=(Offre **)malloc(5*sizeof(Offre *));
    tOffre=lireTravaux(flot, &taille);
}
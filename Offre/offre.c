#include "offre.h"

Offre * newOffre(char *travaux){
    Offre *new;
    new=(Offre *)malloc(sizeof(Offre));
    if (new==NULL){
        printf("Erreur: création structure offre\n");
        exit(1);
    }
    strcpy(new->travaux, travaux);
    new->ldevis=NULL;
    return new;
}

Maillon newMaillon{

}

void test(void){
    Offre *tOffre;
    int tMax=5, taille=0;
    char travaux[10];

    tOffre=(Offre *)malloc(5*sizeof(Offre));
    strcpy(travaux, "Test");
    tOffre=ajoutOffre(tOffre, travaux);
}
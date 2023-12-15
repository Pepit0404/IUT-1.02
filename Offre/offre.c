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

Maillon newMaillon(void){

}

void test(void){
    FILE *flot;
    flot=fopen("précedences.txt","r");
    if(flot==NULL)
    {
        printf("Erreur dans l'ouverture de : précedences.txt !\n");
        exit(1);
    }
    Offre **tOffre;
    int tMax=5, taille=0;
    char travaux[10];

    tOffre=(Offre **)malloc(5*sizeof(Offre *));
    strcpy(travaux, "Test");
    tOffre=ajoutOffre(tOffre, travaux);
    lireTravaux(flot);
}

Offre ** lireTravaux(FILE *flot)
{
    Offre **o, **aux;
    int i, nb=5, tmax=5;
    o=(Offre **)malloc(5*sizeof(Offre *));
    while(!feof(flot))
    { 
        if(nb==tmax)
        {
            tmax=tmax+5;
            aux=(Offre **)realloc(o,tmax*sizeof(Offre *));
            if(aux==NULL)
            {
                printf("Erreur dans l'allocation de aux pour les offres !\n");
                exit(1);
            }
            o=aux;
        }
        fscanf(flot,"%s",o[i]);
        i++;
    }
}
#include "offre.h"

/*
Fonction qui ajoute un devis dans le tableau quand le travail n'est pas encore présent dans le tableau
*/
int newOffre(Offre *tab[], int size, int *tMax, char *travaux){
    Offre *new, **aux;
    new=(Offre *)malloc(sizeof(Offre));
    if (new==NULL){
        printf("Erreur: création structure offre\n");
        exit(1);
    }
    if (size==(*tMax)){
        (*tMax)+=5;
        aux=(Offre **)realloc(tab, (*tMax)*sizeof(Offre *));
        if (aux==NULL){
            printf("Erreur: création tableaux aux\n");
            exit(1);
        }
        tab=aux;
        free(aux);
    }
    strcpy(new->travaux, travaux);
    new->ldevis=NULL;
    tab[size]=new;
    size+=1;
    return size;
}
/*
Maillon newMaillon{

}
*/

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
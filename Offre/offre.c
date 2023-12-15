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

Maillon * Lire1Devis(FILE *flot)
{
    Maillon *d;
    d=(Maillon *)malloc(5*sizeof(Maillon));
    fgets((d->devis).entreprise,31, flot);
    fgets((d->devis).adresse,51, flot);
    fscanf(flot,"%d",&(d->devis).capital);
    fscanf(flot,"%d",&(d->devis).duree); 
    fscanf(flot,"%d",&(d->devis).cout);
    return d;
}


Maillon newMaillon{

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
    tOffre=newOffre(tOffre, travaux);
    lireTravaux(flot);
}


void afficher(Offre o, int nb)
{

}
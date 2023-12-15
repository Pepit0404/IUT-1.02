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
Lit dans le fichier devis.txt un seul devis
*/
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


Maillon newMaillon(){

}

void afficher1Devis(Devis d)
{
    printf("Entreprise : %s\tAdresse : %s\nCapital : %d\tDuree : %d\tCout : %d\n", d.entreprise, d.adresse, d.capital, d.duree, d.cout);
}

void afficherTravaux()


void test(void){
    FILE *flot;
    flot=fopen("devis.txt","r");
    if(flot==NULL)
    {
        printf("Erreur dans l'ouverture de : devis.txt !\n");
        exit(1);
    }
    Offre **tOffre;
    int tMax=5, taille=0;
    char travaux[10];

    tOffre=(Offre **)malloc(5*sizeof(Offre *));
    strcpy(travaux, "Test");
    taille=newOffre(tOffre, taille, &tMax, travaux);
    Devis d;
    d=Lire1Devis(flot);
}



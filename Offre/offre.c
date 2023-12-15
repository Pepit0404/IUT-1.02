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
    Offre **tOffre;
    int tMax=5, size=0;
    char travaux[10];

    tOffre=(Offre **)malloc(5*sizeof(Offre *));
    if (tOffre==NULL){
        printf("Erreur: création tableaux Offre\n");
        exit(1);
    }
    strcpy(travaux, "Test");
    size=newOffre(tOffre, size, &tMax, travaux);
}
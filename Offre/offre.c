#include "offre.h"

/*
###################################################
    Partie File
###################################################
*/

//priver
Liste enliste(Liste l, Devis devis){
    Maillon *new;
    Liste start=l;
    new=(Maillon *)malloc(sizeof(Maillon));
    if (new==NULL){
        printf("Erreur: creation maillon (enliste)\n");
        exit(1);
    }
    new->devis=devis;
    if (l==NULL){
        new->suiv=NULL;
        l=new;
        return l;
    }
    while (strcmp(devis.entreprise, ((l->suiv)->devis.entreprise))>0){
        l=l->suiv;
    }
    new->suiv=l->suiv;
    l->suiv=new;
    return start;
}

/*
Liste delTete(Liste l){
    Maillon *old;
    if (l==NULL){
        printf("Erreur: impossible de delister une liste vide");
        return l;
    }
    old=l;
    l=l->suiv;
    free(old);
    return l;
}

Liste deliste(Liste l, char *entreprise){
    Liste start=l;
    if (l==NULL){
        printf("Erreur: impossible de delister une liste vide\n");
        return l;
    }
    if (strcmp((start->devis).entreprise, entreprise)==0)
        return delTete(l);
    while (strcmp(((l->suiv)->devis).entreprise, entreprise)==0){
        if (l->suiv==NULL){
            printf("Erreur: entreprise non présente dans les donnée\n");
            return start;
        }
        l=l->suiv;
    }
}
*/

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

int  addDevis(Offre *of[], int size, int *max, char *travaux, Devis devis){
    for (int i=0; i<size; i++){
        if (strcmp(of[i]->travaux, travaux)==0){
            of[i]->ldevis=enliste(of[i]->ldevis, devis);
            return size;
        }
    }
    size=newOffre(of, size, max, travaux);
    of[size-1]->ldevis=enliste(of[size-1]->ldevis, devis);
    return size;
}

Devis Lire1Devis(FILE *flot)
{
    Devis d;
    fgets(d.entreprise,31, flot);
    fgets(d.adresse,51, flot);
    fscanf(flot,"%d",&d.capital);
    fscanf(flot,"%d",&d.duree); 
    fscanf(flot,"%d",&d.cout);
    return d;
}

int readOffre(Offre *of[], int size, int *max){
    FILE *file;
    Devis devis;
    char travaux[30];
    file = fopen("devis.txt", "r");
    if (file==NULL){
        printf("Erreur: ouverture de 'devis.txt'\n");
        exit(1);
    }
    fscanf(file, "%s", travaux);
    while (feof(file)==0){
        devis=Lire1Devis(file);
        size=addDevis(of, size, max, travaux, devis);
        fscanf(file, "%s", travaux);
    }
    fclose(file);
    return size;
}
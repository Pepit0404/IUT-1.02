#include "offre.h"

/*
###################################################
    Partie File
###################################################
*/

Liste enfile(Liste l, Devis devis){
    Maillon *new;
    Liste start=l;
    new=(Maillon *)malloc(sizeof(Maillon));
    if (new==NULL){
        printf("Erreur: creation maillon (enfile)\n");
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
Devis Lire1Devis(FILE *flot)
{
    Devis d;
    fgets(d.entreprise,31, flot);
    d.entreprise[strlen(d.entreprise)-1]='\0';
    fgets(d.adresse,51, flot);
    d.adresse[strlen(d.adresse)-1]='\0';
    fscanf(flot,"%d",&d.capital);
    fscanf(flot,"%d",&d.duree); 
    fscanf(flot,"%d",&d.cout);
    return d;
}

/*
Maillon newMaillon(){

}
*/
void afficher1Devis(Devis d)
{
    printf("Entreprise : %s\tAdresse : %s\nCapital : %d\tDuree : %d\tCout : %d\n", d.entreprise, d.adresse, d.capital, d.duree, d.cout);
}

void afficherTravaux()
{

}




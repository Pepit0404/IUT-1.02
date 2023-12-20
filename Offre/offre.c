#include "offre.h"

/*
###################################################
    Partie File
###################################################
*/
int longListe(Liste l)
{
    printf("\n1\n");
    if(l==NULL)
        return 0;
    return longListe(l->suiv)+1;
}

Liste enliste(Liste l, Devis devis)
{
    Maillon *new;
    new=(Maillon *)malloc(sizeof(Maillon));
    if (new==NULL){
        printf("Erreur: creation maillon (enliste)\n");
        exit(1);
    }
    new->devis=devis;
    if(l==NULL)
    {
        new->suiv=NULL;
        l=new;
        return l;
    }
    if(strcmp(devis.entreprise , ((l->devis).entreprise))<0)
    {
        new->suiv=l;
        l=new;
        return l;
    }
    l->suiv=enliste(l->suiv, devis);
    return l;
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

// UTILISER LA FONCTION RECHERCHE TRAVAUX 
int addDevis(Offre *of[], int size, int *max, char *travaux, Devis devis){
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
    d.entreprise[strlen(d.entreprise)-1]='\0';
    fgets(d.adresse,51, flot);
    d.adresse[strlen(d.adresse)-1]='\0';
    fscanf(flot,"%d",&d.capital);
    fscanf(flot,"%d",&d.duree); 
    fscanf(flot,"%d%*c",&d.cout);
    return d;
}

void afficher1Devis(Devis d)
{
    printf("Entreprise : %s\tAdresse : %s\nCapital : %d\tDuree : %d\tCout : %d\n", d.entreprise, d.adresse, d.capital, d.duree, d.cout);
}

void afficher1Travaux(Offre **o, char travaux[], int nb)
{
    int pos, trouve, longueur;
    pos=rechercheTravaux(o, travaux, nb, &trouve);
    if(trouve==0)
    {
        printf("Ce type de travail n'existe pas !\n");
        return;
    }
    longueur=longListe((o[pos]->ldevis));
    printf("\n%s :\n", travaux);
    for(int a=0; a<longueur; a++)
        afficher1Devis((o[pos]->ldevis)->devis);
}

void afficherTout(Offre **o, int nb)
{
    int i;
    for(i=0; i<=nb-1; i++)
        afficher1Travaux(o, o[i]->travaux, nb);
}



int rechercheTravaux(Offre **o, char travaux[], int nb, int *trouve)
{
    int i;
    for(i=0; i<nb; i++)
    {
        if(strcmp(travaux, o[i]->travaux)==0)
        {
            *trouve=1;
            return i;
        }
    }
    *trouve=0;
    return i;
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
    fscanf(file, "%s%*c", travaux);
    while (feof(file)==0){
        devis=Lire1Devis(file);
        size=addDevis(of, size, max, travaux, devis);
        fscanf(file, "%s%*c", travaux);
        afficher1Travaux(of, "Plomberie", size);
    }
    fclose(file);
    return size;
}

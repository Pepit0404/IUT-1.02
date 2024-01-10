#include "offre.h"

/*
###################################################
    Partie File
###################################################
*/
int longListe(ListeDevis l)
{
    if(l==NULL)
        return 0;
    return longListe(l->suiv)+1;
}

//priver
ListeDevis insererEnTete(ListeDevis l, Devis devis){
    Maillon *new;
    new=(Maillon *)malloc(sizeof(Maillon));
    if (new==NULL){
        printf("Erreur: creation maillon (enliste)\n");
        exit(1);
    }
    new->devis=devis;
    new->suiv=l;
    l=new;
    return l;
}

ListeDevis enliste(ListeDevis l, Devis devis)
{
    if(l==NULL)
        return insererEnTete(l, devis);
    if(strcmp(devis.entreprise , ((l->devis).entreprise))<0)
        return insererEnTete(l, devis);
    l->suiv=enliste(l->suiv, devis);
    return l;
}

//vrai si 0 sinon 1
int estVide(ListeDevis l){
    if (l==NULL) return 0;
    return 1;
}

ListeDevis delTete(ListeDevis l){
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
/*
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
    fscanf(flot,"%f%*c",&d.cout);
    return d;
}

void afficher1Devis(Devis d)
{
    printf("Entreprise : %s\tAdresse : %s\nCapital : %d\tDuree : %d\tCout : %.2f\n", d.entreprise, d.adresse, d.capital, d.duree, d.cout);
}

void afficherDevisEntreprise(ListeDevis l, char entreprise[])
{
    int longueur;
    longueur=longListe(l);
    for(int a=0; a<longueur; a++)
    {
        if(strcmp(entreprise, (l->devis).entreprise)==0)
        {
            afficher1Devis(l->devis);
            return ; 
        }
    }
    printf("Cette entreprise n'existe pas ! \n");
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

void afficher1Travaux(Offre **o, char travaux[], int nb)
{
    int pos, trouve, longueur;
    ListeDevis l;
    pos=rechercheTravaux(o, travaux, nb, &trouve);
    l=o[pos]->ldevis;
    if(trouve==0)
    {
        printf("Ce type de travail n'existe pas !\n");
        return;
    }
    longueur=longListe(l);
    printf("\n%s :\n", travaux);
    for(int a=0; a<longueur; a++){
        printf("\n");
        afficher1Devis(l->devis);
        l=l->suiv;
    }

}

void afficherTout(Offre **o, int nb)
{
    int i;
    for(i=0; i<=nb-1; i++){
        afficher1Travaux(o, o[i]->travaux, nb);
        printf("\n-------------------------------------------------------------------------------------------------------------\n");
    }
}

int readOffre(Offre *of[], int size, int *max, char *fileName){
    FILE *file;
    Devis devis;
    char travaux[30];
    file = fopen(fileName, "r");
    if (file==NULL){
        printf("Erreur: ouverture de '%s'\n", fileName);
        return -1;
    }
    fscanf(file, "%s%*c", travaux);
    while (feof(file)==0){
        devis=Lire1Devis(file);
        size=addDevis(of, size, max, travaux, devis);
        fscanf(file, "%s%*c", travaux);
    }
    fclose(file);
    return size;
}

/*
       PARTIE 2
*/


//Fonction qui garde les moins chère
void sortByCost(Offre *of[], int size){
    Devis save;
    ListeDevis l;
    for (int i=0; i<size; i++){
        l=of[i]->ldevis;
        save=l->devis;
        l=delTete(l);
        while (estVide(l)!=0){
            if(l->devis.cout < save.cout)
                save = l->devis;
            else if (l->devis.cout == save.cout && l->devis.capital > save.capital)
                save = l->devis;
            l=delTete(l);
        }
        l=enliste(l, save);
        of[i]->ldevis=l;
    }
}

void affiche(void){
    printf("Coucou je suis la\n");
}

/*
*       PARTIE 3
*/

bool ListeVide(Liste l)
{
    if (l==NULL) return 0;
    return 1;
}

void afficherSuccesseur(Liste l)
{
    while(ListeVide(l)==1)
    { 
        printf("%s\t",l->nom);
        l=l->suiv;
    }
}

void afficherTaches(Tache *t[], int size)
{
    int a;
    for(a=0; a<size; a++)
    {
        printf("\n1\n");
        printf("nom : %s      duree : %d      nbPred : %d\n",t[a]->tache, t[a]->duree, t[a]->nbPred);
        printf("Noms des successeur :" afficherSuccesseur(t[a]->succ));
    }
}

int rechercheTache(Tache *t[], int size, char successeur[])
{
    int a;
    for(a=0; a<size; a++)
        if(strcmp(successeur, t[a]->tache)==0)
            return a;
    return -1;
}

Liste EnTeteTache(Liste l, char successeur[])
{
    Maillon2 *new;
    new=(Maillon2 *)malloc(sizeof(Maillon2));
    if (new==NULL){
        printf("Erreur: creation maillon (enliste)\n");
        exit(1);
    }
    strcpy(new->nom,successeur);
    new->suiv=l;
    l=new;
    return l;
}

Liste enlisteTache(Liste l, char successeur[])
{
    if(l==NULL)
        return EnTeteTache(l, successeur);
    if(strcmp(l->nom , successeur)!=0)
        return EnTeteTache(l, successeur);
    l->suiv=enlisteTache(l->suiv, successeur);
    return l;
}

Tache ** chargerTache(Offre *o[], int size)
{
    FILE *flot;
    flot=fopen("précédents.txt","r");
    if(flot==NULL)
    {
        printf("Pb avec l'ouverture de précédent.txt !\n");
        exit(1);
    }
    char predecesseur[20], successeur[20];
    int a, pos;
    Tache **t;
    t=(Tache **)malloc(size*sizeof(Tache *));
    if(t==NULL){printf("PB de malloc pour Tache !\n");exit(1);}
    for(a=0;a<size;a++)
    {
        strcpy(t[a]->tache , o[a]->travaux);
        t[a]->duree=(o[a]->ldevis->devis).duree;
    }
    while(!feof(flot))
    {
        fscanf(flot,"%s",predecesseur);
        fscanf(flot,"%s",successeur);
        pos=rechercheTache(t, size, successeur);
        if(pos!=-1)
            t[pos]->nbPred=t[pos]->nbPred+1;
        enlisteTache(t[pos]->succ, successeur);
    }
    return t;
}

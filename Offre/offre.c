/**
*\file offre.c
*\brief Fichier contenant le code relatif aux Offres
*\author Erwan Mechoud
*\author Samuel pinto
*\author Sacha Vinel
*/


#include "offre.h"

/*
###################################################
    Partie File
###################################################
*/

/**
*\brief calcule la longueur d'une liste de devis
*\param [ in ] l la liste de devis
*\return la longueur dela liste
*/
int longListeD(ListeDevis l)
{
    if(l==NULL)
        return 0;
    return longListeD(l->suiv)+1;
}

/**
*\brief insère un devis au début d'une liste de devis
*\param [ in , out ] l la liste de devis
*\param [ in ] devis le devis à inserer dans la liste
*\param new maillon crée dans lequel on va mette le devis et qu'on va ajouter à la liste
*\return la liste mise à jour avec le nouveau devis au début
*/

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

/**
*\brief permet d'insérer (à l'aide de la fonction : insererEnTete) un devis dans la liste des devis en gardant un ordre alphabétique
*\param [ in , out ] l la liste de devis
*\param [ in ] devis le devis à inserer dans la liste
*\return la liste mise à jour avec le nouveau devis au bon endroit
*/
ListeDevis enliste(ListeDevis l, Devis devis)
{
    if(l==NULL)
        return insererEnTete(l, devis);
    if(strcmp(devis.entreprise , ((l->devis).entreprise))<0)
        return insererEnTete(l, devis);
    l->suiv=enliste(l->suiv, devis);
    return l;
}

/**
*\brief dit si une liste de devis est null ou non
*\param [ in ] l la liste de devis
*\return 0 si la liste est null et 1 dans le cas contraire
*/
//vrai si 0 sinon 1
int estVide(ListeDevis l){
    if (l==NULL) return 0;
    return 1;
}

/**
*\brief permet de supprimer le 1er devis d'une liste
*\param [ in , out ] l la liste de devis
*\param old maillon qui permet de libérer l'espace mémoire
*\return la liste sans son 1er devis
*/
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


/**
*\brief ajoute dans le tableau une tache qui n'y était pas
*\param [ in , out] tab tableau contenant les différentes taches à réaliser
*\param [ in , out ] size taille logique du tableau des taches
*\param [ in , out] tMax taille physique du tableau des taches
*\param [ in , out] travaux nom de la tache que l'on ajoute
*\param new Offre crée pour mettre la nouvelle tache dedans
*\param aux Offre auxiliaire crée pour agrandir la taille physique du tableau
*\return la nouvelle taille logique du tableau
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

/**
*\brief ajoute un devis dans la bonne tache
*\param [ in , out ] of tableau des taches
*\param [ in , out ] size taille logique du tableau des taches
*\param [ in , out] max taille physique du tableau des taches
*\param [ in , out] travaux nom de la tache que l'on ajoute
*\param [ in , out ] devis le devis que l'on souhaite ajouter
*\param i compteur pour faire une recherche de la bonne tache
*\return la nouvelle taille logique du tableau des taches
*/
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

/**
*\brief lit dans un fichier toute les informations d'un devis
*\param [ in ] flot entrée dans laquelle on lit
*\param [ out ] d devis dans lequel on met les informations lu dans le fichier
*\return le devis qui vient de lu
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
    fscanf(flot,"%f%*c",&d.cout);
    return d;
}

/**
*\brief affiche toute les informations d'un seul devis 
*\param [ in ] d le devis qu'on souhaite afficher
*/
void afficher1Devis(Devis d)
{
    printf("Entreprise : %s\tAdresse : %s\nCapital : %d\tDuree : %d\tCout : %.2f\n", d.entreprise, d.adresse, d.capital, d.duree, d.cout);
}

/**
*\brief affiche le devis d'une certaine entreprise
*\param [ in ] l liste de devis
*\param [ in ] entreprise nom de l'entreprise que l'on souhaite afficher
*\param longueur longueur de la liste l
*\param a compteur dans une boucle
*/
void afficherDevisEntreprise(ListeDevis l, char entreprise[])
{
    int longueur;
    longueur=longListeD(l);
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

/**
*\brief cherche dans un tableau une certaine tache
*\param [ in ] o tableau de tache
*\param [ in ] travaux la tache qu'on cherche dans le tableau
*\param [ in ] nb taille logique du tableau o
*\param [in , out ] trouve indicateur égal à 1 si la tache existe et 0 si l'inverse
*\param [ out ] i compteur dans une boucle
*\return la position de la tache dans le tableau si elle existe, sinon renvoie la position ou elle devrait être
*/
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

/**
*\brief affiche tous les devis d'une certaine tache
*\param [ in , out ] o tableau des taches
*\param [ in , out ] travaux tache que l'on souhaite afficher
*\param [ in , out ] nb taille logique du tableau o
*\param pos position dela tache dans le tableau o
*\param  [out] trouve indice pour savoir si la tache existe ou non
*\param longueur taille de la liste des devis de la tache
*\param [ out ] l liste des devis de la tache
*/
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
    longueur=longListeD(l);
    printf("%s :\n", travaux);
    for(int a=0; a<longueur; a++){
        printf("\n");
        afficher1Devis(l->devis);
        l=l->suiv;
    }

}

/**
*\brief afficher tous les devis de toutes les taches
*\param [ in , out ] o tableau des taches
*\param [ in , out ] nb taille du tableau o
*\param i compteur dans une boucle
*/
void afficherTout(Offre **o, int nb)
{
    int i;
    
    for(i=0; i<=nb-1; i++){
        afficher1Travaux(o, o[i]->travaux, nb);
        printf("\n-------------------------------------------------------------------------------------------------------------\n");
    }
}

/**
*\brief lit toutes les informations d'un fichier pour ajoutes les taches dans le tableau et les devis dans leurs listes
*\param [ in , out] of tableau des taches
*\param [ in , out] size taille logique du tableau of
*\param [ in , out] max taille physique du tableau of
*\param [ in ] filename nom du fichier que l'on va lire
*\param [ out ] file entrée vers le fichier
*\param [ out ] devis nouveaux devis qu'on lit avec la fonction Lire1Devis puit qu'on ajoute dans les bonnes listes à l'aide de la fonction addDevis
*\param [ out ] travaux la tache du devis
*\return la nouvelle taille logique du tableau des taches après avoir ajouter tous les devis
*/
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

/**
*\brief garde le meilleur devis, c'est à dire le moins cher et si 2 ont le même prix alors c'est le capital le plus haut qui est gardé
*\param [ in ] of tableau de toutes les taches
*\param [ in ] size taille logique du tableau of
*\param [ in , out ] save devis dans lequel on sauvegarde le meilleur
*\param [ out ] l nouvelle liste de devis dans laquelle on met le meilleur devis
*\param i compteur dans la boucle
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


/*
*       PARTIE 3
*/

/**
*\brief vérifie si une liste est vide ou non
*\param [ in ] l liste qu'on inspecte
*\return 1 si la liste est vide et 0 si elle ne l'est pas.
*/
bool ListeVide(Liste l)
{
    if(l==NULL)
        return True;
    return False;
}
/**
*\brief affiche une liste des noms de tous les successeurs d'une tache
*\param [ in ] l liste des succeseurs
*/
void afficherSuccesseur(Liste l)
{
    if (ListeVide(l)==1) printf("Aucune");
    else while(ListeVide(l)==0)
    {
        printf("%s;\t",l->nom);
        l=l->suiv;
    }
}

/**
*\brief affiche les informations de toutes les taches 
*\param [ in , out ] t tableau de toutes les taches
*\param  [ in ] size taille logique du tableau t
*\param a compteur d'une boucle
*/
void afficherTaches(Tache *t[], int size)
{
    int a;
    for(a=0; a<size; a++)
    {
        printf("\n");
        printf("nom : %s      duree : %d      nbPred : %d\n",t[a]->tache, t[a]->duree, t[a]->nbPred);
        printf("Noms des successeur : " );
        afficherSuccesseur(t[a]->succ);
        printf("\n");
    }
}

void afficherTachesPlus(Tache *t[], int size)
{
    int a;
    for(a=0; a<size; a++)
    {
        printf("\n");
        printf("nom : %s      duree : %d    debut : %d      nbPred : %d\n",t[a]->tache, t[a]->duree, t[a]->dateDebut, t[a]->nbPred);
        printf("Noms des successeur : " );
        afficherSuccesseur(t[a]->succ);
        printf("\n");
    }
}

/**
*\brief recherche une tache dans le tableau
*\param [ in ] t tableau des taches
*\param [ in ] size taille logique du tableau t
*\param [ in ] successeur tache chercher
*\param [ out ] a compteur d'une boucle
*\return la position de la tache ou -1 si elle n'existe pas
*/

//-1 si pas trouvé
int rechercheTache(Tache *t[], int size, char successeur[])
{
    int a;
    for(a=0; a<size; a++)
        if(strcmp(successeur, t[a]->tache)==0)
            return a;
    return -1;
}

/**
*\brief ajoute un nouveau successeur au début de la liste des successeurs
*\param [ in , out ] l liste des successeurs
*\param [ in ] successeur tache que l'on veut ajouter au début de la liste
*\param new maillon dans lequel on met le nouveau successeur
*\return la liste des successeur mis à jour
*/
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

/**
*\brief place dans la liste des successeur une nouvelle tache
*\param [ in , out] l liste des successeur
*\param [ in , out] successeur la tache que l'on souhaite ajouter à la liste
*\return la liste mis à jour
*/
Liste enlisteTache(Liste l, char successeur[])
{
    if(l==NULL)
        return EnTeteTache(l, successeur);
    if(strcmp(l->nom , successeur)!=0)
         return EnTeteTache(l, successeur);
    return l->suiv=enlisteTache(l->suiv, successeur); 
}

/**
*\brief charge dans le tableau tabTache depuis le tableau des offres, toutes les meilleurs offres
*\param [ in , out ] tabTache tableau des taches à faire
*\param [ in ] o tableau de toutes les offres
*\param [ in , out ] size taille logique du tableau tabTache
*\param flot entrée vers le fichier des prédecesseurs et successeurs
*\param pos indice de position de tache 1 puis de tache 2
*\param [ out ] tache1 prédécesseur de la tache 2
*\param [ out ] tache2 successeur de la tache1
*\param i comteur pour une boucle
*\return
*/
int ChargementTache(Tache *tabTache[], Offre **o, int size){
    FILE *flot;
    int pos=0;
    char tache1[20], tache2[20];
    flot = fopen("precedents.txt", "r");
    if (flot == NULL){
        printf("Erreur\tImpossible d'ouvir 'precedents.txt'\n");
        return -1;
    }
    for (int i=0;i<size;i++){
        tabTache[i]=(Tache *)malloc(sizeof(Tache));
        if (tabTache[i] == NULL) {
                printf("Erreur : allocation mémoire pour tabTache[%d]\n", size);
                return -1;
        }
        strcpy(tabTache[i]->tache,o[i]->travaux);
        tabTache[i]->duree=o[i]->ldevis->devis.duree;
        tabTache[i]->nbPred = 0;
        tabTache[i]->succ=NULL;
        tabTache[i]->dateDebut=0;
        tabTache[i]->traite=False;
    }
    while (!feof(flot)){
        fscanf(flot, "%s %s", tache1,tache2);
        pos=rechercheTache(tabTache,size,tache1);
        if(pos==-1){
            printf ("Erreur: '%s' non existante\n", tache2);
            exit(1);
        }
        tabTache[pos]->succ=enlisteTache(tabTache[pos]->succ,tache2);
        pos=rechercheTache(tabTache,size,tache2);
        if(pos==-1){
            printf ("Erreur: '%s' non existante\n", tache2);
            exit(1);
        }
        tabTache[pos]->nbPred++;
    }
    return size;
}


/*
        Partie 4
*/

/**
*\brief donne la longueur d'une liste
*\param [ in ] l la liste
*\return la longueur de la liste
*/
int longListeL(Liste l)
{
    if(l==NULL)
        return 0;
    return longListeL(l->suiv)+1;
}

/**
*\brief crée une nouvelle file vide
*\param [ in , out ] f file crée
*\return la nouvelle file
*/
File FileNouv(File f)
{   
    f.t=NULL;
    f.q=NULL;
    return f;
}

/**
*\brief ajoute une tache a la queue d'une file
*\param [ in , out ] f la file
*\param [ in ] t la tache ajouter
*\param m maillon dans lequel on met la tache
*\return la file mis à joue
*/
File ajouterQueue(File f, Tache *t)
{
    Maillon3 *m;
    m=(Maillon3 *)malloc(sizeof(Maillon3));
    if(m==NULL)
    {
        printf("Erreur de malloc du maillon3 m !\n");
        exit(1);
    }
    
    m->tache=*t;
    m->suiv=NULL;
    if(f.t==NULL)
    {
        f.t=m;
        f.q=m;
        return f;
    }
    f.q->suiv=m;
    f.q=m;
    return f;
}

/**
*\brief dit si une file est vide
*\param [ in ] f la file
*\return 1 si elle est vide 0 si elle ne l'est pas
*/
bool FileVide(File f)
{
    if(f.t==NULL)
        return True;
    return False;
}


/**
*\brief renvoie le nom de la tache au début de la liste
*\param [ in ] l la liste
*\return le nom de la tache du début da la liste
*/
char * teteListe(Liste l)
{
    if(ListeVide(l))
    {
        printf("La liste est vide\n");
        exit(1);
    }
    return l->nom;
}

/**
*\brief renvoie le nom de la tache au début de la file
*\param [ in ] f la file
*\return le nom de la tache au début de la file
*/
char * teteFile(File f)
{
    if(FileVide(f))
    {
        printf("La file est vide\n");
        exit(1);
    }
    return (f.t->tache).tache;
}


/**
*\brief supprime la tete d'une file
*\param [ in , out ] f la file
*\param m maillon auxiliaire pour supprimer et pouvoir libérer l'espace mémoire
*\return la file mis à jour
*/
File supprimerTete(File f)
{
    Maillon3 *m;
    m=(Maillon3 *)malloc(sizeof(Maillon3));
    if(m==NULL)
    {
        printf("Erreur de malloc du maillon3 m !\n");
        exit(1);
    }
    if(f.t==NULL)
    {
        printf("Liste vide !\n");
        exit(1);
    }
    m=f.t;
    f.t=f.t->suiv;
    free(m);
    return f;
}


void fusion(Tache *P[], int p, Tache *D[], int d, Tache *F[]){
    int i=0, j=0;
    while (p>i && d>j){
        if (P[i]->dateDebut == D[j]->dateDebut){
            if (P[i]->duree < D[i]->duree){
                F[i+j]=P[i];
                i++;
            }
            else {
                F[i+j]=D[j];
                j++;
            }
        }
        
        else if(P[i]->dateDebut < D[j]->dateDebut){
            F[i+j]=P[i];
            i++;
        }
        else {
            F[i+j]=D[j];
            j++;
        }
    }
    while (i<p){
        F[i+j]=P[i];
        i++;
    }
    while (j<d){
        F[i+j]=D[j];
        j++;
    }
}


void cut(Tache *P[], int i, int j, Tache *D[]){
    int a=0;
    while (i<j){
        D[a]=P[i];
        i++;
        a++;
    }
}


void sortByDate(Tache *t[], int size){
    if (size==1) return;
    Tache **D, **F;
    D=(Tache **)malloc((size/2)*sizeof(Tache *));
    F=(Tache **)malloc((size/2)*sizeof(Tache *));
    if (D==NULL || F==NULL) {
        printf("Erreur: problème malloc 'sortByDate'\n");
        exit(1);
    }
    cut(t, 0, size/2, D);
    cut(t, size/2, size, F);
    sortByDate(D, size/2);
    sortByDate(F, size-size/2);
    fusion(D, size/2, F, size-size/2, t);
    free(D);
    free(F);
}

/**
*\brief permet d'ajouter les taches dans l'autre dans la liste d'attente et de les réaliser pour passer à la suivante
*\param [ in , out ] t tableau des taches
*\param [ in , out ] size taille logique de t
*\param [ out ] f File d'attente des taches
*\param [ out ] l liste des taches
*\param [ out ] ti tache
*\param pos position dans le tableau des taches
*\param a compteur de boucle
*\param j compteur de boucle
*\param i compteur de boucle
*\param c compteur de boucle
*/
void Realisation(Tache *t[], int size)
{
    File f;
    Liste l;
    char ti[30];
    int pos;
    f=FileNouv(f);
    for(int a=0;a<size;a++)
        if(t[a]->nbPred ==0)
            f=ajouterQueue(f,t[a]);
    while(FileVide(f)==0)
    {
        strcpy(ti,teteFile(f));
        f=supprimerTete(f);
        pos=rechercheTache(t, size, ti);
        if(pos==-1)
        {
            printf("La tache n'existe pas\n");
            exit(1);
        }
        l=t[pos]->succ;
        
        int tour=longListeL(l);
        for(int j=0; j<tour; j++)
        {
            char tete[20];
            strcpy(tete,teteListe(l));
            for(int i=0; i<size; i++)
            {
                if(i!=pos)
                {
                    if(strcmp(tete, t[i]->tache)==0)
                    {
                        t[i]->dateDebut=t[pos]->duree + t[pos]->dateDebut;
                        (t[i]->nbPred)-=1;
                        if(t[i]->nbPred == 0)
                            f=ajouterQueue(f,t[i]);
                    }
                    if(l->suiv!=NULL)
                        l=l->suiv;
                }
            }
        }
        t[pos]->traite=True;
    }
    sortByDate(t, size);
    for(int c=0; c<size; c++)
    {
        printf("Tache : %s      Date début : %d\n",t[c]->tache,t[c]->dateDebut);
        printf("Traité : %d\n",t[c]->traite);
        printf("\n-------------------------------------------------------------------\n");
    }
    
}

/**
*\brief 
*\param t tbleau de tache
*\param size taille logique du tableau
*/
void displayTime(Tache *t[], int size){
    printf("\nLe projet a pour duree: %d jours\n", t[size-1]->dateDebut+t[size-1]->duree);
}

/**
*\brief 
*\param t tableau de tache
*\param size taille logique du tableau
*\param jour jour de référence
*/
void jour(Tache *t[],int size,int jour){
    printf("Il reste : \n");
    for(int i=0; i<size; i++){
        if(jour<t[i]->dateDebut + t[i]->duree){
            printf("\t-%s\n", t[i]->tache);
        }
    }
    printf(" à réaliser au jour %d\n",jour);
}
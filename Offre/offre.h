/**
*\file offre.h
*\brief Contient les différentes structure de offre
*\author Erwan Mechoud
*\author Samuel pinto
*\author Sacha Vinel
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char entreprise[32];
    char adresse[52];
    int capital;
    int duree;
    float cout;
} Devis;

typedef struct maillon {
    Devis devis;
    struct maillon *suiv;
} Maillon, *ListeDevis;

typedef struct {
    char travaux[30];
    Maillon *ldevis;
} Offre;

//  PARTIE 3

typedef enum{False,True}bool;

typedef struct maillon2 {
    char nom[30];
    struct maillon2 *suiv;
}Maillon2, *Liste; 

typedef struct {
    char tache[30] ; // nom de la tâche ex : Plomberie
    int duree ; // durée de la tâche
    int nbPred ; // nombre de prédécesseurs de la tâche
    Liste succ ; // liste des successeurs de la tâche
    int dateDebut ; // date de début au plutôt de la tâche
    bool traite ; // booléen : la tâche est-elle traitée
} Tache;

//  PARTIE 4

typedef struct maillon3{
    Tache tache;
    struct maillon3 *suiv;
} Maillon3;

typedef struct{
    Maillon3 *t;
    Maillon3 *q;
} File;

ListeDevis enliste(ListeDevis l, Devis devis);
int newOffre(Offre *tab[], int size, int *tMax, char *travaux);
Devis Lire1Devis(FILE *flot);
void afficher1Devis(Devis d);
void afficherDevisEntreprise(ListeDevis l, char entreprise[]);
int readOffre(Offre *of[], int size, int *max, char *fileName);
void sortByCost(Offre *of[], int size);
void afficherTout(Offre **o, int nb);

/**
 * Partie 3
*/
Tache ** chargerTache(Offre *o[], int size);
int ChargementTache(Tache *tabTache[], Offre **tabTravaux, int tLogO);
Liste enlisteTache(Liste l, char successeur[]);
Liste EnTeteTache(Liste l, char successeur[]);
int rechercheTache(Tache *t[], int size, char successeur[]);
void afficherTaches(Tache *t[], int size);
void afficherSuccesseur(Liste l);
bool ListeVide(Liste l);

/**
 * Partie 4
*/
File chargementFile(File f, Tache *t[], int size);
File FileNouv(File f);
void afficherFile(File f);

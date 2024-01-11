/**
*\file offre.h
*\brief Contient les différentes structure de offre
*\author Erwan Mechoud
*\author Samuel pinto
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


ListeDevis enfile(ListeDevis l, Devis devis);
int newOffre(Offre *tab[], int size, int *tMax, char *travaux);
Devis Lire1Devis(FILE *flot);
void afficher1Devis(Devis d);
void afficherDevisEntreprise(ListeDevis l, char entreprise[]);
int readOffre(Offre *of[], int size, int *max);
void sortByCost(Offre *of[], int size);
void afficherTout(Offre **o, int nb);
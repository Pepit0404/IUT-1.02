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
} Maillon, *Liste;

typedef struct {
    char travaux[30];
    Maillon *ldevis;
} Offre;

Liste enfile(Liste l, Devis devis);
int newOffre(Offre *tab[], int size, int *tMax, char *travaux);
Devis Lire1Devis(FILE *flot);
void afficher1Devis(Devis d);
void afficherDevisEntreprise(Liste l, char entreprise[]);
int readOffre(Offre *of[], int size, int *max);
void sortByCost(Offre *of[], int size);
void afficherTout(Offre **o, int nb);
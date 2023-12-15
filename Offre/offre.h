#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char entreprise[30];
    char adresse[50];
    int capital;
    int duree;
    int cout;
} Devis;

typedef struct maillon {
    Devis devis;
    struct maillon *suiv;
} Maillon, *Liste;

typedef struct {
    char travaux[30];
    Maillon *ldevis;
} Offre;

int newOffre(Offre *tab[], int size, int *tMax, char *travaux);
int addDevis(Offre *of[], int size, int *max, char *travaux, Devis devis);
Devis Lire1Devis(FILE *flot);
int readOffre(Offre *of[], int size, int *max);
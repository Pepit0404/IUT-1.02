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

Liste enfile(Liste l, Devis devis);
int newOffre(Offre *tab[], int size, int *tMax, char *travaux);
Devis Lire1Devis(FILE *flot);
void afficher1Devis(Devis d);
void affiche(void);
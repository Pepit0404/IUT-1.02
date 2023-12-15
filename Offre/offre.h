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

void test(void);
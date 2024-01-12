/**
*\file test.c
*\brief Permet de tester le code de offre.c
*\author Erwan Mechoud
*\author Samuel pinto
*/

#include "offre.h"

int main(void){
    int size=0, max=5;
    
    Offre **o;
    o=(Offre **)malloc(5*sizeof(Offre *));
    if(o==NULL){printf("PB de malloc pour offre !\n");exit(1);}
    size=readOffre(o, size, &max, "devis.txt");
    /*
    afficherTout(o, size);
    sortByCost(o, size);
    afficherTout(o, size);
    *//*
    Tache **t;
    t=(Tache **)malloc(5*sizeof(Tache *));
    if(t==NULL){printf("PB de malloc pour tache !\n");exit(1);}*/
    Tache *t[100];
    int s;
    s=fChargementTache(t, 100, o, size);
    afficherTaches(t, s);
    printf("\n");
    return 0;
}

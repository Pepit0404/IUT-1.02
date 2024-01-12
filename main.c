/**
*\file main.c
*\brief Code du menu permettant de naviguer entre les fonctions du code.
*\author Erwan Mechoud
*\author Samuel pinto
*/

#include <stdio.h>
#include "Offre/offre.h"

int main(){
    int choix, error, tSize=0, tMax=5;
    bool charger=False, run=True;
    Offre **tOffre;
    tOffre=(Offre **)malloc(5*sizeof(Offre *));
    if(tOffre==NULL){printf("PB de malloc pour offre !\n");exit(1);}

    while (run==True){
        printf("Que voullez-vous faire ?\n");
        printf("\t1. Charger\n");
        if (charger==True){
            printf("\t2. Afficher les devis\n");
            printf("\t3. Choisir les devis\n");
            printf("\t4. fin\n");
        }
        error=scanf("%d%*c", &choix);
        if (error==0){
            printf("Attention réponse non conforme\n");
        }

        if (choix==1){
            char nameF[30];
            printf("Nom du fichier: ");
            scanf("%s%*c", nameF);
            tSize=readOffre(tOffre, tSize, &tMax, nameF);
            printf("\n\n");
            
            if(tSize>0) charger=True;
        }
        else if (charger==True){
            if (choix==2){
                afficherTout(tOffre, tSize);
                printf("\n\n");
            }
            else if (choix==3) {
                sortByCost(tOffre, tSize);
                printf("Devis choisis avec succés\n");
                afficherTout(tOffre, tSize);
            }
            else if (choix==4){
                run=False;
            }
        }
    }
    return 0;
}
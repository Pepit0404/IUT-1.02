/**
*\file main.c
*\brief Code du menu permettant de naviguer entre les fonctions du code.
*\author Erwan Mechoud
*\author Samuel pinto
*\author Sacha Vinel
*/

#include <stdio.h>
#include "Offre/offre.h"

int main(){
    int choix, error, tSize=0, tMax=5;
    int ttSize;
    bool charger=False, mini=False, simu=False, run=True;
    Offre **tOffre;
    Tache **tTache;
    tOffre=(Offre **)malloc(5*sizeof(Offre *));
    if(tOffre==NULL){printf("PB de malloc pour offre !\n");exit(1);}
    while (run==True){
        printf("Que voullez-vous faire ?\n");
        printf("\t1. Charger\n");
        if (charger==True){
            printf("\t2. Afficher les devis\n");
            printf("\t3. Choisir les devis\n");
            printf("\t4. Charger l'ordre\n");
            if (mini==True){
                printf("\t5. Simuler\n");
                if (simu==True){
                    printf("\t6. Afficher le temps de réalisation du projet\n");
                    printf("\t7. Lister les taches restante un jour j\n");
                }
            }
        }
        printf("\t0. fin\n");
        error=scanf("%d%*c", &choix);
        if (error==0){
            printf("Attention réponse non conforme\n");
        }

        if (choix==1){
            char nameF[30];
            printf("Nom du fichier (devis.txt par defaut): ");
            scanf("%s", nameF);
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
                tTache=(Tache **)malloc(tSize*sizeof(Tache *));
                if(tTache==NULL){printf("PB de malloc pour tache !\n");exit(1);}
                ttSize=ChargementTache(tTache, tOffre, tSize);
                printf("\nChargement reussi\n");
                mini=True;
            }
            else if (mini==True){
                if (choix==5){
                    Realisation(tTache, ttSize);
                    simu=True;
                }
                else if (simu==True){
                    if (choix==6){
                        displayTime(tTache, ttSize);
                    }
                    else if (choix==7){
                        int j;
                        printf("Quel jours voulez-vous vérifier?\n");
                        scanf("%d", &j);
                        jour(tTache, ttSize, j);
                    }
                }
            }
            else if (choix==0){
                run=False;
            }
        }
    }
    return 0;
}
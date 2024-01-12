/**
*\file main.c
*\brief Code du menu permettant de naviguer entre les fonctions du code.
*\author Erwan Mechoud
*\author Samuel pinto
*\author Sacha Vinel
*/

#include <stdio.h>
#include "Offre/offre.h"

/**
*\brief Menu permettant de naviguer entre les différentes fonctions du code
*\param choix prend une valeur numérique pour choisir l'option souhaité
*\param error code d'erreur du scanf pour vérifié la conformité du choix
*\param tSize taille logique du tableau des offres 
*\param tMax taille physique du tableau
*\param charger permet de cacher puis d'activer certaine option
*\param option permet de cacher puis d'activer certaine option
*\param dernier permet de cacher puis d'activer certaine option
*\param run condition de la boucle
*\param tOffre tableau des offres
*\param tTache tableau des Taches
*/
int main(){
    int choix, error, tSize=0, tMax=5;
    bool charger=False, run=True, option=False, dernier=False;
    Offre **tOffre;
    tOffre=(Offre **)malloc(5*sizeof(Offre *));
    if(tOffre==NULL){printf("PB de malloc pour offre !\n");exit(1);}
    Tache **tTache;
    tTache=(Tache **)malloc(5*sizeof(Tache *));
    if(tTache==NULL){printf("PB de malloc pour tache !\n");exit(1);}
    while (run==True){
        printf("\nQue voullez-vous faire ?\n");
        printf("\t1. Charger\n");
        if (charger==True){
            printf("\t2. Afficher les devis\n");
            printf("\t3. Choisir les devis\n");
            if(option==True)
            { 
                printf("\t4. Charger les taches\n");
                printf("\t5. Afficher les taches\n");
                if(dernier==True)
                {
                    printf("\t6. Lancer le projet\n");
                    printf("\t7. fin\n\n");
                }
            }
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
                option=True;
            }
            else if(option==True)
            {
                if(choix==4)
                {
                    tSize=ChargementTache(tTache, tOffre, tSize);
                    dernier=True;
                }
                if(choix==5)
                {
                    afficherTaches(tTache, tSize);
                }
                else if(dernier==True)
                {
                    if(choix==6)
                    {
                        Realisation(tTache, tSize);
                    }
                    else if (choix==7)
                    {
                        run=False;
                    }
                }
                
            }
        }
    }
    return 0;
}
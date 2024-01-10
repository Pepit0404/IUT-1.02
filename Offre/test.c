#include "offre.h"

int main(void){
    FILE *flot;
    flot=fopen("devis.txt","r");
    if(flot==NULL)
    {
        printf("Erreur dans l'ouverture de : devis.txt !\n");
        exit(1);
    }
    int size=0, max=5;
    Offre **o;
    o=(Offre **)malloc(5*sizeof(Offre *));
    if(o==NULL){printf("PB de malloc pour offre !\n");exit(1);}
    size=readOffre(o, size, &max);
    //afficherTout(o, size);
    printf("\n\n");
    sortByCost(o, size);
    //afficherTout(o, size);
    return 0;
}

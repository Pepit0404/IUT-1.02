#include "offre.h"

int main(void){
    int size=0, max=5;
    Offre **o;
    o=(Offre **)malloc(5*sizeof(Offre *));
    if(o==NULL){printf("PB de malloc pour offre !\n");exit(1);}
    size=readOffre(o, size, &max, "devis.txt");
    //afficherTout(o, size);
    printf("\n\n");
    sortByCost(o, size);
    afficherTout(o, size);
    t=chargerTache(o, size);
    afficherTaches(t, size);
    return 0;
}

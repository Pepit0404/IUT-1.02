#include "offre.h"

int main(void){
    FILE *flot;
    flot=fopen("devis.txt","r");
    if(flot==NULL)
    {
        printf("Erreur dans l'ouverture de : devis.txt !\n");
        exit(1);
    }
    Devis d;
    d=Lire1Devis(flot);
    afficher1Devis(d);
    return 0;
}

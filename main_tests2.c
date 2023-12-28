#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ecosys.h"

int main(void) {
    srand(time(NULL));

    Animal* liste_proie = NULL; 
    Animal* liste_predateur = NULL; 

    // Création des animaux
    for (int i = 0; i < 20; i++) {
        ajouter_animal((rand() % 19)+1, (rand() % 49)+1, 0.0, &liste_proie); 
        ajouter_animal((rand() % 19)+1, (rand() % 49)+1, 0.0, &liste_predateur); 
    }

    // On enleve 5 prédateurs    
    for(int i=0; i<5; i++){
        Animal* tmp = liste_predateur->suivant;
        enlever_animal(&liste_predateur,liste_predateur);
        liste_predateur = tmp;
    }

    // Ecriture dans fich.txt
    ecrire_ecosys("fich.txt",liste_predateur,liste_proie);
    afficher_ecosys(liste_proie, liste_predateur); 

    // Lecture depuis fich.txt
    Animal* liste_proie2 = NULL;
    Animal* liste_predateur2 = NULL;
    lire_ecosys("fich.txt",&liste_proie2,&liste_predateur2);
    afficher_ecosys(liste_proie2,liste_predateur2);
    
    // Libération de la mémoire
    liberer_liste_animaux(liste_predateur);
	liberer_liste_animaux(liste_proie);
    liberer_liste_animaux(liste_predateur2);
	liberer_liste_animaux(liste_proie2);
    

    return 0;
}

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"

#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 100000
#define IT_MAX 100



int main(void)
{
	srand(time(NULL));

    // Création des animaux
	Animal* liste_proie = NULL;
	Animal* liste_predateur = NULL;

	//PROIES
    for (int i = 0; i < NB_PROIES; i++) {
        ajouter_animal(rand()%SIZE_X, rand()%SIZE_Y, 100.0, &liste_proie); 
    }
	//PREDATEURS
	for (int i = 0; i < NB_PREDATEURS; i++) {
        ajouter_animal(rand()%SIZE_X, rand()%SIZE_Y, 100.0, &liste_predateur); 
    }
	//HERBE
	int monde[SIZE_X][SIZE_Y];
	for(int i=0; i<SIZE_X; i++){
		for(int j=0; j<SIZE_Y; j++){
			monde[i][j] = 0;
		}
	}

	// On ouvre le fichier pour le graph
	FILE* graph = fopen("Evol_pop.txt","w");

	// EV0LUTI0N DE L'ECOSYSTEME
	int i = 0;
	while((compte_animal_rec(liste_proie)>0 || compte_animal_rec(liste_predateur) >0) && i<IT_MAX ){
		afficher_ecosys(liste_proie,liste_predateur);
		rafraichir_proies(&liste_proie,monde);
		rafraichir_predateurs(&liste_predateur,&liste_proie);
		rafraichir_monde(monde);
		i++;
		printf("%d\n",i);       // Pour afficher l'iteration actuelle
		srand(time(NULL));		// Pour avoir des résutats different lors des évaluation des probabilités (pas sûr)
		fprintf(graph,"%d %d %d\n",i,compte_animal_rec(liste_proie),compte_animal_rec(liste_predateur)); // On ecrit dans le fichier pour le graph
		usleep(T_WAIT);
	}
	afficher_ecosys(liste_proie,liste_predateur);
	


	//Libération de la mémoire
	liberer_liste_animaux(liste_proie);
	liberer_liste_animaux(liste_predateur);
	fclose(graph);
	return 0;
}

/*

Pour avoir des résultats différents de l'évolution de l'écosysteme, on peut jouer sur plusieur variables:
_Le taux de reproduction des animaux
_le temps de repousse de l'herbe
_l'energie des animaux
_le nombre de proie ou prédateurs

L'energie a un plus grand impact lors d'un changement des variables
Les predateurs sont dépendant des proies, si il n'y a plus de proies les prédateurs ne tiennent pas longtemps, contrairement aux proies qui peuvent vivre indépendamment des prédateur grace à l'herbe qui repousse chaque 15 iterations
Plus les animaux se reproduisent moins ils vivent longtemps, car etant donné que l'energie est le facteur le plus détérminant de la durée de vie des animaux, se reproduire divise l'energie en deux. Paradoxalement mais aussi logiquement, les animaux qui se reproduisent moins vivent le plus.
*/

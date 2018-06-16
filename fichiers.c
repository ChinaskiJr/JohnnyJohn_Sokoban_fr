/* fichiers.c
   ----------

   ChinaskiJr pour lui-même 	February 2018

   Rôle : Gère les fichiers .lvl (charge et sauvegarde)

   */
 
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>

#include "constantes.h"
#include "fichiers.h"

int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR], int niveauActuel) {
	char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = {0};
	int i = 0, j = 0;
	FILE* fichier = NULL;

	fichier = fopen("niveaux.lvl", "r");
	if (fichier == NULL)
		return 0;

    //Place le curseur au début de la ligne indiquée par niveauActuel
	if (niveauActuel > 0)
        fseek(fichier, (NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1) * niveauActuel, SEEK_CUR);

    while (fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier) != NULL) {
        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++) {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++) {
                switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j]) {
                    case '0':
                        niveau[j][i] = 0;
                        break;
                    case '1':
                        niveau[j][i] = 1;
                        break;
                    case '2':
                        niveau[j][i] = 2;
                        break;
                    case '3':
                        niveau[j][i] = 3;
                        break;
                    case '4':
                        niveau[j][i] = 4;
                        break;
                }
            }
		}
        fclose(fichier);
        return 1;
    }
    fclose(fichier);
	return 2;
}

int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR]) {
	int i = 0, j = 0;
	FILE* fichier = NULL;

	fichier = fopen("niveauEdition.lvl", "w");
	if (fichier == NULL)
		return 0;

	for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++) {
		for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++) {
			fprintf(fichier, "%d", niveau[j][i]);
		}
	}

	fclose(fichier);
	return 1;
}

int chargerNiveauEditeur(int niveau[][NB_BLOCS_HAUTEUR]) {
	char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = {0};
	int i = 0, j = 0;
	FILE* fichier = NULL;

	fichier = fopen("niveauEdition.lvl", "r");
	if (fichier == NULL)
		return 0;

    fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);

	for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++) {
		for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++) {
			switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j]) {
				case '0':
					niveau[j][i] = 0;
					break;
				case '1':
					niveau[j][i] = 1;
					break;
				case '2':
					niveau[j][i] = 2;
					break;
				case '3':
					niveau[j][i] = 3;
					break;
				case '4':
					niveau[j][i] = 4;
					break;
			}
		}
	}
	fclose(fichier);
	return 1;
}



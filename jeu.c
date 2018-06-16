/* jeu.c
----------

	ChinaskiJr pour lui-même 	February 2018

	Rôle : Contient les fonctions propres au fonctionnement du jeu
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "fichiers.h"
#include "jeu.h"
#include "cinematique.h"

// Permet au joueur de déplacer les caisses
void deplacerCaisse(int *premiereCase, int *secondeCase) {
	if (*premiereCase == CAISSE || *premiereCase == CAISSE_OK) {
		if (*secondeCase == OBJECTIF)
			*secondeCase = CAISSE_OK;
		else
			*secondeCase = CAISSE;
		if (*premiereCase == CAISSE_OK)
			*premiereCase = OBJECTIF;
		else
			*premiereCase = VIDE;
	}
}
// Gestion des collisions. 
void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction) {
	switch (direction) {
		case HAUT:
			if (pos->y - 2 < 0)
				break;
			if (carte[pos->x][pos->y - 1] == MUR)
				break;
			if ((carte[pos->x][pos-> y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) && (pos->y - 3 < 0 || carte[pos->x][pos-> y - 2] == MUR || carte[pos->x][pos-> y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))
				break;
			deplacerCaisse(&carte[pos->x][pos->y -1], &carte[pos->x][pos->y - 2]);
			pos->y--;
			break;
		case BAS:
			if (pos->y + 2 >= NB_BLOCS_HAUTEUR)
				break;
			if (carte[pos->x][pos->y + 1] == MUR)
				break;
			if ((carte[pos->x][pos-> y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK) && (pos->y + 3 >= NB_BLOCS_HAUTEUR || carte[pos->x][pos-> y + 2] == MUR || carte[pos->x][pos-> y + 2] == CAISSE || carte[pos->x][pos-> y + 2] == CAISSE_OK))
				break;
			deplacerCaisse(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);
			pos->y++;
			break;

		case GAUCHE:
			if (pos->x - 2 < 0)
				break;
			if (carte[pos->x - 1][pos->y] == MUR)
				break;
			if ((carte[pos->x - 1][pos-> y] == CAISSE || carte[pos->x - 1][pos->y] == CAISSE_OK) && (pos->x - 3 < 0 || carte[pos->x - 2][pos-> y] == MUR || carte[pos->x - 2][pos-> y] == CAISSE || carte[pos->x - 2][pos-> y] == CAISSE_OK))
				break;
			deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);
			pos->x--;
			break;

		case DROITE:
			if (pos->x + 2 >= NB_BLOCS_LARGEUR)
				break;
			if (carte[pos->x + 1][pos->y] == MUR)
				break;
			if ((carte[pos->x + 1][pos-> y] == CAISSE || carte[pos->x + 1][pos->y] == CAISSE_OK) && (pos->x + 3 >= NB_BLOCS_LARGEUR || carte[pos->x + 2][pos-> y] == MUR || carte[pos->x + 2][pos-> y] == CAISSE || carte[pos->x + 2][pos-> y] == CAISSE_OK))
				break;
			deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);
			pos->x++;
			break;

	}
}

void jouer(SDL_Surface* ecran) {
	SDL_Surface *mario[4] = {NULL};
	SDL_Surface *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL, *imageDeFond = NULL, *escalier = NULL;
	SDL_Rect position, positionJoueur, positionFond, positionEscalier;
	SDL_Event event;
    TTF_Font *police = NULL;

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
    int niveauActuel = 0;
    unsigned long tempsRestant = 601000 + SDL_GetTicks();
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
    int emplacementEscalier = 0;

    positionEscalier.x = 0;
    positionEscalier.y = 0;


	imageDeFond = IMG_Load("sprites/fond.png");
	mur = IMG_Load("sprites/mur.jpg");
	caisse = IMG_Load("sprites/caisse.jpg");
	caisseOK = IMG_Load("sprites/caisse_ok.jpg");
	objectif = IMG_Load("sprites/objectif.png");
    escalier = IMG_Load("sprites/stairs.gif");
	mario[BAS] = IMG_Load("sprites/mario_bas.gif");
	mario[HAUT] = IMG_Load("sprites/mario_haut.gif");
	mario[GAUCHE] = IMG_Load("sprites/mario_gauche.gif");
	mario[DROITE] = IMG_Load("sprites/mario_droite.gif");
	SDL_SetColorKey(mario[BAS], SDL_SRCCOLORKEY, SDL_MapRGB(mario[BAS]->format, 255, 255, 255));
	SDL_SetColorKey(mario[HAUT], SDL_SRCCOLORKEY, SDL_MapRGB(mario[HAUT]->format, 255, 255, 255));
	SDL_SetColorKey(mario[GAUCHE], SDL_SRCCOLORKEY, SDL_MapRGB(mario[GAUCHE]->format, 255, 255, 255));
	SDL_SetColorKey(mario[DROITE], SDL_SRCCOLORKEY, SDL_MapRGB(mario[DROITE]->format, 255, 255, 255));
    SDL_SetColorKey(escalier, SDL_SRCCOLORKEY, SDL_MapRGB(escalier->format, 255, 255 , 255));
	marioActuel = mario[BAS];
	
	positionFond.x = 0;
	positionFond.y = 0;


    /* Chargement de la police de la fonction decompteTemps 
       ici pour éviter d'ouvrir/fermer la police 
       trop régulièrement. Provoquant une erreur de segmentation. */
    TTF_Init();
    if(TTF_Init() == -1) {
        exit(EXIT_FAILURE);
    }

    police = TTF_OpenFont("fonts/broken15.ttf", 25);
    if(!police) {
        printf("TTF_OpenFont : %s\n", TTF_GetError());
    }


	SDL_EnableKeyRepeat(100, 100);
    // Chargement du premier niveau
	if (!chargerNiveau(carte, niveauActuel))
		exit(EXIT_FAILURE);
	// Détection de l'emplacement de départ du joueur
	for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++) {
		for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++) {
			if (carte[i][j] == MARIO) {
				positionJoueur.x = i;
				positionJoueur.y = j;
				carte[i][j] = VIDE;
			}
		}
	}

	while (continuer) {
        // Déplacement du joueur
		while(SDL_PollEvent(&event))
            switch(event.type) {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            continuer = 0;
                            break;
                        case SDLK_UP:
                            marioActuel = mario[HAUT];
                            deplacerJoueur(carte, &positionJoueur, HAUT);
                            break;
                        case SDLK_DOWN:
                            marioActuel = mario[BAS];
                            deplacerJoueur(carte, &positionJoueur, BAS);
                            break;
                        case SDLK_RIGHT:
                            marioActuel = mario[DROITE];
                            deplacerJoueur(carte, &positionJoueur, DROITE);
                            break;
                        case SDLK_LEFT:
                            marioActuel = mario[GAUCHE];
                            deplacerJoueur(carte, &positionJoueur, GAUCHE);
                            break;

                    }
                    break;
            }


        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

        compteurTemps(tempsRestant, &continuer, ecran, police);    

        objectifsRestants = 0;

        // Rafraichissement de la carte
        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++) {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++) {

                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j]) {
                    case MUR:
                        SDL_BlitSurface(mur, NULL, ecran, &position);
                        break;
                    case CAISSE:
                        SDL_BlitSurface(caisse, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        objectifsRestants = 1;
                        break;
                    case CAISSE_OK:
                        SDL_BlitSurface(caisseOK, NULL, ecran, &position);
                        break;
                }
			}
		}


        // Détection de l'emplacement de l'escalier
		if(!objectifsRestants && positionEscalier.x == 0 && positionEscalier.y == 0) {
            // Départ des for à 1 et fin à -2 pour ne pas placer l'escalier sur les bords
            for (i = 1 ; i < NB_BLOCS_LARGEUR - 2 ; i++) {
                for (j = 1 ; j < NB_BLOCS_HAUTEUR - 2 ; j++) {
                    // Vérification que la case soit vide
                    if (carte[i][j] == VIDE && positionJoueur.x != i && positionJoueur.y != j) {
                        positionEscalier.x = i * TAILLE_BLOC;
                        positionEscalier.y = j * TAILLE_BLOC;
                        SDL_BlitSurface(escalier, NULL, ecran, &positionEscalier);
                        break;
                        break;
                    } 
                }
                if (carte[i][j] == VIDE && positionJoueur.x != i && positionJoueur.y != j) {
                    positionEscalier.x = i * TAILLE_BLOC;
                    positionEscalier.y = j * TAILLE_BLOC;
                    break;
                    break;
                }
            }
        }
        // Création de l'escalier 
        if(positionEscalier.x != 0 && positionEscalier.y != 0)
            SDL_BlitSurface(escalier, NULL, ecran, &positionEscalier);

		position.x = positionJoueur.x * TAILLE_BLOC;
		position.y = positionJoueur.y * TAILLE_BLOC;
		SDL_BlitSurface(marioActuel, NULL, ecran, &position);

		SDL_Flip(ecran);

        // Chargement du niveau suivant
        if ((positionJoueur.x * TAILLE_BLOC) == positionEscalier.x && (positionJoueur.y * TAILLE_BLOC) == positionEscalier.y) {
            niveauActuel ++;

            positionEscalier.x = 0;
            positionEscalier.y = 0;

            if (!chargerNiveau(carte, niveauActuel))
                exit(EXIT_FAILURE);
            // Une fois le dernier niveau atteint, on arrête
            else if (chargerNiveau(carte, niveauActuel) == 2) { 
                cinematique(ecran);
                // Et on repart... (sacré JohnnyJohn)
                niveauActuel = 0;
                tempsRestant = 601000 + SDL_GetTicks();
                chargerNiveau(carte, niveauActuel);
            }
            // Détection de l'emplacement de départ du joueur
            for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++) {
                for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++) {
                    if (carte[i][j] == MARIO) {
                        positionJoueur.x = i;
                        positionJoueur.y = j;
                        carte[i][j] = VIDE;
                    }
                }
            }
        }

        SDL_Delay(50);
	}

    SDL_EnableKeyRepeat(0, 0);

    TTF_CloseFont(police);
    TTF_Quit;

    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(caisseOK);
    SDL_FreeSurface(escalier);
    for (i = 0 ; i < 4 ; i++) 
        SDL_FreeSurface(mario[i]);
    SDL_FreeSurface(imageDeFond);
}
//Fonction gérant le timer
void compteurTemps(long temps, int *continuer, SDL_Surface *ecran, TTF_Font *police) {
    SDL_Surface *compteurAffichage = NULL;
    SDL_Rect positionCompteur;
    char compteur[1000] = {0};
    long tempsRestant = 0, tempsPasse = 0;

    SDL_Color couleurCompteur = {0, 0, 0};

    positionCompteur.x = 0;
    positionCompteur.y = 0;

    tempsPasse = SDL_GetTicks();
    if (temps - tempsPasse > 0) {
        if (tempsPasse - tempsRestant > 50) {
            tempsRestant = temps - tempsPasse;

            sprintf(compteur, "Temps restant : %ld", tempsRestant / 1000);
            compteurAffichage = TTF_RenderText_Solid(police, compteur, couleurCompteur);
            SDL_BlitSurface(compteurAffichage, NULL, ecran, &positionCompteur);
        }
        else 
            SDL_Delay(50 - (tempsPasse - tempsRestant));
    }
    else {
        *continuer = 0; 
        SDL_FreeSurface(compteurAffichage);
    }
}

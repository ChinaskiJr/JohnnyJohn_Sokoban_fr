/* editeur.c
   ---------

   ChinaskiJr pour lui-même 	February 2018

   Rôle : Editeur de niveau

   */

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "fichiers.h"

void editeur(SDL_Surface* ecran) {
	SDL_Surface *mur = NULL, *caisse = NULL, *objectif = NULL, *mario = NULL, *imageDeFond = NULL;
	SDL_Rect position, positionFond;
	SDL_Event event;

	int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
	int objetActuel = MUR, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    imageDeFond = IMG_Load("sprites/fond.png");
	mur = IMG_Load("sprites/mur.jpg");
	caisse = IMG_Load("sprites/caisse.jpg");
	objectif = IMG_Load("sprites/objectif.png");
	mario = IMG_Load("sprites/mario_bas.gif");
    SDL_SetColorKey(mario, SDL_SRCCOLORKEY, SDL_MapRGB(mario->format, 255, 255, 255));

    positionFond.x = 0;
    positionFond.y = 0;

	if (!chargerNiveauEditeur(carte))
		exit(EXIT_FAILURE);

	while (continuer) {
		SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
					clicGaucheEnCours = 1;
				}
				else if (event.button.button == SDL_BUTTON_RIGHT) {
					carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = VIDE;
					clicDroitEnCours = 1;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
					clicGaucheEnCours = 0;
				else if (event.button.button == SDL_BUTTON_RIGHT)
					clicDroitEnCours = 0;
				break;
			case SDL_MOUSEMOTION:
				if (clicGaucheEnCours) {
					carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
				}
				else if (clicDroitEnCours) {
					carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = VIDE;
				}
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_ESCAPE:
						continuer = 0;
						break;
					case SDLK_s:
						sauvegarderNiveau(carte);
						break;
					case SDLK_c:
						chargerNiveauEditeur(carte);
						break;
					case SDLK_KP1:
						objetActuel = MUR;
						break;
					case SDLK_KP2:
						objetActuel = CAISSE;
						break;
					case SDLK_KP3:
						objetActuel = OBJECTIF;
						break;
					case SDLK_KP4:
						objetActuel = MARIO;
						break;
				}
			break;
		}
		
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

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
						break;
					case MARIO:
						SDL_BlitSurface(mario, NULL, ecran, &position);
						break;
				}
			}
		}

		SDL_Flip(ecran);
	}
	SDL_FreeSurface(mur);
	SDL_FreeSurface(caisse);
	SDL_FreeSurface(objectif);
	SDL_FreeSurface(mario);
}

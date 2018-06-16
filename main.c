/*
 main.c
 -----------------

 ChinaskiJr pour lui-même 	February 2018

 Rôle : Menu de jeu. Permet de choisir entre l'éditeur et le jeu lui-même. 
 */

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "jeu.h"
#include "editeur.h"
#include "fichiers.h"

int main(int argc, char *argv[]) {
	SDL_Surface *ecran = NULL, *menu = NULL;
	SDL_Rect positionMenu;
	SDL_Event event;

	int continuer = 1;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_WM_SetIcon(IMG_Load("sprites/mario_bas.gif"), NULL);

	ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
	SDL_WM_SetCaption("JohnyJohn - La plus grande épave de Rennes", NULL);

	menu = IMG_Load("sprites/menu.jpg");
	positionMenu.x = 0;
	positionMenu.y = 0;

	while (continuer) {
		SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_ESCAPE:
						continuer = 0;
						break;
					case SDLK_KP1:
						jouer(ecran);
						break;
                    case SDLK_SPACE:
                        jouer(ecran);
                        break;
					case SDLK_KP2:
						editeur(ecran);
						break;
                    case SDLK_2:
                        editeur(ecran);
                        break;
				}
				break;
		}

		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
		SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
		SDL_Flip(ecran);
	}


	SDL_FreeSurface(menu);
	SDL_Quit();

	return EXIT_SUCCESS;
}


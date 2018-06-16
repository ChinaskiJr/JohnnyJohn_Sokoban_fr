/* cinematique.c
   -------------

   ChinaskiJr pour lui-même     February 2018

   Rôle : Contient les fonctions gérant la cinématique finale

*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"

void cinematique(SDL_Surface* ecran) {
    SDL_Surface *mario[4] = {NULL};
    SDL_Surface *marioActuel = NULL, *imageDeFond = NULL, *imageDeFin = NULL;
    SDL_Rect positionJoueur, oldPositionJoueur, positionFond;
    SDL_Rect positionFond_c, positionJoueur_c;
    SDL_Rect clipper;
    SDL_Event event;

    int continuer = 1;
    int avanceX = 0, reculeX = 0, avanceY = 0, reculeY = 0;
    int vitesse = 10;
    int etape = 0;
    unsigned long tempsActuel = 0, tempsPrecedent = 0;
    int i = 0;

    imageDeFond = IMG_Load("sprites/SteAnne.png");
    mario[BAS] = IMG_Load("sprites/mario_bas.gif");
    mario[HAUT] = IMG_Load("sprites/mario_haut.gif");
    mario[DROITE] = IMG_Load("sprites/mario_droite.gif");
    mario[GAUCHE] = IMG_Load("sprites/mario_gauche.gif");
    imageDeFin = IMG_Load("sprites/EcranDeFin.png");

    SDL_SetColorKey(mario[BAS], SDL_SRCCOLORKEY, SDL_MapRGB(mario[BAS]->format, 255, 255, 255));
    SDL_SetColorKey(mario[HAUT], SDL_SRCCOLORKEY, SDL_MapRGB(mario[HAUT]->format, 255, 255, 255));
    SDL_SetColorKey(mario[DROITE], SDL_SRCCOLORKEY, SDL_MapRGB(mario[DROITE]->format, 255, 255, 255));
    SDL_SetColorKey(mario[GAUCHE], SDL_SRCCOLORKEY, SDL_MapRGB(mario[GAUCHE]->format, 255, 255, 255));
    marioActuel = mario[DROITE];
    positionFond.x = 0;
    positionFond.y = 0;

    positionJoueur.x = 0;
    positionJoueur.y = 0;

    oldPositionJoueur.x = 0;
    oldPositionJoueur.y = 0;

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

    SDL_Flip(ecran);

    SDL_Delay(2000);

    //Réveil du JohnnyJohn
    positionJoueur.x = 4 * TAILLE_BLOC;
    positionJoueur.y = 9 * TAILLE_BLOC;
    SDL_BlitSurface(marioActuel, NULL, ecran, &positionJoueur);

    SDL_Flip(ecran);

    oldPositionJoueur.x = positionJoueur.x;
    oldPositionJoueur.y = positionJoueur.y;

    while (continuer) {

        tempsActuel = SDL_GetTicks();

        // Options de l'animation
        clipper.x = positionJoueur.x;
        clipper.y = positionJoueur.y;
        clipper.h = marioActuel->h;
        clipper.w = marioActuel->w;

        // Durée de l'animation avant disparion de JohnnyJohn 
        if (etape <= 8) {
            SDL_BlitSurface(imageDeFond, &clipper, ecran, &oldPositionJoueur);
            SDL_BlitSurface(marioActuel, NULL, ecran, &positionJoueur);
        }
        else
            SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

        oldPositionJoueur.x = positionJoueur.x;
        oldPositionJoueur.y = positionJoueur.y;

        if(avanceX) {
            positionJoueur.x++;
            marioActuel = mario[DROITE];
        }
        if(reculeX) {
            positionJoueur.x--;
            marioActuel = mario[GAUCHE];
        }
        if(avanceY) {
            positionJoueur.y++;
            marioActuel = mario[BAS];
        }
        if(reculeY) {
            positionJoueur.y--;
            marioActuel = mario[HAUT];
        }

        // Déplacements du JohnnyJohn

        switch (etape) {
            case 0:
                SDL_Delay(2000);
                marioActuel = mario[BAS];
                etape++;
                tempsPrecedent = tempsActuel;
                break;
            case 1:
                if(tempsActuel - tempsPrecedent > 1000) {
                    marioActuel = mario[HAUT];
                    etape++;
                    tempsPrecedent = tempsActuel;
                }
                break;
            case 2:
                if(tempsActuel - tempsPrecedent > 1000) {
                    marioActuel = mario[BAS];
                    etape++;
                    tempsPrecedent = tempsActuel;
                }
                break;
            case 3:
                if(tempsActuel - tempsPrecedent > 1000) {
                    marioActuel = mario[HAUT];
                    etape++;
                    tempsPrecedent = tempsActuel;
                }
                break;
            case 4:
                if(tempsActuel - tempsPrecedent > 1000) {
                    marioActuel = mario[BAS];
                    etape++;
                    tempsPrecedent = tempsActuel;
                }
                break;
            case 5:
                if(tempsActuel - tempsPrecedent > 1000) {
                    avanceX = 1;
                    SDL_Delay(vitesse);
                    if (positionJoueur.x == 6 * TAILLE_BLOC - TAILLE_BLOC / 2) {
                        etape++;
                        avanceX = 0;
                    }
                }
                break;
            case 6:
                reculeY = 1;
                SDL_Delay(vitesse);
                if (positionJoueur.y == 6 * TAILLE_BLOC - TAILLE_BLOC / 2) {
                    etape++;
                    reculeY = 0;
                }
                break;
            case 7:
                reculeX = 1;
                SDL_Delay(vitesse);
                if (positionJoueur.x == 3 * TAILLE_BLOC + TAILLE_BLOC / 2) {
                    etape++;
                    reculeX = 0;
                }
                break;
            case 8:
                reculeY = 1;
                SDL_Delay(vitesse);
                if (positionJoueur.y == 2 * TAILLE_BLOC) {
                    etape++;
                    reculeY = 0;
                }
                tempsPrecedent = tempsActuel;
                break;
            case 9:
                if(tempsActuel - tempsPrecedent > 2000) { 
                    SDL_BlitSurface(imageDeFin, NULL, ecran, &positionFond);
                    // Boucle infinie (OLOLOL)
                    SDL_WaitEvent(&event);
                    switch(event.type) {
                        case SDL_QUIT:
                            continuer = 0;
                            break;
                        case SDL_KEYDOWN:
                            switch(event.key.keysym.sym) {
                                case SDLK_SPACE:
                                    continuer = 0;
                                    break;
                            }
                            break;
                    }
                }
                break;
                }

        SDL_Flip(ecran);

    }

    for (i = 0 ; i < 4 ; i++)
        SDL_FreeSurface(mario[i]);
    SDL_FreeSurface(imageDeFond);
}










/*
 jeu.h
 -------

 ChinaskiJr pour lui-même 	February 2018

 Rôle : Contient les prototypes de la fonctions jouer.c

 */

#ifndef DEF_JOUER
#define DEF_JOUER

void jouer(SDL_Surface* ecran);
void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction);
void deplacerCaisse(int *premiereCase, int *secondeCase);
void compteurTemps(long temps, int *continuer, SDL_Surface *ecran, TTF_Font *police); // (en ms)

#endif

/*
 constantes.h
 ----------------------------

 Par ChinaskiJr, pour lui-même

 February 2018

 Rôle : Définit des constantes pour tout le programme du Mario Sokoban
 */

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES
	
	#define TAILLE_BLOC		    34
	#define NB_BLOCS_LARGEUR	12
	#define NB_BLOCS_HAUTEUR	12
	#define LARGEUR_FENETRE		TAILLE_BLOC * NB_BLOCS_LARGEUR
	#define HAUTEUR_FENETRE		TAILLE_BLOC * NB_BLOCS_HAUTEUR

	enum {HAUT, BAS, GAUCHE, DROITE};
	enum {VIDE, MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK};

#endif



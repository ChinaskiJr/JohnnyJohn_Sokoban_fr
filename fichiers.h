/* fichiers.h
   ----------

   ChinaskiJr pour lui-même 	February 2018

   Rôle : Contient les headers de fichiers.c

   */

#ifndef DEF_FICHIERS
#define DEF_FICHIERS
// Renvoie un booléen : vrai si le chargement a réussi, faux s'il a échoué
// NiveauActuel 1 = 0, 2 = 1, ...
// Renvoie 2 une fois arrivé au dernier niveau
int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR], int niveauActuel);
// Renvoie un booléen : vrai si le chargement a réussi, faux s'il a échoué
int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR]);
// Renvoie un booléen : vrai si le chargement a réussi, faux s'il a échoué
int chargerNiveauEditeur(int niveau[][NB_BLOCS_HAUTEUR]);

#endif

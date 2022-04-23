#ifndef IA_H
#define IA_H


void AI(int Matrix[][SIZE],int Mat[][SIZE],int *,int,donnees_t img,donnees_t *donnees);
void help(int Matrix[][SIZE],int Mat[][SIZE],donnees_t img,donnees_t *donnees);
int ScoreforAI(int Mat[][SIZE],donnees_t *);
void afficherScoreIA(donnees_t img,int coordX,donnees_t *donnees);
void afficherBestScoreIA(donnees_t img,int coordX,donnees_t *donnees);


#endif
#ifndef FONCTION_H
#define FONCTION_H

int NUMGAGNE;
int SIZE;


typedef struct 
{
    Image deuxJeu;
    Image quatreJeu;
    Image huitJeu;
    Image seizeJeu;
    Image trentedeuxJeu;
    Image soixantequatreJeu;
    Image centvingthuitJeu;
    Image deuxcentcinquantesixJeu;
    Image cinqcentdouzeJeu;
    Image millevingtquatreJeu;
    Image deuxmillequarantehuitJeu;
    Image fond;
    Image fondnosound;
    Image gagne;
    Image perd;
    Image quit;
    Image quit2;
    Image restart;
    Image restart2;
    Image score1;
    Image score2;
    Image score3;
    Image score4;
    Image score5;
    Image score6;
    Image score7;
    Image score8;
    Image score9;
    Image score0;
    int Score;
    int bestScore;
    int sonCoupe;
    Image SCORE[10];
    Image rightArrow;
    Image leftArrow;
    Image downArrow;
    Image upArrow;
    Image conf1;
    Image conf2;
    Image conf3;
    Image conf4;
    Image conf5;
    Image conf6;
    Image x5;
    Image x5nosound;
    Image menu;
    Image fond4096;
    Image fond4096nosound;
    Image selection;
    Image commande;

    Son assemblage;
    Son decalage;
    Son victoire;

    PisteAudio audioAssemblage;
    PisteAudio audioDecalage;
    PisteAudio Win;
    
}donnees_t;


void toucheClavier(int Matrix[][SIZE],int MatCopie[][SIZE],donnees_t *,int*,int);
int Down(int Matrix [][SIZE],donnees_t *,int,int);
int Up(int Matrix [][SIZE],donnees_t *,int,int);
int Right(int Matrix[][SIZE],donnees_t *,int,int);
int Left(int Matrix[][SIZE],donnees_t *,int,int);
int gagneJeu(int Matrix[][SIZE]);
int perdJeu(int Matrix[][SIZE]);
void aleatoire(int Matrix[][SIZE]);
int DeuxOuQuatre();
int changement(int Mat[][SIZE],int Matrix[][SIZE]);
void copieMatrix(int Matrix[][SIZE],int Mat[][SIZE]);
void imgNombre(int Matrix[][SIZE],donnees_t);
void meilleurScore(donnees_t,donnees_t *);
int rejoue(int Matrix[][SIZE],donnees_t);
donnees_t chargement();
void afficherBestScore(donnees_t img,int coordX);
void afficherScore(donnees_t img,int coordX);
void slideTilesRight(int Matrix[][SIZE],int MatCopie[][SIZE],donnees_t img,int);
void slideTilesLeft(int Matrix[][SIZE],int MatCopie[][SIZE],donnees_t img,int);
void slideTilesDown(int Matrix[][SIZE],int MatCopie[][SIZE],donnees_t img,int);
void slideTilesUp(int Matrix[][SIZE],int MatCopie[][SIZE],donnees_t img,int);
void afficherFondSon(donnees_t *img,donnees_t,int);
void menu(donnees_t,int *);
void AffichageSlideX(donnees_t img,int Slide,int TabDec[SIZE][SIZE],int MatCopie[SIZE][SIZE],int Matrix[SIZE][SIZE],int TabDecCopie[SIZE][SIZE],int direction);
#endif
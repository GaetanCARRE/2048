#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "libTableauNoir.h"
#include "fct.h"




#define ORIGINE_X -160
#define ORIGINE_Y 138
#define DECALAGE_CASE 110
#define POURCENTAGE1 0
#define POURCENTAGE2 15
#define NbEssaiAI 50



donnees_t chargement()
{
    donnees_t img;
    img.deuxJeu = chargerImage("media/2.png");
    img.quatreJeu = chargerImage("media/4.png");
    img.huitJeu = chargerImage("media/8.png");
    img.seizeJeu = chargerImage("media/16.png");
    img.trentedeuxJeu = chargerImage("media/32.png");
    img.soixantequatreJeu = chargerImage("media/64.png");
    img.centvingthuitJeu = chargerImage("media/128.png");
    img.deuxcentcinquantesixJeu = chargerImage("media/256.png");
    img.cinqcentdouzeJeu = chargerImage("media/512.png");
    img.millevingtquatreJeu = chargerImage ("media/1024.png");
    img.deuxmillequarantehuitJeu = chargerImage("media/2048.png");
    img.fond=chargerImage("media/fondSound2.png");
    img.fondnosound=chargerImage("media/fondnoSound2.png");
    img.gagne=chargerImage("media/GAGNE.png");
    img.perd = chargerImage("media/PERD.png");
    img.quit = chargerImage("media/quit.png");
    img.quit2 = chargerImage("media/quit2.png");
    img.restart = chargerImage("media/restart.png");
    img.restart2 = chargerImage("media/restart2.png");
    img.score0 = chargerImage("media/score0.png");
    img.score1 = chargerImage("media/score1.png");
    img.score2 = chargerImage("media/score2.png");
    img.score3 = chargerImage("media/score3.png");
    img.score4 = chargerImage("media/score4.png");
    img.score5 = chargerImage("media/score5.png");
    img.score6 = chargerImage("media/score6.png");
    img.score7 = chargerImage("media/score7.png");
    img.score8 = chargerImage("media/score8.png");
    img.score9 = chargerImage("media/score9.png");
    img.rightArrow = chargerImage("media/flechedroite.png");
    img.leftArrow = chargerImage("media/flechegauche.png");
    img.downArrow = chargerImage("media/flechebas.png");
    img.upArrow = chargerImage("media/flechehaut.png");
    img.conf1 = chargerImage("media/confettis1.png");
    img.conf2 = chargerImage("media/confettis2.png");
    img.conf3 = chargerImage("media/confettis3.png");
    img.conf4 = chargerImage("media/confettis4.png");
    img.conf5 = chargerImage("media/confettis5.png");
    img.conf6 = chargerImage("media/confettis6.png");
    img.menu = chargerImage("media/menu.png");
    img.x5 = chargerImage("media/fond5x5son.png");
    img.x5nosound = chargerImage("media/fond5x5.png");
    img.fond4096 = chargerImage("media/4096fond.png");
    img.fond4096nosound = chargerImage("media/4096nosound.png");
    img.selection = chargerImage("media/selection.png");
    img.commande = chargerImage("media/commande.png");

    img.assemblage = chargerAudio ("media/assemblage.ogg");
    img.decalage = chargerAudio("media/decalage.ogg");
    img.victoire = chargerAudio("media/Victoire.ogg");


    img.sonCoupe=0;


    return img;

}

void toucheClavier(int Matrix[][SIZE],int MatCopie[][SIZE],donnees_t *img,int*exe,int fond) //effectue le mouvement quand on appuie sur la touche du clavier (et sur la souris)
{
    EtatSourisClavier esc =lireEtatSourisClavier();
    fixerModeBufferisation(1);
    while(!(esc.touchesClavier[79]) && !(esc.touchesClavier[80])&& !(esc.touchesClavier[81])&& !(esc.touchesClavier[82])&& !(esc.sourisBoutonGauche==1)){
        esc = lireEtatSourisClavier();
        if(esc.touchesClavier[79]){
            Right(Matrix,img,0,0);
            if(changement(Matrix,MatCopie))
            slideTilesRight(Matrix,MatCopie,*img,fond);

        }
        if(esc.touchesClavier[80]){
            Left(Matrix,img,0,0);
            if(changement(Matrix,MatCopie))
            slideTilesLeft(Matrix,MatCopie,*img,fond);
        }
        if(esc.touchesClavier[81]){
            Down(Matrix,img,0,0);
            if(changement(Matrix,MatCopie))
            slideTilesDown(Matrix,MatCopie,*img,fond);
        }
        if(esc.touchesClavier[82]){
            Up(Matrix,img,0,0);
            if(changement(Matrix,MatCopie))
            slideTilesUp(Matrix,MatCopie,*img,fond);
        }
        if(esc.sourisBoutonGauche==1 && esc.sourisX<800 && esc.sourisX>705 && esc.sourisY<450 && esc.sourisY>355 ){
            exit(1);
        }
        if(esc.sourisBoutonGauche==1 && esc.sourisX>-433 && esc.sourisX<-253 && esc.sourisY<136 && esc.sourisY>-44 ){
            *exe=2;
        }
        if(esc.sourisBoutonGauche==1 && esc.sourisX>-433 && esc.sourisX<-253 && esc.sourisY<-102 && esc.sourisY>-282 ){
            *exe=0;
        }
        if(esc.sourisBoutonGauche==1 && esc.sourisX<800 && esc.sourisX>705 && esc.sourisY<354 && esc.sourisY>259 ){
            img->sonCoupe+=1;

        }
    }


}

int Down(int Matrix [SIZE][SIZE],donnees_t *img,int score,int AI) //fonction fleche bas
{
    int i,j,comp=0; //comp est le compteur de fusion

    for(j=0;j<SIZE;j++)
    {
        i=0;
        if (SIZE==4)
        {
            if ((Matrix[i][j]==Matrix[i+1][j]) && (Matrix[i+2][j]==Matrix[i+3][j])){
                comp=2;//c'est a dire qu'il peut y avoir 2 fusion
            }else
            {
                comp=1;//une seule fusion
            }
        }else if (SIZE==5)
        {
            if (((Matrix[i][j]==Matrix[i+1][j]) && (Matrix[i+2][j]==Matrix[i+3][j])) || ((Matrix[i+2][j]==Matrix[i+1][j]) && (Matrix[i+4][j]==Matrix[i+3][j]))||((Matrix[i][j]==Matrix[i+1][j]) && (Matrix[i+3][j]==Matrix[i+4][j]))||((Matrix[i][j]==Matrix[i+1][j])&&((Matrix[i+2][j]==Matrix[i+4][j])&&(Matrix[i+3][j]==0)))||((Matrix[i][j]==Matrix[i+2][j])&&((Matrix[i+3][j]==Matrix[i+4][j])&&(Matrix[i+2][j]==0)))){
                comp=2;
            }else
            {
                comp=1;
            }
        }


        i=SIZE-2;
        while(1)
        {
            while(Matrix[i][j]==0)
            {
                if(i==-1)
                    break;
                i--;
            }
            if(i==-1)
                break;
            while(i<SIZE-1 && (Matrix[i+1][j]==0))
            {
                Matrix[i+1][j]+=Matrix[i][j];
                Matrix[i][j]=0;
                i++;
            }
            while (i<SIZE-1 && comp>0 &&(Matrix[i][j]==Matrix[i+1][j])){
                Matrix[i+1][j]+=Matrix[i][j];
                Matrix[i][j]=0;
                i++;
                comp--;
                if (AI==0)
                    img->Score += (Matrix[i][j]);

                score += (Matrix[i][j]);
            }
            i--;
        }
    }
    return score;
}
int Up(int Matrix [][SIZE],donnees_t *img,int score,int AI)//fonction fleche haut
{
    int i,j,comp=0;
    for(j=0;j<SIZE;j++)
    {
        i=0;
        if (SIZE==4){
            if ((Matrix[i][j]==Matrix[i+1][j]) && (Matrix[i+2][j]==Matrix[i+3][j])){
                comp=2;
            }else
            {
                comp=1;
            }
        }else if(SIZE==5)
        {
            if (((Matrix[i][j]==Matrix[i+1][j]) && (Matrix[i+2][j]==Matrix[i+3][j]))||((Matrix[i+2][j]==Matrix[i+1][j]) && (Matrix[i+4][j]==Matrix[i+3][j]) )||((Matrix[i][j]==Matrix[i+1][j]) && (Matrix[i+4][j]==Matrix[i+3][j]))||((Matrix[i][j]==Matrix[i+1][j])&&((Matrix[i+2][j]==Matrix[i+4][j])&&(Matrix[i+3][j]==0)))||((Matrix[i][j]==Matrix[i+2][j])&&((Matrix[i+3][j]==Matrix[i+4][j])&&(Matrix[i+2][j]==0)))){ 
                comp=2;
            }else
            {
                comp=1;
            }
        }
        i=1;
        while(1)
        {
            while(Matrix[i][j]==0)
            {
                if(i==SIZE)
                    break;
                i++;
            }
            if(i==SIZE)
                break;
            while(i>0 && (Matrix[i-1][j]==0))
            {
                Matrix[i-1][j]+=Matrix[i][j];
                Matrix[i][j]=0;
                i--;
            }
            while(i>0 && comp>0 && (Matrix[i][j]==Matrix[i-1][j]))
            {
                Matrix[i-1][j]+=Matrix[i][j];
                Matrix[i][j]=0;
                i--;
                comp--;

                if(AI==0)
                    img->Score += (Matrix[i][j]);

                score += (Matrix[i][j]);
            }
            i++;
        }
    }
    return score;
}
int Right(int Matrix[SIZE][SIZE],donnees_t *img,int score,int AI)//fonction fleche droite
{
    int i,j,comp=0;
    for(i=0;i<SIZE;i++)
    {
        j=0;
        if(SIZE==4){
            if ((Matrix[i][j]==Matrix[i][j+1]) && (Matrix[i][j+2]==Matrix[i][j+3])){
                comp=2;
            }else
            {
                comp=1;
            }
        }else if (SIZE==5)
        {
            if (((Matrix[i][j]==Matrix[i][j+1]) && (Matrix[i][j+2]==Matrix[i][j+3])) || ((Matrix[i][j+2]==Matrix[i][j+1]) && (Matrix[i][j+4]==Matrix[i][j+3]))||((Matrix[i][j]==Matrix[i][j+1]) && (Matrix[i][j+3]==Matrix[i][j+4]))||((Matrix[i][j]==Matrix[i][j+1])&&((Matrix[i][j+2]==Matrix[i][j+4])&&(Matrix[i][j+3]==0)))||((Matrix[i][j]==Matrix[i][j+2])&&((Matrix[i][j+3]==Matrix[i][j+4])&&(Matrix[i][j+2]==0)))){
                comp=2;
            }else
            {
                comp=1;
            }
        }


        j=SIZE-2;
        while(1)
        {
            while(Matrix[i][j]==0)
            {
                if(j==-1)
                    break;
                j--;
            }
            if(j==-1)
                break;
            while(j<SIZE-1 && (Matrix[i][j+1]==0))
            {
                Matrix[i][j+1]+=Matrix[i][j];
                Matrix[i][j]=0;
                j++;
            }
            while(j<SIZE-1 && comp>0 && (Matrix[i][j]==Matrix[i][j+1]))
            {
                Matrix[i][j+1]+=Matrix[i][j];
                Matrix[i][j]=0;
                j++;
                comp--;
                if(AI==0)
                    img->Score += (Matrix[i][j]);

                score += (Matrix[i][j]);


            }
            j--;
        }
    }
    return score;
}
int Left(int Matrix[SIZE][SIZE],donnees_t *img,int score,int AI)//fonction fleche gauche
{
    int i,j,comp=0;
    for(i=0;i<SIZE;i++)
    {
        j=0;
        if(SIZE==4){
            if ((Matrix[i][j]==Matrix[i][j+1]) && (Matrix[i][j+2]==Matrix[i][j+3])){
                comp=2;
            }else
            {
                comp=1;
            }
        }else if (SIZE==5)
        {
            if (((Matrix[i][j]==Matrix[i][j+1]) && (Matrix[i][j+2]==Matrix[i][j+3])) || ((Matrix[i][j+2]==Matrix[i][j+1]) && (Matrix[i][j+4]==Matrix[i][j+3]))||((Matrix[i][j]==Matrix[i][j+1]) && (Matrix[i][j+3]==Matrix[i][j+4]))||((Matrix[i][j]==Matrix[i][j+1])&&((Matrix[i][j+2]==Matrix[i][j+4])&&(Matrix[i][j+3]==0)))||((Matrix[i][j]==Matrix[i][j+2])&&((Matrix[i][j+3]==Matrix[i][j+4])&&(Matrix[i][j+2]==0)))){
                comp=2;
            }else
            {
                comp=1;
            }
        }

        j=1;
        while(1)
        {
            while(Matrix[i][j]==0)
            {
                if(j==SIZE)
                    break;
                j++;
            }
            if(j==SIZE)
                break;
            while(j>0 && (Matrix[i][j-1]==0))
            {
                Matrix[i][j-1]+=Matrix[i][j];
                Matrix[i][j]=0;
                j--;
            }
            while(j>0 && comp>0 && (Matrix[i][j]==Matrix[i][j-1]))
            {
                Matrix[i][j-1]+=Matrix[i][j];
                Matrix[i][j]=0;
                j--;
                comp--;

                if(AI==0)
                    img->Score += (Matrix[i][j]);

                score += (Matrix[i][j]);
            }
            j++;
        }
    }
    return score;
}

int gagneJeu(int Matrix[SIZE][SIZE])//fonction qui retourne 1 si on a atteint NUMGAGNE qui est defini dans les directives de preprocesseur
{
    int i,j;
    for(i=0;i<SIZE;++i){
        for (j=0;j<SIZE;++j){
            if (Matrix[i][j]==NUMGAGNE)
            {
                return 1;
            }

        }
    }
    return 0;
}

int perdJeu(int Matrix[SIZE][SIZE])// fonction qui verifie si on a perdu
{
    int i,j;
    for(i=0;i<SIZE;++i){
        for (j=0;j<SIZE;++j){
            if (Matrix[i][j]==0)//si on a une case vide on a pas perdu donc on renvoie 0
            {
                return 0;
            }

        }
    }
    //on arrive ici si la matrice est remplie
    for(i=0;i<SIZE;++i){
        for (j=0;j<SIZE-1;++j){
            if (Matrix[i][j]==Matrix[i][j+1])//on verifie sur chaque ligne si il y a un nombre egale
            {
                return 0;//si oui on a pas perdu
            }

        }
    }

    for(j=0;j<SIZE;++j){
        for (i=0;i<SIZE-1;++i){
            if (Matrix[i][j]==Matrix[i+1][j])//pareil avec les colonnes
            {
                return 0;
            }

        }
    }
    return 1;
}

void aleatoire(int Matrix[SIZE][SIZE])// fonction qui place un nombre aléatoire sur la grille
{

    int nb,i=0,j=0;

    while(1)
    {
        int CASEMAX,CASEMIN=0;
        if (SIZE==4)
            CASEMAX=15;
        else
            CASEMAX=24;


        nb = (rand() % (CASEMAX - CASEMIN + 1)) + CASEMIN; // nombre aleatoire entre 0 et 15
        i=nb%SIZE;//on associe a i et a j des valeur en fonction du nombre aléatoire
        j=nb/SIZE;
        if(Matrix[i][j]==0)
        {
            if((DeuxOuQuatre()))
            {
                Matrix[i][j]=2;
                break;
            }else
            {
                Matrix[i][j]=4;// une chance sur POURCENTAGE2 de mettre un 4
                break;
            }

        }

    }
}

int DeuxOuQuatre()//fonction qui a une chance sur POURCENTAGE2 de retourner 0
{

    int nb;
    nb = (rand() % (POURCENTAGE2 - POURCENTAGE1 + 1)) + POURCENTAGE1;
    if(nb==1){
        return 0;
    }
    return 1;
}

int changement(int Mat[SIZE][SIZE],int Matrix[SIZE][SIZE])//fonction qui verifie si 2 matrices sont les mêmes
{
    int i,j;
    for(i=0;i<SIZE;++i)
    {
        for(j=0;j<SIZE;++j)
        {
            if(Matrix[i][j]!=Mat[i][j])
            {
                return 1;
            }
        }
    }
    return 0;
}

void copieMatrix(int Matrix[SIZE][SIZE],int Mat[SIZE][SIZE]) //fonction qui copie la premiere matrice dans la seconde matrice
{
    int i,j;

    for(i=0;i<SIZE;++i)
    {
        for(j=0;j<SIZE;++j)
        {
            Mat[i][j]=Matrix[i][j];
        }
    }
}



void imgNombre(int Matrix[SIZE][SIZE],donnees_t img)//fonction qui affiche les nombres sur l'interface graphique
{

    int i,j;
    for(i=0;i<SIZE;++i)
    {
        for(j=0;j<SIZE;++j)
        {
            if (Matrix[i][j]==2)
            {
                afficherImage(img.deuxJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


            }
            if (Matrix[i][j]==4)
            {
                afficherImage(img.quatreJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


            }
            if (Matrix[i][j]==8)
            {
                afficherImage(img.huitJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


            }
            if (Matrix[i][j]==16)
            {
                afficherImage(img.seizeJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


            }
            if (Matrix[i][j]==32)
            {
                afficherImage(img.trentedeuxJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


            }
            if (Matrix[i][j]==64)
            {
                afficherImage(img.soixantequatreJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


            }
            if (Matrix[i][j]==128)
            {
                afficherImage(img.centvingthuitJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


            }
            if (Matrix[i][j]==256)
            {
                afficherImage(img.deuxcentcinquantesixJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


            }
            if (Matrix[i][j]==512)
            {
                afficherImage(img.cinqcentdouzeJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


            }
            if (Matrix[i][j]==1024)
            {
                afficherImage(img.millevingtquatreJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


            }
            if (Matrix[i][j]==2048)
            {
                afficherImage(img.deuxmillequarantehuitJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


            }
        }
    }
    tamponner();
}

void afficherScore(donnees_t img,int coordX)// fonction qui affiche le score sur l'interface graphique
{
    img.SCORE[0]=img.score0;
    img.SCORE[1]=img.score1;
    img.SCORE[2]=img.score2;
    img.SCORE[3]=img.score3;
    img.SCORE[4]=img.score4;
    img.SCORE[5]=img.score5;
    img.SCORE[6]=img.score6;
    img.SCORE[7]=img.score7;
    img.SCORE[8]=img.score8;
    img.SCORE[9]=img.score9;
    int temp=-80;
    for (int i=0; i<5; ++i)
    {
        afficherImage(img.SCORE[img.Score%10],coordX-temp,285);
        img.Score/=10;
        temp+=20;
    }

}

void afficherBestScore(donnees_t img,int coordX)// fonction qui affiche le meilleur score sur l'interface graphique
{
    img.SCORE[0]=img.score0;
    img.SCORE[1]=img.score1;
    img.SCORE[2]=img.score2;
    img.SCORE[3]=img.score3;
    img.SCORE[4]=img.score4;
    img.SCORE[5]=img.score5;
    img.SCORE[6]=img.score6;
    img.SCORE[7]=img.score7;
    img.SCORE[8]=img.score8;
    img.SCORE[9]=img.score9;
    int temp=-80;
    for (int i=0; i<5; ++i)
    {
        afficherImage(img.SCORE[img.bestScore%10],coordX-temp,285);
        img.bestScore/=10;
        temp+=20;
    }

}

void meilleurScore(donnees_t img,donnees_t *donnees)//fonction qui change le meilleur score quand le score le dépasse
{
    if (img.Score>donnees->bestScore)
    {
        donnees->bestScore=img.Score;
    }
}

int rejoue(int Matrix[][SIZE],donnees_t img)//fonction qui affiche le menu de fin en fonction de la victoire ou de la défaite
{
    EtatSourisClavier esc;



    if(gagneJeu(Matrix)){

        while(1)
        {
            attendreClicGauche();
            esc=lireEtatSourisClavier();

            if(esc.sourisX>-45 && esc.sourisX<165 && esc.sourisY>-230 && esc.sourisY<-170)
            {
                afficherImage(img.quit2,-45,-170);
                tamponner();
                attendreNms(100);
                return 1;
            }
            if(esc.sourisX>-45 && esc.sourisX<165 && esc.sourisY>-150 && esc.sourisY<-90){
            afficherImage(img.restart2,-45,-90);
            tamponner();
            attendreNms(100);
            return 0;
            }
        }
    }
    else if(perdJeu(Matrix))
    {
        while(1)
        {
            attendreClicGauche();
            esc=lireEtatSourisClavier();

            if(esc.sourisX>-45 && esc.sourisX<165 && esc.sourisY>-230 && esc.sourisY<-170)
            {
                afficherImage(img.quit2,-45,-170);
                tamponner();
                attendreNms(100);
                return 1;
            }
            if(esc.sourisX>-45 && esc.sourisX<165 && esc.sourisY>-150 && esc.sourisY<-90){
                afficherImage(img.restart2,-45,-90);
                tamponner();
                attendreNms(100);
                return 0;
            }
        }
    }

   return 0;
}



void slideTilesRight(int Matrix[SIZE][SIZE],int MatCopie[SIZE][SIZE],donnees_t img,int fond)//fonction qui anime le déplacement de touches vers la droite
{

    int i=0,j=0,k=0;
    int TabDec[SIZE][SIZE];
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            TabDec[i][j]=0;
        }

    }

    int TabDecCopie[SIZE][SIZE];
    int cmpdec=0;
    int a;
    int Slide=0;
    fixerModeBufferisation(1);



        for (i = 0; i < SIZE; i++)
        {
            for (j = SIZE-1; j>=0;j--)
            {
                if (MatCopie[i][j]==0){
                    for(k = j-1;k >= 0;k--)
                    {
                        if(MatCopie[i][k]!=0)
                        TabDec[i][k]+=1;

                    }

                }else if (MatCopie[i][j]==MatCopie[i][j-1])
                {

                    for (k=j-1;k>=0;k--)
                    {
                        if (j!=SIZE-1 && MatCopie[i][k]!=0)
                        {
                        TabDec[i][j-1]+=1;
                        j--;
                        }else
                        {
                        j--;
                        }

                    }

                }

            }
        }
    copieMatrix(TabDec,TabDecCopie);

    while (1)
    {
       
        Slide+=36;
        //effacerTableau();

        afficherFondSon(&img,img,fond);
        afficherScore(img,-126);
        afficherBestScore(img,122);
        AffichageSlideX(img,Slide,TabDec,MatCopie,Matrix,TabDecCopie,1);

        tamponner();
        cmpdec++;

        if (cmpdec % 3 == 0)
        {
            for (i = 0;i<SIZE;i++)
            {
                for(j = 0;j<SIZE;j++)
                {
                    TabDec[i][j]-=1;

                }
            }
        }
        attendreNms(1);
        a=0;
        for (i = 0;i<SIZE;i++)
        {
            for(j = 0;j<SIZE;j++)
            {
                if(TabDec[i][j]<=0)
                    a+=1;

            }
        }

        if (a==SIZE*SIZE)
        {
            break;
        }

    }
}

void slideTilesLeft(int Matrix[SIZE][SIZE],int MatCopie[SIZE][SIZE],donnees_t img,int fond)
{

    int i=0,j=0,k=0;
    int TabDec[SIZE][SIZE];
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            TabDec[i][j]=0;
        }

    }
        int TabDecCopie[SIZE][SIZE];
        int cmpdec=0;
        int a;
        int Slide=0;
        fixerModeBufferisation(1);



        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j<SIZE;j++)
            {
                if (MatCopie[i][j]==0){
                    for(k = j+1;k < SIZE;k++)
                    {
                        if(MatCopie[i][k]!=0)
                        TabDec[i][k]+=1;

                    }

                }else if (MatCopie[i][j]==MatCopie[i][j+1])
                {

                    for (k=j+1;k<SIZE;k++)
                    {
                        if (j!=0 && MatCopie[i][k]!=0)
                        {
                        TabDec[i][j+1]+=1;
                        j++;
                        }else
                        {
                        j++;
                        }

                    }

                }

            }
        }

    copieMatrix(TabDec,TabDecCopie);

    while (1)
    {
        
        Slide-=36;
        //effacerTableau();

        afficherFondSon(&img,img,fond);
        afficherScore(img,-126);
        afficherBestScore(img,122);
        AffichageSlideX(img,Slide,TabDec,MatCopie,Matrix,TabDecCopie,2);
        tamponner();
        cmpdec++;

        if (cmpdec % 3 == 0)
        {
            for (i = 0;i<SIZE;i++)
            {
                for(j = 0;j<SIZE;j++)
                {
                    TabDec[i][j]-=1;

                }
            }
        }
        attendreNms(1);
        a=0;
        for (i = 0;i<SIZE;i++)
        {
            for(j = 0;j<SIZE;j++)
            {
                if(TabDec[i][j]<=0)
                    a+=1;

            }
        }

        if (a==SIZE*SIZE)
        {
            break;
        }





    }


}


void slideTilesDown(int Matrix[SIZE][SIZE],int MatCopie[SIZE][SIZE],donnees_t img,int fond)
{



    int i=0,j=0,k=0;
    int TabDec[SIZE][SIZE];
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            TabDec[i][j]=0;
        }

    }

    int TabDecCopie[SIZE][SIZE];
    int cmpdec=0;
    int a;
    int Slide=0;
    fixerModeBufferisation(1);



        for (j = 0; j < SIZE; j++)
        {
            for (i = SIZE-1; i>=0;i--)
            {
                if (MatCopie[i][j]==0){
                    for(k = i-1;k >= 0;k--)
                    {
                        if(MatCopie[k][j]!=0)
                        TabDec[k][j]+=1;

                    }

                }else if (MatCopie[i][j]==MatCopie[i-1][j])
                {

                    for (k=i-1;k>=0;k--)
                    {
                        if (i!=SIZE-1 && MatCopie[i][k]!=0)
                        {
                        TabDec[i-1][j]+=1;
                        i--;
                        }else
                        {
                        i--;
                        }

                    }

                }

            }
        }
    copieMatrix(TabDec,TabDecCopie);

    while (1)
    {

        Slide-=36;
        //effacerTableau();

        afficherFondSon(&img,img,fond);
        afficherScore(img,-126);
        afficherBestScore(img,122);
        AffichageSlideX(img,Slide,TabDec,MatCopie,Matrix,TabDecCopie,3);

        tamponner();
        cmpdec++;

        if (cmpdec % 3 == 0)
        {
            for (j = 0;j<SIZE;j++)
            {
                for(i = 0;i<SIZE;i++)
                {
                    TabDec[i][j]-=1;

                }
            }
        }
        attendreNms(1);
        a=0;
        for (i = 0;i<SIZE;i++)
        {
            for(j = 0;j<SIZE;j++)
            {
                if(TabDec[i][j]<=0)
                    a+=1;

            }
        }


        if (a==SIZE*SIZE)
        {
            break;
        }

    }

}

void slideTilesUp(int Matrix[SIZE][SIZE],int MatCopie[SIZE][SIZE],donnees_t img,int fond)
{



    int i=0,j=0,k=0;
    int TabDec[SIZE][SIZE];
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            TabDec[i][j]=0;
        }

    }

    int TabDecCopie[SIZE][SIZE];
    int cmpdec=0;
    int a;
    int Slide=0;
    fixerModeBufferisation(1);



        for (j = 0; j < SIZE; j++)
        {
            for (i = 0; i < SIZE; i++)
            {
                if (MatCopie[i][j]==0){
                    for(k = i+1;k < SIZE; k++)
                    {
                        if(MatCopie[k][j]!=0)
                        TabDec[k][j]+=1;

                    }

                }else if (MatCopie[i][j]==MatCopie[i+1][j])
                {

                    for (k=i+1;k < SIZE;k++)
                    {
                        if (i!=0 && MatCopie[i][k]!=0)
                        {
                        TabDec[i+1][j]+=1;
                        i++;
                        }else
                        {
                        i++;
                        }

                    }

                }

            }
        }
    copieMatrix(TabDec,TabDecCopie);

    while (1)
    {


        Slide+=36;
        

        afficherFondSon(&img,img,fond);
        afficherScore(img,-126);
        afficherBestScore(img,122);
        AffichageSlideX(img,Slide,TabDec,MatCopie,Matrix,TabDecCopie,4);

        tamponner();
        cmpdec++;

        if (cmpdec % 3 == 0)
        {
            for (j = 0;j<SIZE;j++)
            {
                for(i = 0;i<SIZE;i++)
                {
                    TabDec[i][j]-=1;

                }
            }
        }
        attendreNms(1);
        a=0;
        for (i = 0;i<SIZE;i++)
        {
            for(j = 0;j<SIZE;j++)
            {
                if(TabDec[i][j]<=0)
                    a+=1;

            }
        }

        if (a==SIZE*SIZE)
        {
            break;
        }

    }

}


void afficherFondSon(donnees_t *img,donnees_t donnees,int fond)
{

    if(img->sonCoupe % 2 == 0)
    {
        if(fond==0)
            afficherImage(donnees.fond,-800,450);
        else if (fond==1)
            afficherImage(donnees.x5,-800,450);
        else if (fond==2)
            afficherImage(donnees.fond4096,-800,450);
    }else{

        if(fond==0)
            afficherImage(donnees.fondnosound,-800,450);
        else if (fond==1)
            afficherImage(donnees.x5nosound,-800,450);
        else if (fond==2)
            afficherImage(donnees.fond4096nosound,-800,450);
    }
}



void menu(donnees_t donnees,int *fond)
{

    afficherImage(donnees.menu,-800,450);
    tamponner();
    EtatSourisClavier esc =lireEtatSourisClavier();
    while (!(esc.sourisX<-320 && esc.sourisX>-756 && esc.sourisY<269 && esc.sourisY>23 && esc.sourisBoutonGauche) && (!(esc.sourisX>318 && esc.sourisX<754 && esc.sourisY<269 && esc.sourisY>23 && esc.sourisBoutonGauche))&&(!(esc.sourisX>-217 && esc.sourisX<219 && esc.sourisY<1 && esc.sourisY>-245 && esc.sourisBoutonGauche)))
    {
        esc =lireEtatSourisClavier();
        if (esc.sourisX<-320 && esc.sourisX>-756 && esc.sourisY<269 && esc.sourisY>23)
        {
            afficherImage(donnees.selection,-760,272);
            tamponner();
            esc =lireEtatSourisClavier();
            if(esc.sourisBoutonGauche)
            {
                *fond=0;
                SIZE=4;
                NUMGAGNE=2048;
                break;
            }
        }else if (esc.sourisX<754 && esc.sourisX>318 && esc.sourisY<269 && esc.sourisY>23)
        {
            afficherImage(donnees.selection,318,272);
            tamponner();
            if(esc.sourisBoutonGauche)
            {
                *fond=1;
                SIZE=5;
                NUMGAGNE=2048;
                break;
            }
        }else if (esc.sourisX<219 && esc.sourisX>-217 && esc.sourisY<1 && esc.sourisY>-245)
        {
            afficherImage(donnees.selection,-220,3);
            tamponner();
            if(esc.sourisBoutonGauche)
            {
                *fond=2;
                SIZE=4;
                NUMGAGNE=4096;
                break;
            }
        }else{
            afficherImage(donnees.menu,-800,450);
            tamponner();
        }


    }
}



void AffichageSlideX(donnees_t img,int Slide,int TabDec[SIZE][SIZE],int MatCopie[SIZE][SIZE],int Matrix[SIZE][SIZE],int TabDecCopie[SIZE][SIZE],int direction)
{
        int i,j;
        int Tab[SIZE][SIZE];
        if(direction==1 ||direction==4)
        {

          for (i = 0; i < SIZE; i++) 
          {
            for ( j = 0; j < SIZE; j++) 
            {
              Tab[i][j]= -TabDecCopie[i][j];
            }
          }
        }else if (direction==2||direction==3)
        {
            copieMatrix(TabDecCopie,Tab);
        }


        for (i=0;i<SIZE;i++)
        {
            for(j=0;j<SIZE;j++)
            {
                if (TabDec[i][j]>0)
                {
                    if (MatCopie[i][j]==2)
                    {
                        
                        if(direction==1 || direction==2)
                            afficherImage(img.deuxJeu,ORIGINE_X+(DECALAGE_CASE*j)+Slide,ORIGINE_Y-(DECALAGE_CASE*i));
                        else
                            afficherImage(img.deuxJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)+Slide);
    


                    }
                    if (MatCopie[i][j]==4)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.quatreJeu,ORIGINE_X+(DECALAGE_CASE*j)+Slide,ORIGINE_Y-(DECALAGE_CASE*i));
                        else 
                            afficherImage(img.quatreJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)+Slide);
                    }
                    if (MatCopie[i][j]==8)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.huitJeu,ORIGINE_X+(DECALAGE_CASE*j)+Slide,ORIGINE_Y-(DECALAGE_CASE*i));
                        else
                            afficherImage(img.huitJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)+Slide);

                    }
                    if (MatCopie[i][j]==16)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.seizeJeu,ORIGINE_X+(DECALAGE_CASE*j)+Slide,ORIGINE_Y-(DECALAGE_CASE*i));
                        else
                            afficherImage(img.seizeJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)+Slide);



                    }
                    if (MatCopie[i][j]==32)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.trentedeuxJeu,ORIGINE_X+(DECALAGE_CASE*j)+Slide,ORIGINE_Y-(DECALAGE_CASE*i));
                        else
                            afficherImage(img.trentedeuxJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)+Slide);



                    }
                    if (MatCopie[i][j]==64)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.soixantequatreJeu,ORIGINE_X+(DECALAGE_CASE*j)+Slide,ORIGINE_Y-(DECALAGE_CASE*i));
                        else
                            afficherImage(img.soixantequatreJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)+Slide);



                    }
                    if (MatCopie[i][j]==128)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.centvingthuitJeu,ORIGINE_X+(DECALAGE_CASE*j)+Slide,ORIGINE_Y-(DECALAGE_CASE*i));
                        else
                            afficherImage(img.centvingthuitJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)+Slide);



                    }
                    if (MatCopie[i][j]==256)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.deuxcentcinquantesixJeu,ORIGINE_X+(DECALAGE_CASE*j)+Slide,ORIGINE_Y-(DECALAGE_CASE*i));
                        else
                            afficherImage(img.deuxcentcinquantesixJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)+Slide);


                    }
                    if (MatCopie[i][j]==512)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.cinqcentdouzeJeu,ORIGINE_X+(DECALAGE_CASE*j)+Slide,ORIGINE_Y-(DECALAGE_CASE*i));
                        else
                            afficherImage(img.cinqcentdouzeJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)+Slide);



                    }
                    if (MatCopie[i][j]==1024)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.millevingtquatreJeu,ORIGINE_X+(DECALAGE_CASE*j)+Slide,ORIGINE_Y-(DECALAGE_CASE*i));
                        else
                            afficherImage(img.millevingtquatreJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)+Slide);



                    }
                    if (MatCopie[i][j]==2048)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.deuxmillequarantehuitJeu,ORIGINE_X+(DECALAGE_CASE*j)+Slide,ORIGINE_Y-(DECALAGE_CASE*i));
                        else
                            afficherImage(img.deuxmillequarantehuitJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)+Slide);



                    }
                }
                if (TabDec[i][j]<=0)
                {
                    if (MatCopie[i][j]==2)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.deuxJeu,ORIGINE_X+(DECALAGE_CASE*j)-Tab[i][j]*DECALAGE_CASE,ORIGINE_Y-(DECALAGE_CASE*i));
                        else 
                            afficherImage(img.deuxJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)-Tab[i][j]*DECALAGE_CASE);

                    }
                    if (MatCopie[i][j]==4)
                    {
                        
                        if(direction==1 || direction==2)
                            afficherImage(img.quatreJeu,ORIGINE_X+(DECALAGE_CASE*j)-Tab[i][j]*DECALAGE_CASE,ORIGINE_Y-(DECALAGE_CASE*i));
                        else 
                            afficherImage(img.quatreJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)-Tab[i][j]*DECALAGE_CASE);


                    }
                    if (MatCopie[i][j]==8)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.huitJeu,ORIGINE_X+(DECALAGE_CASE*j)-Tab[i][j]*DECALAGE_CASE,ORIGINE_Y-(DECALAGE_CASE*i));
                        else 
                            afficherImage(img.huitJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)-Tab[i][j]*DECALAGE_CASE);

                    }
                    if (MatCopie[i][j]==16)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.seizeJeu,ORIGINE_X+(DECALAGE_CASE*j)-Tab[i][j]*DECALAGE_CASE,ORIGINE_Y-(DECALAGE_CASE*i));
                        else 
                            afficherImage(img.seizeJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)-Tab[i][j]*DECALAGE_CASE);


                    }
                    if (MatCopie[i][j]==32)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.trentedeuxJeu,ORIGINE_X+(DECALAGE_CASE*j)-Tab[i][j]*DECALAGE_CASE,ORIGINE_Y-(DECALAGE_CASE*i));
                        else 
                            afficherImage(img.trentedeuxJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)-Tab[i][j]*DECALAGE_CASE);


                    }
                    if (MatCopie[i][j]==64)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.soixantequatreJeu,ORIGINE_X+(DECALAGE_CASE*j)-Tab[i][j]*DECALAGE_CASE,ORIGINE_Y-(DECALAGE_CASE*i));
                        else 
                            afficherImage(img.soixantequatreJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)-Tab[i][j]*DECALAGE_CASE);


                    }
                    if (MatCopie[i][j]==128)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.centvingthuitJeu,ORIGINE_X+(DECALAGE_CASE*j)-Tab[i][j]*DECALAGE_CASE,ORIGINE_Y-(DECALAGE_CASE*i));
                        else 
                            afficherImage(img.centvingthuitJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)-Tab[i][j]*DECALAGE_CASE);


                    }
                    if (MatCopie[i][j]==256)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.deuxcentcinquantesixJeu,ORIGINE_X+(DECALAGE_CASE*j)-Tab[i][j]*DECALAGE_CASE,ORIGINE_Y-(DECALAGE_CASE*i));
                        else 
                            afficherImage(img.deuxcentcinquantesixJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)-Tab[i][j]*DECALAGE_CASE);


                    }
                    if (MatCopie[i][j]==512)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.cinqcentdouzeJeu,ORIGINE_X+(DECALAGE_CASE*j)-Tab[i][j]*DECALAGE_CASE,ORIGINE_Y-(DECALAGE_CASE*i));
                        else 
                            afficherImage(img.cinqcentdouzeJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)-Tab[i][j]*DECALAGE_CASE);


                    }
                    if (MatCopie[i][j]==1024)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.millevingtquatreJeu,ORIGINE_X+(DECALAGE_CASE*j)-Tab[i][j]*DECALAGE_CASE,ORIGINE_Y-(DECALAGE_CASE*i));
                        else 
                            afficherImage(img.millevingtquatreJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)-Tab[i][j]*DECALAGE_CASE);


                    }
                    if (MatCopie[i][j]==2048)
                    {
                        if(direction==1 || direction==2)
                            afficherImage(img.deuxmillequarantehuitJeu,ORIGINE_X+(DECALAGE_CASE*j)-Tab[i][j]*DECALAGE_CASE,ORIGINE_Y-(DECALAGE_CASE*i));
                        else 
                            afficherImage(img.deuxmillequarantehuitJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i)-Tab[i][j]*DECALAGE_CASE);


                    }
                }
                if (MatCopie[i][j]==Matrix[i][j])
                {
                    if (Matrix[i][j]==2)
                    {
                        afficherImage(img.deuxJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


                    }
                    if (Matrix[i][j]==4)
                    {
                        afficherImage(img.quatreJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


                    }
                    if (Matrix[i][j]==8)
                    {
                        afficherImage(img.huitJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


                    }
                    if (Matrix[i][j]==16)
                    {
                        afficherImage(img.seizeJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


                    }
                    if (Matrix[i][j]==32)
                    {
                        afficherImage(img.trentedeuxJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


                    }
                    if (Matrix[i][j]==64)
                    {
                        afficherImage(img.soixantequatreJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


                    }
                    if (Matrix[i][j]==128)
                    {
                        afficherImage(img.centvingthuitJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


                    }
                    if (Matrix[i][j]==256)
                    {
                        afficherImage(img.deuxcentcinquantesixJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


                    }
                    if (Matrix[i][j]==512)
                    {
                        afficherImage(img.cinqcentdouzeJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


                    }
                    if (Matrix[i][j]==1024)
                    {
                        afficherImage(img.millevingtquatreJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


                    }
                    if (Matrix[i][j]==2048)
                    {
                        afficherImage(img.deuxmillequarantehuitJeu,ORIGINE_X+(DECALAGE_CASE*j),ORIGINE_Y-(DECALAGE_CASE*i));


                    }
                }
            }
        }
}

#include <stdlib.h>
#include <stdio.h>
#include "libTableauNoir.h"
#include "fct.h"
#include <time.h> 
#include "IA.h"

#define NbEssaiAI 1000
#define coordXbestScore 122
#define coordXscore -126

void AI(int Matrix[][SIZE],int Mat[][SIZE],int *stop,int fond,donnees_t img,donnees_t *donnees)//fonction Intelligence artificielle
{
    //initialisation des matrices et variable
    int Mat1[SIZE][SIZE];
    int Mat2[SIZE][SIZE];
    int Mat3[SIZE][SIZE];
    int Mat4[SIZE][SIZE];
    int i=0;
    int Tab[4][NbEssaiAI];
    attendreNms(200);
    EtatSourisClavier esc =lireEtatSourisClavier();

    while (!(perdJeu(Matrix)))
    {
        
        esc =lireEtatSourisClavier();
        if(esc.sourisBoutonGauche==1 && esc.sourisX>-433 && esc.sourisX<-253 && esc.sourisY<-102 && esc.sourisY>-282)
        {
            *stop+=1;
            break;
        }
        copieMatrix(Matrix,Mat1);
        copieMatrix(Matrix,Mat2);
        copieMatrix(Matrix,Mat3);
        copieMatrix(Matrix,Mat4);
        
        int scoreBase1,scoreBase2,scoreBase3,scoreBase4;
        int averageScore1,averageScore2,averageScore3,averageScore4;
        int a=0,b=0,c=0,d=0;
        int scoreMax=0;
        int changementScore1=0,changementScore2=0,changementScore3=0,changementScore4=0;

        for(i=0;i<NbEssaiAI;i++)
        {
            
            scoreBase1=0;scoreBase2=0;scoreBase3=0;scoreBase4=0;

            copieMatrix(Matrix,Mat1);
            copieMatrix(Matrix,Mat2);
            copieMatrix(Matrix,Mat3);
            copieMatrix(Matrix,Mat4);

            scoreBase1 += Right(Mat1,donnees,scoreBase1,1);//on commence la partie par le mouvement droite
            scoreBase2 += Left(Mat2,donnees,scoreBase2,1);//on commence la partie par le mouvement gauche
            scoreBase3 += Down(Mat3,donnees,scoreBase3,1);//on commence la partie par le mouvement bas
            scoreBase4 += Up(Mat4,donnees,scoreBase4,1);//on commence la partie par le mouvement haut

             if (!(changement(Mat1,Matrix)))
                changementScore1=1;//Changement score vaut 1 si changement 0 sinon
            
            if (!(changement(Mat2,Matrix)))
                changementScore2=1;

            if (!changement(Mat3,Matrix))
                changementScore3=1;

            if (!(changement(Mat4,Matrix)))
            {
                changementScore4=1;
            }

            copieMatrix(Mat1,Mat);
            if(changement(Mat,Mat1))// si on a un changement on rajoute une tuile aléatoirement
            {
                aleatoire(Mat1);
            }
            copieMatrix(Mat2,Mat);
            if(changement(Mat,Mat2))
            {
                aleatoire(Mat2);
            }
            copieMatrix(Mat3,Mat);
            if(changement(Mat,Mat3))
            {
                aleatoire(Mat3);
            }
            copieMatrix(Mat4,Mat);
            if(changement(Mat,Mat4))
            {
                aleatoire(Mat4);
            }

            while (!(perdJeu(Mat1))&&(!(changementScore1)))// on simule une partie
            {
                copieMatrix(Mat1,Mat);
                scoreBase1 += ScoreforAI(Mat1,donnees);
                    
                if(changement(Mat,Mat1))
                {
                    aleatoire(Mat1);
                }
            }
            Tab[0][i]=scoreBase1; // on stocke le score de la partie dans un tableau de 2dimension 4*NbEssai
            

            while (!(perdJeu(Mat2))&&(!(changementScore2)))
            {
                copieMatrix(Mat2,Mat);
                scoreBase2 += ScoreforAI(Mat2,donnees);
                    
                if(changement(Mat,Mat2))
                {
                    aleatoire(Mat2);
                }
            }
            Tab[1][i]=scoreBase2;

            while (!(perdJeu(Mat3))&&(!(changementScore3)))
            {
                copieMatrix(Mat3,Mat);
                scoreBase3 += ScoreforAI(Mat3,donnees);
                    
                if(changement(Mat,Mat3))
                {
                    aleatoire(Mat3);
                }
            }
            Tab[2][i]=scoreBase3;

            while (!(perdJeu(Mat4))&&(!(changementScore4)))
            {
                copieMatrix(Mat4,Mat);
                scoreBase4 += ScoreforAI(Mat4,donnees);
                    
                if(changement(Mat,Mat4))
                {
                    aleatoire(Mat4);
                }
            }
            Tab[3][i]=scoreBase4;
        }

        for (i = 0; i < NbEssaiAI; i++)//on fait la moyenne des score pour chaque mouvement
        {
            a+=Tab[0][i];
            b+=Tab[1][i];
            c+=Tab[2][i];
            d+=Tab[3][i];
        }
        averageScore1=a/NbEssaiAI;
        averageScore2=b/NbEssaiAI;
        averageScore3=c/NbEssaiAI;
        averageScore4=d/NbEssaiAI;
        

        scoreMax=averageScore1;
        if (scoreMax<averageScore2)
            scoreMax=averageScore2;
        
        if (scoreMax<averageScore3)
            scoreMax=averageScore3;

        if (scoreMax<averageScore4)
            scoreMax=averageScore4;
    
        
        if (scoreMax==averageScore1) // on effectue le mouvement qui aura obtenue une moyenne de score la plus élevée
            Right(Matrix,donnees,0,0);
        else if (scoreMax==averageScore2)
            Left(Matrix,donnees,0,0);

        else if (scoreMax==averageScore3)
            Down(Matrix,donnees,0,0);

        else if (scoreMax==averageScore4)
            Up(Matrix,donnees,0,0);
    
        aleatoire(Matrix);
        

        
        effacerTableau();
        afficherFondSon(donnees,img,fond);
        afficherScoreIA(img,coordXscore,donnees);
        meilleurScore(*donnees,donnees);
        afficherBestScoreIA(img,coordXbestScore,donnees);
        imgNombre(Matrix,img);
        
        
    }

}


/*---------------------------------------------------------------------------------------------------------------------------------------*/



    
void help(int Matrix[][SIZE],int Mat[][SIZE],donnees_t img,donnees_t *donnees)// fonction d'aide ponctuelle
{
    //même fonctionnement que l'AI sauf qu'elle n'effectue pas de changement, affiche une image en fct  du mouvement avec le score le plus élevé
        int scoreMax=0;
        int Mat1[SIZE][SIZE];
        int Mat2[SIZE][SIZE];
        int Mat3[SIZE][SIZE];
        int Mat4[SIZE][SIZE];
        int i=0;
        int Tab[4][NbEssaiAI];

    
        copieMatrix(Matrix,Mat1);
        copieMatrix(Matrix,Mat2);
        copieMatrix(Matrix,Mat3);
        copieMatrix(Matrix,Mat4);
        
        int scoreBase1,scoreBase2,scoreBase3,scoreBase4;
        int averageScore1,averageScore2,averageScore3,averageScore4;
        int a=0,b=0,c=0,d=0;
        int changementScore1=0,changementScore2=0,changementScore3=0,changementScore4=0;
        

        for(i=0;i<NbEssaiAI;i++)
        {
            
            scoreBase1=0;scoreBase2=0;scoreBase3=0;scoreBase4=0;

            copieMatrix(Matrix,Mat1);
            copieMatrix(Matrix,Mat2);
            copieMatrix(Matrix,Mat3);
            copieMatrix(Matrix,Mat4);

            scoreBase1 += Right(Mat1,donnees,scoreBase1,1);
            scoreBase2 += Left(Mat2,donnees,scoreBase2,1);
            scoreBase3 += Down(Mat3,donnees,scoreBase3,1);
            scoreBase4 += Up(Mat4,donnees,scoreBase4,1);

            if (!(changement(Mat1,Matrix)))
                changementScore1=1;
            
            if (!(changement(Mat2,Matrix)))
                changementScore2=1;

            if (!changement(Mat3,Matrix))
                changementScore3=1;

            if (!(changement(Mat4,Matrix)))
                changementScore4=1;

            copieMatrix(Mat1,Mat);
            if(changement(Mat,Mat1))
            {
                aleatoire(Mat1);
            }
            copieMatrix(Mat2,Mat);
            if(changement(Mat,Mat2))
            {
                aleatoire(Mat2);
            }
            copieMatrix(Mat3,Mat);
            if(changement(Mat,Mat3))
            {
                aleatoire(Mat3);
            }
            copieMatrix(Mat4,Mat);
            if(changement(Mat,Mat4))
            {
                aleatoire(Mat4);
            }

            while (!(perdJeu(Mat1))&&!(gagneJeu(Mat1))&&(!(changementScore1)))
            {
                copieMatrix(Mat1,Mat);
                scoreBase1 += ScoreforAI(Mat1,donnees);
                    
                if(changement(Mat,Mat1))
                {
                    aleatoire(Mat1);
                }
            }
            Tab[0][i]=scoreBase1;
            

            while (!(perdJeu(Mat2))&&!(gagneJeu(Mat2))&&(!(changementScore2)))
            {
                copieMatrix(Mat2,Mat);
                scoreBase2 += ScoreforAI(Mat2,donnees);
                    
                if(changement(Mat,Mat2))
                {
                    aleatoire(Mat2);
                }
            }
            Tab[1][i]=scoreBase2;

            while (!(perdJeu(Mat3))&&!(gagneJeu(Mat3))&&(!(changementScore3)))
            {
                copieMatrix(Mat3,Mat);
                scoreBase3 += ScoreforAI(Mat3,donnees);
                    
                if(changement(Mat,Mat3))
                {
                    aleatoire(Mat3);
                }
            }
            Tab[2][i]=scoreBase3;

            while (!(perdJeu(Mat4))&&!(gagneJeu(Mat4))&&(!(changementScore4)))
            {
                copieMatrix(Mat4,Mat);
                scoreBase4 += ScoreforAI(Mat4,donnees);
                    
                if(changement(Mat,Mat4))
                {
                    aleatoire(Mat4);
                }
            }
            Tab[3][i]=scoreBase4;
        }

        for (i = 0; i < NbEssaiAI; i++)
        {
            a+=Tab[0][i];
            b+=Tab[1][i];
            c+=Tab[2][i];
            d+=Tab[3][i];
        }
        averageScore1=a/NbEssaiAI;
        averageScore2=b/NbEssaiAI;
        averageScore3=c/NbEssaiAI;
        averageScore4=d/NbEssaiAI;

        
        

        scoreMax=averageScore1;
        

         if (scoreMax<averageScore2)
            scoreMax=averageScore2;
        
        if (scoreMax<averageScore3)
            scoreMax=averageScore3;

        if (scoreMax<averageScore4)
            scoreMax=averageScore4;
    
        
        if (scoreMax==averageScore1)
            afficherImage(img.rightArrow,-403,110);
    
        
        else if (scoreMax==averageScore2)
            afficherImage(img.leftArrow,-403,110);
            

        else if (scoreMax==averageScore3)
            afficherImage(img.downArrow,-403,110);

        else if (scoreMax==averageScore4)
            afficherImage(img.upArrow,-403,110);

        tamponner();
        attendreNms(400);
    
        
}
//fonction qui prend un chosis aleatoirement un chiffre entre 1 et 4 puis qui execute un mouvement en fonction du chiffre puis retourne le score du mouvement 
int ScoreforAI(int Mat[][SIZE],donnees_t *donnees)
{
    
    int score=0;
    int nb;
    nb=(rand()%(5)+1);
    
    if(nb==2)
    {
        score+=Right(Mat,donnees,score,1);
        
        
    }
    if (nb==1)
    {
        score+=Left(Mat,donnees,score,1);
        
        
    }
    if (nb==3)
    {
        score+=Down(Mat,donnees,score,1);
        
        
    }
    if (nb==4)
    {
        score+=Up(Mat,donnees,score,1);

      
    }
    return score;
    
}



void afficherScoreIA(donnees_t img,int coordX,donnees_t *donnees)//affiche le score durant le fonctionnement de l'AI
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
    int stock=donnees->Score;
    for (int i=0; i<5; ++i) 
    { 
        afficherImage(img.SCORE[stock%10],coordX-temp,285);
        stock/=10;
        temp+=20;
    }
    
}


void afficherBestScoreIA(donnees_t img,int coordX,donnees_t *donnees)//affiche le meilleur score durant le fonctionnement de l'AI
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
    int stock=donnees->bestScore;
    for (int i=0; i<5; ++i) 
    { 
        afficherImage(img.SCORE[stock%10],coordX-temp,285);
        stock/=10;
        temp+=20;
    }
    
}
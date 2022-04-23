#include <stdlib.h>
#include <stdio.h>
#include "libTableauNoir.h"
#include "src/fct.h"
#include <time.h> 
#include "src/IA.h"



int main(){
    
    creerTableau();
    fixerModeBufferisation(1);
    fixerTaille(1600,900);
    donnees_t img=chargement();
    srand(time(NULL));
    img.bestScore=0;
    int i,j;
    int fond;
    afficherImage(img.commande,-800,450);
    tamponner();
    attendreNms(3000);
    menu(img,&fond);
    while(1)
    {
        int Matrix[SIZE][SIZE];
        
        for(i=0;i < SIZE;i++)
        {
            for(j=0;j < SIZE;j++)
            {
                Matrix[i][j]=0;
            }
        }

        int Mat[SIZE][SIZE];
        int Tab[SIZE][SIZE];
        img.Score =0;
        const int coordXscore=-126;
        const int coordXbestScore=122;
        int exe=1;
        int stop=0;
        
        int scoreCopie=0;

        
        aleatoire(Matrix);
        afficherFondSon(&img,img,fond);
        

        
            while (!(gagneJeu(Matrix))&&!(perdJeu(Matrix)))
            {
                
                scoreCopie=img.Score;
                afficherScore(img,coordXscore);
                meilleurScore(img,&img);
                afficherBestScore(img,coordXbestScore);
                imgNombre(Matrix,img);
                copieMatrix(Matrix,Mat);
                
                if(exe==1)
                {
                
                toucheClavier(Matrix,Mat,&img,&exe,fond); 
                  
                }else if(exe==0)
                {
                    AI(Matrix,Tab,&stop,fond,img,&img);
                    exe=1;
                    if (stop==1)
                    {
                        stop=0;
                        continue;
                    }else
                        break;

                    
                }else if(exe==2)
                {
                    help(Matrix,Tab,img,&img);
                    exe=1;
                }
                if(changement(Mat,Matrix))
                {   
                
                    if(scoreCopie==img.Score)
                    {
                        img.audioDecalage=jouerSon(img.decalage,0);
                        if(img.sonCoupe % 2 == 0)
                            volumePiste(img.audioDecalage,0.75);
                        else
                            volumePiste(img.audioDecalage,0);
                    }else
                    {
                        img.audioAssemblage=jouerSon(img.assemblage,0);
                        if(img.sonCoupe % 2 == 0){
                        volumePiste(img.audioAssemblage,0.75);
                        }else{
                        volumePiste(img.audioAssemblage,0);
                        }
                    } 
                    
                }
                  
                effacerTableau();
                afficherFondSon(&img,img,fond);
               
                if(changement(Mat,Matrix))
                    aleatoire(Matrix);
                
            }
            
        effacerTableau();
        afficherFondSon(&img,img,fond);
        imgNombre(Matrix,img);
        if (gagneJeu(Matrix))
        {
            img.Win = jouerSon(img.victoire,0);
            if(img.sonCoupe % 2 == 0){
                volumePiste(img.Win,0.75);
            }else{
                volumePiste(img.Win,0);
            }
            afficherImage(img.gagne,-170,148);
            afficherImage(img.quit,-45,-170);
            afficherImage(img.restart,-45,-90);
            afficherImage(img.conf6,-400,300);
            
        }else
        {
            afficherImage(img.perd,-170,148);
            afficherImage(img.quit,-45,-170);
            afficherImage(img.restart,-45,-90);
        }
        afficherScore(img,coordXscore);
        meilleurScore(img ,&img);
        afficherScore(img,coordXbestScore);

        tamponner();
        
        if (rejoue(Matrix,img)){
            break;
        }
    }
    
    
    return 0;
}


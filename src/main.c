#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include <ANCELMO/chiffres.h>
#include <ANCELMO/lettres.h>

#define LARGEUR_ECRAN 750
#define HAUTEUR_ECRAN 500

typedef struct 
{
    int x,y;
}def_serpent;


void arret_avec_erreur(const char *message_d_erreur);

int main(int argc, char **argv)
{
    int HauteurScore = 60, compteur = 0, scOre = 0, GrandFruit = 0, GrandFruitMoment = 200, TempsAffichageBonus = 0;
    int LARGEUR = LARGEUR_ECRAN, HAUTEUR = HAUTEUR_ECRAN - HauteurScore;
    SDL_Window *fenetre = SDL_CreateWindow("Ancelmo Snake Jeu",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,LARGEUR,HAUTEUR,SDL_WINDOW_SHOWN);
    SDL_Renderer *rendu = SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_ACCELERATED);

    if (SDL_Init(SDL_INIT_EVERYTHING)!=0)
        arret_avec_erreur("Erreur lors de l'ouverture de la SDL.");
    
    if (fenetre==NULL || rendu == NULL)
        arret_avec_erreur("Erreur lors de la creation de la fenetre et du rendu");
    
    //lecture du mzilleure score
    FILE *fichier = fopen("bin/MeilleureScore.txt","r");
    if (fichier==NULL)
        arret_avec_erreur("Erreur Lors de L'ouverture du fichier Meilleure Score");
    char lecture[25];
    fgets(lecture,30,fichier);
    int ScoreLu = SrtToInt(lecture);
    fclose(fichier);

    float L= HauteurScore/2;
    bool jeu_en_cours=true, Pause = false, Bonus = false;
    SDL_Event action;
    int vitesse=6,dx=vitesse,dy=0,taille_serpent=2,TailleFragmentSerpent=5,TailleFruit=5;
    int r=100,v=100,b=100;
    def_serpent *serpent = (def_serpent*)malloc(taille_serpent*sizeof(def_serpent));
    int CoordFruit[2];
    CoordFruit[1]=0;
    CoordFruit[0]=0;
    serpent[0].y = HAUTEUR - 10;
    SDL_bool VerificationMorsure = false;
    int dxPrime =0, dyPrime = 0;
    //la, c la boucle de jeu en bonne et due forme
    while (jeu_en_cours)
    {
        while (SDL_PollEvent(&action))
        {
            if (action.type==SDL_QUIT)
            {
                // condition de sortie
                jeu_en_cours=false;
            }
            if (action.type==SDL_KEYDOWN && !VerificationMorsure)
            {
                //la, on gere les deplacements
                switch (action.key.keysym.sym)
                {
                    case SDLK_UP :
                    {
                        if (dy==0)
                        {
                            dx=0;
                            dy=-vitesse;
                        }
                    }break;
                    case SDLK_DOWN :
                    {
                        if (dy==0)
                        {
                            dx=0;
                            dy=vitesse;
                        }
                    }break;
                    case SDLK_LEFT :
                    {
                        if (dx==0)
                        {
                            dy=0;
                            dx=-vitesse;
                        }
                    }break;
                    case SDLK_RIGHT :
                    {
                        if (dx==0)
                        {
                            dy=0;
                            dx=vitesse;
                        }
                    }break;
                    case SDLK_SPACE :
                    {
                        if (Pause){
                            Pause = false;
                            dx = dxPrime, dy = dyPrime;
                        }
                        else{
                            Pause = true;
                            dxPrime = dx, dyPrime = dy ,dx = 0, dy = 0; 
                        }
                    }break;
                }
            }
            
        }
        // bon, la c pour definir la couleur du rendu en rgb et ensuite on met le clear (je ne sais pas encore bien a qw ca sert)
        SDL_SetRenderDrawColor(rendu,0,0,0,255); //couleur noir
        SDL_RenderClear(rendu);

        //permettre le deplacement
        serpent[0].x+= dx;
        serpent[0].y+= dy;

        
        if (compteur>=10)
        {
            compteur = 0;
            r =  1 + rand() % 255;
            v =  1 + rand() % 255;
            b =  1 + rand() % 255;
        }
        
        //gerer les deplacements du serpent (sa tete plutot) hors du cadre
        if (serpent[0].x >=LARGEUR)
            serpent[0].x=0;
        if (serpent[0].x<0)
            serpent[0].x=LARGEUR;
        if (serpent[0].y >=HAUTEUR)
            serpent[0].y=0;
        if (serpent[0].y<0)
            serpent[0].y=HAUTEUR;

        // mettre a jour le deplacement de tout les segments du serpent
        for (int i = taille_serpent-1; i > 0 && !VerificationMorsure && !Pause; i--)
        {
            serpent[i].x=serpent[i-1].x;
            serpent[i].y=serpent[i-1].y;
        }
        // verifier si le sysyteme est en pause
        if (Pause)
        {
            TempsAffichageBonus++;
            float X = 0, Y =0;
            int LongueurMessage = AffichageMot(0,"PAUSE",X,Y,80,r,v,b,5,rendu);
            X = (LARGEUR_ECRAN - LongueurMessage)/2, Y = (HAUTEUR - 80)/2;
            AffichageMot(1,"PAUSE",X,Y,80,r,v,b,5,rendu);        
        }
        
        
        //dessine le serpent
        for (int i = 0; i < taille_serpent; i++)
        {
            SDL_SetRenderDrawColor(rendu,r,v,b,255);
            SDL_Rect FragmentSerpent = {serpent[i].x,serpent[i].y,TailleFragmentSerpent,TailleFragmentSerpent};
            SDL_RenderFillRect(rendu,&FragmentSerpent);
        }

        // generation de coordonnee aleatoire
        srand(time(NULL));
        while (!((CoordFruit[0]>TailleFruit && CoordFruit[0]<=LARGEUR-TailleFruit) && (CoordFruit[1]>TailleFruit+HauteurScore && CoordFruit[1]<HAUTEUR-TailleFruit)))
        {
            CoordFruit[0]=1+ rand() % LARGEUR;
            CoordFruit[1]=1+ rand() % HAUTEUR;
        }
        
        // dessine le point 
        SDL_SetRenderDrawColor(rendu,r,v,b,255);
        SDL_Rect FruitDuSerpent = {CoordFruit[0],CoordFruit[1],TailleFruit,TailleFruit};
        SDL_RenderFillRect(rendu,&FruitDuSerpent);

        GrandFruit++;
        double distance2 = 0, distanceX2 = 0, distanceY2 = 0;
        if (GrandFruit == GrandFruitMoment)
        {
            Bonus = true;
            
        }
        
        if (Bonus)
        {
            
            GrandFruitMoment++, GrandFruit = 0 ;
            SDL_SetRenderDrawColor(rendu,r,v,b,255);
            SDL_Rect GrandFruitRect = {(int)fabs(CoordFruit[0]-LARGEUR),(int)fabs(CoordFruit[1]-HAUTEUR),TailleFruit*3,TailleFruit*3};
            SDL_RenderFillRect(rendu,&GrandFruitRect);
            
            distanceX2 = serpent[0].x - fabs(CoordFruit[0]-LARGEUR), distanceY2 = serpent[0].y - fabs(CoordFruit[1]-HAUTEUR);
            distance2 = sqrt(distanceX2*distanceX2 + distanceY2*distanceY2);
            if (distance2<10)
            {
                scOre+= 6;
                compteur+=6;
                
                taille_serpent += 6;
                serpent = (def_serpent *)realloc(serpent, taille_serpent * sizeof(def_serpent));
                Bonus = false;
            }
            TempsAffichageBonus++;
        }
        
        if (TempsAffichageBonus == 100)
        {
            Bonus = false;
            TempsAffichageBonus = 0;
        }
        
        // verification de la consommation du fruit par le serpent
        //pour cela, on compare la distance entre le fruit et le centre de la tete du serpent
        double distance=0,distanceX=0,distanceY=0;
        distanceX=serpent[0].x-CoordFruit[0];
        distanceY=serpent[0].y-CoordFruit[1];

        distance=sqrt(distanceX*distanceX + distanceY*distanceY);
        if (distance<8)
        {
            scOre++;
            compteur++;
            CoordFruit[0]=0;
            CoordFruit[1]=0;
            while (!((CoordFruit[0]>TailleFruit && CoordFruit[0]<=LARGEUR-TailleFruit) && (CoordFruit[1]>TailleFruit && CoordFruit[1]<HAUTEUR-TailleFruit)))
            {
                CoordFruit[0]=1+ rand() % LARGEUR;
                CoordFruit[1]=1+ rand() % HAUTEUR;
            }
            taille_serpent++;
            serpent = (def_serpent *)realloc(serpent, taille_serpent * sizeof(def_serpent));
        }
        
        SDL_SetRenderDrawColor(rendu,r,v,b,255);
        SDL_Rect score = {0,0,LARGEUR_ECRAN,HauteurScore};
        SDL_RenderFillRect(rendu,&score);
        float PositionScoreX = 10, PositionScoreY = 10;
        
        AffichageNombre(taille_serpent-2,PositionScoreX,PositionScoreY,HauteurScore,0,0,0,3.1,rendu);
        
        L = AffichageNombre(ScoreLu,LARGEUR - L - 10,10,HauteurScore,0,0,0,3.1,rendu);
        // gestion de la frame et de la presentation du rendu

        // VERIFIACTION DE L'AUTOMORSURE DU SERPENT 
        for (int i = 2; i < taille_serpent ; i++)
        {
            if (serpent[i].x == serpent[0].x && serpent[i].y == serpent[0].y)
            {
                VerificationMorsure = true;
                dx = 0;
                dy = 0;
                float X = 0, Y = 0;
                int LongueurMessage = AffichageMot(0,"GAME OVER",X,Y,80,r,v,b,5,rendu);
                X = (LARGEUR_ECRAN - LongueurMessage)/2, Y = (HAUTEUR - 80)/2;
                AffichageMot(1,"GAME OVER",X,Y,80,r,v,b,5,rendu);
            }
        }
        

        SDL_Delay(100);
        SDL_RenderPresent(rendu);
    }
    
    if (ScoreLu<scOre)
    {
        FILE *fichier1 = fopen("bin/MeilleureScore.txt","w");
        if (fichier1==NULL)
            arret_avec_erreur("Erreur Lors de L'ouverture du fichier Meilleure Score");

        fprintf(fichier1,"%d",scOre);
        fclose(fichier1);
    }
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}

void arret_avec_erreur(const char *message_d_erreur)
{
    SDL_Log("Erreur Identifie !\n\tNature -> %s \n",message_d_erreur);
    SDL_Quit();
    exit(EXIT_FAILURE);
}

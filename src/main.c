#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define LARGEUR 600
#define HAUTEUR 350

typedef struct 
{
    int x,y;
}def_serpent;


void arret_avec_erreur(const char *message_d_erreur);

int main(int argc, char **argv)
{
    SDL_Window *fenetre = NULL;
    SDL_Renderer *rendu = NULL;

    if (SDL_Init(SDL_INIT_EVERYTHING)!=0)
        arret_avec_erreur("Erreur lors de l'ouverture de la SDL.");
    
    if (SDL_CreateWindowAndRenderer(LARGEUR,HAUTEUR,0,&fenetre,&rendu)!=0)
        arret_avec_erreur("Erreur lors de la creation de la fenetre et du rendu.");
    
    bool jeu_en_cours=true;
    SDL_Event action;
    int vitesse=7,dx=vitesse,dy=0,taille_serpent=2,TailleFragmentSerpent=5,TailleFruit=5;
    int r=0,v=0,b=0;
    def_serpent *serpent = (def_serpent*)malloc(taille_serpent*sizeof(def_serpent));
    int CoordFruit[2];
    CoordFruit[1]=0;
    CoordFruit[0]=0;

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
            if (action.type==SDL_KEYDOWN)
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
                }
            }
            
        }
        // bon, la c pour definir la couleur du rendu en rgb et ensuite on met le clear (je ne sais pas encore bien a qw ca sert)
        SDL_SetRenderDrawColor(rendu,0,0,0,255); //couleur noir
        SDL_RenderClear(rendu);

        //permettre le deplacement
        serpent[0].x+= dx;
        serpent[0].y+= dy;
        if (taille_serpent<10)
        {
            r=0;
            v=0;
            b=255;
        }
        else if (taille_serpent>=10 && taille_serpent<50)
        {
            r=0;
            v=255;
            b=0;
        }
        else
        {
            r=255;
            v=0;
            b=0;
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
        for (int i = taille_serpent-1; i > 0; i--)
        {
            serpent[i].x=serpent[i-1].x;
            serpent[i].y=serpent[i-1].y;
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
        while (!((CoordFruit[0]>TailleFruit && CoordFruit[0]<=LARGEUR-TailleFruit) && (CoordFruit[1]>TailleFruit && CoordFruit[1]<HAUTEUR-TailleFruit)))
        {
            CoordFruit[0]=1+ rand() % LARGEUR;
            CoordFruit[1]=1+ rand() % HAUTEUR;
        }
        
        // dessine le point 
        SDL_SetRenderDrawColor(rendu,r,v,b,255);
        SDL_Rect FruitDuSerpent = {CoordFruit[0],CoordFruit[1],TailleFruit,TailleFruit};
        SDL_RenderFillRect(rendu,&FruitDuSerpent);

        // verification de la consommation du fruit par le serpent
        //pour cela, on compare la distance entre le fruit et le centre de la tete du serpent
        double distance=0,distanceX=0,distanceY=0;
        distanceX=serpent[0].x-CoordFruit[0];
        distanceY=serpent[0].y-CoordFruit[1];

        distance=sqrt(distanceX*distanceX + distanceY*distanceY);
        if (distance<8)
        {
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
        
        // gestion de la frame et de la presentation du rendu
        SDL_Delay(100);
        SDL_RenderPresent(rendu);
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

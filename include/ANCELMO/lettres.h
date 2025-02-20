#ifndef LETTRES_H
#define LETTRES_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include <ANCELMO/chiffres.h>

void ConversionMajuscule(char chaine[]);
void SortieAvecErreur(const char *message);
void DessinBarreRectangulaire (float Epaisseur,float Xd, float Yd,float Xf, float Yf, int ColorRed, int ColorGreen, int ColorBlue,SDL_Renderer *rendu);
void DessinLettre(char Lettre, float Epaisseur, float Xa,float Ya,float Xb,float Yb,float Xc,float Yc,float Xd,float Yd, int ColorRed, int ColorGreen, int ColorBlue,SDL_Renderer *rendu);
int AffichageMot(int setting,char mot[],float PositionX, float PositionY, float HauteurAffichage, int ColorRed, int ColorGreen, int ColorBlue,float Epaisseur, SDL_Renderer *rendu);

void DessinBarreRectangulaire (float Epaisseur,float Xd, float Yd,float Xf, float Yf, int ColorRed, int ColorGreen, int ColorBlue,SDL_Renderer *rendu)
{
    double Phi = (atan((Yf - Yd)/(Xf - Xd))),L = Epaisseur, d = (Epaisseur/2)*sqrt(3);
    double Xm = Xd + d*cos(Phi), Ym = Yd + d*sin(Phi), Xb = Xm - (L/2)*sin(Phi), Yb = Ym + (L/2)*cos(Phi);
    double Xc = Xm + (L/2)*sin(Phi), Yc = Ym - (L/2)*cos(Phi);
    double Lr =  sqrt((Xd-Xf)*(Xd-Xf) + (Yd-Yf)*(Yd-Yf)) - 2*d ;
    SDL_SetRenderDrawColor(rendu,ColorRed,ColorGreen,ColorBlue,255);
    DessinTriangle(Xd,Yd,Xb,Yb,Xc,Yc,rendu);

    double Xg = Xb + Lr*cos(Phi), Yg = Yb + Lr*sin(Phi), Xe = Xc+Lr*cos(Phi),Ye = Yc + Lr*sin(Phi);
    DessinTriangle(Xe,Ye,Xg,Yg,Xf,Yf,rendu);
    DessinerRectangle(Xc,Yc,Xb,Yb,Xg,Yg,Xe,Ye,rendu);
}
void DessinLettre(char Lettre, float Epaisseur, float Xa,float Ya,float Xb,float Yb,float Xc,float Yc,float Xd,float Yd, int ColorRed, int ColorGreen, int ColorBlue,SDL_Renderer *rendu)
{
    float X9 = ((Xa+Xb)/2+(Xc+Xd)/2)/2, Y9 = ((Ya+Yb)/2+(Yc+Yd)/2)/2;
    if (Lettre == 'A')
    {
        // Barre A
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre B
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre C
        DessinBarreRectangulaire(Epaisseur,Xb,Yb,(Xc+Xb)/2,(Yc+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre D
        DessinBarreRectangulaire(Epaisseur,(Xb+Xc)/2,(Yb+Yc)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre L
        DessinBarreRectangulaire(Epaisseur,X9,Y9,(Xb+Xc)/2,(Yb+Yc)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre P
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
    }
    else if(Lettre == 'B')
    {
        // Barre A
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre B
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre C
        DessinBarreRectangulaire(Epaisseur,Xb,Yb,(Xc+Xb)/2,(Yc+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre D
        DessinBarreRectangulaire(Epaisseur,(Xb+Xc)/2,(Yb+Yc)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre E
        DessinBarreRectangulaire(Epaisseur,(Xc+Xd)/2,(Yc+Yd)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre F
        DessinBarreRectangulaire(Epaisseur,Xd,Yd,(Xc+Xd)/2,(Yc+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre L
        DessinBarreRectangulaire(Epaisseur,X9,Y9,(Xb+Xc)/2,(Yb+Yc)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre P
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
    }
    else if(Lettre == 'C')
    {
        // Barre A
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre B
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre E
        DessinBarreRectangulaire(Epaisseur,(Xc+Xd)/2,(Yc+Yd)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre F
        DessinBarreRectangulaire(Epaisseur,Xd,Yd,(Xc+Xd)/2,(Yc+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if(Lettre == 'D' || Lettre == 'O')
    {
        // Barre A
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre B
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre C
        DessinBarreRectangulaire(Epaisseur,Xb,Yb,(Xc+Xb)/2,(Yc+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre D
        DessinBarreRectangulaire(Epaisseur,(Xb+Xc)/2,(Yb+Yc)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre E
        DessinBarreRectangulaire(Epaisseur,(Xc+Xd)/2,(Yc+Yd)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre F
        DessinBarreRectangulaire(Epaisseur,Xd,Yd,(Xc+Xd)/2,(Yc+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if (Lettre == 'E')
    {
        // Barre A
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre B
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre E
        DessinBarreRectangulaire(Epaisseur,(Xc+Xd)/2,(Yc+Yd)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre F
        DessinBarreRectangulaire(Epaisseur,Xd,Yd,(Xc+Xd)/2,(Yc+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre P
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if(Lettre == 'F')
    {
        // Barre A
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre B
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre P
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if(Lettre ==  'G')
    {
        // Barre A
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre B
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre D
        DessinBarreRectangulaire(Epaisseur,(Xb+Xc)/2,(Yb+Yc)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre E
        DessinBarreRectangulaire(Epaisseur,(Xc+Xd)/2,(Yc+Yd)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre F
        DessinBarreRectangulaire(Epaisseur,Xd,Yd,(Xc+Xd)/2,(Yc+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre L
        DessinBarreRectangulaire(Epaisseur,X9,Y9,(Xb+Xc)/2,(Yb+Yc)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if(Lettre == 'H')
    {
        // Barre C
        DessinBarreRectangulaire(Epaisseur,Xb,Yb,(Xc+Xb)/2,(Yc+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre D
        DessinBarreRectangulaire(Epaisseur,(Xb+Xc)/2,(Yb+Yc)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre L
        DessinBarreRectangulaire(Epaisseur,X9,Y9,(Xb+Xc)/2,(Yb+Yc)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre P
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if(Lettre == 'I')
    {
        // Barre E
        DessinBarreRectangulaire(Epaisseur,(Xc+Xd)/2,(Yc+Yd)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre F
        DessinBarreRectangulaire(Epaisseur,Xd,Yd,(Xc+Xd)/2,(Yc+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre A
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre B
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre N
        DessinBarreRectangulaire(Epaisseur,X9,Y9,(Xd+Xc)/2,(Yd+Yc)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre J
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if(Lettre == 'J')
    {
        // Barre A
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre B
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre J
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre N
        DessinBarreRectangulaire(Epaisseur,X9,Y9,(Xd+Xc)/2,(Yd+Yc)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre F
        DessinBarreRectangulaire(Epaisseur,Xd,Yd,(Xc+Xd)/2,(Yc+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if(Lettre == 'K')
    {
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre K
        DessinBarreRectangulaire(Epaisseur,X9,Y9,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre M
        DessinBarreRectangulaire(Epaisseur,X9,Y9,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre P
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if(Lettre == 'L')
    {
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre E
        DessinBarreRectangulaire(Epaisseur,(Xc+Xd)/2,(Yc+Yd)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre F
        DessinBarreRectangulaire(Epaisseur,Xd,Yd,(Xc+Xd)/2,(Yc+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if(Lettre == 'M')
    {
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre C
        DessinBarreRectangulaire(Epaisseur,Xb,Yb,(Xc+Xb)/2,(Yc+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre D
        DessinBarreRectangulaire(Epaisseur,(Xb+Xc)/2,(Yb+Yc)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre I
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre K
        DessinBarreRectangulaire(Epaisseur,X9,Y9,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if(Lettre == 'N')
    {
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre C
        DessinBarreRectangulaire(Epaisseur,Xb,Yb,(Xc+Xb)/2,(Yc+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre D
        DessinBarreRectangulaire(Epaisseur,(Xb+Xc)/2,(Yb+Yc)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre I
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre M
        DessinBarreRectangulaire(Epaisseur,X9,Y9,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if(Lettre == 'P')
    {
        // Barre A
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre B
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre C
        DessinBarreRectangulaire(Epaisseur,Xb,Yb,(Xc+Xb)/2,(Yc+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre L
        DessinBarreRectangulaire(Epaisseur,X9,Y9,(Xb+Xc)/2,(Yb+Yc)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre P
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if(Lettre == 'Q')
    {
        // Barre A
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre B
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre C
        DessinBarreRectangulaire(Epaisseur,Xb,Yb,(Xc+Xb)/2,(Yc+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre D
        DessinBarreRectangulaire(Epaisseur,(Xb+Xc)/2,(Yb+Yc)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre E
        DessinBarreRectangulaire(Epaisseur,(Xc+Xd)/2,(Yc+Yd)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre F
        DessinBarreRectangulaire(Epaisseur,Xd,Yd,(Xc+Xd)/2,(Yc+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre M
        DessinBarreRectangulaire(Epaisseur,X9,Y9,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if(Lettre == 'R')
    {
        // Barre A
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre B
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre C
        DessinBarreRectangulaire(Epaisseur,Xb,Yb,(Xc+Xb)/2,(Yc+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre L
        DessinBarreRectangulaire(Epaisseur,X9,Y9,(Xb+Xc)/2,(Yb+Yc)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre M
        DessinBarreRectangulaire(Epaisseur,X9,Y9,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre P
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if (Lettre == 'S')
    {
        // Barre A
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre B
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre D
        DessinBarreRectangulaire(Epaisseur,(Xb+Xc)/2,(Yb+Yc)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre E
        DessinBarreRectangulaire(Epaisseur,(Xc+Xd)/2,(Yc+Yd)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre F
        DessinBarreRectangulaire(Epaisseur,Xd,Yd,(Xc+Xd)/2,(Yc+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre L
        DessinBarreRectangulaire(Epaisseur,X9,Y9,(Xb+Xc)/2,(Yb+Yc)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre P
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if (Lettre == 'T')
    {
        // Barre A
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre B
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre J
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre N
        DessinBarreRectangulaire(Epaisseur,X9,Y9,(Xd+Xc)/2,(Yd+Yc)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if (Lettre == 'U')
    {
        // Barre C
        DessinBarreRectangulaire(Epaisseur,Xb,Yb,(Xc+Xb)/2,(Yc+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre D
        DessinBarreRectangulaire(Epaisseur,(Xb+Xc)/2,(Yb+Yc)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre E
        DessinBarreRectangulaire(Epaisseur,(Xc+Xd)/2,(Yc+Yd)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre F
        DessinBarreRectangulaire(Epaisseur,Xd,Yd,(Xc+Xd)/2,(Yc+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if (Lettre == 'V')
    {
        //Pour le V, des barres speciales s'ajoutent
        // Barre C
        DessinBarreRectangulaire(Epaisseur,Xb,Yb,(Xc+Xb)/2,(Yc+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre X
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,(Xc+Xd)/2,(Yc+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre Y 
        DessinBarreRectangulaire(Epaisseur,(Xc+Xd)/2,(Yc+Yd)/2,(Xb+Xc)/2,(Yb+Yc)/2,ColorRed,ColorGreen,ColorBlue,rendu);
    }
    else if (Lettre == 'W')
    {
        // Barre C
        DessinBarreRectangulaire(Epaisseur,Xb,Yb,(Xc+Xb)/2,(Yc+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre D
        DessinBarreRectangulaire(Epaisseur,(Xb+Xc)/2,(Yb+Yc)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre G
        DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre H
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre M
        DessinBarreRectangulaire(Epaisseur,X9,Y9,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre O
        DessinBarreRectangulaire(Epaisseur,Xd,Yd,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if (Lettre == 'X')
    {
        // Barre I
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre K
        DessinBarreRectangulaire(Epaisseur,X9,Y9,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre M
        DessinBarreRectangulaire(Epaisseur,X9,Y9,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre O
        DessinBarreRectangulaire(Epaisseur,Xd,Yd,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if (Lettre == 'Y')
    {
        // Barre I
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre K
        DessinBarreRectangulaire(Epaisseur,X9,Y9,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre N
        DessinBarreRectangulaire(Epaisseur,X9,Y9,(Xd+Xc)/2,(Yd+Yc)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }
    else if (Lettre == 'Z')
    {
        // Barre A
        DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre B
        DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre E
        DessinBarreRectangulaire(Epaisseur,(Xc+Xd)/2,(Yc+Yd)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre F
        DessinBarreRectangulaire(Epaisseur,Xd,Yd,(Xc+Xd)/2,(Yc+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre O
        DessinBarreRectangulaire(Epaisseur,Xd,Yd,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        // Barre K
        DessinBarreRectangulaire(Epaisseur,X9,Y9,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
        
    }

    // if(Lettre == "0")
    // {
    //     // Barre A
    //     DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xb)/2,(Ya+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
    //     // Barre B
    //     DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
    //     // Barre C
    //     DessinBarreRectangulaire(Epaisseur,Xb,Yb,(Xc+Xb)/2,(Yc+Yb)/2,ColorRed,ColorGreen,ColorBlue,rendu);
    //     // Barre D
    //     DessinBarreRectangulaire(Epaisseur,(Xb+Xc)/2,(Yb+Yc)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
    //     // Barre E
    //     DessinBarreRectangulaire(Epaisseur,(Xc+Xd)/2,(Yc+Yd)/2,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
    //     // Barre F
    //     DessinBarreRectangulaire(Epaisseur,Xd,Yd,(Xc+Xd)/2,(Yc+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
    //     // Barre G
    //     DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,Xd,Yd,ColorRed,ColorGreen,ColorBlue,rendu);
    //     // Barre H
    //     DessinBarreRectangulaire(Epaisseur,Xa,Ya,(Xa+Xd)/2,(Ya+Yd)/2,ColorRed,ColorGreen,ColorBlue,rendu);
    //     // Barre I
    //     DessinBarreRectangulaire(Epaisseur,Xa,Ya,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
    //     // Barre J
    //     DessinBarreRectangulaire(Epaisseur,(Xa+Xb)/2,(Ya+Yb)/2,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
    //     // Barre K
    //     DessinBarreRectangulaire(Epaisseur,X9,Y9,Xb,Yb,ColorRed,ColorGreen,ColorBlue,rendu);
    //     // Barre L
    //     DessinBarreRectangulaire(Epaisseur,X9,Y9,(Xb+Xc)/2,(Yb+Yc)/2,ColorRed,ColorGreen,ColorBlue,rendu);
    //     // Barre M
    //     DessinBarreRectangulaire(Epaisseur,X9,Y9,Xc,Yc,ColorRed,ColorGreen,ColorBlue,rendu);
    //     // Barre N
    //     DessinBarreRectangulaire(Epaisseur,X9,Y9,(Xd+Xc)/2,(Yd+Yc)/2,ColorRed,ColorGreen,ColorBlue,rendu);
    //     // Barre O
    //     DessinBarreRectangulaire(Epaisseur,Xd,Yd,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
    //     // Barre P
    //     DessinBarreRectangulaire(Epaisseur,(Xa+Xd)/2,(Ya+Yd)/2,X9,Y9,ColorRed,ColorGreen,ColorBlue,rendu);
        
    // }
}
int AffichageMot(int setting,char mot[],float PositionX, float PositionY, float HauteurAffichage, int ColorRed, int ColorGreen, int ColorBlue,float Epaisseur, SDL_Renderer *rendu)
{
    float longueur = 0;
    int epsilon=15;
    float Largeur = HauteurAffichage/2;
    typedef struct
    {
        float x,y;
    } Coordonnees;
    typedef struct
    {
        Coordonnees I, J, K, L;
    } CoordChiffre;

    CoordChiffre Chiffre[strlen(mot)];
    for (int i = 0; i < strlen(mot); i++)
    {
        Chiffre[i].I.x = PositionX + epsilon*i + Largeur*i;
        Chiffre[i].I.y = PositionY;
        
        Chiffre[i].J.x = PositionX + epsilon*i + Largeur*(i+1);
        Chiffre[i].J.y = PositionY;

        Chiffre[i].K.x = PositionX + epsilon*i + Largeur*(i+1);
        Chiffre[i].K.y = PositionY + HauteurAffichage - epsilon;

        Chiffre[i].L.x =  PositionX + epsilon*i + Largeur*i;
        Chiffre[i].L.y = PositionY + HauteurAffichage - epsilon;

        if (setting == 1)
        {
            DessinLettre(mot[i],Epaisseur,Chiffre[i].I.x,Chiffre[i].I.y,Chiffre[i].J.x ,Chiffre[i].J.y,Chiffre[i].K.x,Chiffre[i].K.y,Chiffre[i].L.x,Chiffre[i].L.y,ColorRed,ColorGreen,ColorBlue,rendu);
        }
    }
    longueur = ((HauteurAffichage/2) +epsilon)*strlen(mot);
    return (int)longueur;
}

#endif
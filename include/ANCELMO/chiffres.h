#ifndef CHIFFRES_H
#define CHIFFRES_H

#include <SDL2/SDL.h>
#include <math.h>
#include <string.h>

typedef struct {
    int x, y;
} Point;

int AffichageNombre(int Score,float PositionX, float PositionY, float HauteurAffichage, int ColorRed, int ColorGreen, int ColorBlue,float Epaisseur, SDL_Renderer *rendu);
int TableauDeChiffre(int Nombre,int *tab);
int NombreDeChiffre(int chiffre);
void DessinBarre (float Epaisseur,float PositionX1, float PositionY1,float PositionX2, float PositionY2, int ColorRed, int ColorGreen, int ColorBlue,SDL_Renderer *rendu);
void DessinTriangle (float X1, float Y1,float X2, float Y2,float X3, float Y3,SDL_Renderer *rendu);
void EchangeCoordonnees(float *X1, float *Y1);
void DessinerUneLigneHorizontale(SDL_Renderer *rendu,float Xstart, float Xend, float Y);
void DessinerRectangle(float X1,float Y1,float X2,float Y2,float X3,float Y3,float X4,float Y4,SDL_Renderer *rendu);
void fillPolygon(SDL_Renderer *renderer, Point* vertices, int vertexCount);
int intersect(Point p1, Point p2, int y);
void DessinNombre(int nombre, float Epaisseur, float X1,float Y1,float X2,float Y2,float X3,float Y3,float X4,float Y4, int ColorRed, int ColorGreen, int ColorBlue,SDL_Renderer *rendu);
int SrtToInt(char *chaine);



void DessinBarre (float Epaisseur,float Xd, float Yd,float Xf, float Yf, int ColorRed, int ColorGreen, int ColorBlue,SDL_Renderer *rendu)
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
void DessinTriangle (float X1, float Y1,float X2, float Y2,float X3, float Y3,SDL_Renderer *rendu)
{
    SDL_RenderDrawLine(rendu,X1,Y1,X2,Y2);
    SDL_RenderDrawLine(rendu,X2,Y2,X3,Y3);
    SDL_RenderDrawLine(rendu,X1,Y1,X3,Y3);
    //d'abord, on cherche a classe les coordonnees du plus petit au plus grand en fonction des Y, en mode Y1 doit etre le plus petit et Y3 le plus grand
    if (Y1 > Y2) { EchangeCoordonnees(&Y1,&Y2); EchangeCoordonnees(&X1,&X2); }
    if (Y1 > Y3) { EchangeCoordonnees(&Y1,&Y3); EchangeCoordonnees(&X1,&X3); }
    if (Y2 > Y3) { EchangeCoordonnees(&Y2,&Y3); EchangeCoordonnees(&X2,&X3); }

    //calcul des pentes
    float dX12 = (Y2-Y1) != 0 ? (X2-X1)/(Y2-Y1) : 0;
    // cette phrase veut dire que la pente de la droite 12 est egale : 
        // 1- (X2-X1)/(Y2-Y1) si (Y2-Y1 != 0)
        // 0 sinon
    float dX23 = (Y3-Y2 )!= 0 ? (X3-X2)/(Y3-Y2) : 0;
    float dX13 = (Y3-Y1 )!= 0 ? (X3-X1)/(Y3-Y1) : 0;

    // trace de la premiere partie du triangle (de Y1 a Y2)
    float Xstart = X1, Xend = X1;
    for (float y = Y1; y < Y2; y++)
    {
        DessinerUneLigneHorizontale(rendu,Xstart,Xend,y);
        Xstart += dX12;
        Xend += dX13;
    }
    Xstart = X2;
    for (float y = Y2; y <= Y3; y++)
    {  
        DessinerUneLigneHorizontale(rendu,Xstart,Xend,y);
        Xstart += dX23;
        Xend += dX13;
    }
}
void EchangeCoordonnees(float *X1, float *Y1){
    int VariableProvisoire = *X1;
    *X1 = *Y1;
    *Y1 = VariableProvisoire;
}
void DessinerUneLigneHorizontale(SDL_Renderer *rendu,float Xstart, float Xend, float Y)
{
    if (Xstart > Xend) { EchangeCoordonnees(&Xend,&Xstart); }
    SDL_RenderDrawLine(rendu,Xstart,Y,Xend,Y);
}
void DessinerRectangle(float X1,float Y1,float X2,float Y2,float X3,float Y3,float X4,float Y4,SDL_Renderer *rendu)
{
    Point vertices[] = {
        {X1, Y1},  // Coin supérieur gauche
        {X2, Y2},  // Coin supérieur droit
        {X3, Y3},  // Coin inférieur droit
        {X4, Y4}   // Coin inférieur gauche
    };
    int vertexCount = sizeof(vertices) / sizeof(vertices[0]);

    fillPolygon(rendu,vertices,vertexCount);
}
int intersect(Point p1, Point p2, int y) {
    if (p1.y == p2.y) return -1;  // Pas d'intersection si la ligne est horizontale
    if (y < p1.y && y < p2.y || y > p1.y && y > p2.y) return -1; // Pas d'intersection si la ligne horizontale est en dehors du segment
    if (y == p1.y) return p1.x;   // Si l'intersection est au niveau d'un sommet
    if (y == p2.y) return p2.x;   // Si l'intersection est au niveau d'un sommet

    // Calcul de l'intersection en utilisant la formule de la droite
    return p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
}
void fillPolygon(SDL_Renderer *renderer, Point* vertices, int vertexCount) {
    // Calculer les limites de l'axe Y pour le scanline
    int minY = vertices[0].y, maxY = vertices[0].y;
    for (int i = 1; i < vertexCount; i++) {
        if (vertices[i].y < minY) minY = vertices[i].y;
        if (vertices[i].y > maxY) maxY = vertices[i].y;
    }

    // Balayer ligne par ligne entre minY et maxY
    for (int y = minY; y <= maxY; y++) {
        // Calculer les points d'intersection de la ligne horizontale avec les côtés du polygone
        int intersections[2], intersectionCount = 0;
        for (int i = 0; i < vertexCount; i++) {
            int j = (i + 1) % vertexCount;  // Le dernier point rejoint le premier
            int x = intersect(vertices[i], vertices[j], y);
            if (x != -1) {
                intersections[intersectionCount++] = x;
            }
        }

        // Si nous avons deux intersections, les relier avec une ligne
        if (intersectionCount == 2) {
            // Trier les intersections (pour s'assurer que le point de gauche est à gauche)
            if (intersections[0] > intersections[1]) {
                int temp = intersections[0];
                intersections[0] = intersections[1];
                intersections[1] = temp;
            }
            // Dessiner la ligne entre les deux intersections
            for (int x = intersections[0]; x <= intersections[1]; x++) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}
void DessinNombre(int nombre, float Epaisseur, float X1,float Y1,float X2,float Y2,float X3,float Y3,float X4,float Y4, int ColorRed, int ColorGreen, int ColorBlue,SDL_Renderer *rendu)
{
    float epsilon = 5;
    switch (nombre)
    {
        case 0:
        {
            //barre A
            DessinBarre(Epaisseur,X1 + epsilon,Y1,X2 - epsilon,Y2,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre C
            DessinBarre(Epaisseur,X4+epsilon,Y4,X3-epsilon,Y3,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre D
            DessinBarre(Epaisseur,X1,Y1+epsilon,(X1+X4)/2,(Y1+Y4)/2-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre E
            DessinBarre(Epaisseur,(X1+X4)/2,(Y1+Y4)/2+epsilon,X4,Y4-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre F
            DessinBarre(Epaisseur,X2,Y2+epsilon,(X2+X3)/2,(Y2+Y3)/2-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre G
            DessinBarre(Epaisseur,(X2+X3)/2,(Y2+Y3)/2+epsilon ,X3,Y3-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
        }
        break;
        case 1:
        {
            //barre F
            DessinBarre(Epaisseur,X2,Y2+epsilon,(X2+X3)/2,(Y2+Y3)/2-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre G
            DessinBarre(Epaisseur,(X2+X3)/2,(Y2+Y3)/2+epsilon ,X3,Y3-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
        }
        break;
        case 2:
        {
            //barre A
            DessinBarre(Epaisseur,X1 + epsilon,Y1,X2 - epsilon,Y2,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre B
            DessinBarre(Epaisseur,(X1+X4)/2 + epsilon,(Y1+Y4)/2,(X2+X3)/2-epsilon,(Y2+Y3)/2,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre C
            DessinBarre(Epaisseur,X4+epsilon,Y4,X3-epsilon,Y3,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre E
            DessinBarre(Epaisseur,(X1+X4)/2,(Y1+Y4)/2+epsilon,X4,Y4-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre F
            DessinBarre(Epaisseur,X2,Y2+epsilon,(X2+X3)/2,(Y2+Y3)/2-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
        }
        break;
        case 3:
        {
            //barre A
            DessinBarre(Epaisseur,X1 + epsilon,Y1,X2 - epsilon,Y2,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre B
            DessinBarre(Epaisseur,(X1+X4)/2 + epsilon,(Y1+Y4)/2,(X2+X3)/2-epsilon,(Y2+Y3)/2,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre C
            DessinBarre(Epaisseur,X4+epsilon,Y4,X3-epsilon,Y3,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre F
            DessinBarre(Epaisseur,X2,Y2+epsilon,(X2+X3)/2,(Y2+Y3)/2-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre G
            DessinBarre(Epaisseur,(X2+X3)/2,(Y2+Y3)/2+epsilon ,X3,Y3-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
        }
        break;
        case 4:
        {
            //barre B
            DessinBarre(Epaisseur,(X1+X4)/2 + epsilon,(Y1+Y4)/2,(X2+X3)/2-epsilon,(Y2+Y3)/2,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre D
            DessinBarre(Epaisseur,X1,Y1+epsilon,(X1+X4)/2,(Y1+Y4)/2-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre F
            DessinBarre(Epaisseur,X2,Y2+epsilon,(X2+X3)/2,(Y2+Y3)/2-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre G
            DessinBarre(Epaisseur,(X2+X3)/2,(Y2+Y3)/2+epsilon ,X3,Y3-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
        }
        break;
        case 5:
        {
            //barre A
            DessinBarre(Epaisseur,X1 + epsilon,Y1,X2 - epsilon,Y2,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre B
            DessinBarre(Epaisseur,(X1+X4)/2 + epsilon,(Y1+Y4)/2,(X2+X3)/2-epsilon,(Y2+Y3)/2,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre C
            DessinBarre(Epaisseur,X4+epsilon,Y4,X3-epsilon,Y3,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre D
            DessinBarre(Epaisseur,X1,Y1+epsilon,(X1+X4)/2,(Y1+Y4)/2-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre G
            DessinBarre(Epaisseur,(X2+X3)/2,(Y2+Y3)/2+epsilon ,X3,Y3-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
        }
        break;
        case 6:
        {
            //barre A
            DessinBarre(Epaisseur,X1 + epsilon,Y1,X2 - epsilon,Y2,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre B
            DessinBarre(Epaisseur,(X1+X4)/2 + epsilon,(Y1+Y4)/2,(X2+X3)/2-epsilon,(Y2+Y3)/2,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre C
            DessinBarre(Epaisseur,X4+epsilon,Y4,X3-epsilon,Y3,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre D
            DessinBarre(Epaisseur,X1,Y1+epsilon,(X1+X4)/2,(Y1+Y4)/2-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre E
            DessinBarre(Epaisseur,(X1+X4)/2,(Y1+Y4)/2+epsilon,X4,Y4-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre G
            DessinBarre(Epaisseur,(X2+X3)/2,(Y2+Y3)/2+epsilon ,X3,Y3-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
        }
        break;
        case 7:
        {
            //barre A
            DessinBarre(Epaisseur,X1 + epsilon,Y1,X2 - epsilon,Y2,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre F
            DessinBarre(Epaisseur,X2,Y2+epsilon,(X2+X3)/2,(Y2+Y3)/2-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre G
            DessinBarre(Epaisseur,(X2+X3)/2,(Y2+Y3)/2+epsilon ,X3,Y3-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
        }
        break;
        case 8:
        {
            //barre A
            DessinBarre(Epaisseur,X1 + epsilon,Y1,X2 - epsilon,Y2,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre B
            DessinBarre(Epaisseur,(X1+X4)/2 + epsilon,(Y1+Y4)/2,(X2+X3)/2-epsilon,(Y2+Y3)/2,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre C
            DessinBarre(Epaisseur,X4+epsilon,Y4,X3-epsilon,Y3,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre D
            DessinBarre(Epaisseur,X1,Y1+epsilon,(X1+X4)/2,(Y1+Y4)/2-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre E
            DessinBarre(Epaisseur,(X1+X4)/2,(Y1+Y4)/2+epsilon,X4,Y4-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre F
            DessinBarre(Epaisseur,X2,Y2+epsilon,(X2+X3)/2,(Y2+Y3)/2-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre G
            DessinBarre(Epaisseur,(X2+X3)/2,(Y2+Y3)/2+epsilon ,X3,Y3-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
        }
        break;
        case 9:
        {
            //barre A
            DessinBarre(Epaisseur,X1 + epsilon,Y1,X2 - epsilon,Y2,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre B
            DessinBarre(Epaisseur,(X1+X4)/2 + epsilon,(Y1+Y4)/2,(X2+X3)/2-epsilon,(Y2+Y3)/2,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre C
            DessinBarre(Epaisseur,X4+epsilon,Y4,X3-epsilon,Y3,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre D
            DessinBarre(Epaisseur,X1,Y1+epsilon,(X1+X4)/2,(Y1+Y4)/2-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre F
            DessinBarre(Epaisseur,X2,Y2+epsilon,(X2+X3)/2,(Y2+Y3)/2-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
            //barre G
            DessinBarre(Epaisseur,(X2+X3)/2,(Y2+Y3)/2+epsilon ,X3,Y3-epsilon,ColorRed,ColorGreen,ColorBlue,rendu);
        }
        break;
        
        default:
        break;
    }
}
int NombreDeChiffre(int chiffre)
{
    int number = 0;
    if (chiffre<0)
        chiffre=-chiffre;
    if (chiffre<10 )
    {
        number=1;
    }
    else
    {
        while (chiffre>=10)
        {
            chiffre=chiffre/10;
            number++;
        }
        number++;
    }
    return number;
}
int TableauDeChiffre(int Nombre,int tab[])
{
    int temp = NombreDeChiffre(Nombre);
    int i=0, count= NombreDeChiffre(Nombre);
    float NombreReel = (float)Nombre;
    
    for ( i = 0; i < count; i++)
    {
        NombreReel = NombreReel/10 + 0.001;
        tab[count-i-1] = (int)(10*(NombreReel-(int)NombreReel));
    }
    return temp;
}
int AffichageNombre(int Score,float PositionX, float PositionY, float HauteurAffichage, int ColorRed, int ColorGreen, int ColorBlue,float Epaisseur, SDL_Renderer *rendu)
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
    int tab[NombreDeChiffre(Score)];
    TableauDeChiffre(Score,tab);
    CoordChiffre Chiffre[NombreDeChiffre(Score)];
    for (int i = 0; i < NombreDeChiffre(Score); i++)
    {
        Chiffre[i].I.x = PositionX + epsilon*i + Largeur*i;
        Chiffre[i].I.y = PositionY;
        
        Chiffre[i].J.x = PositionX + epsilon*i + Largeur*(i+1);
        Chiffre[i].J.y = PositionY;

        Chiffre[i].K.x = PositionX + epsilon*i + Largeur*(i+1);
        Chiffre[i].K.y = PositionY + HauteurAffichage - epsilon;

        Chiffre[i].L.x =  PositionX + epsilon*i + Largeur*i;
        Chiffre[i].L.y = PositionY + HauteurAffichage - epsilon;

        DessinNombre(tab[i],Epaisseur,Chiffre[i].I.x,Chiffre[i].I.y,Chiffre[i].J.x ,Chiffre[i].J.y,Chiffre[i].K.x,Chiffre[i].K.y,Chiffre[i].L.x,Chiffre[i].L.y,ColorRed,ColorGreen,ColorBlue,rendu);
    }
    longueur = ((HauteurAffichage/2) +epsilon)*NombreDeChiffre(Score);
    return (int)longueur;
}

int SrtToInt(char *chaine)
{
    int entier=0,i=0,verification=1;
    int taille=strlen(chaine);
    for ( i = 0; i < taille; i++)
    {
        if (chaine[i]!='1' && chaine[i]!='2' && chaine[i]!='3' && chaine[i]!='4' && chaine[i]!='5' && chaine[i]!='6' && chaine[i]!='7' && chaine[i]!='8' && chaine[i]!='9' && chaine[i]!='0')
        {
            verification=0;
            // printf("\nLa chaine de caractere saisi contient des lettres !\n");
            break;
        }
    }
    if (verification==1)
    {
        int tab_entier[taille];
        for ( i = 0; i < taille; i++)
        {
            if (chaine[i]=='0')
            {
                tab_entier[i]=0;
            }
            else if (chaine[i]=='1')
            {
                tab_entier[i]=1;
            }
            else if (chaine[i]=='2')
            {
                tab_entier[i]=2;
            }
            else if (chaine[i]=='3')
            {
                tab_entier[i]=3;
            }
            else if (chaine[i]=='4')
            {
                tab_entier[i]=4;
            }
            else if (chaine[i]=='5')
            {
                tab_entier[i]=5;
            }
            else if (chaine[i]=='6')
            {
                tab_entier[i]=6;
            }
            else if (chaine[i]=='7')
            {
                tab_entier[i]=7;
            }
            else if (chaine[i]=='9')
            {
                tab_entier[i]=9;
            }
            else if (chaine[i]=='8')
            {
                tab_entier[i]=8;
            }
        }
        double reel=0;
        for ( i = 0; i < taille; i++)
        { 
            double puissance=(pow(10,(double)(taille-1-i)));
            reel=reel+((double)tab_entier[i])*puissance;
        }
        entier=(int)reel;
    }
    return entier;
}





#endif
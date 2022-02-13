//Barsoni Dorian
//g++ Labyrinthe.cpp -Wall -o Labyrinthe
//  Labyrinthe.hpp
//  Laby-p3
//
//

#ifndef Labyrinthe_hpp
#define Labyrinthe_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string>
#include <iostream>

using namespace std;

//Fonction effectuant une rotation sur un paterne
void rotate(int* tab, int nb_rot);
//Fonction retournant un paterne predefini avec une rotation aleatoire
void selec_pattern(int* tab);


///Classe Point repr�sentant un point
class Point
{
    private :
        int x;
        int y;
    public :
        int getX(); //Fonction retournant x
        int getY(); //Fonction retournant y
        void setX(int x); //Fonction mettant � jour x
        void setY(int y); //Fonction mettant � jour y
        void aff(); //Fonction affichant le point
        Point(); //constructeur du point par d�faut
        Point(int x, int y); //Contructeur du point avec 2 entiers
        bool sontEgaux(Point p);
};

bool Point::sontEgaux(Point p)
{
    if(this->x == p.getX() && this->y == p.getY()) return true;
    return false;
}

//Fonction retournant x
int Point::getX()
{
    return x;
}

//Fonction retournant y
int Point::getY()
{
    return y;
}

//Fonction mettant � jour x
void Point::setX(int x)
{
    this->x = x;
}

//Fonction mettant � jour y
void Point::setY(int y)
{
    this->y = y;
}

//Fonction affichant le point
void Point::aff()
{
    cout <<"("<<x<<","<<y<<")"<<endl;
}

//constructeur du point par d�faut
Point::Point() :
x(0),y(0)
{
}

//Contructeur du point avec 2 entiers
Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

///Classe Dijkstra permettant de calculer la distance la plus courte
///entre deux points
class Dijkstra
{
    public :
        Point sommet;
        int valeur;
        Dijkstra* predecesseur;
        Dijkstra* sommetAdj;
        int taille_sommetAdj;

        Dijkstra();
        Dijkstra(Point sommet);
        ~Dijkstra();
        void setPredecesseur(Dijkstra* predecesseur); //Fonction modifiant le pr�d�cesseur d'un �l�ment de Dijkstra
        void addSommetAdj(Dijkstra d); //Fonction ajoutant un sommet adjacent � un �l�ment de Dijkstra
};

Dijkstra::Dijkstra()
{
}

Dijkstra::Dijkstra(Point sommet)
{
    this->sommet = sommet;
    valeur = 1000000;
    sommetAdj = new Dijkstra[4];
    taille_sommetAdj = 0;
}

Dijkstra::~Dijkstra()
{
    delete[] sommetAdj;
    delete predecesseur;
}

//Fonction modifiant le pr�d�cesseur d'un �l�ment de Dijkstra
void Dijkstra::setPredecesseur(Dijkstra* predecesseur)
{
    this->predecesseur = predecesseur;
}

//Fonction ajoutant un sommet adjacent � un �l�ment de Dijkstra
void Dijkstra::addSommetAdj(Dijkstra d)
{
    sommetAdj[taille_sommetAdj] = d;
    taille_sommetAdj++;
}

///Class pile pour Dijkstra
class PileDijkstra
{
    public :
        Dijkstra* pile;
        int sommet_pile;

        PileDijkstra(int taille);
        ~PileDijkstra();
        void push(Dijkstra d);
        Dijkstra pop();
};

PileDijkstra::PileDijkstra(int taille)
{
    pile = new Dijkstra[taille];
    sommet_pile = 0;
}

PileDijkstra::~PileDijkstra()
{
    delete[] pile;
}

void PileDijkstra::push(Dijkstra d)
{
    pile[sommet_pile] = d;
    sommet_pile++;
}

Dijkstra PileDijkstra::pop()
{
    sommet_pile--;
    return pile[sommet_pile];
}

///Class Pile reproduisant le fonctionnement du tableau Pile et comportant
///les fonctions push et pop de la partie 2
class Pile
{
    private :
        int* data;
    public :
        int sommet;
        Pile(int taille);
        ~Pile();
        void push(int i);
        int pop();
};

Pile::Pile(int taille)
{
    data = new int[taille];
    sommet = 0;
}

Pile::~Pile()
{
    delete[] data;
}

void Pile::push(int i)
{
    data[sommet] = i;
    sommet++;
}

int Pile::pop()
{
    if(sommet == 0) return -1;
    sommet--;
    return data[sommet];
}

class Labyrinthe
{
private:
    int nb_lignes;
    int nb_colonnes;
    int taille;
    char* grille;
    std::string aff;

    // Retourne le caract�re � afficher pour la valeur val.
    char getAff(char val);

public:
    /// Constructeurs et destructeurs
    Labyrinthe(int nLignes, int nColonnes); //Cr�e un labyrinthe vide.
    Labyrinthe(char data[]) ; //Cr�e un labyrinthe � partir d'un descripteur.
    ~Labyrinthe(); //D�truit le labyrinthe courant.

    /// M�thodes d'acc�s
    int getID(int ligne, int colonne); //Retourne l'identifiant d'une cellule.
    int getLigne(int id); //Retourne la ligne de la cellule d'identifiant id.
    int getCol(int id); //Retourne la colonne de la cellule d'identifiant id.
    void modifie(int ligne, int colonne, char x); //Modifie la valeur d'une cellule.
    char lit(int ligne, int colonne); //Retourne la valeur de la cellule de coordonn�es (i,j).

    /// M�thode d'acc�s suppl�mentaires
    int getNbLignes(); //Retourne le nombre de lignes de la grille.
    int getNbColonnes(); //Retourne le nombre de lignes de la grille.
    int lit(int id); //Retourne la valeur de la cellule id.
    void modifie(int id, char x); //Modifie la valeur de la cellule id.

    /// M�thodes d'affichage
    // Initialise les caract�res utilis�s pour l'affichage. Si motif contient n caract�res alors
    // motif[i] est affich� pour repr�senter une case de valeur i entre 0 et n-2.
    // Toute autre valeur provoque l'affichage du caract�re motif[n-1].
    void setAff(const char* motifs);
    void affiche(); // Affiche le labyrinthe.
    void afficheDescr(); //Affiche le descripteur du labyrinthe courant.

    /// M�thode de haut niveau
    bool connexe(); //V�rifie si toutes les cellules de valeur 0 sont connect�es.
    void genLaby(int nb); //Produit un labyrinthe al�atoire connexe avec nb cases blanches.
    int distMin(int id1, int id2); //Retourne la distance minimum entre les cases id1 et id2.

    /// M�thodes de d�monstration
    // Mat�rialise un chemin de longueur minimale entre les cases d'identifiants
    // id1 et id2 en pla�ant des valeurs 2 dans les cases de ce chemin.
    void chemin(int id1, int id2);
    // Lance une d�monstration de productions de labyrinthes et de recherche de
    // chemins de longueur minimale.
    static void demo();

    ///FONCTIONS DE TEST
    int test(); // Fonction test global
    int test_getID(); //Fonction test de getID
    int test_getLigne(); //Fonction test de getLigne
    int test_getCol(); //Fonction test de getCol
    int test_lit(); //Fonction test de lit
    int test_lit2(); //Fonction test de lit
    int test_modifie(); //Fonction test de mofifie
    int test_modifie2(); //Fonction test de mofifie
    int test_getNbLignes(); //Fonction test de getNbLignes
    int test_getNbColonnes(); //Fonction test de getNbColonnes
    int test_connexe(); //Fonction test de connexe
};

#endif /* Labyrinthe_hpp */

/// Constructeurs et destructeurs
Labyrinthe::Labyrinthe(int nLignes, int nColonnes) //Cr�e un labyrinthe vide.
{
    nb_lignes = nLignes;
    nb_colonnes = nColonnes;
    grille = new char[nLignes*nColonnes];
    for(int i=0; i<(nLignes*nColonnes); i++) grille[i] = 0;
}

Labyrinthe::Labyrinthe(char data[]) //Cr�e un labyrinthe � partir d'un descripteur.
{
    nb_lignes = data[0];
    nb_colonnes = data[1];
    grille = new char[data[0]*data[1]];
    for(int i=0; i<(data[0]*data[1]); i++) grille[i] = data[i+2];
}

Labyrinthe::~Labyrinthe() //D�truit le labyrinthe courant.
{
    delete[] grille;
}

/// M�thodes d'acc�s
int Labyrinthe::getID(int ligne, int colonne) //Retourne l'identifiant d'une cellule.
{
    return getNbColonnes()*ligne + colonne;
}

int Labyrinthe::getLigne(int id) //Retourne la ligne de la cellule d'identifiant id.
{
    int ligne = 0;

    if(id<0) return -1;

    while(id > nb_colonnes - 1)
    {
        id = id - nb_colonnes;
        ligne++;
    }
    return ligne;
}

int Labyrinthe::getCol(int id) //Retourne la colonne de la cellule d'identifiant id.
{
    return id%nb_colonnes;
}
void Labyrinthe::modifie(int ligne, int colonne, char x) //Modifie la valeur d'une cellule.
{
    grille[getID(ligne, colonne)] = x;
}

char Labyrinthe::lit(int ligne, int colonne) //Retourne la valeur de la cellule de coordonn�es (i,j).
{
    return grille[getID(ligne, colonne)];
}

/// M�thode d'acc�s suppl�mentaires
int Labyrinthe::getNbLignes() //Retourne le nombre de lignes de la grille.
{
    return nb_lignes;
}

int Labyrinthe::getNbColonnes() //Retourne le nombre de lignes de la grille.
{
    return nb_colonnes;
}
int Labyrinthe::lit(int id) //Retourne la valeur de la cellule id.
{
     return grille[id];
}

void Labyrinthe::modifie(int id, char x) //Modifie la valeur de la cellule id.
{
    grille[id] = x;
}

 /// M�thodes d'affichage
// Initialise les caract�res utilis�s pour l'affichage. Si motif contient n caract�res alors
// motif[i] est affich� pour repr�senter une case de valeur i entre 0 et n-2.
// Toute autre valeur provoque l'affichage du caract�re motif[n-1].
void Labyrinthe::setAff(const char* motifs)
{
    int i = 0;
    while(motifs[i] != 0)
    {
        aff = aff + motifs[i];
        i++;
    }
}

void Labyrinthe::affiche() // Affiche le labyrinthe.
{
    for(int i=0; i<(nb_colonnes + 2); i++) cout <<aff[aff.length()-1]; //Premiere ligne de Bord
    cout <<endl;
    for(int i=0; i<nb_lignes; i++) //Boucle affichant les bords et la grille ligne par ligne
    {
        cout <<aff[aff.length()-1]; //Bord gauche
        for(int j=0; j<nb_colonnes; j++) //Boucle affichant les colonnes de la grille pour la ligne en cours
        {
            cout <<aff[lit(i,j)];
        }
        cout <<aff[aff.length()-1]; //Bord droit
        cout <<endl;
    }
    for(int i=0; i<(nb_colonnes + 2); i++) cout <<aff[aff.length()-1]; //Derni�re ligne de Bord
    cout <<endl<<endl;
}

/// M�thode de haut niveau
bool Labyrinthe::connexe() //V�rifie si toutes les cellules de valeur 0 sont connect�es.
{
    Pile pile = Pile(nb_lignes*nb_colonnes);
    int cases_blanches = 0, get_id = 0, id, cases_marquees = 0, i;
    for(i=0; i<nb_colonnes*nb_lignes; i++) //Boucle comptant le nombre de cases blanches et selectionnant la premiere case blanche trouve
    {
        if(grille[i] == 0)
        {
            cases_blanches++;
            if(get_id == 0)
            {
                pile.push(i);
                grille[i] = 2;
                get_id++;
            }
        }
    }

    if(cases_blanches == 0) //Arret si le labyrinthe ne contient pas de case blanche
    {
        cout <<endl<<"|!| Le labyrinthe ne contient aucune case blanche |!|"<<endl<<endl;
        return false;
    }

     while(pile.sommet != 0) //Remplissage de 2
    {
        id = pile.pop();

        if(getCol(id) - 1 >= 0) //Case a gauche
        {
            if(grille[id - 1] == 0)
            {
                grille[id - 1] = 2;
                pile.push(id - 1);
            }
        }

        if(getCol(id) + 1 < nb_colonnes) //Case a droite
        {
            if(grille[id + 1] == 0)
            {
                grille[id + 1] = 2;
                pile.push(id + 1);
            }
        }

        if(getLigne(id) - 1 >= 0) //Case en haut
        {
            if(grille[id - nb_colonnes] == 0)
            {
                grille[id - nb_colonnes] = 2;
                pile.push(id - nb_colonnes);
            }
        }

        if(getLigne(id) + 1 < nb_lignes) //Case en bas
        {
            if(grille[id + nb_colonnes] == 0)
            {
                grille[id + nb_colonnes] = 2;
                pile.push(id + nb_colonnes);
            }
        }
    }

    for(i=0; i<nb_lignes*nb_colonnes; i++) //Decompte et remise a 0 des cases marquees
    {
        if(grille[i] == 2)
        {
            grille[i] = 0;
            cases_marquees++;
        }
    }

    if(cases_blanches == cases_marquees) //Retour sur la connexite du labyrinthe
    {
        //printf("\nLabyrinthe connexe\n\n");
        return true;
    }
    else
    {
        //printf("\nLabyrinthe non connexe\n\n");
        return false;
    }
}

void Labyrinthe::genLaby(int nb) //Produit un labyrinthe al�atoire connexe avec nb cases blanches.
{
    int nb_murs, securite = 0, i, j, l, c, n, paterne[9] = {0};

    for(i=1; i<(nb_lignes - 1); i++) //Double boucle parcourant la Grille de la case (1,2) a la case (NB_LIGNES-1, NB_COLONNES-2) sans passer par les cases collant les bords
    {
        for(j=2; j<(nb_colonnes - 2); j++)
        {
            if(getID(i, j) != 2*nb_colonnes - 2 && getID(i, j) != (1 + nb_colonnes*(nb_lignes - 2))) //Eclusion des coins en haut � droite et en bas � gauche des cases s�lectionnees
            {
                if(lit(getID(i, j)) == 0) //Si la valeur de la Grille est 0
                {
                    if (rand()%2 == 0) //On a une chance sur 2 de placer un paterne
                    {
                        selec_pattern(paterne);
                        n=0;
                        for(l=(i-1); l<(i+2); l++) //Ajout du paterne
                        {
                            for(c=(j-1); c<(j+2); c++)
                            {
                                modifie(getID(l, c), paterne[n]);
                                n++;
                            }
                        }

                        for(l=i-3; l<i+4; l++) //Ajout des 3 pour ne pas que les paternes empietent les uns sur les autres
                        {
                            for(c=j-3; c<j+4; c++)
                            {
                                if(l >= 0 && l < nb_lignes) //Verification qu'on ne sort pas des lignes de la Grille
                                {
                                    if(c >= 0 && c < nb_colonnes) //Verification qu'on ne sort pas des colonnes de la Grille
                                    {
                                        if(lit(getID(l,c)) == 0) modifie(getID(l,c), 3);
                                    }
                                }
                            }
                        }
                        nb_murs = 0;
                        for(l=0; l<nb_colonnes*nb_lignes; l++) //On compte le nombre de murs
                        {
                            if(lit(l) == 1) nb_murs++;
                        }
                        if((nb_colonnes*nb_lignes) - nb_murs <= nb) //Si le nombre de cases vides est inferieur ou egale a k
                        {
                            for(i=0; i<nb_colonnes*nb_lignes; i++) //On remet toutes les cases de la Grille qui valent 3 a 0
                            {
                                if(lit(i) == 3) modifie(i, 0);
                            }
                            return; //On arrete la construction du labyrinthe
                        }
                    }
                }
            }
        }
    }

    for(i=0; i<nb_colonnes*nb_lignes; i++) //On remet toutes les cases de la Grille qui valent 3 a 0
    {
        if(lit(i) == 3) modifie(i, 0);
    }

    while((nb_lignes*nb_colonnes - nb_murs) != nb && securite != 5) //On boucle tant que k != cases_vides et tant que securite != 5
    {
        for(int i=1; i < (nb_lignes*nb_colonnes - 1); i++) //Boucle permettant de traverser le tableau de l'ID 2 au dernier Id - 1
        {
            if(lit(i) == 0) //La boucle ne s'execute que sur les cases vides
            {
                nb_murs = 0; //On reinitialise le nombre de murs
                modifie(i, 1); //On met 1 a l'ID i
                if(!connexe()) modifie(i, 0); //Si le labyrinthe n'est plus connexe on remet le 0
                else
                {
                    if(rand()%2) modifie(i, 0); //Sinon on a une chance sur 2 de remettre le 0
                }
                for(int j=0; j<nb_lignes*nb_colonnes; j++) //Decompte du nombre de murs
                {
                    if(lit(j) == 1) nb_murs++;
                }
                if( (nb_lignes*nb_colonnes - nb_murs) <= nb ) return; //Si k <= au nombre de cases vides on arrete la fonction
            }
        }
        securite++; //On incemente securite
    }
}

//Fonction effectuant une rotation sur un paterne
void rotate(int* tab, int nb_rot)
{
    int ligne1[3], ligne2[3], ligne3[3], i, j;
    for(j=0; j<nb_rot; j++)
    {
        for(i=0; i<3; i++) //Boucle copiant les lignes du paterne
        {
            ligne1[i] = tab[i];
            ligne2[i] = tab[i+3];
            ligne3[i] = tab[i+6];
        }

        for(i=0; i<3; i++) //Boucle remplacant les colones du paterne par les lignes copiees
        {
            tab[2 + 3*i] = ligne1[i];
            tab[1 + 3*i] = ligne2[i];
            tab[3*i] = ligne3[i];
        }
    }
}

//Fonction retournant un paterne predefini avec une rotation aleatoire
void selec_pattern(int* tab)
{
    int pattern1[] = {1, 1, 1, 0, 0, 1, 1, 0, 1}; //Tournant
    int pattern2[] = {1, 1, 1, 0, 0, 0, 1, 1, 1}; //Couloir
    int pattern3[] = {1, 0, 1, 0, 0, 0, 1, 1, 1}; //Carrefour 3 voies
    int pattern4[] = {1, 0, 1, 0, 0, 0, 1, 0, 1}; //Carrefour 4 voies
    int* Tab[4]; //Tableau contenant tous les paternes
    Tab[0] = pattern1;
    Tab[1] = pattern2;
    Tab[2] = pattern3;
    Tab[3] = pattern4;

    int pattern = rand()%4; //Selection aleatoire d'un paterne
    int nb_rot = rand()%4; //Rotation aleatoire d'un paterne

    rotate(Tab[pattern], nb_rot); //On fait tourner le paterne
    for(int i=0; i<9; i++) tab[i] = Tab[pattern][i]; //On copie le paterne dans tab
}

int Labyrinthe::distMin(int id1, int id2) //Retourne la distance minimum entre les cases id1 et id2.
{
    //Cr�ation d'un tableau de dijkstra de la taille de la grille
    Dijkstra tableau[getNbLignes()][getNbColonnes()];
    for(int i=0; i<getNbLignes(); i++)
    {
        for(int j=0; i<getNbColonnes(); j++)
        {
            if(lit(getID(i, j)) == 0 ) tableau[i][j] = Dijkstra(Point(getLigne(getID(i, j)), getCol(getID(i, j))));
            else tableau[i][j] = Point(-1, -1);
        }
    }


    //Remplissage des sommets adjacents
    for(int i=0; i<getNbLignes(); i++)
    {
        for(int j=0; j<getNbColonnes(); j++)
        {
            if(j>0) //case de gauche
            {
                if(lit(getID(i, j-1)) == 0)
                {
                    tableau[i][j].addSommetAdj(tableau[i][j-1]);
                }
            }
            if(j<getNbColonnes() - 1) //case de droite
            {
                if(lit(getID(i, j+1)) == 0)
                {
                    tableau[i][j].addSommetAdj(tableau[i][j+1]);
                }
            }
            if(i>0) //case du haut
            {
                if(lit(getID(i-1, j)) == 0)
                {
                    tableau[i][j].addSommetAdj(tableau[i-1][j]);
                }
            }
            if(i<getNbLignes() - 1) //case du bas
            {
                if(lit(getID(i+1, j)) == 0)
                {
                    tableau[i][j].addSommetAdj(tableau[i+1][j]);
                }
            }
        }
    }



    Dijkstra debut = tableau[getLigne(id1)][getCol(id1)]; //On d�finie le point de d�part
    Dijkstra fin = tableau[getLigne(id2)][getCol(id2)]; //On d�finie le point d'arriv�
    PileDijkstra pile = PileDijkstra(getNbLignes()*getNbColonnes()); //On cr�e une pile de la taille de labyrinthe

    debut.valeur = 0; //On place la valeur de sommet initial � 0
    debut.setPredecesseur(&debut); //Le pr�decesseur du sommet initial est lui m�me
    pile.push(debut); //On met debut dans la pile

    Dijkstra sommetCourant; //On cr�e un sommet courant

    while(pile.sommet_pile != 0) //Tant que la pile n'est pas vide
    {
        sommetCourant = pile.pop(); //Le sommet courant prend la derni�re valeur de la pile
        for(int i=0; i<sommetCourant.taille_sommetAdj; i++) //Pour i allant de 0 taille_sommetAdj du sommet courant
        {
            if(!(sommetCourant.sommetAdj[i].sommet.sontEgaux(sommetCourant.predecesseur->sommet)) && !(sommetCourant.sommet.sontEgaux(fin.sommet))) //Si le sommet adjacent
            {//n'est ni le pr�d�cesseur du sommet courant ni fin
                if(sommetCourant.sommetAdj[i].valeur > sommetCourant.valeur + 1) //Si la valeur du sommet adjacent est sup�rieur � la valeur du sommet courant + 1
                {
                    pile.push(sommetCourant.sommetAdj[i]); //On met dans la pile le sommet adjacent
                    sommetCourant.sommetAdj[i].setPredecesseur(&sommetCourant); //On d�finie que le sommet courant est son pr�d�cesseur
                    sommetCourant.sommetAdj[i].valeur = sommetCourant.valeur + 1; //On modifie sa valeur � la valeur du sommet adjacent + 1
                }
            }
        }
    }

    sommetCourant = fin;
    int dist = 0;

    while(!(sommetCourant.predecesseur->sommet.sontEgaux(debut.sommet))) //Tant que le pr�d�cesseur du sommet courant n'est pas le sommet du d�but
    {
        sommetCourant = *sommetCourant.predecesseur; //Le sommet courant devient le pr�d�cesseur du sommet courant
        dist++; //On incr�mente dist
    }

    return dist; //On retourne dist
}

//Remet a 0 la grille
void reset(Labyrinthe* l)
{
    for(int i=0; i<l->getNbColonnes()*l->getNbLignes(); i++) l->modifie(i, 0);
}

///FONCTIONS DE TEST
int Labyrinthe::test() // Fonction test global
{
    cout <<"_________________________________________________"<<endl<<"====================="<<endl<<"|Operations de tests|"<<endl<<"====================="<<endl<<endl;
    if( test_getID() && test_getLigne() && test_getCol() && test_lit() && test_lit2() && test_modifie() && test_modifie2() && test_getNbColonnes() && test_getNbLignes() && test_connexe() ) //On test si toutes les fonctions test renvoient 1
    {
        cout <<"|v| Toutes les fonctions sont operationnelles |v|"<<endl<<"_________________________________________________"<<endl<<endl;
        return 1;
    }
    cout <<"|!| Defaillances detectees |!|"<<endl<<"_________________________________________________"<<endl<<endl;
    return 0;
}

int Labyrinthe::test_getID() //Fonction test de getID
{
    if (getID(0,0) != 0 && getID(1,1) != (nb_colonnes + 1) )
    {
        cout <<"|!| getID() defaillant |!|"<<endl;
        return 0;
    }
    return 1;
}
int Labyrinthe::test_getLigne() //Fonction test de getLigne
{
    if(getLigne(nb_colonnes - 1) != 0 || getLigne(nb_colonnes) != 1) //On verifie si l'id juste avant le saut de ligne a bien un getLigne = 0 et si celui juste apres en a un de 1
    {
        cout <<"|!| getLigne() defaillant |!|"<<endl;
        return 0;
    }
    return 1;
}

int Labyrinthe::test_getCol() //Fonction test de getCol
{
    if(getCol(3) != 3%nb_colonnes || getCol(4) != 4%nb_colonnes) //On verifie si l'id 3 et l'id 4 on bien une colonne respectivement 3%NB_COLONNES et 4%NB_COLONNES
    {
        cout <<"|!| getCol() defaillant |!|"<<endl;
        return 0;
    }
    return 1;
}

int Labyrinthe::test_lit() //Fonction test de lit
{
    if(lit(0, 0) != 0) //On verifie que la premiere valeur de grille[0] est egale a 0
    {
        cout <<"|!| lit(ligne, col) defaillant |!|"<<endl;
        return 0;
    }
    return 1;
}

int Labyrinthe::test_lit2() //Fonction test de lit
{
    if(lit(0) != 0) //On verifie que la premiere valeur de grille[0] est egale a 0
    {
        cout <<"|!| lit(id) defaillant |!|"<<endl;
        return 0;
    }
    return 1;
}

int Labyrinthe::test_modifie() //Fonction test de mofifie
{
    char x = grille[0];
    modifie(0,0,1);
    if(grille [0] != 1) //On verifie que la premiere valeur de Grille est bien modifie a 1
    {
        cout <<"|!| modifie(ligne, colonne, x) defaillant |!|"<<endl;
        return 0;
    }
    modifie(0,0,x);
    return 1;
}

int Labyrinthe::test_modifie2() //Fonction test de mofifie
{
    char x = grille[0];
    modifie(0,1);
    if(grille [0] != 1) //On verifie que la premiere valeur de Grille est bien modifie a 1
    {
        cout <<"|!| modifie(id, x) defaillant |!|"<<endl;
        return 0;
    }
    modifie(0,x);
    return 1;
}

int Labyrinthe::test_getNbLignes() //Fonction test de getNbLignes
{
    Labyrinthe l = Labyrinthe(2, 3);
    if(l.getNbLignes() != 2)
    {
        cout <<"|!| getNbLignes() defaillant |!|"<<endl;
        return 0;
    }
    return 1;
}

int Labyrinthe::test_getNbColonnes() //Fonction test de getNbColonnes
{
     Labyrinthe l = Labyrinthe(2, 3);
    if(l.getNbColonnes() != 3)
    {
        cout <<"|!| getNbColonnes() defaillant |!|"<<endl;
        return 0;
    }
    return 1;
}

int Labyrinthe::test_connexe() //Fonction test de connexe
{
    int test = 1, i; //test est le booleen qui indiquera si la fonction s'execute correctement

    if(!connexe()) test = 0; //On test si la Grille vide est

    for(i=0; i<nb_colonnes*nb_lignes; i++) grille[i] = 1; //On remplie Grille de 1
    if(connexe()) test = 0; //on test si on obtient bien l'erreur
    reset(this); //reset() remet la Grille a 0

    if(nb_colonnes > 1) //Test possible que si on a plusieurs colonnes
    {
        for(i=0; i<nb_lignes; i++) grille[getID(i, 1)] = 1; //On remplie la colonne 1 de 1
        if(connexe()) test = 0; //On verifie que la fonction renvoie non connexe
        reset(this);
    }

    if(nb_lignes > 2) //Test possible que si on a plus de 2 lignes
    {
        for(i=0; i<nb_colonnes; i++) grille[getID(1, i)] = 1; //On remplie la ligne 1 de 1
        if(connexe()) test = 0; //On verifie que la fonction renvoie non connexe
        reset(this);
    }

    if(test == 0 ) cout <<"|!| connexe() defaillant |!|"<<endl; //Si test vaut 0 on affiche la defaillance de la fonction connexe
    return test;
}

int main()
{
    srand((unsigned) time(NULL));
    Labyrinthe l = Labyrinthe(30, 30);
    l.test();

    l.setAff(" X.");
    l.genLaby(l.getNbColonnes()*l.getNbLignes()/2);
    l.affiche();
}

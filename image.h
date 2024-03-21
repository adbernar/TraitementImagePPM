#ifndef _IMAGE_H_INCLUDED
#define _IMAGE_H_INCLUDED
#include <iostream>
#include <vector>

using namespace std;

class Image {
  vector<vector<int>> _rouge;
  vector<vector<int>> _bleu;
  vector<vector<int>> _vert;
  int _largeur;
  int _hauteur;

public:
  /// Constructeurs

  // Constructeur à partir des vecteurs couleurs
  Image(vector<vector<int>> rouge, vector<vector<int>> vert,
        vector<vector<int>> bleu);

  // Constructeur à partir d'un fichier ppm
  Image(string &fichier);

  Image(int hauteur = 0, int largeur = 0);
  // Affichage sous forme de matrice
  //(debug uniquement)
  void display() const;

  // Creation d'une nouvelle image à partir de l'image actuelle
  // ayant uniquement le canal rouge, les autres a 0
  // Retourne l'image créée
  Image composanteRouge() const;

  // Detection de la couleur donnee en parametre
  // sous la forme RVB
  // Retourne True si la couleur est dans l'image, False sinon ou si la couleur est invalide
  bool detection(int rouge, int vert, int bleu) const;

  // Creation d'une copie de l'image actuelle
  // la passe en niveaux de gris
  // Retourne l'image créée
  Image niveauGris() const;

  // Creation d'une copie de l'image actuelle
  // Passe tout les pixel en dessous du facteur en noir au dessus en blanc
  // Retourne l'image créée
  Image noirEtBlanc(int facteur) const;

  // Creation d'une copie de l'image actuelle
  // change ses couleurs pour correspondre à la vision Deuteranope
  // Retourne l'image créée
  Image visionDeuteranopie() const;

  // Creation d'une copie de l'image actuelle
  // Change ses couleurs pour correspondre à la vision Protanopie
  // Retourne l'image créée
  Image visionProtanopie() const;

  // Creation d'une copie de l'image actuelle
  // Change ses couleurs pour correspondre à la vision Tritanopie
  // Retourne l'image créée
  Image visionTritanopie() const;

  // Creation d'un Histogramme basé sur l'image en niveau de gris
  // listant le nombre d'iteration de chaque valeur de gris
  // Retourne cet histogramme dans un vecteur de 256 valeurs
  vector<int> histogrammeGris() const;

  // Creation d'un Histogramme basé sur l'image en couleur
  // listant le nombre d'iteration de chaque valeur des canaux rouge vert et
  // bleu Retourne cet histogramme dans un vecteur 3D de 256*256*256 valeurs
  vector<vector<vector<int>>> histogrammeCouleur() const;

  int luminositeMoyenne() const;

  Image reglageAuto() const;

  // Creation d'une copie de l'image actuelle
  // Augmente sa luminosité globale par le facteur donne en parametre
  // Retourne l'image créée
  Image luminosityUp(float facteur) const;

  // Creation d'une copie de l'image actuelle
  // Diminue sa luminosité globale par le facteur donne en parametre
  // Retourne l'image créée
  Image luminosityDown(float facteur) const;

  // Creation d'une copie de l'image actuelle
  // Augmente le contraste global par le facteur donne en parametre
  // Retourne l'image créée
  Image contrastUp(float facteur) const;

  // Creation d'une copie de l'image actuelle
  // Diminue le contraste global par le facteur donne en parametre
  // Retourne l'image créée
  Image contrastDown(float facteur) const;

  /*
  Image reglageAuto() const;
  */

  // Ecrit l'objet image dans un fichier ppm
  void vers_ppm(const string &nom_fichier) const;

  // Normalise les valeurs dans les vecteurs rouge vert et bleu
  // Empeche qu'une valeur soit supérieure a 255 ou inferieur a 0
  void normaliser();

  // Creation d'une copie de l'image actuelle
  // Supprime nb colonnes de l'image en partant de la premiere colonne
  // Retourne l'image créée
  Image rognerG(int nb) const;

  // Creation d'une copie de l'image actuelle
  // Supprime nb colonnes de l'image en partant de la derniere colonne
  // Retourne l'image créée
  Image rognerD(int nb) const;

  // Creation d'une copie de l'image actuelle
  // Supprime nb lignes de l'image en partant de la premiere ligne
  // Retourne l'image créée
  Image rognerH(int nb) const;

  // Creation d'une copie de l'image actuelle
  // Supprime nb lignes de l'image en partant de la derniere ligne
  // Retourne l'image créée
  Image rognerB(int nb) const;

  // Creation d'une copie de l'image actuelle
  // Supprime nb colonnes ou lignes de l'image en fonction de choix ('g','d','h'
  // ou 'b') Retourne l'image créée
  Image rogner(int nb, char choix) const;

  // Creation d'une copie de l'image actuelle
  // Effectue une rotation à 90 degree dans le sens anti-horaire sur l'image
  // Retourne l'image créée
  Image rotationG() const;

  // Creation d'une copie de l'image actuelle
  // Effectue une rotation à 90 degree dans le sens horaire sur l'image
  // Retourne l'image créée
  Image rotationD() const;

  // Creation d'une copie de l'image actuelle
  // Rotation à 90 degree de l'image dans le sens définie par choix ('g' ou 'd')
  // Retourne l'image créée
  Image rotation(char choix) const;

  // Creation d'une copie de l'image actuelle
  // Effectue une symmetrie d'axe horizontal sur l'image
  // Retourne l'image créée
  Image retournementH() const;

  // Creation d'une copie de l'image actuelle
  // Effectue une symmetrie d'axe vertical sur l'image
  // Retourne l'image créée
  Image retournementV() const;

  // Creation d'une copie de l'image actuelle
  // Effectue une symmetrie d'axe définie par choix ('h' ou 'v') sur l'image
  // Retourne l'image créée
  Image retournement(char choix) const;

  // Creation d'une copie de l'image actuelle
  // Agrandie l'image en fonction du facteur
  // Retourne l'image créée
  Image agrandissement(int facteur) const; // run a l'infini

  // Creation d'une copie de l'image actuelle
  // Retrecie l'image en fonction du facteur
  // Retourne l'image créée
  Image retrecissement(int facteur) const; // runtime error

  bool operator==(const Image&) const;

  Image flou() const;

  Image flouGaussien() const;

  Image gradientX() const;

  Image gradientY() const;

  Image gradient(char choix) const;

  Image contourSobel();

  Image detectionDesBords();

  Image contrasteFiltre() const;

  // Retourne le vecteur rouge de l'image
  vector<vector<int>> getRouge() const;

  // Retourne le vecteur vert de l'image
  vector<vector<int>> getVert() const;

  // Retourne le vecteur bleu de l'image
  vector<vector<int>> getBleu() const;

  // Retourne la hauteur de l'image
  int getHaut() const;

  // Retourne la largeur de l'image
  int getLarg() const;


};

#endif // IMAGE_H_INCLUDED

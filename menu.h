#ifndef _MENU_H_
#define _MENU_H_
#include "image.h"
#include <iostream>
#include <vector>
using namespace std;

// liste des fonctions implémentées
const vector<string> FONCTIONS = {"Composante Rouge",
                                  "Niveau De Gris",
                                  "Deutéranopie (experimental)",
                                  "Protanopie (experimental)",
                                  "Tritanopie (experimental)",
                                  "Noir Et Blanc",
                                  "Augmenter Luminosite",
                                  "Diminuer Luminosite",
                                  "Augmenter Contraste",
                                  "Diminuer Contraste",
                                  "Rogner",
                                  "Rotation",
                                  "Retournement",
                                  "Agrandissement",
                                  "Retrecissement",
                                  "Flou (Filtre)",
                                  "Flou Gaussien (Filtre)",
                                  "Gradient",
                                  "Contour Sobel",
                                  "Detection des bords",
                                  "Contraste (Filtre)",
                                  "Reglage auto",
                                  "Annuler derniere modification"};

// Demande à l'utilisateur de saisir le nom du fichier à éditer
// retourne le nom saisie par l'utilisateur
string saisirFichier();

// Affiche les fonctionnalités disponibles
void listeFonction();

// Demande à l'utilisateur de saisir un entier
// retourne cet entier (qui sera utilisé pour choisir une fonctionnalité)
int choixFonction();

// Demande à l'utilisateur de saisir un facteur
// nécessaire pour certaines fonctionnalités
// et retourne ce facteur
float saisirFacteur();

// Demande à l'utilisateur de saisir une direction parmi haut, bas, gauche,
// droite sous la forme 'h','b','g','d' et retourne le caractere saisi
char saisirDirectionFull();

// Demande à l'utilisateur de saisir une direction parmi gauche ou droite
// sous la forme 'g','d'
// et retourne le caractere saisi
char saisirDirectionGD();

// Demande à l'utilisateur de saisir une direction parmi haut ou bas
// sous la forme 'h','b'
// et retourne le caractere saisi
char saisirDirectionHB();

// Demande à l'utilisateur de saisir un sens (vertical ou horizontal)
// sous la forme 'h','v'
// et retourne le caractere saisi
char saisirSens();

// Crée une copie de l'image "Image"
// et y applique la fonction numéro "choix"
// Puis l'ajoute au vecteur "histor" et la retourne
Image appliquerFonction(Image &image, int choix, vector<Image> &histor);

// Utilise les fonctions précédentes
// pour afficher un menu fonctionnel
void menu();
#endif

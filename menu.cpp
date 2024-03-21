#include "menu.h"
#include "image.h"
#include <iostream>
#include <vector>

string saisirFichier() {
  string nomFichier;
  cout << "Nom du fichier (sans extension): ";
  cin >> nomFichier;
  return nomFichier;
}

void listeFonction() {
  cout << endl << "Fonctionnalités : " << endl;
  for (int i = 0; i < FONCTIONS.size(); i++) {
    // affiche toutes les fonctions du vecteur constant FONCTIONS
    cout << i << " - " << FONCTIONS[i] << endl;
  }
  cout << "Tout autre nombre servira a quitter le programme." << endl;
}

int choixFonction() {
  int choix; // numero de la fonction choisie
  cout << "Choix : ";
  cin >> choix; // saisie d'un entier
  return choix;
}

float saisirFacteur() {
  float facteur; // facteur a retourner
  cout << "Facteur : ";
  cin >> facteur; // saisie d'un nombre décimal (float)
  return facteur;
}

char saisirDirectionFull() {
  char direction; // direction a retourner

  // Boucle de verification de saisie
  do {
    cout << "Direction (Gauche G, Droite D, Haut H, Bas B) : ";
    cin >> direction;               // Saisie d'un caractere
    direction = toupper(direction); // Convertit la saisie en majuscule

    // Recommence tant que la saisie n'est pas valide
  } while (direction != 'G' && direction != 'D' && direction != 'H' &&
           direction != 'B');
  return direction;
}

char saisirDirectionGD() {
  char direction; // direction a retourner

  // Boucle de verification de saisie
  do {
    cout << "Direction (Gauche G, Droite D) : ";
    cin >> direction;               // Saisie d'un caractere
    direction = toupper(direction); // Convertit la saisie en majuscule

    // Recommence tant que la saisie n'est pas valide
  } while (direction != 'G' && direction != 'D');
  return direction;
}

char saisirDirectionHB() {
  char direction; // direction a retourner

  // Boucle de verification de saisie
  do {
    cout << "Direction (Haut H, Bas B) : ";
    cin >> direction;               // Saisie d'un caractere
    direction = toupper(direction); // Convertit la saisie en majuscule

    // Recommence tant que la saisie n'est pas valide
  } while (direction != 'H' && direction != 'B');
  return direction;
}

char saisirSens() {
  char sens; // sens a retourner

  // Boucle de verification de saisie
  do {
    cout << "Sens (Horizontalement , Verticalement V) : ";
    cin >> sens;          // Saisie d'un caractere
    sens = toupper(sens); // Convertit la saisie en majuscule

    // Recommence tant que la saisie n'est pas valide
  } while (sens != 'H' && sens != 'V');
  return sens;
}

Image appliquerFonction(Image &image, int choix, vector<Image> &histor) {
  char direction;   // Direction pour certaines transformations
  float facteur;    // Facteur pour certaines transformations
  Image I1 = image; // Image modifiée

  switch (choix) { // Applique la fonction correspondant a choix
  case 0:
    I1 = image.composanteRouge(); // Crée la nouvelle image
    break;

  case 1:
    I1 = image.niveauGris(); // Crée la nouvelle image
    break;

  case 2:
    I1 = image.visionDeuteranopie(); // Crée la nouvelle image
    break;

  case 3:
    I1 = image.visionProtanopie(); // Crée la nouvelle image
    break;

  case 4:
    I1 = image.visionTritanopie(); // Crée la nouvelle image
    break;

  case 5:
    facteur = saisirFacteur();       // Saisie du facteur
    I1 = image.noirEtBlanc(facteur); // Crée la nouvelle image
    break;

  case 6:
    facteur = saisirFacteur();        // Saisie du facteur
    I1 = image.luminosityUp(facteur); // Crée la nouvelle image
    break;

  case 7:
    facteur = saisirFacteur();          // Saisie du facteur
    I1 = image.luminosityDown(facteur); // Crée la nouvelle image
    break;

  case 8:
    facteur = saisirFacteur();      // Saisie du facteur
    I1 = image.contrastUp(facteur); // Crée la nouvelle image
    break;

  case 9:
    facteur = saisirFacteur();        // Saisie du facteur
    I1 = image.contrastDown(facteur); // Crée la nouvelle image
    break;

  case 10:
    facteur = saisirFacteur();             // Saisie du facteur
    direction = saisirDirectionFull();     // Saisie de la direction
    I1 = image.rogner(facteur, direction); // Crée la nouvelle image
    break;

  case 11:
    direction = saisirDirectionGD(); // Saisie de la direction (uniquement
                                     // gauche/droite)
    I1 = image.rotation(direction);  // Crée la nouvelle image
    break;

  case 12:
    direction = saisirSens();           // Saisie du sens (horizontal/vertical)
    I1 = image.retournement(direction); // Crée la nouvelle image
    break;

  case 13:
    facteur = saisirFacteur();          // Saisie du facteur
    I1 = image.agrandissement(facteur); // Crée la nouvelle image
    break;

  case 14:
    facteur = saisirFacteur();          // Saisie du facteur
    I1 = image.retrecissement(facteur); // Crée la nouvelle image
    break;

  case 15:
    I1 = I1.flou();
    break;

  case 16:
    I1 = I1.flouGaussien();
    break;

  case 17:
    direction = saisirSens();
    I1 = image.gradient(direction);
    break;

  case 18:
    I1 = image.contourSobel();
    break;

  case 19:
    I1 = image.detectionDesBords();
    break;

  case 20:
    I1 = I1.contrasteFiltre();
    break;

  case 21:
    I1 = I1.reglageAuto();
    break;

  case 22:
    I1 = histor.back(); // assigne l'image precedente a I1
    histor.pop_back();  // retire la derniere image de l'historique
    break;
  }
  return I1; // Retourne la nouvelle image
}

void menu() {
  string nomFichier = saisirFichier(); // Saisie du nom du fichier
  Image I1(nomFichier);     // Creation de l'image a partir du fichier
  int choix;           // Choix de la fonction

  vector<Image> historique; // Historique des images
  historique.push_back(I1); // Ajoute l'image de départ a l'historique

  do {
    listeFonction();         // Affiche les fonctions disponibles
    choix = choixFonction(); // Saisie du choix de la fonction
    I1 = appliquerFonction(I1, choix, historique); // Crée la nouvelle image

  } while (choix >= 0 && choix <= FONCTIONS.size()); // Repeter tant que l'utilisateur n'a pas stoppé

  I1.vers_ppm(nomFichier); // Ecrire l'image dans le fichier ppm
}

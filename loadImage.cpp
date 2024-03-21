#include <fstream> // Important !
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void loadImage(string &name, vector<vector<int>> &red,
               vector<vector<int>> &green, vector<vector<int>> &blue) {
  // Declaration des variables
  string line; // pour recuperer les lignes du fichier image au format .ppm, qui
               // est code en ASCII.
  string format; // pour recuperer le format de l'image : celui-ci doit être de
                 // la forme P3
  // string name; // au cas où l'utilisateur se trompe dans le nom de l'image a
  //  charger, on redemande le nom.
  int taille;
  vector<int> mypixels; // pour recuperer les donnees du fichier de maniere
                        // lineaire. On repartira ensuite ces donnees dans les
                        // tableaux correspondants
  ifstream entree; // Declaration d'un "flux" qui permettra ensuite de lire les
                   // donnees de l'image.
  int hauteur;     // pour bien verifier que l'image est carree, et de taille
                   // respectant les conditions fixees par l'enonce
  // Initialisation des variables
  // name = picture;
  // Permet d'ouvrir le fichier portant le nom picture
  // ouverture du fichier portant le nom picture
  entree.open("images/" + name + ".ppm");
  // On verifie que le fichier a bien ete ouvert. Si cela n'est pas le cas, on
  // redemande un nom de fichier valide
  while (!entree) {
    // cin.rdbuf(oldbuf);
    cerr << "Erreur! Impossible de lire de fichier " << name << " ! " << endl;
    cerr << "Redonnez le nom du fichier a ouvrir SVP. Attention sans "
            "l'extension (pas de .ppm)."
         << endl;
    cin >> name;
    entree.open("images/" + name + ".ppm"); // relance
  }
  // Lecture du nombre definissant le format (ici P3)
  entree >> format;
  // on finit de lire la ligne (caractere d'espacement)
  getline(entree, line);
  // Lecture du commentaire
  getline(entree, line);
  // lecture des dimensions
  entree >> taille >> hauteur;
  getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
  // On verifie que l'image a une taille qui verifie bien les conditions
  // requises par l'enonce. Si cela n'est pas le cas, on redemande un fichier
  // valide, et ce, tant que necessaire.
  while (format != "P3") {
    if (format != "P3") {
      cerr << "Erreur! L'image que vous nous avez donnee a un format ne "
              "verifiant pas les conditions requises."
           << endl;
      cerr << "L'image que vous nous avez donnee doit etre codee en ASCII et "
              "non en brut."
           << endl;
    }
    entree.close();
    // On va redemander un nom de fichier valide.
    do {
      cerr << "Veuillez redonner un nom de fichier qui respecte les conditions "
              "de format et de taille. Attention, ce nom doit etre de la forme "
              "nom.ppm."
           << endl;
      cin >> name;
      entree.open("images/" + name + ".ppm"); // relance
    } while (!entree);
    // Lecture du nombre definissant le format (ici P3)
    entree >> format;
    getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
    // Lecture du commentaire
    getline(entree, line);
    // lecture des dimensions
    entree >> taille >> hauteur; // relance
    getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
  }
  // Lecture de la valeur max
  getline(entree, line);
  // Lecture des donnees et ecriture dans les tableaux :
  //  Pour plus de simplicite, on stocke d'abord toutes les donnees dans
  //  mypixels dans l'ordre de lecture puis ensuite on les repartira dans les
  //  differents tableaux.
  // Les donnees stockees dans mypixels sont de la forme RGB RGB RGB ....
  //  Il faudra donc repartir les valeurs R correspondant a la composante rouge
  //  de l'image dans le tableau red, de même pour G et B.
  int pix;
  mypixels.resize(3 * taille *
                  hauteur); // taille fixe : on alloue une fois pour toutes
  for (int i = 0; i < 3 * taille * hauteur; i++) {
    entree >> pix;
    mypixels[i] = pix;
  }
  // Remplissage des 3 tableaux : on repartit maintenant les valeurs dans les
  // bonnes composantes Comme dans mypixels, les donnees sont stockees de la
  // maniere suivante : RGB RGB RGB, il faut mettre les valeurs correspondant a
  // la composante rouge dans red, ... Ainsi, les valeurs de la composante rouge
  // correspondent aux valeurs stockes aux indices congrus a 0 mod 3 dans
  // mypixels, que les valeurs de la composante verte correspond aux valeurs
  // stockes aux indices sont congrus a 1 mod 3, ...
  // les valeurs d'une ligne
  int val;
  red.resize(hauteur);
  green.resize(hauteur);
  blue.resize(hauteur);
  for (int i = 0; i < hauteur; i++) {
    vector<int> ligneR(taille);
    vector<int> ligneB(taille); // les lignes ont toutes la même taille
    vector<int> ligneG(taille);
    for (int j = 0; j < taille; j++) {
      val = mypixels[3 * j + 3 * taille * i];
      ligneR[j] = val;
      val = mypixels[3 * j + 1 + 3 * taille * i];
      ligneG[j] = val;
      val = mypixels[3 * j + 2 + 3 * taille * i];
      ligneB[j] = val;
    }
    red[i] = ligneR;
    green[i] = ligneG;
    blue[i] = ligneB;
  }
  // Informations a l'utilisateur pour dire que tout s'est bien passe
  cout << " L'image " << name << " a bien ete chargee dans les tableaux ."
       << endl;
  entree.close();
}

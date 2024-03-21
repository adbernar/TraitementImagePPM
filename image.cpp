#include "image.h"
#include "filtre.h"
#include "loadImage.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

Image::Image(vector<vector<int>> rouge, vector<vector<int>> vert,
             vector<vector<int>> bleu) {
  if (rouge.size() != bleu.size() || rouge.size() != vert.size()) {
    throw invalid_argument("Un des vecteurs n'est pas de la bonne taille");
  }
  _rouge = rouge;
  _bleu = bleu;
  _vert = vert;
  _hauteur = rouge.size();
  _largeur = rouge[0].size();
}

Image::Image(string &fichier) {
  loadImage(fichier, _rouge, _vert, _bleu);
  _hauteur = _rouge.size();
  _largeur = _rouge[0].size();
}

Image::Image(int hauteur, int largeur) {

  _hauteur = hauteur;
  _largeur = largeur;
  _rouge = vector<vector<int>>(_hauteur, vector<int>(_largeur, 0));
  _vert = vector<vector<int>>(_hauteur, vector<int>(_largeur, 0));
  _bleu = vector<vector<int>>(_hauteur, vector<int>(_largeur, 0));
}

void Image::display() const {
  cout << endl << "rouge" << endl;
  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      cout << " " << _rouge[i][j];
    }
    cout << endl;
  }
  cout << endl << "vert" << endl;
  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      cout << " " << _bleu[i][j];
    }
    cout << endl;
  }
  cout << endl << "bleu" << endl;
  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      cout << " " << _vert[i][j];
    }
    cout << endl;
  }
}

Image Image::composanteRouge() const {
  vector<vector<int>> vert(_hauteur, vector<int>(_largeur, 0));
  vector<vector<int>> bleu(_hauteur, vector<int>(_largeur, 0));
  return Image(_rouge, vert, bleu);
}

Image Image::visionDeuteranopie() const {
  vector<vector<int>> vert(_hauteur, vector<int>(_largeur, 0));
  return Image(_rouge, vert, _bleu);
}

Image Image::visionProtanopie() const {
  vector<vector<int>> rouge(_hauteur, vector<int>(_largeur, 0));
  return Image(rouge, _vert, _bleu);
}

Image Image::visionTritanopie() const {
  vector<vector<int>> bleu(_hauteur, vector<int>(_largeur, 0));
  return Image(_rouge, _vert, bleu);
}

bool Image::detection(int rouge, int vert, int bleu) const {
  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      if (_rouge[i][j] == rouge && _vert[i][j] == vert && _bleu[i][j] == bleu) {
        return true;
      }
    }
  }
  return false;
}

Image Image::niveauGris() const {
  int avg;
  Image I = *this;
  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      avg = (_rouge[i][j] + _vert[i][j] + _bleu[i][j]) /
            3; // calcul de la moyenne
      I._rouge[i][j] = avg;
      I._vert[i][j] = avg;
      I._bleu[i][j] = avg;
    }
  }
  return I;
}

Image Image::noirEtBlanc(int facteur) const {
  if (facteur > 255 || facteur < 0) {
    throw invalid_argument("seuil non compris entre 0 et 255");
  }
  Image I_Gris = this->niveauGris();
  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      if (I_Gris._rouge[i][j] < facteur) {
        I_Gris._rouge[i][j] = 0;
        I_Gris._vert[i][j] = 0;
        I_Gris._bleu[i][j] = 0;
      } else {
        I_Gris._rouge[i][j] = 255;
        I_Gris._vert[i][j] = 255;
        I_Gris._bleu[i][j] = 255;
      }
    }
  }
  return I_Gris;
}

vector<int> Image::histogrammeGris() const {
  Image I_Gris = this->niveauGris();
  vector<int> histogramme(256, 0);
  for (int i = 0; i < I_Gris._rouge.size(); i++) {
    for (int j = 0; j < I_Gris._rouge[i].size(); j++) {
      histogramme[I_Gris._rouge[i][j]]++;
      // I_Gris._rouge[i][j] = valeur gris à l'index i,j
    }
  }
  return histogramme;
}

vector<vector<vector<int>>> Image::histogrammeCouleur() const {
  vector<vector<vector<int>>> histogramme(
      256, vector<vector<int>>(256, vector<int>(256, 0)));
  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      histogramme[_rouge[i][j]][_vert[i][j]][_bleu[i][j]]++;
    }
  }
  return histogramme;
}

int Image::luminositeMoyenne() const {
  Image gris = niveauGris();
  int avg = 0;

  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      avg += gris._rouge[i][j];
    }
  }
  avg = avg / (_largeur * _hauteur);
  return avg;
}

Image Image::luminosityUp(float facteur) const {
  Image I_LumUp = *this;
  if (facteur < 1) { // Verification du facteur
    throw invalid_argument(
        "La luminosité doit être supérieure à 1"); // Envoie d'une erreur en cas
                                                   // de facteur invalide
  }
  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      I_LumUp._rouge[i][j] *= facteur; // Multiplication par le facteur
      I_LumUp._vert[i][j] *= facteur;
      I_LumUp._bleu[i][j] *= facteur;
    }
  }
  I_LumUp.normaliser();
  return I_LumUp;
}

Image Image::luminosityDown(float facteur) const {
  Image I_LumDown = *this;
  if (facteur > 1) { // Verification du facteur
    throw invalid_argument(
        "La luminosité doit être inférieure à 1"); // Envoie d'une erreur en cas
                                                   // de facteur invalide
  }
  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      I_LumDown._rouge[i][j] *= facteur; // Multiplication par le facteur
      I_LumDown._vert[i][j] *= facteur;
      I_LumDown._bleu[i][j] *= facteur;
    }
  }
  I_LumDown.normaliser();
  return I_LumDown;
}

Image Image::contrastUp(float facteur) const {
  Image I_ContrastUp = *this;
  if (facteur < 1) { // vérification du facteur
    throw invalid_argument("Le facteur de contraste doit être supérieure à 1");
  }
  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      I_ContrastUp._rouge[i][j] = (I_ContrastUp._rouge[i][j] - 128) * facteur +
                                  128; // augmentation de la distance à 128

      I_ContrastUp._vert[i][j] =
          (I_ContrastUp._vert[i][j] - 128) * facteur + 128;

      I_ContrastUp._bleu[i][j] =
          (I_ContrastUp._bleu[i][j] - 128) * facteur + 128;
    }
  }
  I_ContrastUp.normaliser(); // normalisation
  return I_ContrastUp;
}

Image Image::contrastDown(float facteur) const {
  Image I_ContrastDown = *this;
  if (facteur > 1 || facteur < 0) { // vérification du facteur
    throw invalid_argument("Le facteur de contraste doit être supérieure à 1");
  }
  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      I_ContrastDown._rouge[i][j] =
          (I_ContrastDown._rouge[i][j] - 128) * facteur +
          128; // réduction de la distance à 128

      I_ContrastDown._vert[i][j] =
          (I_ContrastDown._vert[i][j] - 128) * facteur + 128;

      I_ContrastDown._bleu[i][j] =
          (I_ContrastDown._bleu[i][j] - 128) * facteur + 128;
    }
  }
  I_ContrastDown.normaliser(); // normalisation
  return I_ContrastDown;
}

void Image::normaliser() {
  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      if (_rouge[i][j] > 255) { // Si plus grand que 255 mettre à 255
        _rouge[i][j] = 255;
      } else if (_rouge[i][j] < 0) {
        _rouge[i][j] = 0;
      }
      if (_vert[i][j] > 255) {
        _vert[i][j] = 255;
      } else if (_vert[i][j] < 0) {
        _vert[i][j] = 0;
      }
      if (_bleu[i][j] > 255) {
        _bleu[i][j] = 255;
      } else if (_bleu[i][j] < 0) {
        _bleu[i][j] = 0;
      }
    }
  }
}

Image Image::reglageAuto() const {
  Image I1(_largeur, _hauteur);

  int avgLum = luminositeMoyenne();
  if (avgLum == 0) {
    cout << "Impossible de regler une image avec une luminosité de 0" << endl;
    return I1;
  }

  float lumRatio = 128.0 / avgLum;

  if (avgLum < 128) { // regler la luminosite
    I1 = luminosityUp(lumRatio);
  } else if (avgLum > 128) {
    I1 = luminosityDown(lumRatio);
  }

  I1 = I1.contrastUp(2);
  I1.normaliser();
  return I1;
}

Image Image::rognerD(int nb) const {
  Image I1 = *this;
  for (int i = 0; i < I1._hauteur; i++) {
    for (int j = 0; j < nb; j++) {
      I1._rouge[i].pop_back();
      I1._vert[i].pop_back();
      I1._bleu[i].pop_back();
    }
  }
  I1._largeur = _largeur - nb;
  return I1;
}

Image Image::rognerG(int nb) const {
  Image I(_hauteur);
  for (int i = 0; i < _hauteur; i++) {
    for (int j = nb; j < _largeur; j++) {
      I._rouge[i].push_back(_rouge[i][j]);
      I._bleu[i].push_back(_bleu[i][j]);
      I._vert[i].push_back(_vert[i][j]);
    }
  }
  I._largeur = _largeur - nb;
  return I;
}

Image Image::rognerB(int nb) const {
  Image I1 = *this;
  for (int i = 0; i < nb; i++) {
    I1._rouge.pop_back();
    I1._vert.pop_back();
    I1._bleu.pop_back();
  }
  I1._hauteur = I1._hauteur - nb;
  return I1;
}

Image Image::rognerH(int nb) const {
  Image I;
  I._hauteur = _hauteur - nb;
  I._largeur = _largeur;
  for (int i = nb; i < _hauteur; i++) {
    I._rouge.push_back(_rouge[i]);
    I._bleu.push_back(_bleu[i]);
    I._vert.push_back(_vert[i]);
  }
  return I;
}

Image Image::rogner(int nb, char choix) const {
  choix = toupper(choix);
  switch (choix) {
  case 'G':
    return rognerG(nb);
  case 'D':
    return rognerD(nb);
  case 'B':
    return rognerB(nb);
  case 'H':
    return rognerH(nb);
  default:
    cout << "Erreur de saisie, rien n'a changé" << endl;
    return *this;
  }
}

Image Image::rotationD() const {

  Image I(_hauteur);
  I._largeur = _largeur;
  for (int j = 0; j < _largeur; j++) {
    for (int i = _hauteur - 1; i >= 0; i--) {
      I._vert[j].push_back(_vert[i][j]);
      I._bleu[j].push_back(_bleu[i][j]);
      I._rouge[j].push_back(_rouge[i][j]);
    }
  }
  return I;
}

Image Image::rotationG() const {
  Image I(_hauteur);
  I._largeur = _largeur;
  for (int j = _largeur - 1; j >= 0; j--) {
    for (int i = 0; i < _hauteur; i++) {
      I._vert[_largeur - j - 1].push_back(_vert[i][j]);
      I._bleu[_largeur - j - 1].push_back(_bleu[i][j]);
      I._rouge[_largeur - j - 1].push_back(_rouge[i][j]);
    }
  }
  return I;
}

Image Image::rotation(char choix) const {
  choix = toupper(choix);
  switch (choix) {
  case 'G':
    return rotationG();
  case 'D':
    return rotationD();
  default:
    cout << "Erreur de saisie, rien n'a changé" << endl;
    return *this;
  }
}

Image Image::retournementH() const {
  Image I(_hauteur);
  I._largeur = _largeur;
  for (int i = 0; i < _hauteur; i++) {
    for (int j = _largeur - 1; j >= 0; j--) {
      I._vert[i].push_back(_vert[i][j]);
      I._rouge[i].push_back(_rouge[i][j]);
      I._bleu[i].push_back(_bleu[i][j]);
    }
  }
  return I;
}

Image Image::retournementV() const {
  Image I;
  I._largeur = _largeur;
  I._hauteur = _hauteur;
  for (int i = _hauteur - 1; i >= 0; i--) {
    I._vert.push_back(_vert[i]);
    I._rouge.push_back(_rouge[i]);
    I._bleu.push_back(_bleu[i]);
  }
  return I;
}

Image Image::retournement(char choix) const {
  choix = toupper(choix);
  switch (choix) {
  case 'V':
    return this->retournementV();
  case 'H':
    return this->retournementH();
  default:
    cout << "Erreur de saisie, rien n'a changé" << endl;
    return *this;
  }
}

Image Image::agrandissement(int facteur) const {
  Image I;
  for (int i = 0; i < _hauteur * facteur; i += facteur) {
    I._vert.push_back(vector<int>(0));
    I._rouge.push_back(vector<int>(0));
    I._bleu.push_back(vector<int>(0));
    for (int j = 0; j < _largeur; j++) {
      for (int k = 0; k < facteur; k++) {
        I._vert[i].push_back(_vert[i / facteur][j]);
        I._bleu[i].push_back(_bleu[i / facteur][j]);
        I._rouge[i].push_back(_rouge[i / facteur][j]);
      }
    }
    for (int k = 0; k < facteur - 1; k++) {
      I._vert.push_back(I._vert.back());
      I._rouge.push_back(I._rouge.back());
      I._bleu.push_back(I._bleu.back());
    }
  }
  I._hauteur = _hauteur * facteur;
  I._largeur = _largeur * facteur;
  return I;
}

Image Image::retrecissement(int facteur) const {
  Image I(_hauteur / facteur, _largeur / facteur);
  int moyr;
  int moyv;
  int moyb;
  for (int i = 0; i < _hauteur; i += facteur) {
    for (int j = 0; j < _largeur; j += facteur) {
      moyr = 0;
      moyv = 0;
      moyb = 0;
      for (int k = 0; k < facteur; k++) {
        for (int l = 0; l < facteur; l++) {
          if ((i + k) < _hauteur && (j + l) < _largeur) {
            moyr += _rouge[i + k][j + l];
            moyv += _vert[i + k][j + l];
            moyb += _bleu[i + k][j + l];
          }
        }
      }
      moyr = moyr / (facteur * facteur);
      moyv = moyv / (facteur * facteur);
      moyb = moyb / (facteur * facteur);
      if (i / facteur != I._hauteur && j / facteur != I._largeur) {
        I._rouge[i / facteur][j / facteur] = moyr;
        I._vert[i / facteur][j / facteur] = moyv;
        I._bleu[i / facteur][j / facteur] = moyb;
      }
    }
  }
  return I;
}
vector<vector<int>> Image::getRouge() const { return _rouge; }

vector<vector<int>> Image::getBleu() const { return _bleu; }

vector<vector<int>> Image::getVert() const { return _vert; }

int Image::getHaut() const { return _largeur; }

int Image::getLarg() const { return _hauteur; }

void Image::vers_ppm(const string &nom_fichier) const {

  ofstream output;
  string fichier;
  cout << "\nQuel nom voulez vous donner au nouveau fichier ppm:\n";
  cin >> fichier;
  output.open("images/" + fichier + ".ppm");

  output << "P3" << endl;
  output << "#Image cree par Alain et Adrian\n";
  output << _largeur << " " << _hauteur << endl;

  output << "255\n";
  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      output << _rouge[i][j] << ' ' << _vert[i][j] << ' ' << _bleu[i][j]
             << '\n';
    }
  }
  output.close();
}

bool Image::operator==(const Image &I) const {

  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      if (_rouge[i][j] != I._rouge[i][j] || _vert[i][j] != I._vert[i][j] ||
          _bleu[i][j] != I._bleu[i][j])
        return false;
    }
  }
  return true;
}

Filtre flouG3(vector<vector<float>>{{1.0 / 16.0, 1.0 / 8.0, 1.0 / 16.0},
                                    {1.0 / 8.0, 1.0 / 4.0, 1.0 / 8.0},
                                    {1.0 / 16.0, 1.0 / 8.0, 1.0 / 16.0}});

Filtre flouG5(vector<vector<float>>{
    {1. / 256, 4. / 256, 6. / 256, 4. / 256, 1. / 256},
    {4. / 256, 16. / 256, 24. / 256, 16. / 256, 4. / 256},
    {6. / 256, 24. / 256, 36. / 256, 24. / 256, 6. / 256},
    {4. / 256, 16. / 256, 24. / 256, 16. / 256, 4. / 256},
    {1. / 256, 4. / 256, 6. / 256, 4. / 256, 1. / 256}});

Filtre contraster(vector<vector<float>>{
    {0., -1., 0.}, {-1., 5., -1.}, {0., -1., 0.}});

Filtre GRADIENTX(vector<vector<float>>{{-1, 0, 1}, {-2, 0, 2}, {1, 0, 1}});

Filtre GRADIENTY(vector<vector<float>>{{-1, -2, 1}, {0, 0, 0}, {1, 2, 1}});

Image Image::flou() const { return flouG3.application(*this); }

Image Image::flouGaussien() const { return flouG5.application(*this); }

Image Image::gradientX() const { return GRADIENTX.application(*this); }

Image Image::gradientY() const { return GRADIENTY.application(*this); }

Image Image::gradient(char choix) const {
  switch (choix) {
  case 'H':
    return gradientX();
    break;

  case 'V':
    return gradientY();
    break;

  default:
    cout << "Erreur de saisie, rien n'a changé" << endl;
    return *this;
  }
}

Image Image::contourSobel() {
  Image G(_hauteur, _largeur);
  Image Gx = gradientX();
  Image Gy = gradientY();

  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      G._rouge[i][j] = sqrt(pow(Gx._rouge[i][j], 2) + pow(Gy._rouge[i][j], 2));
      G._vert[i][j] = sqrt(pow(Gx._vert[i][j], 2) + pow(Gy._vert[i][j], 2));
      G._bleu[i][j] = sqrt(pow(Gx._bleu[i][j], 2) + pow(Gy._bleu[i][j], 2));
    }
  }

  G.normaliser();
  return G;
}

Image Image::detectionDesBords() {
  Image G(_hauteur, _largeur);
  Image Gx = gradientX();
  Image Gy = gradientY();

  for (int i = 0; i < _hauteur; i++) {
    for (int j = 0; j < _largeur; j++) {
      G._rouge[i][j] = abs(Gx._rouge[i][j]) + abs(Gy._rouge[i][j]);
      G._vert[i][j] = abs(Gx._vert[i][j]) + abs(Gy._vert[i][j]);
      G._bleu[i][j] = abs(Gx._bleu[i][j]) + abs(Gy._bleu[i][j]);
    }
  }

  G.normaliser();
  return G;
}

Image Image::contrasteFiltre() const { return contraster.application(*this); }

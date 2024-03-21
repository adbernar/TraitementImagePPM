#include "image.h"
#include "loadImage.h"
#include "menu.h"
#include <iostream>
using namespace std;

void mainTest() {

  //---tests automatiques---

  cout << endl << "test composanteRouge():" << endl;
  cout << "cas general (Vecteur rouge avec valeurs non nulles)" << endl;

  Image test({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
             {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
             {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});

  Image expect({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
               {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
               {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

  if (test.composanteRouge() == expect) {
    cout << "test reussi" << endl << endl;
  } else {
    cout << "erreur, image renvoye incorrecte" << endl << endl;
  }

  cout << "cas particulier (Vecteur rouge avec valeurs nulles)" << endl;

  test = Image({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
               {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
               {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});

  expect = Image({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                 {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                 {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

  if (test.composanteRouge() == expect) {
    cout << "test reussi" << endl << endl;
  } else {
    cout << "erreur, image renvoye incorrecte" << endl << endl;
  }

  cout << endl << "test detection():" << endl;
  cout << "cas general (Couleur non dans tableau)" << endl;

  test = Image({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
               {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
               {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});

  if (!test.detection(2, 2, 2)) {
    cout << "test reussi" << endl << endl;
  } else {
    cout << "erreur, renvoie vrai quand la couleur n'est pas dans l'image"
         << endl
         << endl;
  }

  cout << "cas general 2 (Couleur dans tableau)" << endl;

  test = Image({{2, 1, 1}, {1, 1, 1}, {1, 1, 1}},
               {{2, 1, 1}, {1, 1, 1}, {1, 1, 1}},
               {{2, 1, 1}, {1, 1, 1}, {1, 1, 1}});

  if (test.detection(2, 2, 2)) {
    cout << "test reussi" << endl << endl;
  } else {
    cout << "erreur, renvoie faux alors que la couleur est dans l'image" << endl
         << endl;
  }

  cout << "cas particulier (Couleur invalide)" << endl;

  test = Image({{2, 1, 1}, {1, 1, 1}, {1, 1, 1}},
               {{2, 1, 1}, {1, 1, 1}, {1, 1, 1}},
               {{2, 1, 1}, {1, 1, 1}, {1, 1, 1}});

  if (!test.detection(512, 512, 512)) {
    cout << "test reussi" << endl << endl;
  } else {
    cout << "erreur, renvoie vrai alors que la couleur n'est pas dans l'image"
         << endl
         << endl;
  }

  cout << endl << "test noirEtBlanc():" << endl;
  cout << "cas general (seuil compris entre 0 et 255)" << endl;

  test = Image({{120, 120, 120}, {1, 1, 1}, {1, 1, 1}},
               {{120, 120, 120}, {1, 1, 1}, {1, 1, 1}},
               {{120, 120, 120}, {1, 1, 1}, {1, 1, 1}});

  expect = Image({{255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
                 {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}},
                 {{255, 255, 255}, {0, 0, 0}, {0, 0, 0}});

  if (test.noirEtBlanc(100) == expect) {
    cout << "test reussi" << endl << endl;
  } else {
    cout << "erreur, image renvoyé erronée" << endl << endl;
  }

  cout << "cas particulier 1 (Image entièrement noire)" << endl;

  test = Image({{0}}, {{0}}, {{0}});

  expect = Image({{0}}, {{0}}, {{0}});

  if (test.noirEtBlanc(100) == expect) {
    cout << "test reussi" << endl << endl;
  } else {
    cout << "erreur, image renvoyé erronée" << endl << endl;
  }

  cout << "cas particulier 2 (Image entièrement blanche)" << endl;

  test = Image({{255}}, {{255}}, {{255}});

  expect = Image({{255}}, {{255}}, {{255}});

  if (test.noirEtBlanc(100) == expect) {
    cout << "test reussi" << endl << endl;
  } else {
    cout << "erreur, image renvoyé erronée" << endl << endl;
  }

  cout << "cas d'erreur (seuil non compris entre 0 et 255)" << endl;

  try {
    test = Image({{120, 120, 120}, {1, 1, 1}, {1, 1, 1}},
                 {{120, 120, 120}, {1, 1, 1}, {1, 1, 1}},
                 {{120, 120, 120}, {1, 1, 1}, {1, 1, 1}});
    Image I1 = test.noirEtBlanc(256);
  } catch (const invalid_argument &e) {
    cout << "erreur recue, test reussi" << endl;
  }
}
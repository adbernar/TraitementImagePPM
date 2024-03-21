#ifndef _LOADIMAGE_H_INCLUDED
#define _LOADIMAGE_H_INCLUDED
#include <fstream> // Important !
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// loadPicture : prend le nom d'un fichier contenant une image au format ppm,
// remplit 3 tableaux 2D avec les donnees de cette image, et renvoie la taille
// effective de ces tableaux (identique pour les 3 tableaux).
// parametres (D) image : chaine de caracteres
//  		 (R) tabR, tabB, tabG : tableaux [0,MAX-1][0,MAX-1] d'entiers
void loadImage(string &name, vector<vector<int>> &red,
               vector<vector<int>> &green, vector<vector<int>> &blue);

#endif // IMAGE_H_INCLUDED

#ifndef FILTRE_H_INCLUDED
#define FILTRE_H_INCLUDED
#include "image.h"

class Filtre{
    vector<vector<float>> _action;
    int _rayon;

public:
    Filtre(const vector<vector<float>>&);
    Image application(const Image&) const;
};

#endif // FILTRE_H_INCLUDED
#include "image.h"
#include "filtre.h"
using namespace std;

Filtre::Filtre(const vector<vector<float>>& action){
    _action = action;
    _rayon = action.size()/2;

}

Image Filtre::application(const Image& img) const{
    vector<vector<int>> rouge = img.getRouge();
    vector<vector<int>> vert= img.getVert();
    vector<vector<int>> bleu= img.getBleu();

    vector<vector<int>> rougeRes = img.getRouge();
    vector<vector<int>> vertRes = img.getVert();
    vector<vector<int>> bleuRes = img.getBleu();

    int r;
    int v;
    int b;

    for (int i = 0; i < img.getHaut(); i++) {
        for (int j = 0; j < img.getLarg(); j++) {
            r = 0;
            v = 0;
            b = 0;
            for (int k = -(_rayon); k <= _rayon; k++) {
                for (int l = -(_rayon); l <= _rayon; l++) {
                    if (i - k > 0 && i - k < img.getHaut() && j - l > 0 && j - l < img.getLarg()) {
                        r += (rouge[i - k][j - l]) * (_action[k + _rayon][l + _rayon]);
                        v += (vert[i - k][j - l]) * (_action[k + _rayon][l + _rayon]);
                        b += (bleu[i - k][j - l]) * (_action[k + _rayon][l + _rayon]);

                    }
                }
            }
            rougeRes[i][j] = r;
            vertRes[i][j] = v;
            bleuRes[i][j] = b;
        };
    }

    Image newImg(rougeRes, vertRes, bleuRes);
    newImg.normaliser();

    return newImg;
}

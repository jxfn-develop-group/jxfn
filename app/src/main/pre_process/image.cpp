#include "image.hpp"


// the __init__ of Image.
// args:
//     n int,
//     m int,
//     array double array :
//         0, ... , n,
//         ... ,
//         m, ... , m*n
// return:
//     no return value.
Image::Image(int n, int m, int* array):vector()
{
    this->resize(m);
    for (size_t i = 0; i < m; i++) {
        (*this)[i].resize(n);
        for (size_t j = 0; j < n; j++) {
            (*this)[i][j] = array[i*m + j];
        }
    }
}



// the hist table of image.
// args:
//     none,
// return:
//     std::vector<std::pair<int, int>>
std::map<int, int> Image::imageHist()
{
    std::map<int, int> res;
    // Image::iterator is a std::vector<std::vector<int>>::iterator.
    for (Image::iterator i = this->begin(); i != this->end(); i++) {
        for (std::vector<int>::iterator j = i->begin(); j != i->end(); j++) {
            if (res.find(*j) != res.end()) {
                res[*j] += 1;
            }
            else {
                res[*j] = 1;
            }
        }
    }

    return res;
}


// Invert the image. Be ware of that this func doesn't return a Image.
void Image::imageInvert(int threshold)
{
    for (Image::iterator i = this->begin(); i != this->end(); i++) {
        for (std::vector<int>::iterator j = i->begin(); j != i->end(); j++) {
            if (*j > threshold) {
                *j = 0;
            }
            else {
                *j = 255;
            }
        }
    }
}

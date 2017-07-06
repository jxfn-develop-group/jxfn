#include "image.hpp"

Image::Image(int n, int m, double array[]):vector()
/*
    the __init__ of image
    args:
        n int,
        m int,
        array double array :
            0, ... , n,
            ... ,
            m, ... , m*n
    return:
        no return value.
*/
{
    this->resize(m);
    for (size_t i = 0; i < m; i++) {
        (*this)[i].resize(n);
        for (size_t j = 0; j < n; j++) {
            (*this)[i][j] = array[i*m + j];
        }
    }
}

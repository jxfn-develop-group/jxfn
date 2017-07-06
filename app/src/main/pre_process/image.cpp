#include <iostream>

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
    for (auto i = this->begin(); i != this->end(); i++) {
        for (auto j = i->begin(); j != i->end(); j++) {
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
// also do the 2-value work.
void Image::imageInvert(int threshold)
{
    for (auto i = this->begin(); i != this->end(); i++) {
        for (auto j = i->begin(); j != i->end(); j++) {
            if (*j > threshold) {
                *j = 0;
            }
            else {
                *j = 255;
            }
        }
    }
}


// change the image to a 2-value image.
void Image::imageTwoValue(int threshold)
{
    for (auto i = this->begin(); i != this->end(); i++) {
        for (auto j = i->begin(); j != i->end(); j++) {
            if (*j > threshold) {
                *j = 255;
            }
            else {
                *j = 0;
            }
        }
    }
}


// use the hist table to smart choose a threshold.
// automate do the Invert when needed.
// the stardand image means a black background (0) and white text (255)
void Image::imageStandard()
{
    std::map<int, int> hist = this->imageHist();

    auto maxItem = hist.begin();
    auto minItem = hist.begin();
    for (auto i = hist.begin(); i != hist.end(); i++) {
        if (i->second > maxItem->second) {
            maxItem = i;
        }
        if (i->second < minItem->second) {
            minItem = i;
        }
    }

    // if the background is white (255), then invert it.
    if (maxItem->first > minItem->first) {
        this->imageInvert(minItem->first);
    }
    else {
        this->imageTwoValue(minItem->first);
    }
}

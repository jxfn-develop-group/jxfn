#include <iostream>

#include "image.hpp"


// the __init__ of Image.
// args:
//     n int,
//     m int,
//     array double array
// return:
//     no return value.
Image::Image(int n, int m, int* array):vector()
{
    this->resize(n);
    for (size_t i = 0; i < n; i++) {
        (*this)[i].resize(m);
        for (size_t j = 0; j < m; j++) {
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
    for (auto i = hist.begin(); i != hist.end(); i++) {
        if (i->second > maxItem->second) {
            maxItem = i;
        }
    }

    int downloadCnt = 0;
    auto minItem = maxItem;
    auto preItem = hist.begin();
    for (auto i = hist.begin(); i != maxItem; ++i) {
        if (i->second < preItem->second) {
            downloadCnt ++;
        }
        else if (downloadCnt < 3) {
            downloadCnt = 0;
        }
        preItem = i;

        if (i->second < minItem->second && downloadCnt >= 3) {
            minItem = i;
        }
    }

    // if the background is white (255), then invert it.
    if (maxItem->first > 128) {
        this->imageInvert(minItem->first);
    }
    else {
        this->imageTwoValue(minItem->first);
    }
}

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "image.hpp"


int main(int argc, char const *argv[]) {
    int array[1280*960 + 5] = {};

    FILE* inputData = fopen("out1", "r");

    for (size_t i = 0; i < 1280*960; i++) {
        fscanf(inputData, "%d", &array[i]);
    }

    Image img(1280, 960, array);

    for (size_t i = 0; i < 960; i++) {
        for (size_t j = 0; j < 1280; j++) {
            // std::cout << img[i][j] << '\n';
        }
    }

    auto res = img.imageHist();
    for (std::map<int, int>::iterator it = res.begin(); it != res.end(); it++) {
        // std::cout << it->first << ' ' << it->second << '\n';
    }

    // std::cout << "=================================================" << '\n';

    // img.imageStandard();
    img.imageInvert(134);
    for (size_t i = 0; i < 960; i++) {
        for (size_t j = 0; j < 1280; j++) {
            std::cout << img[i][j] << '\n';
        }
    }

    res = img.imageHist();
    for (std::map<int, int>::iterator it = res.begin(); it != res.end(); it++) {
        // std::cout << it->first << ' ' << it->second << '\n';
    }

    return 0;
}

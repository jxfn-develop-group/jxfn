#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "image.hpp"


int main(int argc, char const *argv[]) {
    int array[1200*900 + 5] = {};

    FILE* inputData = fopen("out1", "r");

    for (size_t i = 0; i < 1200*900; i++) {
        fscanf(inputData, "%d", &array[i]);
    }

    Image img(1200, 900, array);

    for (size_t i = 0; i < 900; i++) {
        for (size_t j = 0; j < 1200; j++) {
            // std::cout << img[i][j] << '\n';
        }
    }

    auto res = img.imageHist();
    for (std::map<int, int>::iterator it = res.begin(); it != res.end(); it++) {
        std::cout << it->first << ' ' << it->second << '\n';
    }

    img.imageStandard();
    for (size_t i = 0; i < 900; i++) {
        for (size_t j = 0; j < 1200; j++) {
            // std::cout << img[i][j] << '\n';
        }
    }

    res = img.imageHist();
    for (std::map<int, int>::iterator it = res.begin(); it != res.end(); it++) {
        std::cout << it->first << ' ' << it->second << '\n';
    }

    return 0;
}

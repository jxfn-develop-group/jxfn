#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "image.hpp"


int main(int argc, char const *argv[]) {
    // int cnt = 0;
    const int n = 1280;
    const int m = 960;
    int array[1280*960 + 5] = {};

    FILE* inputData = fopen("out1", "r");

    for (size_t i = 0; i < n*m; i++) {
        fscanf(inputData, "%d", &array[i]);
    }

    Image img(1280, 960, array);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            // std::cout << img[i][j] << '\n';
        }
    }

    auto res = img.imageHist();
    for (std::map<int, int>::iterator it = res.begin(); it != res.end(); it++) {
        // std::cout << it->first << ' ' << it->second << '\n';
    }

    img.imageStandard();
    // img.imageInvert(87);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            std::cout << img[i][j] << '\n';
        }
    }

    res = img.imageHist();
    for (std::map<int, int>::iterator it = res.begin(); it != res.end(); it++) {
        // std::cout << it->first << ' ' << it->second << '\n';
    }

    return 0;
}

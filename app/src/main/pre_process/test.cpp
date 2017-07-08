#include <cstdio>
#include <fstream>
#include <iostream>
#include "image.hpp"


int main(int argc, char const *argv[]) {
    // int cnt = 0;
    const int n = 1280;
    const int m = 960;
    int array[1280*960] = {0};

    std::ifstream ifs("out1", std::fstream::in);
    for (int i = 0; i < n*m; i++) {
        ifs >> array[i];
    }
    ifs.close();

    Image img(n, m, array);

    // for (size_t i = 0; i < n; i++) {
    //     for (size_t j = 0; j < m; j++) {
    //         std::cout << img[i][j] << ' ';
    //     }
    //     std::cout << '\n';
    // }

    auto res = img.imageHist();
    for (std::map<int, int>::iterator it = res.begin(); it != res.end(); it++) {
        // std::cout << it->first << ' ' << it->second << '\n';
    }

    img.imageStandard();
    // img.imageInvert(87);
    // for (size_t i = 0; i < n; i++) {
    //     for (size_t j = 0; j < m; j++) {
    //         std::cout << img[i][j] << ' ';
    //     }
    //     std::cout << '\n';
    // }

    res = img.imageHist();
    for (std::map<int, int>::iterator it = res.begin(); it != res.end(); it++) {
        // std::cout << it->first << ' ' << it->second << '\n';
    }

    auto grids = img.findGrid();
    for (auto i = grids.begin(); i != grids.end(); ++i) {
        for (auto j = i->begin(); j != i->end(); ++j) {
            std::cout << *j << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}

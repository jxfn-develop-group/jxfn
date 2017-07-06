#include <iostream>
#include "image.hpp"


int main(int argc, char const *argv[]) {
    int array[4] = {1, 147, 255, 255};
    Image img(2, 2, array);

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            std::cout << img[i][j] << '\n';
        }
    }

    auto res = img.imageHist();

    for (std::map<int, int>::iterator it = res.begin(); it != res.end(); it++) {
        std::cout << it->first << ' ' << it->second << '\n';
    }

    img.imageStandard();
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            std::cout << img[i][j] << '\n';
        }
    }

    return 0;
}

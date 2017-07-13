#include <cstdio>
#include <string>
#include <sstream>
#include "image.hpp"
#include "charsort.hpp"
#include "interface.hpp"
#include "edu_jxfn_jxfn_PreProcess.hpp"


std::string IntToString (long a)
{
    std::ostringstream temp;
    temp<<a;
    return temp.str();
}



JNIEXPORT jstring JNICALL Java_edu_jxfn_jxfn_PreProcess_preProcess(
    JNIEnv* env, jclass cls, jintArray jArray)
{
    jint arrayLen = env->GetArrayLength(jArray);

    if (arrayLen < 1280*960) {
        return env->NewStringUTF("Error!");
    }
    jint* arr = env->GetIntArrayElements(jArray, false);
    int buff[1280*960] = {};
    for (int i = 0; i < 1280*960; ++i) {
        buff[i] = arr[i];
    }
    int n = 1280;
    int m = 960;
    Image img(n, m, buff);
    img.imageStandard();
    auto grids = img.findGrid();
    // std::string tres = IntToString(grids.end() - grids.begin());
    // return env->NewStringUTF(tres.c_str());
    for (auto grid = grids.begin(); grid != grids.end(); ++grid) {
        grid->push_back(cnnInterface(img.resizeGrid(*grid)));
    }
    std::string res = charasort(grids);
    return env->NewStringUTF(res.c_str());
}


// int main(int argc, char const *argv[]) {
//     // int cnt = 0;
//     const int n = 1280;
//     const int m = 960;
//     int array[1280*960] = {0};
//
//     std::ifstream ifs("out1", std::fstream::in);
//     for (int i = 0; i < n*m; i++) {
//         ifs >> array[i];
//     }
//     ifs.close();
//
//     Image img(n, m, array);
//
//     auto res = img.imageHist();
//     for (auto it = res.begin(); it != res.end(); it++) {
//         // std::cout << it->first << ' ' << it->second << '\n';
//     }
//
//     img.imageStandard();
//     // img.imageInvert(87);
//     // for (auto i = img.begin(); i != img.end(); ++i) {
//     //     for (auto j = i->begin(); j != i->end(); ++j) {
//     //         std::cout << *j << ' ';
//     //     }
//     //     std::cout << '\n';
//     // }
//
//     res = img.imageHist();
//     for (auto it = res.begin(); it != res.end(); it++) {
//         // std::cout << it->first << ' ' << it->second << '\n';
//     }
//
//     auto grids = img.findGrid();
//     for (auto grid = grids.begin(); grid != grids.end(); ++grid) {
//         for (auto j = grid->begin(); j != grid->end(); ++j) {
//             std::cout << *j << ' ';
//         }
//         std::cout << '\n';
//         // int& x1 = (*grid)[0];
//         // int& x2 = (*grid)[2];
//         // int& y1 = (*grid)[1];
//         // int& y2 = (*grid)[3];
//         // for (int i = x1; i <= x2; ++i) {
//         //     for (int j = y1; j<= y2; ++j) {
//         //         if (img[i][j]) {
//         //             std::cout << 1;
//         //         }
//         //         else {
//         //             std::cout << 0;
//         //         }
//         //     }
//         //     std::cout << '\n';
//         // }
//         auto resizeGrid = img.resizeGrid(*grid);
//         // for (int i = x1; i <= x2; ++i) {
//         //     for (int j = y1; j<= y2; ++j) {
//         //         if (img[i][j]) {
//         //             std::cout << 1;
//         //         }
//         //         else {
//         //             std::cout << 0;
//         //         }
//         //     }
//         //     std::cout << '\n';
//         // }
//         for (auto i = resizeGrid.begin(); i != resizeGrid.end(); ++i) {
//             for (auto j = i->begin(); j != i->end(); ++j) {
//                 if (*j) {
//                     std::cout << 1;
//                 }
//                 else {
//                     std::cout << 0;
//                 }
//             }
//             std::cout << '\n';
//         }
//     }
//
//     return 0;
// }

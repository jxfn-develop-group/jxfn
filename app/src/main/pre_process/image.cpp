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


// return the Grid that contain at least one pixels is white(255).
// return :
//      res [[0, 1, 2, 3], ..., ]
//      each of vector in stand of a grid [x1, y1, x2, y2]
//      (x1, y2) ... (x2, y2)
//      ...      ... ...
//      (x1, y1) ... (x2, y1)
std::vector<std::vector<int>> Image::findGrid()
{
    int dir[4][2] = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    };
    std::vector<std::vector<int>> res;
    std::set<std::pair<int, int>> vis;
    std::queue<std::pair<int, int>> bfsQueue;

    for (auto i = this->begin(); i != this->end(); ++i) {
        for (auto j = i->begin(); j != i->end(); ++j) {
            // you should turn this Image to a 2-value first.
            // white = 255.
            if (*j == 255) {
                // bfs
                int nowX = i - this->begin();
                int nowY = j - i->begin();
                // the start point.
                std::pair<int, int> coordinate(nowX, nowY);

                // check whether this point has been visited.
                if (vis.find(coordinate) != vis.end()) {
                    continue;
                }
                bfsQueue.push(coordinate);

                // the edge of Grid.
                // [x1, y1, x2, y2]
                //      (x1, y2) ... (x2, y2)
                //      ...      ... ...
                //      (x1, y1) ... (x2, y1)
                std::vector<int> edge;
                edge.resize(4);
                // x1, x2
                edge[0] = edge[2] = nowX;
                // y1, y2
                edge[1] = edge[3] = nowY;

                while (!bfsQueue.empty()) {
                    coordinate = bfsQueue.front();
                    bfsQueue.pop();
                    if (vis.find(coordinate) != vis.end()) {
                        continue;
                    }
                    vis.insert(coordinate);

                    nowX = coordinate.first;
                    nowY = coordinate.second;

                    int nextX = 0;
                    int nextY = 0;
                    for (size_t k = 0; k < 4; k++) {
                        // next point.
                        nextX = nowX + dir[k][0];
                        nextY = nowY + dir[k][1];

                        std::pair<int, int> nextCoordinate(nextX, nextY);

                        // prevent that array out of range.
                        if (nextX >= this->size()) {
                            continue;
                        }
                        if (nextY >= i->size()) {
                            continue;
                        }

                        // reflash edge
                        if ((*this)[nextX][nextY] == 255 &&
                                vis.find(nextCoordinate) == vis.end()) {
                            bfsQueue.push(nextCoordinate);
                            // x1, x2
                            if (nextX < edge[0]) {
                                edge[0] = nextX;
                            }
                            else if (nextX > edge[2]) {
                                edge[2] = nextX;
                            }
                            // y1, y2
                            if (nextY < edge[1]) {
                                edge[1] = nextY;
                            }
                            else if (nextY > edge[3]) {
                                edge[3] = nextY;
                            }
                        }
                    }
                }

                res.push_back(edge);
            }
        }
    }

    return res;
}

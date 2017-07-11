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
    this->resize(m);
    for (size_t i = 0; i < m; i++) {
        (*this)[i].resize(n);
        for (size_t j = 0; j < n; j++) {
            (*this)[i][j] = array[i*n + j];
        }
    }
}


// the hist table of image.
// args:
//     none,
// return:
//     std::map<int, int>
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
// you should turn this Image to a 2-value first.
std::vector<std::vector<int>> Image::findGrid()
{
    int dir[8][2] = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0},
        {1, 1},
        {1, -1},
        {-1, 1},
        {-1, -1}
    };
    std::set<std::pair<int, int>> vis;
    std::vector<std::vector<int>> res;
    std::queue<std::pair<int, int>> bfsQueue;
    // find grids.
    for (auto i = this->begin(); i != this->end(); ++i) {
        for (auto j = i->begin(); j != i->end(); ++j) {
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
                // the begin of bfs.
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
                // bfs cycle.
                while (!bfsQueue.empty()) {
                    coordinate = bfsQueue.front();
                    bfsQueue.pop();
                    // if this point has been visited.
                    if (vis.find(coordinate) != vis.end()) {
                        continue;
                    }
                    // mark this point as visited.
                    vis.insert(coordinate);
                    // update nowPoint.
                    nowX = coordinate.first;
                    nowY = coordinate.second;
                    // update edge.
                    // x1, x2
                    if (nowX < edge[0]) {
                        edge[0] = nowX;
                    }
                    else if (nowX > edge[2]) {
                        edge[2] = nowX;
                    }
                    // y1, y2
                    if (nowY < edge[1]) {
                        edge[1] = nowY;
                    }
                    else if (nowY > edge[3]) {
                        edge[3] = nowY;
                    }
                    int nextX = 0;
                    int nextY = 0;
                    for (size_t k = 0; k < 8; k++) {
                        // next point.
                        nextX = nowX + dir[k][0];
                        nextY = nowY + dir[k][1];
                        std::pair<int, int> nextCoordinate(nextX, nextY);
                        // prevent that array out of range.
                        if (nextX >= this->size() || nextX < 0) {
                            continue;
                        }
                        if (nextY >= i->size() || nextY < 0) {
                            continue;
                        }
                        // reflash edge
                        if ((*this)[nextX][nextY] == 255 &&
                                vis.find(nextCoordinate) == vis.end()) {
                            // if not visited next point.
                            bfsQueue.push(nextCoordinate);
                        }
                    }
                }
                if (this->gridJudge(edge)) {
                    res.push_back(edge);
                }
            }
        }
    }
    // merge the grids.
    std::vector<std::vector<int>> mergeRes;
    std::set<std::vector<std::vector<int>>::iterator> mergeVis;
    for (auto base = res.begin(); base != res.end(); ++base) {
        int mergeFlag = 0;
        // merge aim into base.
        if (mergeVis.find(base) != mergeVis.end()) {
            continue;
        }
        for (auto aim = base; aim != res.end(); ++aim) {
            // jump the first one.
            if (aim == base) {
                continue;
            }
            if (mergeVis.find(aim) != mergeVis.end()) {
                continue;
            }
            // judge.
            int baseX1 = (*base)[0];
            int baseX2 = (*base)[2];
            int baseY1 = (*base)[1];
            int baseY2 = (*base)[3];
            int aimX1 = (*aim)[0];
            int aimX2 = (*aim)[2];
            int aimY1 = (*aim)[1];
            int aimY2 = (*aim)[3];
            std::pair<int, int> baseCenter(
                (baseX1 + baseX2)/2, (baseY1 + baseY2)/2
            );
            std::pair<int, int> aimCenter(
                (aimX1 + aimX2)/2, (aimY1 + aimY2)/2
            );
            if ((aimCenter.second > baseY1 && aimCenter.second < baseY2) ||
                    (baseCenter.second > aimY1 && baseCenter.second > aimY2)) {
                int disX = aimCenter.first - baseCenter.first;
                if (disX < 0) {
                    disX *= -1;
                }
                // judge if disX is small enough.
                if (disX < (baseX2-baseX1)/2 || disX < (aimX2 - aimX1)/2) {
                    // merge the aim into base.
                    std::vector<int> mergeBaseAim;
                    mergeBaseAim.resize(4);
                    mergeBaseAim[0] = std::min((*base)[0], (*aim)[0]);
                    mergeBaseAim[1] = std::min((*base)[1], (*aim)[1]);
                    mergeBaseAim[2] = std::max((*base)[2], (*aim)[2]);
                    mergeBaseAim[3] = std::max((*base)[3], (*aim)[3]);
                    mergeRes.push_back(mergeBaseAim);
                    mergeVis.insert(aim);
                    mergeFlag = 1;
                    break;
                }
            }
        }
        mergeVis.insert(base);
        if (mergeFlag == 0) {
            mergeRes.push_back(*base);
        }
    }
    // return res;
    return mergeRes;
}


// judge whether a grid is big enough.
bool Image::gridJudge(std::vector<int> edge)
{
    if (edge.size() != 4) {
        return false;
    }
    int col = edge[2] - edge[0] + 1;
    int row = edge[3] - edge[1] + 1;
    if (col < 2 && row < 2) {
        return false;
    }
    return true;
}

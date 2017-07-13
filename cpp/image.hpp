#ifndef _IMAGE_H
#define _IMAGE_H "image headers"
    #include <map>
    #include <set>
    #include <queue>
    #include <vector>
    #include <algorithm>

    class Image : public std::vector<std::vector<int> >{
        public:
            Image(int n, int m, int* array);

            // return the hist table of Image.
            std::map<int, int> imageHist();
            // invert image. (0 -> 255 while 255 -> 0)
            void imageInvert(int threshold);
            void imageTwoValue(int threshold);
            // stardand the image.
            void imageStandard(int invert);
            // find grid that contain a AlphaBeta
            // be ware of that may contain nothing at all.
            std::vector<std::vector<int> > findGrid();
            // resize the grids.
            // args:
            //      grid std::vector<int> size 4 [x1, y1, x2, y2],
            // return:
            //      a 2-d vector of int include val of image that lagra 28*28.
            std::vector<std::vector<int> > resizeGrid(std::vector<int> grid);
        private:
            bool gridJudge(std::vector<int> edge);
    };
#endif

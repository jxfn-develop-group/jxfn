#ifndef _IMAGE_H
#define _IMAGE_H "image headers"
    #include <map>
    #include <set>
    #include <queue>
    #include <vector>
    #include <algorithm>

    class Image : public std::vector<std::vector<int>>{
        public:
            Image(int n, int m, int* array);

            // return the hist table of Image.
            std::map<int, int> imageHist();
            // invert image. (0 -> 255 while 255 -> 0)
            void imageInvert(int threshold);
            void imageTwoValue(int threshold);
            // stardand the image.
            void imageStandard();
            // find grid that contain a AlphaBeta
            // be ware of that may contain nothing at all.
            std::vector<std::vector<int>> findGrid();
        private:
            bool gridJudge(std::vector<int> edge);
    };
#endif

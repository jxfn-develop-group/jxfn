#ifndef _IMAGE_H
#define _IMAGE_H "image headers"
    #include <map>
    #include <vector>

    class Image : public std::vector<std::vector<int>>{
        public:
            Image(int n, int m, int* array);
            std::map<int, int> imageHist();
    };
#endif

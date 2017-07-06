#ifndef _IMAGE_H
#define _IMAGE_H "image headers"
    #include <vector>

    class Image : public std::vector<std::vector<double>>{
        public:
            Image(int n, int m, double array[]);
    };
#endif

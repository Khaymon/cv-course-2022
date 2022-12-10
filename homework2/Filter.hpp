#ifndef __BMP_IMAGE__
    #define __BMP_IMAGE__
    #include "BmpImage.hpp"
#endif

#ifndef __PIXEL__
    #define __PIXEL__
    #include "Pixel.hpp"
#endif


class MedianFilter {
public:
    BmpImage SortingFilter(BmpImage&, int);
    BmpImage HuangFilter(BmpImage&, int);
    BmpImage PerreaultFilter(BmpImage&, int);

private:
    std::vector<int> GetColorValues(std::vector<Pixel>&, Color);
    Pixel GetMedianPixel(std::vector<Pixel>&);
    double GetMedian(std::vector<int>&);
    double GetHistogramMedian(std::vector<int>&);

    void CountingSort(std::vector<int>&);
};
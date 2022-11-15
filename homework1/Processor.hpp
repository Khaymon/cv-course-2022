#include <vector>

#ifndef __PIXEL__
    #define __PIXEL__
    #include "Pixel.hpp"
#endif

#ifndef __COLOR__
    #define __COLOR__
    #include "Color.hpp"
#endif

#ifndef __BMP_IMAGE__
    #define __BMP_IMAGE__
    #include "BmpImage.hpp"
#endif

class ProcessorTester;

class Processor {
public:
    BmpImage PreprocessImage(BmpImage&);
private:
    Pixel PreprocessPixel(BmpImage&, Position);

    friend class ProcessorTester;
};

class ProcessorTester {
public:
    Pixel PreprocessPixel(Processor processor, BmpImage& bmp_image, Position position) {
        return processor.PreprocessPixel(bmp_image, position);
    }
};
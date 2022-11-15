#include <iostream>
#include <vector>

#ifndef __BMP_IMAGE__
    #define __BMP_IMAGE__
    #include "BmpImage.hpp"
#endif

#ifndef __POSITION__
    #define __POSITION__
    #include "Position.hpp"
#endif

#ifndef __PROCESSOR__
    #define __PROCESSOR__
    #include "Processor.hpp"
#endif

#ifndef __GRADIENT__
    #define __GRADIENT__
    #include "Gradient.hpp"
#endif

#include "bitmap_image.hpp"

int main() {
    std::string input_image_path = "./resources/RGB_CFA.bmp";
    std::string output_image_path = "./resources/RGB_CFA_result.bmp";

    Processor processor;
    
    BmpImage image(std::move(input_image_path));
    BmpImage result_image = processor.PreprocessImage(image);

    result_image.SaveImage(std::move(output_image_path));
}
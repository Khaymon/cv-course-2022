#include <iostream>
#include <vector>
#include <stdexcept>
#include <chrono>

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

    BmpImage input_image(std::move(input_image_path));

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    BmpImage result_image = processor.PreprocessImage(input_image);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    size_t width = input_image.GetWidth();
    size_t height = input_image.GetHeight();

    double num_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    double num_seconds = num_milliseconds / 1000;
    double seconds_per_pixel = num_seconds / (width * height);
    double seconds_per_megapixel = seconds_per_pixel * 1000000;

    std::cout << "Image shape: (" << width << ", " << height << ")" << std::endl;
    std::cout << "Speed is " << seconds_per_megapixel << " seconds per megapixel" << std::endl;

    result_image.SaveImage(std::move(output_image_path));
}
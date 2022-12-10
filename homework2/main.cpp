#include <iostream>
#include <chrono>

#ifndef __BMP_IMAGE__
    #define __BMP_IMAGE__
    #include "BmpImage.hpp"
#endif

#include "Filter.hpp"


bool CheckImages(BmpImage& first_image, BmpImage& second_image) {
    if (first_image.GetHeight() != second_image.GetHeight() || first_image.GetWidth() != second_image.GetWidth()) {
        return false;
    }

    int height = first_image.GetHeight();
    int width = first_image.GetWidth();

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            Pixel first_pixel = first_image.Get(Position(i, j));
            Pixel second_pixel = second_image.Get(Position(i, j));

            if (first_pixel.red != second_pixel.red || first_pixel.green != second_pixel.green ||
                first_pixel.blue != second_pixel.blue) {
                
                return false;
            }
        }
    }

    return true;
}

double MillisecondsForMegapixel(std::chrono::steady_clock::time_point begin, 
                                std::chrono::steady_clock::time_point end, int height, int width) {
    double num_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    double milliseconds_per_pixel = num_milliseconds / (width * height);
    double milliseconds_per_megapixel = milliseconds_per_pixel * 1000000;

    return milliseconds_per_megapixel;
}

int main() {
    std::string input_image_path = "./resources/sample.bmp";

    std::string window_5_result_image_path = "./resources/window_5_result.bmp";
    std::string window_15_result_image_path = "./resources/window_15_result.bmp";
    std::string window_35_result_image_path = "./resources/window_35_result.bmp";

    BmpImage input_image(std::move(input_image_path));

    MedianFilter filter;

    BmpImage result_image = filter.HuangFilter(input_image, 5);
    result_image.SaveImage(std::move(window_5_result_image_path));

    result_image = filter.HuangFilter(input_image, 15);
    result_image.SaveImage(std::move(window_15_result_image_path));

    result_image = filter.HuangFilter(input_image, 35);
    result_image.SaveImage(std::move(window_35_result_image_path));
}
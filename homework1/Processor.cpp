#include <vector>
#include <stdexcept>

#ifndef __PROCESSOR__
    #define __PROCESSOR__
    #include "Processor.hpp"
#endif

#ifndef __GRADIENT__
    #define __GRADIENT__
    #include "Gradient.hpp"
#endif

BmpImage Processor::PreprocessImage(BmpImage& bmp_image) {
    BmpImage preprocessed_image(bmp_image);

    for (int i = 0; i < bmp_image.GetWidth(); ++i) {
        for (int j = 0; j < bmp_image.GetHeight(); ++j) {
            preprocessed_image.Set(Position(i, j), PreprocessPixel(bmp_image, Position(i, j)));
        }
    }

    return preprocessed_image;
}

Pixel Processor::PreprocessPixel(BmpImage& bmp_image, Position position) {
    double k1 = 1.5;
    double k2 = 0.5;

    Color pixel_color = bmp_image.GetPixelColor(position);
    int pixel_value = bmp_image.GetPixelValue(position);

    GradientsBunch gradients_bunch(bmp_image, position);

    double max_gradient = gradients_bunch.GetMaxGradient();
    double min_gradient = gradients_bunch.GetMinGradient();

    double threshold = (k1 * min_gradient) + (k2 * (max_gradient + min_gradient));
    // std::cout << "Threshold: " << threshold << std::endl;

    std::vector<Gradient> gradients_subset = gradients_bunch.FilterByThreshold(threshold);

    double red_sum = 0;
    double green_sum = 0;
    double blue_sum = 0;

    for (auto& gradient: gradients_subset) {
        Pixel gradient_averages = gradient.GetAverages();
        // std::cout << "Gradient with averages: " << gradient_averages.red << " " << gradient_averages.green << " " << gradient_averages.blue << std::endl;
        red_sum += gradient_averages.red;
        green_sum += gradient_averages.green;
        blue_sum += gradient_averages.blue;
    }

    Pixel pixel;

    if (pixel_color == Color::GREEN) {
        // std::cout << "Green color" << std::endl;
        pixel.green = pixel_value;
        pixel.red = pixel.green + (red_sum - green_sum) / gradients_subset.size();
        pixel.blue = pixel.green + (blue_sum - green_sum) / gradients_subset.size();
    } else if (pixel_color == Color::RED) {
        // std::cout << "Red color" << std::endl;
        pixel.red = pixel_value;
        pixel.green = pixel.red + (green_sum - red_sum) / gradients_subset.size();
        pixel.blue = pixel.red + (blue_sum - red_sum) / gradients_subset.size();
    } else if (pixel_color == Color::BLUE) {
        // std::cout << "Blue color" << std::endl;
        pixel.blue = pixel_value;
        pixel.green = pixel.blue + (green_sum - blue_sum) / gradients_subset.size();
        pixel.red = pixel.blue + (red_sum - blue_sum) / gradients_subset.size();
    } else {
        throw std::invalid_argument("Invalid color");
    }

    // pixel.red = std::max(pixel.red, 0.f);
    // pixel.green = std::max(pixel.green, 0.f);
    // pixel.blue = std::max(pixel.blue, 0.f);

    // pixel.red = std::min(pixel.red, 255.f);
    // pixel.green = std::min(pixel.green, 255.f);
    // pixel.blue = std::min(pixel.blue, 255.f);

    return pixel;
}
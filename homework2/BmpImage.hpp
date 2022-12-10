#include <vector>
#include <string>

#include "bitmap_image.hpp"
#ifndef __PIXEL__
    #define __PIXEL__
    #include "Pixel.hpp"
#endif

#ifndef __COLOR__
    #define __COLOR__
    #include "Color.hpp"
#endif

#ifndef __POSITION__
    #define __POSITION__
    #include "Position.hpp"
#endif

class BmpImageTester;

class BmpImage {
public:
    BmpImage(std::string&&);
    BmpImage() {};

    size_t GetWidth();
    size_t GetHeight();

    Pixel Get(Position);
    Color GetPixelColor(Position);
    double GetPixelValue(Position);

    Pixel Set(Position, Pixel);
    void SaveImage(std::string&&);
private:

    size_t height_;
    size_t width_;
    std::vector<std::vector<Pixel>> bmp_image_;

    friend class BmpImageTester;
};

class BmpImageTester {
public:
    void SetBmpImage(std::vector<std::vector<Pixel>>& image) {
        bmp_image.width_ = image.size();
        bmp_image.height_ = image[0].size();

        bmp_image.bmp_image_ = std::vector<std::vector<Pixel>>(bmp_image.width_, std::vector<Pixel>(bmp_image.height_, Pixel()));

        for (int i = 0; i < bmp_image.width_; ++i) {
            for (int j = 0; j < bmp_image.height_; ++j) {
                bmp_image.bmp_image_[i][j] = image[i][j];
            }
        }
    }

    BmpImage bmp_image;
};
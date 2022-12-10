#include <string>
#include <exception>

#ifndef __BMP_IMAGE__
    #define __BMP_IMAGE__
    #include "BmpImage.hpp"
#endif

BmpImage::BmpImage(std::string&& path) {
    bitmap_image image(path);
    this->bmp_image_ = std::vector<std::vector<Pixel>>(image.width(), std::vector<Pixel>(image.height()));

    width_ = image.width();
    height_ = image.height();

    for (int i = 0; i < this->bmp_image_.size(); ++i) {
        for (int j = 0; j < this->bmp_image_[i].size(); ++j) {
            this->bmp_image_[i][j].red = image.get_pixel(i, j).red;
            this->bmp_image_[i][j].green = image.get_pixel(i, j).green;
            this->bmp_image_[i][j].blue = image.get_pixel(i, j).blue;
        }
    }
}

Pixel BmpImage::Get(Position position) {
    if (position.x < 0 || position.x >= width_ || position.y < 0 || position.y >= height_) {
        return Pixel();
    }

    return bmp_image_[position.x][position.y];
}

size_t BmpImage::GetWidth() {
    return width_;
}

size_t BmpImage::GetHeight() {
    return height_;
}

Color BmpImage::GetPixelColor(Position position) {
    if (position.x < 0 || position.x >= width_ || position.y < 0 || position.y >= height_) {
        return Color::UNKNOWN;
    }

    if ((position.x + position.y) % 2 == 0) {
        if (position.x % 2 == 0) {
            return Color::RED;
        }
        
        return Color::BLUE;
    }
    
    return Color::GREEN;
}

double BmpImage::GetPixelValue(Position position) {
    Color pixel_color = GetPixelColor(position);
    if (pixel_color == Color::UNKNOWN) {
        return 0;
    } else if (pixel_color == Color::RED) {
        return bmp_image_[position.x][position.y].red;
    } else if (pixel_color == Color::GREEN) {
        return bmp_image_[position.x][position.y].green;
    } else if (pixel_color == Color::BLUE) {
        return bmp_image_[position.x][position.y].blue;
    } else {
        throw std::invalid_argument("Pixel color is not in the lisft of colors!");
    }
}

Pixel BmpImage::Set(Position position, Pixel pixel) {
    if (position.x < 0 || position.x >= width_ || position.y < 0 || position.y >= height_) {
        std::cout << position.x << " " << position.y << std::endl;
        throw std::invalid_argument("Pixel coordinate is out-of-bounds");
    }

    bmp_image_[position.x][position.y] = pixel;
    
    return pixel;
}

void BmpImage::SaveImage(std::string&& path) {
    bitmap_image image(width_, height_);

    for (int i = 0; i < width_; ++i) {
        for (int j = 0; j < height_; ++j) {
            Pixel pixel = Get(Position(i, j));
            image.set_pixel(i, j, pixel.red, pixel.green, pixel.blue);
        }
    }

    image.save_image(path);
}
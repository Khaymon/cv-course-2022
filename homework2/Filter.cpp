
#include "Filter.hpp"

#ifndef __BMP_IMAGE__
    #define __BMP_IMAGE__
    #include "BmpImage.hpp"
#endif

#ifndef __COLOR__
    #define __COLOR__
    #include "Color.hpp"
#endif

#include <vector>
#include <stdexcept>

BmpImage MedianFilter::SortingFilter(BmpImage& bmp_image, int window_size) {
    if (window_size % 2 == 0) {
        throw std::invalid_argument("Window size should be odd");
    }

    BmpImage result_image(bmp_image);
    int radius = window_size / 2;

    // std::cout << result_image.GetHeight() << " " << result_image.GetWidth() << std::endl;

    for (int i = 0; i < bmp_image.GetWidth(); ++i) {
        for (int j = 0; j < bmp_image.GetHeight(); ++j) {
            std::vector<Pixel> window_values;

            std::vector<int> red_hist(256);
            std::vector<int> green_hist(256);
            std::vector<int> blue_hist(256);
            
            for (int x_relative = -radius; x_relative <= radius; ++x_relative) {
                for (int y_relative = -radius; y_relative <= radius; ++y_relative) {
                    int x_position = i + x_relative;
                    int y_position = j + y_relative;
                    if (x_position < 0 || x_position >= bmp_image.GetWidth() ||
                        y_position < 0 || y_position >= bmp_image.GetHeight()) {
                        
                        continue;
                    }
                    Pixel pixel = bmp_image.Get(Position(x_position, y_position));
                    ++red_hist[(int) pixel.red];
                    ++green_hist[(int) pixel.green];
                    ++blue_hist[(int) pixel.blue];
                }
            }
            Pixel result_pixel;
            result_pixel.red = GetHistogramMedian(red_hist);
            result_pixel.green = GetHistogramMedian(green_hist);
            result_pixel.blue = GetHistogramMedian(blue_hist);

            result_image.Set(Position(i, j), result_pixel);
        }
    }

    return result_image;
}

BmpImage MedianFilter::HuangFilter(BmpImage& bmp_image, int window_size) {
    if (window_size % 2 == 0) {
        throw std::invalid_argument("Window size should be odd");
    }

    BmpImage result_image(bmp_image);
    int radius = window_size / 2;

    // std::cout << result_image.GetHeight() << " " << result_image.GetWidth() << std::endl;
    int height = result_image.GetHeight();
    int width = result_image.GetWidth();

    for (int j = 0; j < height; ++j) {
        std::vector<int> red_hist(256);
        std::vector<int> green_hist(256);
        std::vector<int> blue_hist(256);
        for (int i = -radius; i < width; ++i) {
            if (i - radius - 1 >= 0) {
                for (int y_relative = -radius; y_relative <= radius; ++y_relative) {
                    int y_position = j + y_relative;
                    if (y_position >= 0 && y_position < height) {
                        Pixel pixel = bmp_image.Get(Position(i - radius - 1, y_position));
                        --red_hist[(int) pixel.red];
                        --green_hist[(int) pixel.green];
                        --blue_hist[(int) pixel.blue];
                    }
                }
            }

            if (i + radius < width) {
                for (int y_relative = -radius; y_relative <= radius; ++y_relative) {
                    int y_position = j + y_relative;
                    if (y_position >= 0 && y_position < height) {
                        Pixel pixel = bmp_image.Get(Position(i + radius, y_position));
                        ++red_hist[(int) pixel.red];
                        ++green_hist[(int) pixel.green];
                        ++blue_hist[(int) pixel.blue];
                    }
                }
            }

            if (i >= 0) {
                Pixel result_pixel;
                result_pixel.red = GetHistogramMedian(red_hist);
                result_pixel.green = GetHistogramMedian(green_hist);
                result_pixel.blue = GetHistogramMedian(blue_hist);
                result_image.Set(Position(i, j), result_pixel);
            }
        }
    }

    return result_image;
}

BmpImage MedianFilter::PerreaultFilter(BmpImage& bmp_image, int window_size) {
    if (window_size % 2 == 0) {
        throw std::invalid_argument("Window size should be odd");
    }

    BmpImage result_image(bmp_image);
    int radius = window_size / 2;

    // std::cout << result_image.GetHeight() << " " << result_image.GetWidth() << std::endl;
    int height = result_image.GetHeight();
    int width = result_image.GetWidth();

    std::vector<std::vector<int>> red_hists(width, std::vector<int>(256));
    std::vector<std::vector<int>> green_hists(width, std::vector<int>(256));
    std::vector<std::vector<int>> blue_hists(width, std::vector<int>(256));

    for (int j = -radius; j < height; ++j) {

        if (j + radius < height) {
            for (int k = 0; k < width; ++k) {
                Pixel pixel = bmp_image.Get(Position(k, j + radius));
                ++red_hists[k][(int) pixel.red];
                ++green_hists[k][(int) pixel.green];
                ++blue_hists[k][(int) pixel.blue];
            }
        }

        if (j - radius - 1 >= 0) {
            for (int k = 0; k < width; ++k) {
                Pixel pixel = bmp_image.Get(Position(k, j - radius - 1));
                --red_hists[k][(int) pixel.red];
                --green_hists[k][(int) pixel.green];
                --blue_hists[k][(int) pixel.blue];
            }
        }

        std::vector<int> red_hist(256);
        std::vector<int> green_hist(256);
        std::vector<int> blue_hist(256);

        for (int i = -radius; i < width; ++i) {
            if (i + radius < width) {
                for (int k = 0; k < 256; ++k) {
                    red_hist[k] += red_hists[i + radius][k];
                    green_hist[k] += green_hists[i + radius][k];
                    blue_hist[k] += blue_hists[i + radius][k];
                }
            }

            if (i - radius - 1 >= 0) {
                for (int k = 0; k < 256; ++k) {
                    red_hist[k] -= red_hists[i - radius - 1][k];
                    green_hist[k] -= green_hists[i - radius - 1][k];
                    blue_hist[k] -= blue_hists[i - radius - 1][k];
                }
            }

            if (i >= 0 & j >= 0) {
                Pixel result_pixel;
                result_pixel.red = GetHistogramMedian(red_hist);
                result_pixel.green = GetHistogramMedian(green_hist);
                result_pixel.blue = GetHistogramMedian(blue_hist);
                result_image.Set(Position(i, j), result_pixel);
            }
        }
    }

    return result_image;
}

double MedianFilter::GetHistogramMedian(std::vector<int>& values) {
    int total_values = 0;
    for (int i = 0; i < values.size(); ++i) {
        total_values += values[i];
    }
    int half_items = total_values / 2 + 1;

    int cumsum = 0;
    int previous_item = 0;
    for (int i = 0; i < values.size(); ++i) {
        cumsum += values[i];
        if (cumsum >= half_items) {
            if (total_values % 2 == 1) {
                return i;
            } else {
                if (cumsum == half_items) {
                    return (i + previous_item) / 2;
                } else {
                    return i;
                }
            }
        }
        if (values[i] > 0) {
            previous_item = i;
        }
    }
}

std::vector<int> MedianFilter::GetColorValues(std::vector<Pixel>& values, Color color) {
    std::vector<int> result(values.size());

    for (int i = 0; i < values.size(); ++i) {
        if (color == Color::RED) {
            result[i] = values[i].red;
        } else if (color == Color::GREEN) {
            result[i] = values[i].green;
        } else if (color == Color::BLUE) {
            result[i] = values[i].blue;
        }
    }

    return result;
}

Pixel MedianFilter::GetMedianPixel(std::vector<Pixel>& values) {
    Pixel result_color;
    
    std::vector<int> red_color = GetColorValues(values, Color::RED);
    std::vector<int> green_color = GetColorValues(values, Color::GREEN);
    std::vector<int> blue_color = GetColorValues(values, Color::BLUE);

    result_color.red = GetMedian(red_color);
    result_color.green = GetMedian(green_color);
    result_color.blue = GetMedian(blue_color);

    return result_color;
}

double MedianFilter::GetMedian(std::vector<int>& values) {
    CountingSort(values);
    if (values.size() % 2 == 1) {
        return values[values.size() / 2 + 1];
    }
    
    return (values[values.size() / 2] + values[values.size() / 2 - 1]) / 2;
}

void MedianFilter::CountingSort(std::vector<int>& values) {
    std::vector<int> counts(256);
    for (int i = 0; i < values.size(); ++i) {
        ++counts[values[i]];
    }

    int ptr = 0;
    int cnt_ptr = 0;

    while (cnt_ptr < counts.size()) {
        if (counts[cnt_ptr] > 0) {
            --counts[cnt_ptr];
            values[ptr++] = cnt_ptr;
        } else {
            ++cnt_ptr;
        }
    }
}
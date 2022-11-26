#include <cmath>
#include <algorithm>

#include "Gradient.hpp"

//------------------- Gradient class -------------------//

double Gradient::GetGradient() {
    return value_;
}

Pixel Gradient::GetAverages() {
    return averages_;
}

double Gradient::ComputeGradient(BmpImage& bmp_image, Position position, 
        const std::vector<GradientCellPosition>& positions_data) {
    value_ = 0;

    for (const GradientCellPosition& cell_position: positions_data) {
        RelativePosition relative_position = cell_position.relative_position;
        RelativePosition shift = cell_position.shift;

        Position vector_end = position + relative_position;
        Position vector_start = position + relative_position + shift;
        float weight = cell_position.weight;

        float start_value = bmp_image.GetPixelValue(vector_start);
        float end_value = bmp_image.GetPixelValue(vector_end);

        float current_value = (end_value - start_value) * weight;
        if (current_value < 0) {
            current_value = -current_value;
        }
        value_ += current_value;

        // std::cout << "Start: (" << vector_start.y << ", " << vector_start.x << "): " << start_value << ", End: (" << vector_end.y << ", " << vector_end.x << "): " << end_value << ", Wight: " << weight << std::endl;
    }

    // std::cout << "Gradient value: " << value_ << std::endl;
    return value_;
}

Pixel Gradient::ComputeAverages(BmpImage& bmp_image, Position position, 
        const std::vector<RelativePosition>& average_positions) {
    averages_ = Pixel();

    int red_count = 0;
    int green_count = 0;
    int blue_count = 0;
    for (const RelativePosition& average_position: average_positions) {
        Position current_position = position + average_position;
        Color current_color = bmp_image.GetPixelColor(current_position);
        float current_value = bmp_image.GetPixelValue(current_position);

        if (current_color == Color::RED) {
            ++red_count;
            averages_.red += current_value;
        } else if (current_color == Color::GREEN) {
            ++green_count;
            averages_.green += current_value;
        } else if (current_color == Color::BLUE) {
            ++blue_count;
            averages_.blue += current_value;
        }
    }

    if (red_count > 0) {
        averages_.red /= red_count;
    }
    if (green_count > 0) {
        averages_.green /= green_count;
    }
    if (blue_count > 0) {
        averages_.blue /= blue_count;
    }
    return averages_;
}

//------------------- End of Gradient class -------------------//
//------------------- GradientsBunch class -------------------//

GradientsBunch::GradientsBunch(BmpImage& bmp_image, Position position) {
    north_gradient.ComputeGradient(bmp_image, position, north_gradient.positions);
    south_gradient.ComputeGradient(bmp_image, position, south_gradient.positions);
    east_gradient.ComputeGradient(bmp_image, position, east_gradient.positions);
    west_gradient.ComputeGradient(bmp_image, position, west_gradient.positions);
    north_gradient.ComputeAverages(bmp_image, position, north_gradient.average_positions);
    south_gradient.ComputeAverages(bmp_image, position, south_gradient.average_positions);
    east_gradient.ComputeAverages(bmp_image, position, east_gradient.average_positions);
    west_gradient.ComputeAverages(bmp_image, position, west_gradient.average_positions);

    Color color = bmp_image.GetPixelColor(position);

    if (color == Color::GREEN) {
        north_east_gradient.ComputeGradient(bmp_image, position, north_east_gradient.green_center_positions);
        north_west_gradient.ComputeGradient(bmp_image, position, north_west_gradient.green_center_positions);
        south_east_gradient.ComputeGradient(bmp_image, position, south_east_gradient.green_center_positions);
        south_west_gradient.ComputeGradient(bmp_image, position, south_west_gradient.green_center_positions);
        north_east_gradient.ComputeAverages(bmp_image, position, north_east_gradient.average_positions);
        north_west_gradient.ComputeAverages(bmp_image, position, north_west_gradient.average_positions);
        south_east_gradient.ComputeAverages(bmp_image, position, south_east_gradient.average_positions);
        south_west_gradient.ComputeAverages(bmp_image, position, south_west_gradient.average_positions);
    } else {
        north_east_gradient.ComputeGradient(bmp_image, position, north_east_gradient.non_green_center_positions);
        north_west_gradient.ComputeGradient(bmp_image, position, north_west_gradient.non_green_center_positions);
        south_east_gradient.ComputeGradient(bmp_image, position, south_east_gradient.non_green_center_positions);
        south_west_gradient.ComputeGradient(bmp_image, position, south_west_gradient.non_green_center_positions);

        north_east_gradient.ComputeAverages(bmp_image, position, north_east_gradient.average_positions);
        north_west_gradient.ComputeAverages(bmp_image, position, north_west_gradient.average_positions);
        south_east_gradient.ComputeAverages(bmp_image, position, south_east_gradient.average_positions);
        south_west_gradient.ComputeAverages(bmp_image, position, south_west_gradient.average_positions);
    }
}

double GradientsBunch::GetMaxGradient() {
    double max_gradient = north_gradient.GetGradient();
    max_gradient = std::max(south_gradient.GetGradient(), max_gradient);
    max_gradient = std::max(east_gradient.GetGradient(), max_gradient);
    max_gradient = std::max(west_gradient.GetGradient(), max_gradient);

    max_gradient = std::max(north_east_gradient.GetGradient(), max_gradient);
    max_gradient = std::max(north_west_gradient.GetGradient(), max_gradient);
    max_gradient = std::max(south_east_gradient.GetGradient(), max_gradient);
    max_gradient = std::max(south_west_gradient.GetGradient(), max_gradient);

    return max_gradient;
}

double GradientsBunch::GetMinGradient() {
    double min_gradient = north_gradient.GetGradient();
    min_gradient = std::min(south_gradient.GetGradient(), min_gradient);
    min_gradient = std::min(east_gradient.GetGradient(), min_gradient);
    min_gradient = std::min(west_gradient.GetGradient(), min_gradient);

    min_gradient = std::min(north_east_gradient.GetGradient(), min_gradient);
    min_gradient = std::min(north_west_gradient.GetGradient(), min_gradient);
    min_gradient = std::min(south_east_gradient.GetGradient(), min_gradient);
    min_gradient = std::min(south_west_gradient.GetGradient(), min_gradient);

    return min_gradient;
}

std::vector<Gradient> GradientsBunch::FilterByThreshold(float threshold) {
    std::vector<Gradient> filtered_gradients;

    if (north_gradient.GetGradient() <= threshold) {
        filtered_gradients.push_back(north_gradient);
    }
    if (south_gradient.GetGradient() <= threshold) {
        filtered_gradients.push_back(south_gradient);
    }
    if (east_gradient.GetGradient() <= threshold) {
        filtered_gradients.push_back(east_gradient);
    }
    if (west_gradient.GetGradient() <= threshold) {
        filtered_gradients.push_back(west_gradient);
    }
    if (north_east_gradient.GetGradient() <= threshold) {
        filtered_gradients.push_back(north_east_gradient);
    }
    if (north_west_gradient.GetGradient() <= threshold) {
        filtered_gradients.push_back(north_west_gradient);
    }
    if (south_east_gradient.GetGradient() <= threshold) {
        filtered_gradients.push_back(south_east_gradient);
    }
    if (south_west_gradient.GetGradient() <= threshold) {
        filtered_gradients.push_back(south_west_gradient);
    }

    return filtered_gradients;
}

//------------------- End of GradientsBunch class -------------------//
#include <stdexcept>

#include "Position.hpp"

//------------------- Position class -------------------//

Position::Position(): x(0), y(0) {}
Position::Position(int x, int y): x(x), y(y) {}

Position Position::operator+(RelativePosition const& position) {
    return Position(this->x + position.x, this->y + position.y);
}

//------------------- End of Position class -------------------//
//------------------- RelativePosition class -------------------//

RelativePosition::RelativePosition(): x(0), y(0) {}

RelativePosition::RelativePosition(int x, int y) {
    if (x < -2 || x > 2 || y < -2 || y > 2) {
        throw std::invalid_argument("Bad value for relative position");
    }

    this->x = x;
    this->y = y;
}

//------------------- End of RelativePosition class -------------------//
//------------------- GradientCellData class -------------------//

GradientCellPosition::GradientCellPosition(RelativePosition relative_position, RelativePosition shift, float weight): 
        relative_position(relative_position), shift(shift), weight(weight) {}

//------------------- End of GradientCellData class -------------------//
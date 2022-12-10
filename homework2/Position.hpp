class RelativePosition;

//------------------- Position class -------------------//

struct Position {
    Position();
    Position(int, int);

    Position operator+(RelativePosition const&);

    int x;
    int y;
};

//------------------- End of Position class -------------------//
//------------------- RelativePosition class -------------------//

struct RelativePosition {
    RelativePosition();
    RelativePosition(int, int);

    int x;
    int y;
};

//------------------- End of RelativePosition class -------------------//
//------------------- GradientCellData class -------------------//

struct GradientCellPosition {
    GradientCellPosition(RelativePosition, RelativePosition, float);

    RelativePosition relative_position;
    RelativePosition shift;
    float weight;
};

//------------------- End of GradientCellData class -------------------//
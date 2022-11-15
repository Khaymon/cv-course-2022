#include <vector>

#ifndef __BMP_IMAGE__
    #define __BMP_IMAGE__
    #include "BmpImage.hpp"
#endif

#ifndef __POSITION__
    #define __POSITION__
    #include "Position.hpp"
#endif

#ifndef __PIXEL__
    #define __PIXEL__
    #include "Pixel.hpp"
#endif

#ifndef __COLOR__
    #define __COLOR__
    #include "Color.hpp"
#endif

class GradientTester;

//------------------- Gradient class -------------------//

class Gradient {
public:
    double GetGradient();
    Pixel GetAverages();
    double ComputeGradient(BmpImage&, Position, const std::vector<GradientCellPosition>&);
    Pixel ComputeAverages(BmpImage&, Position, const std::vector<RelativePosition>&);
protected:
    Position position_;
    double value_ = 0;
    Pixel averages_;

    friend class GradientTester;
};

//------------------- End of Gradient class -------------------//
//------------------- GradientTester class -------------------//

class GradientTester {
public:
    int ComputeGradient(Gradient gradient, BmpImage& bmp_image, Position position,
            const std::vector<GradientCellPosition>& cell_positions) {
        return gradient.ComputeGradient(bmp_image, position, cell_positions);
    }

    Pixel ComputeAverages(Gradient gradient, BmpImage& bmp_image, Position position, 
            const std::vector<RelativePosition>& average_positions) {
        return gradient.ComputeAverages(bmp_image, position, average_positions);
    }
};

//------------------- End of GradientTester class -------------------//
//------------------- Directive Gradients classes -------------------//

/*
  Coordinate plane looks like this

  (0,0)      x
    +-------->
    |
    |
    |
  y v

  Gradient is computed by taking the (x, y) absolute coordinate + relative position
  for given direction, absolute coordinate + relative position + shift and evaluation
  of absolute difference of these pixels' values.
*/

class NorthGradient : public Gradient {
public:
    const std::vector<GradientCellPosition> positions = {
        GradientCellPosition(RelativePosition(0, -2), RelativePosition(0, 2), 1),
        GradientCellPosition(RelativePosition(0, -1), RelativePosition(0, 2), 1),

        GradientCellPosition(RelativePosition(-1, -2), RelativePosition(0, 2), 0.5),
        GradientCellPosition(RelativePosition(-1, -1), RelativePosition(0, 2), 0.5),

        GradientCellPosition(RelativePosition(1, -2), RelativePosition(0, 2), 0.5),
        GradientCellPosition(RelativePosition(1, -1), RelativePosition(0, 2), 0.5)
    };

    const std::vector<RelativePosition> average_positions = {
        RelativePosition(-1, 0), RelativePosition(-1, -1), RelativePosition(-1, -2),
        RelativePosition(0, 0), RelativePosition(0, -1), RelativePosition(0, -2),
        RelativePosition(1, 0), RelativePosition(1, -1), RelativePosition(1, -2),
    };
};

class SouthGradient : public Gradient {
public:
    const std::vector<GradientCellPosition> positions = {
        GradientCellPosition(RelativePosition(0, 1), RelativePosition(0, -2), 1),
        GradientCellPosition(RelativePosition(0, 2), RelativePosition(0, -2), 1),

        GradientCellPosition(RelativePosition(-1, 1), RelativePosition(0, -2), 0.5),
        GradientCellPosition(RelativePosition(-1, 2), RelativePosition(0, -2), 0.5),

        GradientCellPosition(RelativePosition(1, 1), RelativePosition(0, -2), 0.5),
        GradientCellPosition(RelativePosition(1, 2), RelativePosition(0, -2), 0.5)
    };

    const std::vector<RelativePosition> average_positions = {
        RelativePosition(-1, 0), RelativePosition(-1, 1), RelativePosition(-1, 2),
        RelativePosition(0, 0), RelativePosition(0, 1), RelativePosition(0, 2),
        RelativePosition(1, 0), RelativePosition(1, 1), RelativePosition(1, 2),
    };
};

class EastGradient : public Gradient {
public:
    const std::vector<GradientCellPosition> positions = {
        GradientCellPosition(RelativePosition(1, 0), RelativePosition(-2, 0), 1),
        GradientCellPosition(RelativePosition(2, 0), RelativePosition(-2, 0), 1),

        GradientCellPosition(RelativePosition(1, -1), RelativePosition(-2, 0), 0.5),
        GradientCellPosition(RelativePosition(2, -1), RelativePosition(-2, 0), 0.5),

        GradientCellPosition(RelativePosition(1, 1), RelativePosition(-2, 0), 0.5),
        GradientCellPosition(RelativePosition(2, 1), RelativePosition(-2, 0), 0.5)
    };

    const std::vector<RelativePosition> average_positions = {
        RelativePosition(0, -1), RelativePosition(1, -1), RelativePosition(2, -1),
        RelativePosition(0, 0), RelativePosition(1, 0), RelativePosition(2, 0),
        RelativePosition(0, 1), RelativePosition(1, 1), RelativePosition(2, 1),
    };
};

class WestGradient : public Gradient {
public:
    const std::vector<GradientCellPosition> positions = {
        GradientCellPosition(RelativePosition(-2, 0), RelativePosition(2, 0), 1),
        GradientCellPosition(RelativePosition(-1, 0), RelativePosition(2, 0), 1),

        GradientCellPosition(RelativePosition(-2, -1), RelativePosition(2, 0), 0.5),
        GradientCellPosition(RelativePosition(-1, -1), RelativePosition(2, 0), 0.5),

        GradientCellPosition(RelativePosition(-2, 1), RelativePosition(2, 0), 0.5),
        GradientCellPosition(RelativePosition(-1, 1), RelativePosition(2, 0), 0.5)
    };

    const std::vector<RelativePosition> average_positions = {
        RelativePosition(0, -1), RelativePosition(-1, -1), RelativePosition(-2, -1),
        RelativePosition(0, 0), RelativePosition(-1, 0), RelativePosition(-2, 0),
        RelativePosition(0, 1), RelativePosition(-1, 1), RelativePosition(-2, 1),
    };
};

class NorthEastGradient : public Gradient {
public:
    const RelativePosition BIG_SHIFT = RelativePosition(-2, 2);
    const RelativePosition SMALL_SHIFT = RelativePosition(-1, 1);

    const std::vector<GradientCellPosition> green_center_positions = {
        GradientCellPosition(RelativePosition(1, -1), BIG_SHIFT, 1),
        GradientCellPosition(RelativePosition(2, -2), BIG_SHIFT, 1),
        
        GradientCellPosition(RelativePosition(1, -2), BIG_SHIFT, 1),
        GradientCellPosition(RelativePosition(2, -1), BIG_SHIFT, 1),
    };

    const std::vector<GradientCellPosition> non_green_center_positions = {
        GradientCellPosition(RelativePosition(1, -1), BIG_SHIFT, 1),
        GradientCellPosition(RelativePosition(2, -2), BIG_SHIFT, 1),
        
        GradientCellPosition(RelativePosition(0, -1), SMALL_SHIFT, 0.5),
        GradientCellPosition(RelativePosition(1, -2), SMALL_SHIFT, 0.5),
        GradientCellPosition(RelativePosition(1, 0), SMALL_SHIFT, 0.5),
        GradientCellPosition(RelativePosition(2, -1), SMALL_SHIFT, 0.5),
    };

    const std::vector<RelativePosition> average_positions = {
        RelativePosition(0, 0), RelativePosition(0, -1), RelativePosition(0, -2),
        RelativePosition(1, 0), RelativePosition(1, -1), RelativePosition(1, -2),
        RelativePosition(2, 0), RelativePosition(2, -1), RelativePosition(2, -2),
    };
};

class NorthWestGradient : public Gradient {
public:
    const RelativePosition BIG_SHIFT = RelativePosition(2, 2);
    const RelativePosition SMALL_SHIFT = RelativePosition(1, 1);

    const std::vector<GradientCellPosition> green_center_positions = {
        GradientCellPosition(RelativePosition(-1, -1), BIG_SHIFT, 1),
        GradientCellPosition(RelativePosition(-2, -2), BIG_SHIFT, 1),

        GradientCellPosition(RelativePosition(-1, -2), BIG_SHIFT, 1),
        GradientCellPosition(RelativePosition(-2, -1), BIG_SHIFT, 1),
    };

    const std::vector<GradientCellPosition> non_green_center_positions = {
        GradientCellPosition(RelativePosition(-1, -1), BIG_SHIFT, 1),
        GradientCellPosition(RelativePosition(-2, -2), BIG_SHIFT, 1),
        
        GradientCellPosition(RelativePosition(0, -1), SMALL_SHIFT, 0.5),
        GradientCellPosition(RelativePosition(-1, -2), SMALL_SHIFT, 0.5),
        GradientCellPosition(RelativePosition(-1, 0), SMALL_SHIFT, 0.5),
        GradientCellPosition(RelativePosition(-2, -1), SMALL_SHIFT, 0.5),
    };

    const std::vector<RelativePosition> average_positions = {
        RelativePosition(0, 0), RelativePosition(0, -1), RelativePosition(0, -2),
        RelativePosition(-1, 0), RelativePosition(-1, -1), RelativePosition(-1, -2),
        RelativePosition(-2, 0), RelativePosition(-2, -1), RelativePosition(-2, -2),
    };
};

class SouthEastGradient : public Gradient {
public:
    const RelativePosition BIG_SHIFT = RelativePosition(-2, -2);
    const RelativePosition SMALL_SHIFT = RelativePosition(-1, -1);

    const std::vector<GradientCellPosition> green_center_positions = {
        GradientCellPosition(RelativePosition(1, 1), BIG_SHIFT, 1),
        GradientCellPosition(RelativePosition(2, 2), BIG_SHIFT, 1),

        GradientCellPosition(RelativePosition(1, 2), BIG_SHIFT, 1),
        GradientCellPosition(RelativePosition(2, 1), BIG_SHIFT, 1),
    };

    const std::vector<GradientCellPosition> non_green_center_positions = {
        GradientCellPosition(RelativePosition(1, 1), BIG_SHIFT, 1),
        GradientCellPosition(RelativePosition(2, 2), BIG_SHIFT, 1),
        
        GradientCellPosition(RelativePosition(0, 1), SMALL_SHIFT, 0.5),
        GradientCellPosition(RelativePosition(1, 2), SMALL_SHIFT, 0.5),
        GradientCellPosition(RelativePosition(1, 0), SMALL_SHIFT, 0.5),
        GradientCellPosition(RelativePosition(2, 1), SMALL_SHIFT, 0.5),
    };

    const std::vector<RelativePosition> average_positions = {
        RelativePosition(0, 0), RelativePosition(0, 1), RelativePosition(0, 2),
        RelativePosition(1, 0), RelativePosition(1, 1), RelativePosition(1, 2),
        RelativePosition(2, 0), RelativePosition(2, 1), RelativePosition(2, 2),
    };
};

class SouthWestGradient : public Gradient {
public:
    const RelativePosition BIG_SHIFT = RelativePosition(2, -2);
    const RelativePosition SMALL_SHIFT = RelativePosition(1, -1);

    const std::vector<GradientCellPosition> green_center_positions = {
        GradientCellPosition(RelativePosition(-1, 1), BIG_SHIFT, 1),
        GradientCellPosition(RelativePosition(-2, 2), BIG_SHIFT, 1),

        GradientCellPosition(RelativePosition(-1, 2), BIG_SHIFT, 1),
        GradientCellPosition(RelativePosition(-2, 1), BIG_SHIFT, 1),
    };

    const std::vector<GradientCellPosition> non_green_center_positions = {
        GradientCellPosition(RelativePosition(-1, 1), BIG_SHIFT, 1),
        GradientCellPosition(RelativePosition(-2, 2), BIG_SHIFT, 1),
        
        GradientCellPosition(RelativePosition(0, 1), SMALL_SHIFT, 0.5),
        GradientCellPosition(RelativePosition(-1, 2), SMALL_SHIFT, 0.5),
        GradientCellPosition(RelativePosition(-1, 0), SMALL_SHIFT, 0.5),
        GradientCellPosition(RelativePosition(-2, 1), SMALL_SHIFT, 0.5),
    };

    const std::vector<RelativePosition> average_positions = {
        RelativePosition(0, 0), RelativePosition(0, 1), RelativePosition(0, 2),
        RelativePosition(-1, 0), RelativePosition(-1, 1), RelativePosition(-1, 2),
        RelativePosition(-2, 0), RelativePosition(-2, 1), RelativePosition(-2, 2),
    };
};

//------------------- End of Directive Gradients classes -------------------//
//------------------- GradientBunch class -------------------//

class GradientsBunch {
public:
    GradientsBunch(BmpImage&, Position);

    double GetMaxGradient();
    double GetMinGradient();

    std::vector<Gradient> FilterByThreshold(float);
private:
    NorthGradient north_gradient;
    SouthGradient south_gradient;
    EastGradient east_gradient;
    WestGradient west_gradient;

    NorthEastGradient north_east_gradient;
    NorthWestGradient north_west_gradient;
    SouthEastGradient south_east_gradient;
    SouthWestGradient south_west_gradient;
};

//------------------- End of GradientBunch class -------------------//
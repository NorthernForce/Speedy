#pragma once

#include "Constants.h"
#include <units/length.h>

namespace CPlane {
    class Point {
       public:
        units::inch_t x,y;
        bool relative;

        Point();
        Point(units::inch_t x, units::inch_t y, bool relative=false);

        Point Add(Point p, bool resultRelative=false);

        Point Subtract(Point p, bool resultRelative=false);
    };
}
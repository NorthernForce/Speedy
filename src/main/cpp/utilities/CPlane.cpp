#include "utilities/CPlane.h"

CPlane::Point::Point() {
    x = 0_in;
    y = 0_in;
    relative = false;
}

CPlane::Point::Point(units::inch_t x, units::inch_t y, bool relative) 
: x(x), y(y), relative(relative) {}

CPlane::Point CPlane::Point::Add(Point p, bool resultRelative) {
    return CPlane::Point(x + p.x, y + p.y, resultRelative);
}

CPlane::Point CPlane::Point::Subtract(Point p, bool resultRelative) {
    return CPlane::Point(x - p.x, y - p.y, resultRelative);
}
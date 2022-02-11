#include "Constants.h"
#include <units/length.h>


namespace CPlane {
    class Point {
       public:
        double x,y,distance;
        Point(double x=0, double y=0, double distance=0)
        : x(x), y(y), distance(distance) {}
    };
}
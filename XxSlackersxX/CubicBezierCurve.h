#ifndef _CUBIC_BEZIER_CURVE_H_
#define _CUBIC_BEZIER_CURVE_H_

#include "Point.h"
#include <string>
#include <vector>

class CubicBezierCurve {
    
public:
    CubicBezierCurve();
    CubicBezierCurve(const std::vector<Point>& controlPoints);
    
    void draw(const int resolution);
    
    
private:
    void render(Point p0, Point p1, Point p2, Point p3, int resolution);
    Point evaluate(Point p0, Point p1, Point p2, Point p3, float t);
    
    std::vector<Point> controlPoints;
};

#endif
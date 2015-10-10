#ifndef _CUBIC_BEZIER_CURVE_H_
#define _CUBIC_BEZIER_CURVE_H_

#include "Point.h"
#include <string>
#include <vector>

class CubicBezierCurve {
    
public:
    CubicBezierCurve();
    CubicBezierCurve(const std::vector<Point>& controlPoints, const int resolution);
    CubicBezierCurve(const std::string& filename);
    
    void draw(const int resolution);
    void loadPoints(const std::string& filename);
    
    
private:
    void render(Point p0, Point p1, Point p2, Point p3, int resolution);
    Point evaluate(Point p0, Point p1, Point p2, Point p3, float t);
    
    
    std::vector<Point> controlPoints;
};

#endif
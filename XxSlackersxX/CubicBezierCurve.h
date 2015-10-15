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
    
    void setControlPoints(const std::vector<Point> points) {
        this->controlPoints = points;
    }
    
    const std::vector<Point>& getCurvePoints();

    
private:
    void render(Point p0, Point p1, Point p2, Point p3, int resolution);
   
    std::vector<Point> controlPoints;
    std::vector<Point> curvePoints;
};

Point evaluateBezier(Point p0, Point p1, Point p2, Point p3, float t);
Point evaluateBezier(std::vector<Point> points, float t);



#endif
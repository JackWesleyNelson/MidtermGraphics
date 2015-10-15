#ifndef _BEZIER_PATCH_H_
#define _BEZIER_PATCH_H_

#include "BezierCurve.h"
#include <vector>
#include "Point.h"

using std::vector;

class BezierPatch {
    
public:
    BezierPatch(std::vector<Point> controlPoints, float u, float v);
    BezierPatch();
    
    void draw(const int resolution);
    void drawPoints();
    void connectPoints(const int resolution);
    
    void setControlPoints(const std::vector<Point> points);
    
    
private:
    Point evaluate();
    float u;
    float v;
    std::vector<Point> controlPoints;
    
    
};

Point evaluatePatchTerm(const Point p, const float u, const float v);
Point evaluatePatch(const vector<Point> points, const float u, const float v);
Point evaluateSurface(const vector<Point> points, const float u, const float v);

#endif
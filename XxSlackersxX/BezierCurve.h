//
//  BezierCurve.h
//  MidtermGraphics_
//
//  Created by jamie koning on 10/14/15.
//  Copyright © 2015 jamiekoning. All rights reserved.
//

#ifndef BezierCurve_h
#define BezierCurve_h

#include "CubicBezierCurve.h"
#include <math.h>
#include <fstream>
#include <iostream>

#ifdef __APPLE__			// if compiling on Mac OS
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUI/glui.h>
#else					// else compiling on Linux OS
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glui.h>			// include our GLUI header
#endif

#include <vector>
#include <cmath>
#include <map>
#include "Point.h"

class BezierCurve {
public:
    BezierCurve(const std::vector<Point>& controlPoints);
    BezierCurve();
    
    void setControlPoints(const std::vector<Point> points);
    
    void draw(const int resolution);
    void drawPoints();
    void render(const Point p0, const Point p1, const Point p2, const Point p3,const int resolution);
    void connectPoints(const int resolution);
    
    void calculateCurvePoints();
    void calculateCurvePointsArcLength(float ds);
    
    const std::vector<Point>& getCurvePoints();
    const std::vector<Point>& getCurvePointsArcLength();
    
    void setDu(float du);
    
private:
    float du;
    std::vector<Point> controlPoints;
    std::vector<Point> curvePoints;
    std::vector<Point> curvePointsArcLength;
    std::map<float, float> arcLengthTable;
};

float bezierBasis(const int i, const float u);
int factorial(const int n);
Point evaluateCurveTerm(const Point& p, const float u, const int i);
Point evaluateCurve(const std::vector<Point>& points, const float u);
Point evaluateCurve(Point p0, Point p1, Point p2, Point p3, float t);
std::vector<BezierCurve> makeCurves(std::vector<Point> points);
void drawCurves(std::vector<BezierCurve> curves);
std::vector<Point> getAllCurvePoints(std::vector<BezierCurve> curves);
std::vector<Point> getAllCurvePointsArcLength(std::vector<BezierCurve> curves);


#endif /* BezierCurve_h */

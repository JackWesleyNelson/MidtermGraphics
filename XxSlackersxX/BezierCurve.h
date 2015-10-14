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
#include "Point.h"

class BezierCurve {
public:
    BezierCurve(const std::vector<Point>& controlPoints);
    BezierCurve();
    
    void setControlPoints(const std::vector<Point> points);
    
    void draw(const int resolution);
    void drawPoints();
    void connectPoints(const int resolution);
    
private:
    
    std::vector<Point> controlPoints;
};

float bezierBasis(const int i, const float u);
int factorial(const int n);
Point evaluateCurveTerm(const Point& p, const float u, const int i);
Point evaluateCurve(const std::vector<Point>& points, const float u);

#endif /* BezierCurve_h */

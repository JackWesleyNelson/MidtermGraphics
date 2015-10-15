//
//  BezierCurve.cpp
//  MidtermGraphics_
//
//  Created by jamie koning on 10/14/15.
//  Copyright © 2015 jamiekoning. All rights reserved.
//

#include "BezierCurve.h"
#include <cmath>

using std::vector;

// Bezier Class Functions
BezierCurve::BezierCurve(const vector<Point>& controlPoints) {
    this->controlPoints = controlPoints;
}

BezierCurve::BezierCurve() {
    
}

void BezierCurve::setControlPoints(const std::vector<Point> points) {
    this->controlPoints = points;
}

const vector<Point>& BezierCurve::getCurvePoints() {
    return curvePoints;
}

void BezierCurve::draw(const int resolution) {
    //drawPoints();
    
    int count = 0;
    vector<Point> points;
    
   	for(int i = 0; i<controlPoints.size()-2; i+=3) {
        render(controlPoints[i], controlPoints[i+1], controlPoints[i+2], controlPoints[i+3], resolution);
    }

}

void BezierCurve::render(const Point p0, const Point p1, const Point p2, const Point p3, const int resolution) {
    glPushMatrix();
    glColor3f(1, 0, 0);
    glBegin( GL_LINE_STRIP );{
        for(int i=0; i <= resolution; i++) {
            float j = i;
            j /= resolution;
            Point pb = evaluateCurve( p0, p1, p2, p3, j);
            glVertex3f( pb.getX(), pb.getY(), pb.getZ() );
        }
    }; glEnd();
    glPopMatrix();
}

void BezierCurve::drawPoints() {
    if (!curvePoints.empty())
        curvePoints.clear();
    
    glColor3f(0,1,0);
    for(int i =0; i < controlPoints.size(); i++) {
        glPushMatrix();
        glTranslatef(controlPoints[i].getX(), controlPoints[i].getY(), controlPoints[i].getZ());
        GLUquadric *quad;
        quad = gluNewQuadric();
        gluQuadricDrawStyle( quad, GLU_FILL);
        
        gluSphere(quad, .2, 10, 10);
        gluDeleteQuadric(quad);
        glPopMatrix();
    }
}

void BezierCurve::connectPoints(const int resolution) {
    glPushMatrix();
    glBegin( GL_LINE_STRIP );{
        Point pb;
        float j;
        
        for(int i=0; i <= resolution; i++) {
            j = i;
            j /= resolution;
            pb = evaluateCurve(controlPoints, j);
            curvePoints.push_back(pb);
            glVertex3f( pb.getX(), pb.getY(), pb.getZ() );
        }
    }; glEnd();
    glPopMatrix();
}

// =======================


// General Math / Curve Functions

Point evaluateCurveTerm(const Point& p, const float u, const int i) {
    return p * bezierBasis(i, u);
}

Point evaluateCurve(const vector<Point>& points, const float u) {
    Point p;
    
    for (int i = 0; i <= 3; i++) {
        p = p + evaluateCurveTerm(points[i], u, i);
    }
    
    return p;
}

Point evaluateCurve( Point p0, Point p1, Point p2, Point p3, float t ) {
    float b0 = (1-t)*(1-t)*(1-t);
    float b1 = 3* (1-t)*(1-t)*t;
    float b2 = 3 * (1-t)*t*t;
    float b3 = t*t*t;
    return (b0*p0 + b1*p1 + b2*p2 + b3*p3);
}

float bezierBasis(const int i, const float u) {
    return (factorial(3) / (factorial(i) * factorial(3 - i))) * powf(u, i) * powf(1 - u, 3 - i);
}

int factorial(const int n) {
    if (n <= 1) return 1;
    
    return n * factorial(n - 1);
}

// =================================
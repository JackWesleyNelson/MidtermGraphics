//
//  BezierCurve.cpp
//  MidtermGraphics_
//
//  Created by jamie koning on 10/14/15.
//  Copyright © 2015 jamiekoning. All rights reserved.
//

#include "BezierCurve.h"
#include <cmath>
#include <iostream>
using namespace std;

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

void BezierCurve::draw(const int resolution) {
    drawPoints();
    connectPoints(resolution);
}

void BezierCurve::drawPoints() {
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
    // Connect our control points
    
    glPushMatrix(); {
		glColor3f(1,1,0);
		glLineWidth( 3.0 );
		glBegin( GL_LINE_STRIP ); {
			for(int i =0; i<controlPoints.size(); i++) {
				glVertex3f( controlPoints[i].getX(), controlPoints[i].getY(), controlPoints[i].getZ() );
			}
		}; glEnd();
    } glPopMatrix();
    
    glPushMatrix(); {
		glColor3f(0,0,1);
		glBegin( GL_LINE_STRIP );{
			Point pb;
			float j;
        for(int i=0; i<controlPoints.size()-2; i+=3)
		{
			vector<Point> temp;
			for(int j=0;j<4;j++) {
				Point t = controlPoints[i+j];
				temp.push_back(Point(t.getX(), t.getY(), t.getZ()));
			}
			for(int i=0; i <= resolution; i++) {
				j = i;
				j /= resolution;
				pb = evaluateCurve(temp, j);
				glVertex3f( pb.getX(), pb.getY(), pb.getZ() );
			}
		}
		}; glEnd();
    } glPopMatrix();
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

float bezierBasis(const int i, const float u) {
    return (factorial(3) / (factorial(i) * factorial(3 - i))) * powf(u, i) * powf(1 - u, 3 - i);
}

int factorial(const int n) {
    if (n <= 1) return 1;
    
    return n * factorial(n - 1);
}

// =================================
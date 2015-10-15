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

const vector<Point>& BezierCurve::getCurvePoints() {
    return curvePoints;
}

void BezierCurve::calculateCurvePoints() {
    Point curvePoint;
    
    for(int i = 0; i < controlPoints.size() - 2; i += 3) {
        for (float u = 0; u <= 1; u += du) {
            curvePoint = evaluateCurve(controlPoints[i], controlPoints[i+1], controlPoints[i+2], controlPoints[i+3], u);
            curvePoints.push_back(curvePoint);
        }
    }
}


void BezierCurve::calculateCurvePointsArcLength(float ds) {
    float u = 0;
    

    
    vector<std::pair<float, float>> tarcLengthTable;
    
    tarcLengthTable.push_back(std::make_pair(0, 0));
    
    for (int i = 1; i < curvePoints.size(); ++i) {
        tarcLengthTable[i].first = u;
        tarcLengthTable[i].second = (distance(curvePoints[i - 1], curvePoints[i])) + tarcLengthTable[i - 1].second;
        
        u += du;
    }
    
    float s = 0;
    vector<float> tValues;
    
    for (int i = 0; i < tarcLengthTable.size(); i++) {
        if (tarcLengthTable[i].second == s) {
            tValues.push_back(tarcLengthTable[i].first);
        }
        
        float dt = 0;
        float t = 0;
        if (tarcLengthTable[i].second > s) {
            //linear interpolate between the two values
            dt = tarcLengthTable[i].first - tarcLengthTable[i - 1].first;
            t = (((s - tarcLengthTable[i - 1].second) / (tarcLengthTable[i].second - tarcLengthTable[i - 1].second)) * (dt)) +  tarcLengthTable[i - 1].first;
            
            tValues.push_back(t);
        }
        s += ds;
    }
    
    Point curvePoint;
    
    //calculate points using t values
    for(int i = 0; i < controlPoints.size() - 2; i += 3) {
        for (float u = 0; u <= 1; u += du) {
            curvePoint = evaluateCurve(controlPoints[i], controlPoints[i+1], controlPoints[i+2], controlPoints[i+3], u);
            curvePointsArcLength.push_back(curvePoint);
        }
    }
}

void BezierCurve::draw(const int resolution) {
    glPushMatrix();
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    for (auto p : curvePoints) {
        glVertex3f( p.getX(), p.getY(), p.getZ() );
    }
    glEnd();
    glPopMatrix();
}

void BezierCurve::render(const Point p0, const Point p1, const Point p2, const Point p3, const int resolution) {
    glPushMatrix();
    glColor3f(1, 0, 0);
    glBegin( GL_LINE_STRIP );{
        for(int i=0; i <= resolution; i++) {
            float j = i;
            j /= resolution;
            Point pb = evaluateCurve( p0, p1, p2, p3, j);
            curvePoints.push_back(pb);
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

    glPushMatrix();
    glBegin( GL_LINE_STRIP );{
        Point pb;
        float j;
        
        for(int i=0; i <= resolution; i++) {
            j = i;
            j /= resolution;
            pb = evaluateCurve(controlPoints, j);
            
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
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
    du = 0.01;
}

void BezierCurve::setControlPoints(const std::vector<Point> points) {
    this->controlPoints = points;
}

const vector<Point>& BezierCurve::getCurvePoints() {
    return curvePoints;
}

const std::vector<Point>& BezierCurve::getCurvePointsArcLength() {
    return curvePointsArcLength;
}

void BezierCurve::calculateCurvePoints() {
    Point curvePoint;
    
    for(int i = 0; i < controlPoints.size() - 2; i += 3) {
        for (float u = 0; u <= 1; u += du) {
            curvePoint = evaluateCurve(controlPoints[i], controlPoints[i + 1], controlPoints[i + 2], controlPoints[i + 3], u);
            curvePoints.push_back(curvePoint);
        }
    }

    
}


void BezierCurve::calculateCurvePointsArcLength(float ds) {
    float u = 0;
    ds = 0.01;
    
    vector<std::pair<float, float> > tarcLengthTable;
    
    tarcLengthTable.push_back(std::make_pair(0, 0));
    
    std::pair<float, float> pair;
    float x;
    float y;
    
    for (int i = 1; i < curvePoints.size(); ++i) {
    
        float dx = (curvePoints[i - 1].getX() - curvePoints[i].getX());
        float dy = (curvePoints[i - 1].getY() - curvePoints[i].getY());
        float dz = (curvePoints[i - 1].getZ() - curvePoints[i].getZ());
        
        dx *= dx;
        dy *= dy;
        dz *= dz;
        
        float distance = sqrtf(dx + dy + dz);
        
        
        tarcLengthTable.push_back(std::make_pair(u,distance + tarcLengthTable[i-1].second));
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
            
            float top = s - tarcLengthTable[i - 1].second;
            float bottom = tarcLengthTable[i].second - tarcLengthTable[i - 1].second;
            float low = tarcLengthTable[i - 1].first;
            
            t = (((top) / (bottom)) * (dt)) + low;
            
            tValues.push_back(t);
        }
        s += ds;
    }
    
    Point curvePoint;
    
    //calculate points using t values

    
    float tVal = 0;
    int i = 0;
    for (vector<float>::iterator iter = tValues.begin(); iter != tValues.end(); ++iter) {
        tVal = *iter;
        
        int curveN = (int) tVal;
        curveN *= 3;
        
        curvePoint = evaluateCurve(controlPoints[curveN], controlPoints[curveN + 1], controlPoints[curveN + 2], controlPoints[curveN + 3], *iter);
        i += 1;
        curvePointsArcLength.push_back(curvePoint);
    }
}

void BezierCurve::draw(const int resolution) {
    glPushMatrix();
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    for (vector<Point>::iterator iter = curvePoints.begin(); iter != curvePoints.end(); ++iter) {
        glVertex3f( iter->getX(), iter->getY(), iter->getZ() );
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

vector<BezierCurve> makeCurves(vector<Point> points) {
    vector<BezierCurve> curves;
    BezierCurve curve;
    vector<Point> controlPoints;
    
    for(int i = 0; i < points.size() - 2; i += 3) {
        controlPoints.push_back(points[i]);
        controlPoints.push_back(points[i+1]);
        controlPoints.push_back(points[i+2]);
        controlPoints.push_back(points[i+3]);
        
        curve.setControlPoints(controlPoints);
        curve.calculateCurvePoints();
        curve.calculateCurvePointsArcLength(1);
        controlPoints.clear();
        
        curves.push_back(curve);
    }
    
    return curves;
}

void drawCurves(vector<BezierCurve> curves) {
    for (vector<BezierCurve>::iterator iter = curves.begin(); iter != curves.end(); ++iter) {
        iter->draw(0);
    }
}

vector<Point> getAllCurvePoints(vector<BezierCurve> curves) {
    vector<Point> points;
    
    int numElements = 0;
    
    for (vector<BezierCurve>::iterator iter = curves.begin(); iter != curves.end(); ++iter) {
        numElements +=  iter->getCurvePoints().size();
        points.reserve(numElements);
        points.insert(points.end(), iter->getCurvePoints().begin(), iter->getCurvePoints().end());
        
    }
    
    return points;
}
vector<Point> getAllCurvePointsArcLength(vector<BezierCurve> curves) {
    vector<Point> points;
    
    int numElements = 0;
    
    for (vector<BezierCurve>::iterator iter = curves.begin(); iter != curves.end(); ++iter) {
        numElements += iter->getCurvePoints().size();
        points.reserve(numElements);
        points.insert(points.end(), iter->getCurvePointsArcLength().begin(), iter->getCurvePointsArcLength().end());
        
    }
    
    return points;
}

// =================================
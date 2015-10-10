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

using std::ifstream;
using std::string;

CubicBezierCurve::CubicBezierCurve() {
    
}

CubicBezierCurve::CubicBezierCurve(const std::string& filename) {
    loadPoints(filename);
}

void CubicBezierCurve::draw(const int resolution) {
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
    
    // Connect our control points
    glColor3f(1,1,0);
    glPushMatrix();
    glLineWidth( 3.0 );
    glBegin( GL_LINE_STRIP ); {
        for(int i =0; i<controlPoints.size(); i++) {
            glVertex3f( controlPoints[i].getX(), controlPoints[i].getY(), controlPoints[i].getZ() );
        }
    }; glEnd();
    glPopMatrix();
    
    glColor3f(0, 0, 1);
    
    for(int i = 0; i < controlPoints.size() - 2; i += 3) {
        render(controlPoints[i], controlPoints[i+1], controlPoints[i+2], controlPoints[i+3], resolution);
    }
}

void CubicBezierCurve::loadPoints(const string& filename) {
    ifstream file;
    file.open(filename);
    
    string value;
    getline ( file, value, '\n' );
    
    int numPoints = atoi(value.c_str());
    
    
    for(int i=0; i < numPoints; i++) {
        string x, y, z;
        getline ( file, x, ',' );
        getline ( file, y, ',' );
        getline ( file, z, '\n' );
        int a = atoi( x.c_str());
        int b = atoi( y.c_str());
        int c = atoi( z.c_str());
        controlPoints.push_back(Point( a, b, c ));
    }
}

void CubicBezierCurve::render(Point p0, Point p1, Point p2, Point p3, int resolution) {
    glPushMatrix();
    glBegin( GL_LINE_STRIP );{
        Point pb;
        float j;
        
        for(int i=0; i <= resolution; i++) {
            j = i;
            j /= resolution;
            pb = evaluate( p0, p1, p2, p3, j);
            glVertex3f( pb.getX(), pb.getY(), pb.getZ() );
        }
    }; glEnd();
    glPopMatrix();
}

Point CubicBezierCurve::evaluate(Point p0, Point p1, Point p2, Point p3, float t) {
    float b0 = powf((1-t), 3);
    float b1 = 3 * powf((1-t), 2) * t;
    float b2 = 3 * (1-t) * powf(t, 2);
    float b3 = powf(t, 3);
    return (b0*p0 + b1*p1 + b2*p2 + b3*p3);
}




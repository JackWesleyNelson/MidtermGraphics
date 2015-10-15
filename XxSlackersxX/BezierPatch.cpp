#include "BezierPatch.h"
#include <iostream>
using std::vector;

BezierPatch::BezierPatch(vector<Point> controlPoints, float u, float v) {
    this->controlPoints = controlPoints;
    this->u = u;
    this->v = v;
}

BezierPatch::BezierPatch() {
    
    
}

void BezierPatch::draw(const int resolution) {
    drawPoints();
    //connectPoints(resolution);
    float u = 0;
    float v = 0;
    
    float du = 0.01;
    float dv = 0.01;
    
    vector<Point> surfacePoints;
    
    while (u < 1.0 && v < 1.0) {
        Point p0 = evaluateCurve(controlPoints[0], controlPoints[1], controlPoints[2], controlPoints[3], u);
        Point p1 = evaluateCurve(controlPoints[4], controlPoints[5], controlPoints[6], controlPoints[7], u);
        Point p2 = evaluateCurve(controlPoints[8], controlPoints[9], controlPoints[10], controlPoints[11], u);
        Point p3 = evaluateCurve(controlPoints[12], controlPoints[13], controlPoints[14], controlPoints[15], u);
    
        Point pSurface = evaluateCurve(p0, p1, p2, p3, v);
        
        surfacePoints.push_back(pSurface);
        
        if (surfacePoints.size() == 4) {
            
            
            for(int i =0; i < surfacePoints.size(); i++) {
                glPushMatrix();
                glColor3f(1, 0, 0);
                glTranslatef(surfacePoints[i].getX(), surfacePoints[i].getY(), surfacePoints[i].getZ());
                GLUquadric *quad;
                quad = gluNewQuadric();
                gluQuadricDrawStyle( quad, GLU_FILL);
                
                gluSphere(quad, .2, 10, 10);
                gluDeleteQuadric(quad);
                glPopMatrix();
            }
            
            
            
            glBegin(GL_QUADS);
            for (int i = 0; i < surfacePoints.size(); ++i) {
                //glVertex3f(surfacePoints[i].getX(), surfacePoints[i].getY(), surfacePoints[i].getZ());

            }
            glEnd();

            
            
            surfacePoints.clear();
        }
        
        u += du;
        v += dv;
    }
    
}


void BezierPatch::drawPoints() {
    
    for(int i =0; i < controlPoints.size(); i++) {
        glPushMatrix();
        glColor3f(0,1,0);
        glTranslatef(controlPoints[i].getX(), controlPoints[i].getY(), controlPoints[i].getZ());
        GLUquadric *quad;
        quad = gluNewQuadric();
        gluQuadricDrawStyle( quad, GLU_FILL);
        
        gluSphere(quad, .2, 10, 10);
        gluDeleteQuadric(quad);
        glPopMatrix();
    }
}

void BezierPatch::setControlPoints(const vector<Point> points) {
    this->controlPoints = points;
}

void BezierPatch::connectPoints(const int resolution) {
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
    
    glPushMatrix();
    glBegin( GL_LINE_STRIP );{
        Point pb;
        float j;
        
        for(int i=0; i <= resolution; i++) {
            j = i;
            j /= resolution;
            pb = evaluateSurface(controlPoints, 0.6, 0.4);
            glVertex3f( pb.getX(), pb.getY(), pb.getZ() );
        }
    }; glEnd();
    glPopMatrix();
}



Point evaluateSurface(const vector<Point> points, const float u, const float v) {
    Point p;
    
    for (int i = 0; i <= 3; ++i) {
        for (int j = 0; j <= 3; ++j) {
            p = p + (points[(i * 4) + j] * bezierBasis(i, u) * bezierBasis(j, v));
        }
    }
    
    return p;
}

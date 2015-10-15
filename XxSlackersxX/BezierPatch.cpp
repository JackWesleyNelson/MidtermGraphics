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
    
    Point surfacePoints[100][100];
    
    for (u = 0; u <= 1; u += du) {
        for (v = 0; v <= 1; v += dv) {
            Point p0 = evaluateCurve(controlPoints[0], controlPoints[1], controlPoints[2], controlPoints[3], u);
            Point p1 = evaluateCurve(controlPoints[4], controlPoints[5], controlPoints[6], controlPoints[7], u);
            Point p2 = evaluateCurve(controlPoints[8], controlPoints[9], controlPoints[10], controlPoints[11], u);
            Point p3 = evaluateCurve(controlPoints[12], controlPoints[13], controlPoints[14], controlPoints[15], u);
            
            Point pSurface = evaluateCurve(p0, p1, p2, p3, v);
            
            surfacePoints[(int)(u * du)][(int)(v * dv)] = pSurface;
        }
    }
    
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
    Point p;
    Point pU;
    Point pV;
    Point pUV;
    
    for (int i = 0; i < 99; ++i) {
        for (int j = 0; j < 99; ++j) {
            p = surfacePoints[i][j];
            pU = surfacePoints[i + 1][j];
            pUV = surfacePoints[i + 1][j + 1];
            pV = surfacePoints[i][j+1];
            
            glVertex3f(p.getX(), p.getY(), p.getZ());
            glVertex3f(pU.getX(), pU.getY(), pU.getZ());
            glVertex3f(pUV.getX(), pUV.getY(), pUV.getZ());
            glVertex3f(pV.getX(), pV.getY(), pV.getZ());
        }
    }
    glEnd();
    glPopMatrix();
    
    
    
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

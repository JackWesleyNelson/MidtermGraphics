#include "BezierPatch.h"
#include <iostream>
using std::vector;

BezierPatch::BezierPatch(vector<Point> controlPoints, float u, float v) {
    this->controlPoints = controlPoints;
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
    
    Point surfacePoints[101][101];
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; ++j) {
            u = i * du;
            v = j * dv;
            Point p0 = evaluateCurve(controlPoints[0], controlPoints[4], controlPoints[8], controlPoints[12], u);
            Point p1 = evaluateCurve(controlPoints[1], controlPoints[5], controlPoints[9], controlPoints[13], u);
            Point p2 = evaluateCurve(controlPoints[2], controlPoints[6], controlPoints[10], controlPoints[14], u);
            Point p3 = evaluateCurve(controlPoints[3], controlPoints[7], controlPoints[11], controlPoints[15], u);
            
            Point pSurface = evaluateCurve(p0, p1, p2, p3, v);
            
            
            surfacePoints[i][j] = pSurface;
            
            //std::cout << "(i,j,u,v)=" << i << "," << j << "," << u << "," << v << std::endl;
        }
    }
    /*Point p0 = evaluateCurve(controlPoints[0], controlPoints[4], controlPoints[8], controlPoints[12], 0);
    
    glPushMatrix();
    glTranslatef(p0.getX(), p0.getY(), p0.getZ());
    glColor3f(0,0, 1);
    GLUquadric *quad;
    quad = gluNewQuadric();
    gluQuadricDrawStyle( quad, GLU_FILL);
    
    gluSphere(quad, 2, 10, 10);
    gluDeleteQuadric(quad);
    glPopMatrix();
    
    glPushMatrix();*/
    glColor3f(.8, 0, 0);

    
    Point p;
    Point pU;
    Point pV;
    Point pUV;

    
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            p = surfacePoints[i][j];
            pU = surfacePoints[i + 1][j];
            pUV = surfacePoints[i + 1][j + 1];
            pV = surfacePoints[i][j+1];
            
            glPushMatrix();
            glTranslatef(p.getX(), p.getY(), p.getZ());
            glColor3f(0,1,0);
            GLUquadric *quad;
            quad = gluNewQuadric();
            gluQuadricDrawStyle( quad, GLU_FILL);
            
            //gluSphere(quad, .2, 10, 10);
            gluDeleteQuadric(quad);
            glPopMatrix();
            
            glBegin(GL_QUADS);
            glColor3f(.7, 0, 0);
            glVertex3f(p.getX(), p.getY(), p.getZ());
            glVertex3f(pU.getX(), pU.getY(), pU.getZ());
            glVertex3f(pUV.getX(), pUV.getY(), pUV.getZ());
            glVertex3f(pV.getX(), pV.getY(), pV.getZ());
            glEnd();
        }
    }
    
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

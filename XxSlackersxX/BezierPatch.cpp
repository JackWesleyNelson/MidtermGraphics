#include "BezierPatch.h"

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
    connectPoints(resolution);
}


void BezierPatch::drawPoints() {
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

// OpenGL / GLUT Libraries we need
#ifdef __APPLE__			// if compiling on Mac OS
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUI/glui.h>			// include our GLUI header
#else					// else compiling on Linux OS
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif



#include <math.h>

#include "ARCamera.h"

//initialize the ARCamera looking at the origin
ARCamera::ARCamera()
{
	this->ARdirX = 0;
	this->ARdirY = 0;
	this->ARdirZ = 0;
	this->ARCameraRadius = 10;
}

//initialize the ARCamera looking at the given location
ARCamera::ARCamera(float X, float Y, float Z)
{
	this->ARdirX = X;
	this->ARdirY = Y;
	this->ARdirZ = Z;
	this->ARCameraRadius = 10;
}
//initialize the ARCamera looking at the given point
ARCamera::ARCamera(Point p)
{
	this->ARdirX = p.getX();
	this->ARdirY = p.getY();
	this->ARdirZ = p.getZ();
	this->ARCameraRadius = 10;
}

//called when hero moves
void ARCamera::shiftDir( float heroX, float heroY, float heroZ )
{
	ARdirX = heroX;
	ARdirY = heroY;
	ARdirZ = heroZ;
}

//sets camera position based on ARdir coordinates, phi, theta, and radius
void ARCamera::recomputeOrientation()
{
	ARCameraX = ARCameraRadius*sin(ARCameraTheta)*sin(ARCameraPhi)+ARdirX;
	ARCameraY = -ARCameraRadius*cos(ARCameraPhi)+ARdirY;
	ARCameraZ = -ARCameraRadius*cos(ARCameraTheta)*sin(ARCameraPhi)+ARdirZ;
}

void ARCamera::lookAt()
{
	gluLookAt(ARCameraX, ARCameraY, ARCameraZ,
	ARdirX, ARdirY, ARdirZ,
	0, 1, 0);
}

void ARCamera::setTheta(float angle)
{
	ARCameraTheta += angle;
}

void ARCamera::setPhi(float angle)
{
	ARCameraPhi += angle;
}

void ARCamera::setRadius(float radius)
{
	ARCameraRadius += radius;
	if(ARCameraRadius < 0)
		ARCameraRadius = .0001;
}
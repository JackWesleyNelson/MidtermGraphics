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
#include <GL/glui.h>			// include our GLUI header
#endif



#include <math.h>

#include "Camera.h"

//initialize the camera at the origin
Camera::Camera()
{
	this->cameraX = 0;
	this->cameraY = 0;
	this->cameraZ = 0;
	this->movementConstant = 0.3f;
}

//initialize the camera at the given location
Camera::Camera(float cameraX, float cameraY, float cameraZ)
{
	this->cameraX = cameraX;
	this->cameraY = cameraY;
	this->cameraZ = cameraZ;
	this->movementConstant = 0.3f;
}
//initialize the camera at the given point
Camera::Camera(Point p)
{
	this->cameraX = p.getX();
	this->cameraY = p.getY();
	this->cameraZ = p.getZ();
}

void Camera::updateCameraRotation(int mouseDeltaX, int mouseDeltaY)
{
	cameraTheta += (mouseDeltaX)*0.005;
	cameraPhi += (mouseDeltaY)*0.005;
	// make sure that phi stays within the range (0, M_PI)
	if (cameraPhi <= 0)
		cameraPhi = 0 + 0.001;
	if (cameraPhi >= M_PI)
		cameraPhi = M_PI - 0.001;
}

void Camera::moveForward()
{
	cameraX += dirX*movementConstant;
	cameraY += dirY*movementConstant;
	cameraZ += dirZ*movementConstant;
}

void Camera::moveBackward()
{
	cameraX -= dirX*movementConstant;
	cameraY -= dirY*movementConstant;
	cameraZ -= dirZ*movementConstant;
}

void Camera::lookAt()
{
	gluLookAt(cameraX, cameraY, cameraZ,                  // camera is located at (x,y,z)
	cameraX + dirX, cameraY + dirY, cameraZ + dirZ,   // camera is looking at at (x,y,z) + (dx,dy,dz) -- straight ahead
	0.0f, 1.0f, 0.0f);                            // up vector is (0,1,0) (positive Y)
}

void Camera::setTheta(float angle)
{
	cameraTheta = angle;
}

void Camera::setPhi(float angle)
{
	cameraPhi = angle;
}

// recomputeOrientation() //////////////////////////////////////////////////////
//
// This function updates the camera's position in cartesian coordinates based 
//  on its position in spherical coordinates. Should be called every time 
//  cameraTheta, cameraPhi, or cameraRadius is updated. 
//
////////////////////////////////////////////////////////////////////////////////
void Camera::recomputeOrientation() {
	dirX = sinf(cameraTheta)*sinf(cameraPhi);
	dirZ = -cosf(cameraTheta)*sinf(cameraPhi);
	dirY = -cosf(cameraPhi);

	//and normalize this directional vector!
	float mag = sqrt(dirX*dirX + dirY*dirY + dirZ*dirZ);
	dirX /= mag;  dirY /= mag;  dirZ /= mag;
}
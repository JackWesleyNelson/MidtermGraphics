#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Point.h"

class Camera {
public:
	Camera();
	Camera(float cameraX, float cameraY, float cameraZ);
	Camera(Point p);
	void updateCameraRotation(int mouseDeltaX, int mouseDeltaY);
	void recomputeOrientation();
	void moveForward();
	void moveBackward();
	void lookAt();
	void setTheta(float angle);
	void setPhi(float angle);

private:
	float cameraX, cameraY, cameraZ;            // camera position in cartesian coordinates
	float cameraTheta, cameraPhi;               // camera DIRECTION in spherical coordinates
	float dirX, dirY, dirZ;                     // camera DIRECTION in cartesian coordinates
	float movementConstant;				//forward and backward movement speed of the camera
};
#endif
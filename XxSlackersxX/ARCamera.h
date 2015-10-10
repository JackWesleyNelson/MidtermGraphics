#pragma once
#ifndef _ARCAMERA_H_
#define _ARCAMERA_H_

#include "Point.h"

class ARCamera {
public:
	ARCamera();
	ARCamera(float ARCameraX, float ARCameraY, float ARCameraZ);
	ARCamera(Point p);
	
	void shiftDir(float heroX, float heroY, float heroZ);
	void recomputeOrientation();
	void lookAt();
	void setTheta(float angle);
	void setPhi(float angle);
	void setRadius(float radius);

private:
	float ARCameraX, ARCameraY, ARCameraZ;            // ARCamera position in cartesian coordinates
	float ARCameraTheta, ARCameraPhi;               // ARCamera DIRECTION in spherical coordinates
	float ARdirX, ARdirY, ARdirZ;                     // ARCamera DIRECTION in cartesian coordinates
	float ARCameraRadius;			//distance from camera to focus point
};
#endif
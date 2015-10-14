#pragma once
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

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

class Material{
public:
	Material();
	Material(float color[4]);
	Material(const float color[4]);
	void applyMaterial() const;
private:
	float diffuseColor[4];
	int facesEnum;
	int colorTypeEnum;
};

#endif
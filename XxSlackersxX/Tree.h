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

#ifndef _TREE_H_
#define _TREE_H_

#include "Material.h"
#include "Point.h"

class Tree {
public:
	Tree();
	Tree(float characterX, float characterY, float characterZ);
	Tree(Point p);
	void draw();
private:
	float position[3];
	float green[4];
	Material materialGreen;
};

#endif
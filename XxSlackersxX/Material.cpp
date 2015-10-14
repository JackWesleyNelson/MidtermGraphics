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

#include "Material.h"

Material::Material()
{
	//set default face
	facesEnum = GL_FRONT_AND_BACK;
	//set the default color type
	colorTypeEnum = GL_DIFFUSE;
	//set default color
	diffuseColor[0] = 0;
	diffuseColor[1] = 0;
	diffuseColor[2] = 0;
	diffuseColor[3] = 1;
}

Material::Material(float color[4])
{
	//set default face
	facesEnum = GL_FRONT_AND_BACK;
	//set the default color type
	colorTypeEnum = GL_DIFFUSE;
	//set the colors to the argument.
	for (int i = 0; i < 4; i++) {
		this->diffuseColor[i] = color[i];
	}
}


void Material::applyMaterial() const
{
	//set color material to disabled
	if (glIsEnabled(GL_COLOR_MATERIAL)) {
		glDisable(GL_COLOR_MATERIAL);
	}
	glMaterialfv(facesEnum, colorTypeEnum, diffuseColor);
}

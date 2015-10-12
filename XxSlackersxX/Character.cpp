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

#include "Character.h"

////////////////////////////////////////////////////////////////////////////////
//
//  Functions to draw Zilch avatar
//
////////////////////////////////////////////////////////////////////////////////
void Character::drawBody() {
	glColor3f(red, green, blue);							// Torso
	glPushMatrix(); {
		glTranslatef(0, -1.15, 0);
		glScalef(.75, .9, .80);
		glutSolidCube(2);
	}; glPopMatrix();

	glColor3f(red, green, blue);
	glPushMatrix(); {									// Right Arm
		glTranslatef(0, -.575, 1);
		glRotatef(-limbTheta, 0, 0, 1);
		glTranslatef(0, -.575, 0);
		glScalef(.65, 1.75, .65);
		glutSolidCube(1);
		glScalef(1, 1 / 1.75, 1);
		glTranslatef(0, -.7, .1);
		glColor3f(1, 1, 1);
		glutSolidCube(.6);
	}; glPopMatrix();

	glColor3f(red, green, blue);
	glPushMatrix(); {									// Left Arm
		glTranslatef(0, -.575, -1);
		glRotatef(limbTheta, 0, 0, 1);
		glTranslatef(0, -.575, 0);
		glScalef(.65, 1.75, .65);
		glutSolidCube(1);
		glScalef(1, 1 / 1.75, 1);
		glTranslatef(0, -.7, -.1);
		glColor3f(1, 1, 1);
		glutSolidCube(.6);
	}; glPopMatrix();

	glColor3f(red, green, blue);									//Right Leg
	glPushMatrix(); {
		glTranslatef(0, -1.5, .35);
		glRotatef(limbTheta, 0, 0, 1);
		glTranslatef(0, -1.5, 0);
		glScalef(.6, 2, .6);
		glutSolidCube(1);
	}; glPopMatrix();

	glColor3f(red, green, blue);									// Left Leg
	glPushMatrix(); {
		glTranslatef(0, -1.5, -.35);
		glRotatef(-limbTheta, 0, 0, 1);
		glTranslatef(0, -1.5, 0);
		glScalef(.6, 2, .6);
		glutSolidCube(1);
	}; glPopMatrix();
}

void Character::drawHead() {
	glColor3f(1, 1, 1);
	glutSolidCube(1);

	glColor3f(red, green, blue);									// Hat Brim
	glPushMatrix(); {
		glTranslatef(0, .55, 0);
		glScalef(1.35, .25, 1.35);
		glutSolidCube(1);
	}; glPopMatrix();

	glPushMatrix(); {									// Hat Top
		glTranslatef(0, .75, 0);
		glScalef(.9, .75, .9);
		glutSolidCube(1);
	}; glPopMatrix();

	glColor3f(1, 0, 0);
	glPushMatrix(); {									// Right Eye
		glTranslatef(.5, .20, .25);
		glRotatef(-eyeTheta, 1, 0, 0);
		glutSolidCube(.25);
	}; glPopMatrix();

	glPushMatrix(); {									// Left Eye
		glTranslatef(.5, .20, -.25);
		glRotatef(eyeTheta, 1, 0, 0);
		glutSolidCube(.25);
	}; glPopMatrix();


}

void Character::drawName() {
	glDisable(GL_LIGHTING);
	// the text
	//char scrtext[64] = "Zilch";

	// choose a colour
	glColor3f(0, 1, 0);
	glPushMatrix();
	// where we want it written
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.35, 1.75, 0);
	// how big we want it
	glScalef(.01, .01, .01);
	for (int c = 0; name[c] != 0; ++c)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, name[c]);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Character::draw() {
	glPushMatrix(); {
		glTranslatef(heroX, heroY, heroZ);				// X, Y and Z position
		glRotatef(-heroTheta, 0, 1, 0);					// Y axis rotation
		glScalef(.5, .5, .5);
		glPushMatrix(); {
			drawName();									// Name above head
		}; glPopMatrix();

		glPushMatrix(); {
			drawHead();									// Hat, Face, and Head
		}; glPopMatrix();

		glPushMatrix(); {
			drawBody();
		}; glPopMatrix();

	}; glPopMatrix();
}

// moveLimbs() /////////////////////////////////////////////////////////////////
//
//	Special function for moving Zilch legs and arms
//
////////////////////////////////////////////////////////////////////////////////
void Character::moveLimbs() {
	if (limbUp)
		limbTheta += 2;
	else limbTheta -= 2;

	if (limbTheta > 40)
		limbUp = false;
	if (limbTheta < -40)
		limbUp = true;
}

void Character::incrementEyeTheta()
{
	eyeTheta++;
	if (eyeTheta > 360) {
		eyeTheta = 0;
	}
}

void Character::positionLimbs()
{
	if (moving) {
		moveLimbs();
	}
	else limbTheta = 0;
}

void Character::moveForward()
{
	if (characterF) {
		heroX += step * cos(heroTheta*M_PI / 180);
		heroZ += step * sin(heroTheta*M_PI / 180);
	}
}

void Character::moveBackward()
{
	if (characterB) {
		heroX -= step * cos(heroTheta*M_PI / 180);
		heroZ -= step * sin(heroTheta*M_PI / 180);
	}
}

void Character::rotateLeft()
{
	if (characterL)
		heroTheta--;
}

void Character::rotateRight()
{
	if (characterR)
		heroTheta++;
}

bool Character::isMoving()
{
	return moving;
}

bool Character::isCharacterL()
{
	return characterL;
}

bool Character::isCharacterR()
{
	return characterR;
}

bool Character::isCharacterF()
{
	return characterF;
}

bool Character::isCharacterB()
{
	return characterB;
}

void Character::setMoving(bool state)
{
	moving = state;
}

void Character::setCharacterL(bool state)
{
	characterL = state;
}

void Character::setCharacterR(bool state)
{
	characterR = state;
}

void Character::setCharacterF(bool state)
{
	characterF = state;
}

void Character::setCharacterB(bool state)
{
	characterB = state;
}

void Character::setTheta(float angle)
{
	heroTheta = angle;
}

void Character::setX(float x)
{
	heroX = x;
}

void Character::setZ(float z)
{
	heroZ = z;
}

void Character::setColor(float r, float g, float b)
{
	red = r;
	green = g;
	blue = b;
}

void Character::setName(char* n)
{
	name = n;
}

float Character::getX()
{
	return heroX;
}

float Character::getY()
{
	return heroY;
}

float Character::getZ()
{
	return heroZ;
}

float Character::getTheta()
{
	return heroTheta;
}

Character::Character()
{
	heroX = 0;
	heroY = 2;
	heroZ = 0;
	heroTheta = 0;
	eyeTheta = 0;
	limbTheta = 0;
	step = .25f;
	moving = false;
	limbUp = true;
	characterL = false;
	characterR = false;
	characterF = false;
	characterB = false;
	red = 0.1f;
	green = 0.1f;
	blue = 0.1f;
	name = "Zilch";
}

Character::Character(float characterX, float characterY, float characterZ)
{
	heroX = characterX;
	heroY = characterY+2;
	heroZ = characterZ;
	heroTheta = 0;
	eyeTheta = 0;
	limbTheta = 0;
	step = .25f;
	moving = false;
	limbUp = true;
	characterL = false;
	characterR = false;
	characterF = false;
	characterB = false;
	red = 0.1f;
	green = 0.1f;
	blue = 0.1f;
	name = "Zilch";
}

Character::Character(Point p)
{
	heroX = p.getX();
	heroY = p.getY() + 2;
	heroZ = p.getZ();
	heroTheta = 0;
	eyeTheta = 0;
	limbTheta = 0;
	step = .25f;
	moving = false;
	limbUp = true;
	characterL = false;
	characterR = false;
	characterF = false;
	characterB = false;
	red = 0.1f;
	green = 0.1f;
	blue = 0.1f;
	name = "Zilch";
}

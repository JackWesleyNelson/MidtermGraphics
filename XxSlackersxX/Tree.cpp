#include "Tree.h"

Tree::Tree()
{
	//initialize position
	position[0] = 0;
	position[1] = 0;
	position[2] = 0;
	position[3] = 1;
	//initialize color for material
	green[0] = 0;
	green[1] = 1;
	green[2] = 0;
	green[3] = 1;
	//initialize material
	materialGreen = Material(green);
}

Tree::Tree(float characterX, float characterY, float characterZ)
{
	//initialize position
	position[0] = characterX;
	position[1] = characterY;
	position[2] = characterZ;
	position[3] = 1;
	//initialize color for material
	green[0] = 0;
	green[1] = 1;
	green[2] = 0;
	green[3] = 1;
	//initialize material
	materialGreen = Material(green);
}

Tree::Tree(Point p)
{
	//initialize position
	position[0] = p.getX();
	position[1] = p.getY();
	position[2] = p.getZ();
	position[3] = 1;
	//initialize color for material
	green[0] = 0;
	green[1] = 1;
	green[2] = 0;
	green[3] = 1;
	//initialize material
	materialGreen = Material(green);
}

void Tree::draw()
{
	GLdouble height = 3;
	GLdouble radius = .75;

	glTranslatef(position[0], position[1], position[1]);
	glRotatef(270, 1, 0, 0);

	glPushMatrix(); {
		materialGreen.applyMaterial();
		glutSolidCone(radius, height, 30, 30);
		glPushMatrix(); {
			glTranslatef(0, 0, height*.33);
			glutSolidCone(radius, height, 30, 30);
			glPushMatrix(); {
				glTranslatef(0, 0, height*.33);
				glutSolidCone(radius, height, 30, 30);
			}; glPopMatrix();
		}; glPopMatrix();
	}; glPopMatrix();
}

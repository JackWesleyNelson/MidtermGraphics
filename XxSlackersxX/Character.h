#pragma once
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Point.h"
#include "Material.h"

class Character {
public:
	Character();
	Character(float characterX, float characterY, float characterZ);
	Character(Point p);
	
	void draw();
	void moveLimbs();
	void incrementEyeTheta();
	void positionLimbs();
	void moveForward();
	void moveBackward();
	void rotateLeft();
	void rotateRight();

	bool isMoving();
	bool isCharacterL();
	bool isCharacterR();
	bool isCharacterF();
	bool isCharacterB();

	void setMoving(bool state);
	void setCharacterL(bool state);
	void setCharacterR(bool state);
	void setCharacterF(bool state);
	void setCharacterB(bool state);
	void setTheta(float angle);
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setColor(float r, float g, float b, float a);
	void setName(char* n);
	char* getName();
	
	float getX();
	float getY();
	float getZ();
	float getTheta();

private:
	//Zilch's attributes
	float heroX, heroY, heroZ, heroTheta, eyeTheta, limbTheta, step, color[4];
	bool moving, limbUp, characterL, characterR, characterF, characterB;
	char* name;
	Material materialCustom;

	float red[4];
	float green[4];
	float blue[4];
	float white[4];
	float black[4];

	Material materialRed;
	Material materialGreen;
	Material materialBlue;
	Material materialWhite;
	Material materialBlack;

	void drawBody();
	void drawHead();
	void drawName();
	void setMaterials();

};

#endif
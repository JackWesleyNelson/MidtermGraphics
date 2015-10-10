#pragma once
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Point.h"

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

	float getX();
	float getY();
	float getZ();


private:
	//Zilch's attributes
	float heroX, heroY, heroZ, heroTheta, eyeTheta, limbTheta, step;
	bool moving, limbUp, characterL, characterR, characterF, characterB;

	void drawBody();
	void drawHead();
	void drawName();

};

#endif
#pragma once
#ifndef _POINT_H_
#define _POINT_H_

class Point {
public:
	Point();
	Point(float x, float y, float z);
	float getX();
	float getY();
	float getZ();
private:
	float x, y, z;
};

Point operator*(Point p, float f);//multiplies a Point by a float
Point operator*(float f, Point p);//multiplies a float by a Point
Point operator+(Point a, Point b);//add two Points together

float distance(Point p1, Point p2);

#endif
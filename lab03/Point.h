class Point {

	public:
		float x;
		float y;
		float z;

	Point();
	Point(float a, float b, float c);

	float getX();
	float getY();
	float getZ();
};

Point operator*( Point p, float f ); // multiplies a Point by a float
Point operator*( float f, Point p ); // multiplies a float by a Point
Point operator+( Point a, Point b ); // adds two Points together
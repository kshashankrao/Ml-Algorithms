#pragma once

//////* Friend Function*//////
class Shape
{
private:
	int width;
	int height;

public:
	float area;
	Shape(int w, int h): width(w), height(h)
	{}
	/* This function can be used outside the class to access the private and protected variables*/
	friend Shape calcArea();
};

//////* Friend Class*//////

void friends_main();
#include "Understanding_Friends_in_Inheritance.h"
#include <iostream>

Shape calcArea()
{
	/* This function is a friend function because it is not part of the class Shape, but can access its private and protected variables by overloading 
	   the function specified in the class with the keyword friend*/
	Shape shape(2,3);
	shape.area = shape.width * shape.height;
	return shape;
}

void friends_main()
{
	/* Friend Function*/
	Shape s = calcArea();
	std::cout << "Area = " << s.area;
}
#pragma once
struct Point
{
	float x;
	float y;
	float z;
	bool knn; /* True if the point is inside k*/
	float dist; /* Distance from a given point*/
	float val; /* Class index*/
};


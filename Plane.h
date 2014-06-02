#pragma once

#include "CGFobject.h"
class Plane
{
public:
	Plane(void);
	Plane(float);
	~Plane(void);
	void draw(float xRatio, float yRatio, float yAxis);
    void drawWindow();
private:
	float _numDivisions; // Number of triangles that constitute rows/columns
};


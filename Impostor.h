#ifndef Impostor_H
#define Impostor_H

#include "Plane.h"
class Impostor {
public:
	Impostor();
	Impostor(int div, double domain, double delta);
	~Impostor(void);
	float getTextureX(int opt);
	float getTextureZ(int opt);
	void draw();
private:
	int _numDivisions;
	double _domain;
	double _delta;
};
#endif


#ifndef MY_CYLINDER
#define MY_CYLINDER

#include "CGFobject.h"

#include <vector>

typedef struct coordinate {
    float x;
    float y;
    float z;
} crd;

class Cylinder : public CGFobject {

	bool smooth;
	int slices;
	int stacks;

	public:
		Cylinder(int slices, int stacks, bool smooth);
		void draw();

};



#endif

#ifndef CHAIR_H
#define CHAIR_H

#include "CGFobject.h"

#include "CGFappearance.h"

class Chair: public CGFobject {
private:
    int angle;
    
    CGFappearance *material;
    
public:
    void draw();
    
    Chair();
};

#endif
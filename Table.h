#ifndef TABLE_H
#define TABLE_H

#include "CGFobject.h"

#include "CGFappearance.h"

class Table: public CGFobject {
private:
    int angle;
    
    CGFappearance *materialT;
    CGFappearance *materialL;
    CGFappearance *tableAppearance;
    
public:
    void draw();
    
    Table();
};

#endif
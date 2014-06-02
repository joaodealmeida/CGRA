//
//  CylinderSlice.h
//  CGFExample
//
//  Created by Eduardo Almeida on 19/03/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#ifndef __CGFExample__CylinderSlice__
#define __CGFExample__CylinderSlice__

#include "CGFobject.h"

#include "Cylinder.h"

#include <vector>

class CylinderSlice : public CGFobject {
    
private:
    
    int _slices;
    
    bool _smooth;
    
    bool _isClockBase;
    
    std::vector<coordinate> _vertices;
    
    void drawBase(float yAxis);
    
public:
    
    CylinderSlice(int slices, bool smooth);
    
    void draw();
    
    void setIsClockBase(bool cl) {
        _isClockBase = cl;
    }
};

#endif /* defined(__CGFExample__CylinderSlice__) */

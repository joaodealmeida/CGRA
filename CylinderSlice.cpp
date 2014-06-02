//
//  CylinderSlice.cpp
//  CGFExample
//
//  Created by Eduardo Almeida on 19/03/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#include "CylinderSlice.h"

#include "CGFappearance.h"

#include <cmath>

static float pi = acos(-1.0);
static float deg2rad = pi/180.0;

CylinderSlice::CylinderSlice(int slices, bool smooth) {
    _slices = slices;
    _smooth = smooth;
}

void CylinderSlice::draw() {
		drawBase(0);

		drawBase(1);

        float angle = (360.0f / _slices)*deg2rad;
		glPushMatrix();

		for (int i =0; i<_slices;i++)
		{

			glBegin(GL_QUADS);
			if(_smooth) {

				glNormal3f(cos(angle*i), 0,sin(angle*i));
				glVertex3f(cos(angle*i),0,sin(angle*i));

				glNormal3f(cos(angle*i), 0,sin(angle*i));
				glVertex3f(cos(angle*i),1, sin(angle*i));

				glNormal3f(cos(angle*(i+1)), 0,sin(angle*(i+1)));
				glVertex3f(cos(angle*(i+1)),1,sin(angle*(i+1)));

				glNormal3f(cos(angle*(i+1)), 0,sin(angle*(i+1)));
				glVertex3f(cos(angle*(i+1)),0 ,sin(angle*(i+1)));
				
			}
			else {

				glNormal3f(cos(angle*i + angle/2),0,sin(angle*i + angle/2));

				glVertex3f(cos(angle*i),0,sin(angle*i));

				glVertex3f(cos(angle*i), 1,sin(angle*i));

				glVertex3f(cos(angle*(i+1)),1,sin(angle*(i+1)));

				glVertex3f(cos(angle*(i+1)),0,sin(angle*(i+1)));
			}

			glEnd();
		}
	glPopMatrix();
}

void CylinderSlice::drawBase(float yAxis) {
    float angle = 360.0f / _slices;
    
    float last_angle = 0.0f;
    
    glPushMatrix();
    
    if (_isClockBase) {
        float amb[3] = {1, 1, 1};
        float dif[3] = {1, 1, 1};
        float spec[3] = {1, 1, 1};
        float shininess = 10.0f;
        
        CGFappearance *clockAppearance = new CGFappearance(amb, dif, spec, shininess);
        clockAppearance->setTexture("clock.png");
        
        clockAppearance->apply();
    }
    
    if (yAxis) {
        glTranslated(0, yAxis, 0);
        
        glRotated(180, 0.0f, 0.0f, 1.0f);
        
        if (_smooth)
            glNormal3f(0, 1, 0);
    } else if (_smooth)
        glNormal3f(0, -1, 0);
    
    /*glBegin(GL_POLYGON);
    
    crd first_crd;
    
    first_crd.x = -0.5f / _slices;
    first_crd.y = 0.0f;
    first_crd.z = 0.5f / _slices;
    
	glTexCoord2d((cos(_slices-1 * deg2rad) +1) / 2,
		(sin(_slices-1 * deg2rad) +1) / 2);
    
    glVertex3f(first_crd.x, first_crd.y, first_crd.z);
    
    _vertices.push_back(first_crd);
    
    crd second_crd;
    
    second_crd.x = 0.5f / _slices;
    second_crd.y = 0.0f;
    second_crd.z = 0.5f / _slices;
    
	glTexCoord2d((cos(_slices-2 * deg2rad) +1) / 2,
		(sin(_slices-2 * deg2rad) +1) / 2);
    
    glVertex3f(second_crd.x, second_crd.y, second_crd.z);
    
    _vertices.push_back(second_crd);
    
    crd last_crd;
    
    last_crd.x = 0.5f / _slices;
    last_crd.y = 0.0f;
    last_crd.z = 0.5f / _slices;
    
    for (int i = 0; i < _slices - 2; i++) {
        last_crd.x += cosf(deg2rad * (angle + last_angle)) / _slices;
        last_crd.z += sinf(deg2rad * (angle + last_angle)) / _slices;
        
        last_angle += angle;
        
        _vertices.push_back(last_crd);
        
       // glTexCoord2d(last_crd.x, last_crd.z);
		 glTexCoord2d((cos(i * deg2rad) +1) / 2,
				(sin(i * deg2rad) +1) / 2);
        glVertex3f(last_crd.x, last_crd.y, last_crd.z);
    }
    
    glEnd();*/
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.5, 0.5);
	glVertex3f(0, 0, 0);
	for (int i =0; i<=_slices;i++) {	
		glTexCoord2f((cos(angle*i)+1)/2,(sin(angle*i)+1)/2);
		glVertex3f(cos(angle*i), 0, sin(angle*i));
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, -1, 0);
	glVertex3f(0, 1, 0);
	for (int i =0; i<=_slices;i++) {
		glVertex3f(cos(-angle*i), 1, sin(-angle*i));
	}
	glEnd();

    
    glPopMatrix();
}
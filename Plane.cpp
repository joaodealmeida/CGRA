#include "Plane.h"

#include <GL/glui.h>

Plane::Plane(void) {
	_numDivisions = 1.0f;
}

Plane::Plane(float n) {
	_numDivisions = n;
}


Plane::~Plane(void) {
    
}

void Plane::draw(float xRatio, float yRatio, float yAxis) {
	glPushMatrix();
	glRotatef(180.0,1,0,0);
	glTranslatef(-0.5,0.0,-0.5);
	glScalef(1.0/(double) _numDivisions, 1 ,1.0/(double) _numDivisions);
	glNormal3f(0,-1,0);
    
	for (float bx = 0; bx<_numDivisions; bx++) {
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2d(bx / _numDivisions  *xRatio,0+yAxis);
		glVertex3f(bx, 0, 0);
        
		for (float bz = 0; bz<_numDivisions; bz++) {
			glTexCoord2d((bx + 1) / _numDivisions * xRatio, (bz / _numDivisions) * yRatio + yAxis);
			glVertex3f(bx + 1, 0, bz);
			glTexCoord2d((bx / _numDivisions) * xRatio, ((bz + 1) / _numDivisions) * yRatio + yAxis);
			glVertex3f(bx, 0, bz + 1);
		}
        
		glTexCoord2d(((bx + 1) / _numDivisions * xRatio), 1*yRatio +yAxis);
		glVertex3d(bx + 1, 0, _numDivisions);
		glEnd();
	}
	glPopMatrix();

}

void Plane::drawWindow() {
	glPushMatrix();
	glRotatef(180.0, 1, 0, 0);
	glTranslatef(-0.5, 0.0, -0.5);
	glScalef(1.0 / (double) _numDivisions, 1, 1.0 / (double) _numDivisions);
	glNormal3f(0, -1, 0);

	for (int bx = 0; bx < _numDivisions; bx++) {
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2d(0, 1);
		glVertex3f(bx, 0, 0);
		for (int bz = 0; bz < _numDivisions; bz++) {
			glTexCoord2d(0, 0);
			glVertex3f(bx + 1, 0, bz);
			glTexCoord2d(1, 1);
			glVertex3f(bx, 0, bz + 1);
		}
		glTexCoord2d(1, 0);
		glVertex3d(bx + 1, 0, _numDivisions);

		glEnd();
	}
	glPopMatrix();

}
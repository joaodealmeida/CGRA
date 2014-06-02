#include "Impostor.h"
#include "Cube.h"

Impostor::Impostor() {
	_numDivisions = 1;
	_domain = 1;
	_delta = 0;
}

Impostor::Impostor(int divisions, double domain, double delta) {
	_numDivisions = divisions;
	_domain = domain;
	_delta = delta;
}

float Impostor::getTextureX(int opt) {
	switch (opt) {
	case 0:
		return -1;
	case 1:
		return 0.04;
	case 2:
		return 0.96;
	case 3:
		return 2;
	}
}

float Impostor::getTextureZ(int opt) {
	switch (opt) {
	case 0:
		return -1;
	case 1:
		return 0.05;
	case 2:
		return 0.95;
	case 3:
		return 2;
	}
}

Impostor::~Impostor(void) {
}

void Impostor::draw() {
	glPushMatrix();
	glRotatef(180.0, 1, 0, 0);
	glTranslatef(-0.5, 0.0, -0.5);
	glScalef(1.0 / (double) _numDivisions, 1, 1.0 / (double) _numDivisions);
	glNormal3f(0, -1, 0);

	for (int bx = 0; bx < _numDivisions; bx++) {
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2d(getTextureX(bx), getTextureZ(0));
		glVertex3f(bx, 0, 0);
		for (int bz = 0; bz < _numDivisions; bz++) {
			if (bz == 1 && bx == 1) {
				glTexCoord2d(getTextureX(bx + 1), getTextureZ(bz));
				glVertex3f(bx + 1, 0, bz);

				glEnd();

				glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2d(getTextureX(bx), getTextureZ(bz + 1));
				glVertex3f(bx, 0, bz + 1);
			} else {
				glTexCoord2d(getTextureX(bx + 1), getTextureZ(bz));
				glVertex3f(bx + 1, 0, bz);

				glTexCoord2d(getTextureX(bx), getTextureZ(bz + 1));
				glVertex3f(bx, 0, bz + 1);
			}
		}
		glTexCoord2d(getTextureX(bx + 1), getTextureZ(_numDivisions));
		glVertex3d(bx + 1, 0, _numDivisions);

		glEnd();
	}
	glPopMatrix();
}



#include "Robot.h"
#define PI 3.141592653589793238463
#define DegToRad PI/180
#include <cmath>
#include <iostream>


Robot::Robot(double xpos, double ypos , double zpos,double yOrient, int stacks) {
	_xpos = xpos;
	_ypos = ypos;
	_zpos = zpos;
	_angle= yOrient;
	_stacks = stacks;
	_textured = true;
}



void Robot::move(int dir){
	if (dir == 0) {
		_zpos += cos(_angle * DegToRad) * 0.1;
		_xpos += sin(_angle * DegToRad) * 0.1;
	} else if (dir == 1) {
		_zpos -= cos(_angle * DegToRad) * 0.1;
		_xpos -= sin(_angle * DegToRad) * 0.1;
	}
}

void Robot::rotate(int dir) {
	if (dir == 0) 
		_angle += 2.5;
	if (dir == 1)
		_angle -= 2.5;
}

void Robot::draw() {
		double dx = 1/3 , alpha = -5 * PI / 4 , dalpha = -PI / 6 ;
		float jump=30;
		glDisable(GL_CULL_FACE);

		if(_textured)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//TEXEL CORRESSPONDENTE S = x+ 0,5 | T=z+0.5
	//TOP
		glPushMatrix();
		glTranslated(_xpos, 1+_ypos, _zpos);
			glBegin(GL_POLYGON);
			for (float i=15.0; i<375.0; i+=jump) {
					float x=sin(DegToRad*i)/4;
					float y=0, z =cos(DegToRad*i)/4;
					glNormal3d(0,1,0);
					glTexCoord2f(x+0.5,z+0.5);
					glVertex3d(x, y, z);
			}
			glEnd();
		glPopMatrix();

	//BOTTOM
		glPushMatrix();
			glNormal3d(0, 1, 0);
			glTranslated(_xpos, _ypos, _zpos);
			glRotated(_angle, 0, 1, 0);
			glBegin(GL_POLYGON);
				glTexCoord2f(0,0);
				glVertex3d(-0.5, 0, -0.5);
				glTexCoord2f(1,0);
				glVertex3d(0.5, 0, -0.5);
				glTexCoord2f(1,1);
				glVertex3d(0.5, 0, 0.5);
				glTexCoord2f(0,1);
				glVertex3d(-0.5, 0, 0.5);
			glEnd();

	
		glPopMatrix();


		glEnable(GL_CULL_FACE);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );


		




	//ROBOT
	glTranslated(_xpos, _ypos, _zpos);
	glRotated(_angle,0,1,0);
	for (int j = 0; j < 4; j++) {

		glRotated(90 * j, 0, 1, 0);
		for (int i = 0; i < 3; i++) {
			double x1 = cos((alpha + dalpha * (i))) * 0.25;
			double z1 = sin((alpha + dalpha * (i))) * 0.25;
			double x2 = cos((alpha + dalpha * (i + 1))) * 0.25;
			double z2 = sin((alpha + dalpha * (i + 1))) * 0.25;
			double px1 = -0.5 + (1 / 3.0) * i;
			double px2 = -0.5 + (1 / 3.0) * (i + 1);
			double pz1 = 0.5, pz2 = 0.5;
			double py = 0;
			double dex1 = abs((x1 - px1) / _stacks), dey = abs(
					(1 - py) / _stacks), dez1 = abs((z1 - pz1) / _stacks);
			double dex2 = abs((x2 - px2) / _stacks), dez2 = abs(
					(z2 - pz2) / _stacks);
			glBegin(GL_TRIANGLE_STRIP);
			glNormal3d(px1, 0, pz1);
			glTexCoord2f(px1+0.5,1-(pz1+0.5));
			glVertex3f(px1, py, pz1);
			glNormal3d(px2, 0, pz2);
			glTexCoord2f(px2+0.5,1-(pz2+0.5));
			glVertex3f(px2, py, pz2);
			for (int k = 1; k < _stacks; k++) {
				if (px1 < 0)
					px1 = px1 + dex1;
				else
					px1 = px1 - dex1;
				if (px2 < 0)
					px2 = px2 + dex2;
				else
					px2 = px2 - dex2;
				py = py + dey;
				pz1 = pz1 - dez1;
				pz2 = pz2 - dez2;

				glNormal3d(px1, 0, pz1);
				glTexCoord2f(px1+0.5,1-(pz1+0.5));
				glVertex3f(px1, py, pz1);
				glNormal3d(px2, 0, pz2);
				glTexCoord2f(px2+0.5,1-(pz2+0.5));
				glVertex3f(px2, py, pz2);

			}

			glNormal3d(x1, 0, z1);
			glTexCoord2f(x1+0.5,1-(z1+0.5));
			glVertex3f(x1, 1, z1);
			glNormal3d(x2, 0, z2);
			glTexCoord2f(x2+0.5,1-(z2+0.5));
			glVertex3f(x2, 1, z2);
			glEnd();
		}
	}
	glPopMatrix();

}

void Robot::setTypeofTexture(bool opt){
	_textured=opt;
}





#include "ClockHand.h"

#include "Cube.h"

ClockHand::ClockHand() {
	_angle=0;
	float ambC[3] = {0.2, 0.2, 0.2};
	float difC[3] = {0.6, 0.6, 0.6};
	float specC[3] = /* {0.2, 0.2, 0.2} */ {0.0, 0.2, 0.8};
	float shininessC = /*   10.f    */ 120.0f;
	
	chAppearance = new CGFappearance(ambC, difC, specC, shininessC);
}

void ClockHand::setAngle(float angle) {
    _angle = angle;
	
}

void ClockHand::draw() {
	Cube *chand = new Cube();
	glPushMatrix();
	
	switch (_tt) {
	case kTimeTypeSeconds:
			glRotated(_angle,1,0,0);
			glScaled(0.025,0.42,0.05);
			glTranslated(2.4,0,0);
			chAppearance->apply();
			chand->draw();
		break;

	case kTimeTypeMinutes:
			glRotated(_angle,1,0,0);
			glScaled(0.025,0.6,0.05);
			glTranslated(2.2,0,0);
			chAppearance->apply();
			chand->draw();
		break;

	case kTimeTypeHours:
		
			glRotated(_angle,1,0,0);
			glScaled(0.025,0.69,0.01);
			glTranslated(2.8,0,0);
			chAppearance->apply();
			chand->draw();
		
		break;

	default:

		break;
	}

	glPopMatrix();
}

float ClockHand::getAngle(){
	return _angle;
}

ClockHand::~ClockHand() {

}


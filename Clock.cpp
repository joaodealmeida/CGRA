#include "Clock.h"

#include "CGFappearance.h"

Clock::Clock() {
	clockCyl = new Cylinder(12, 1, true);
	HourHand = new ClockHand();
	MinHand = new ClockHand();
	SecHand = new ClockHand();

	HourHand->setAngle(270);
	MinHand->setAngle(180);
	SecHand->setAngle(90);
	_active=true;


}

void Clock::draw() {
	// Coefficients for material B
	float ambB[3] = {0.2, 0.2, 0.2};
	float difB[3] = {0.6, 0.6, 0.6};
	float specB[3] = {0.8, 0.8, 0.8};
	float shininessB = 120.f;

	clockAppearance = new CGFappearance(ambB,difB,specB,shininessB);
	clockAppearance->setTexture("clock.png");
	clockAppearance->setTextureWrap(GL_REPEAT, GL_REPEAT);

	Cylinder* c1 = new Cylinder(12,1,true);

	glPushMatrix();
		glScaled(0.10,1,1);
		glRotated(90,0,1,0);
		clockAppearance->apply();
		c1->draw();
	glPopMatrix();

	HourHand->setTimeType(kTimeTypeHours);
	MinHand->setTimeType(kTimeTypeMinutes);
	SecHand->setTimeType(kTimeTypeSeconds);

	HourHand->draw();
	MinHand->draw();
	SecHand->draw();   
}

void Clock::resetClock(){
	HourHand->setAngle(0);
	MinHand->setAngle(0);
	SecHand->setAngle(0);
}

void Clock::update(unsigned long time)
{
	if(_active){
		float a = ((float)(time)/1000.0)*360.0/60.0;

		HourHand->setAngle(HourHand->getAngle() - (a/(3600.0/5.0))); 
		MinHand->setAngle(MinHand->getAngle() - (a/60.0) );
		SecHand->setAngle(SecHand->getAngle() - a);
		
		HourHand->draw();
		MinHand->draw();
		SecHand->draw();
	}


}

Clock::~Clock() {
    
}
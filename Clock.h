#pragma once
#include "Cylinder.h"
#include "ClockHand.h"
class Clock
{
	 Cylinder* clockCyl;
	 bool _active;
	 CGFappearance* clockAppearance;


public:
	ClockHand* HourHand;
	ClockHand* MinHand;
	ClockHand* SecHand;
	Clock(void);
	void update(unsigned long time);
	
	void setActive(bool isActive) {
		_active = isActive;
	}

	bool getActive() {
		return _active;
	}

	void resetClock();
	
	void draw();
	~Clock(void);
};

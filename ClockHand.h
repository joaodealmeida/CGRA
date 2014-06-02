#pragma once

#include "CGFobject.h"
#include "CGFappearance.h"

typedef enum {
	kTimeTypeSeconds,
	kTimeTypeMinutes,
	kTimeTypeHours
} kTimeType;

class ClockHand {
    
    float _angle;

	bool _skipDrawing;

	kTimeType _tt;
    
public:
    CGFappearance* chAppearance;

	ClockHand();
    
    void setAngle(float angle);

	float getAngle();

	void setTimeType(kTimeType tt) {
		_tt = tt;
	}

	kTimeType getTimeType() {
		return _tt;
	}
    
	void draw();

	void draw(kTimeType t);
    
	~ClockHand();
};

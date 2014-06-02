#ifndef LightingScene_H
#define LightingScene_H

#include "CGFscene.h"
#include "CGFappearance.h"
#include "Table.h"
#include "Plane.h"
#include "Chair.h"
#include "Clock.h"
#include "Robot.h"
#include "Impostor.h"

class LightingScene : public CGFscene
{
	
public:
	void init();
	void display();
	int sceneVar;

	CGFlight* light0;
	CGFlight* light1;
    CGFlight* light2;
    CGFlight* light3;
	int _light0;
	int _light1;
	int _light2;
	int _light3;
	int clock_status1;
	int clock_status2;
	int _textselect;
	int _radiobutton;

	Table* table;
    Chair* chair;
	Plane* wall;
	Plane* boardA;
	Plane* boardB;
	Clock* clock;
	Robot* robot;
	Impostor* impostor;
	CGFappearance* materialA;
	CGFappearance* materialB;
    CGFappearance* materialFW;
	CGFappearance* tableAppearance;
    CGFappearance* windowAppearance;
    CGFappearance* floorAppearance;
	CGFappearance* backgroundAppearance;
	CGFappearance* Robot1Appearance;
	CGFappearance* Robot2Appearance;
	CGFappearance* Robot3Appearance;

	~LightingScene();

	unsigned long _last_time_ms;
    
    void update(unsigned long ms);
	void toggleSomething();
};

#endif
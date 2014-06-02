#include "LightingScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "Table.h"
#include "Plane.h"
#include "Chair.h"
#include "Cylinder.h"
#include "ClockHand.h"
#include "Robot.h"
#include <iostream>

#include <math.h>

float pi = acos(-1.0);
float deg2rad=pi/180.0;

#define BOARD_HEIGHT 6.0
#define BOARD_WIDTH 6.4

// Positions for two lights
float light0_pos[4] = {4, 6.0, 1.0, 1.0};
float light1_pos[4] = {10.5, 6.0, 1.0, 1.0};

float light2_pos[4] = {10.5, 6.0, 5.0, 1.0};
float light3_pos[4] = {4, 6.0, 5.0, 1.0};

// Global ambient light (do not confuse with ambient component of individual lights)
float globalAmbientLight[4]= /*{0.2,0.2,0.2,1.0}*/{0, 0, 0, 1};

// number of divisions
#define BOARD_A_DIVISIONS 30*30
#define BOARD_B_DIVISIONS 100

// Coefficients for material A
float ambA[3] = {0.2, 0.2, 0.2};
float difA[3] = {0.6, 0.6, 0.6};
float specA[3] = /* {0.2, 0.2, 0.2} */ {0.0, 0.2, 0.8};
float shininessA = /*   10.f    */ 120.0f;

// Coefficients for material B
float ambB[3] = {0.2, 0.2, 0.2};
float difB[3] = {0.6, 0.6, 0.6};
float specB[3] = {0.8, 0.8, 0.8};
float shininessB = 120.f;

// Coefficients for floor/wall
float ambFW[3] = {75.0f / 255.0f, 0.0f, 0.0f};
float difFW[3] = {75.0f / 255.0f, 0.0f, 0.0f};
float specFW[3] = {75.0f / 255.0f, 0.0f, 0.0f};
float shininessFW = 150.f;

float ambientNull[4]={0,0,0,1};
float yellow[4]={1,1,0,1};

void LightingScene::init() 
{
	sceneVar=0;
	_light0=0;
	_light1=0;
	_light2=0;
	_light3=0;
	_textselect=1;
	_radiobutton=0;
	// Enables lighting computations
	glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	// Computes lighting only using the front face normals and materials
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);  
	
	// Define ambient light (do not confuse with ambient component of individual lights)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);
    
    glShadeModel(GL_SMOOTH);
	
	// Declares and enables two lights, with null ambient component

	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->setAmbient(yellow);

	//light0->disable();
	light0->enable();

	light1 = new CGFlight(GL_LIGHT1, light1_pos);
	light1->setAmbient(ambientNull);
	
	//  light1->disable();
	light1->enable();
    
    light2 = new CGFlight(GL_LIGHT2, light2_pos);
    light2->setAmbient(ambientNull);
    
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2f);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0f);
    
    light2->enable();
    
    light3 = new CGFlight(GL_LIGHT3, light3_pos);
    light3->setAmbient(ambientNull);
    
    glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 1.0f);
    
    light3->enable();
	
	// Uncomment below to enable normalization of lighting normal vectors
	glEnable (GL_NORMALIZE);

	//Declares scene elements
	table = new Table();
    //chair = new Chair();
	wall = new Plane();
	impostor = new Impostor(3, 2.5, -0.75);
	clock = new Clock();
	robot = new Robot(5.0,0.1,5.0,0,8);
    
	boardA = new Plane(BOARD_A_DIVISIONS);
	boardB = new Plane(BOARD_B_DIVISIONS);
	
	//Declares materials and textures
	materialA = new CGFappearance(ambA,difA,specA,shininessA);
	materialB = new CGFappearance(ambB,difB,specB,shininessB);
    materialFW = new CGFappearance(ambFW, difFW, specFW, shininessFW);
	Robot1Appearance = new CGFappearance(ambB, difB, specB, shininessB);

    
    materialA -> setTexture("slides.png");
    materialB -> setTexture("board.png");
    
    windowAppearance = new CGFappearance(ambA, difA, specA, shininessA);
    windowAppearance -> setTexture("window.png");
	windowAppearance -> setTextureWrap(GL_CLAMP, GL_CLAMP);

	backgroundAppearance = new CGFappearance(ambA, difA, specA, shininessA);
	backgroundAppearance -> setTexture("background.jpg");
    
    floorAppearance = new CGFappearance(ambA, difA, specA, shininessA);
    floorAppearance -> setTexture("floor.png");

	Robot1Appearance = new CGFappearance(ambB, difB, specB, shininessB);
	Robot1Appearance->setTexture("robot1.jpg");
	Robot1Appearance->setTextureWrap(GL_CLAMP,GL_CLAMP);

	Robot2Appearance = new CGFappearance(ambB, difB, specB, shininessB);
	Robot2Appearance->setTexture("robot2.jpg");
	Robot2Appearance->setTextureWrap(GL_CLAMP,GL_CLAMP);

	Robot3Appearance = new CGFappearance(ambB, difB, specB, shininessB);
	Robot3Appearance->setTexture("robot3.jpg");
	Robot3Appearance->setTextureWrap(GL_CLAMP,GL_CLAMP);
	

	setUpdatePeriod(100);

}

void LightingScene::display() 
{

	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();
	light0->draw();
	light1->draw();
    light2->draw();
    light3->draw();
	//Light0 
	if(_light0 == 1)
		light0->enable();
	else
		light0->disable();
	//Light1
	if(_light1 == 1)
		light1->enable();
	else
		light1->disable();
	//Light2
	if(_light2 == 1)
		light2->enable();
	else
		light2->disable();
	//Light3
	if(_light3 == 1)
		light3->enable();
	else
		light3->disable();
	
		glPushMatrix();
			if (_textselect == 1)
				Robot1Appearance->apply();
			if (_textselect == 2)
				Robot2Appearance->apply();
			if (_textselect == 3)
				Robot3Appearance->apply();
			robot->draw();
		glPopMatrix();

	if(_radiobutton)
		robot->setTypeofTexture(true);
	else
		robot->setTypeofTexture(false);

	
	// Draw axis
	axis.draw();

	// ---- END Background, camera and axis setup

	// ---- BEGIN Primitive drawing section
    
	//Column1
	glPushMatrix();
		Cylinder *cyl = new Cylinder(20, 8, true);
		glScaled(1,5,1);
		glTranslated(3.0f, 0.5f, 2.0f);
		glRotated(90,1,0,0);
		cyl->draw();
	glPopMatrix();
    
	//Column2
    glPushMatrix();
		//glScalef(5, 1, 5);
		Cylinder *cyl2 = new Cylinder(20, 8, false);
		glScaled(1,5,1);
		glTranslated(7.0f, 0.5f, 2.0f);
		glRotated(90,1,0,0);
		cyl2->draw();
	glPopMatrix();
    
    /* First Chair
    
    glPushMatrix();
    glTranslated(5, 0, 4);
    chair->draw();
    glPopMatrix();*/
    
    /* Second Chair
    
    glPushMatrix();
    glTranslated(14, 0, 6);
    chair->draw();
    glPopMatrix();*/
    
    //First Table
    
    glPushMatrix();
    glTranslated(5,0,8);
    table->draw();
	glPopMatrix();
    
	/*Second Table
	glPushMatrix();
    glTranslated(12,0,8);
    table->draw();
	glPopMatrix();
    
    materialFW->apply();*/

	//Floor
	glPushMatrix();
		glTranslated(7.5,0,7.5);
		glScaled(15,0.2,15);
		floorAppearance->setTextureWrap(GL_REPEAT, GL_REPEAT);
		floorAppearance->apply();
		wall->draw(12.0f, 10.0f,0);
	glPopMatrix();

	//Impostor
	glPushMatrix();
		glTranslated(0,4,7.5);
		glRotated(-90.0,0,0,1);
		glScaled(8,0.2,15);
		windowAppearance->apply();
		impostor->draw();
	glPopMatrix();
    
    /*glPushMatrix();
    
    glTranslated(0.2, 4, 7.5);
    glRotated(-90.0,0,0,1);
    glScaled(4, 0.1, 7.5);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    windowAppearance->apply();
    wall->draw(1.0f, 1.0f,0);
    
    glPopMatrix();*/
	

	//BackGround
	glPushMatrix();
		glTranslated(-50, 4, 7.5);
		glRotated(-90.0, 0, 0, 1);
		glScaled(75, 0.2, 100);
		backgroundAppearance->apply();
		wall->drawWindow();
	glPopMatrix();

	//Right Wall
	glPushMatrix();
		glTranslated(7.5,4,0);
		glRotated(90.0,1,0,0);
		glScaled(15,0.2,8);
		materialFW->apply();
		wall->draw(2.0f, 2.0f,0);
	glPopMatrix();


	//Board A
	glPushMatrix();
		glTranslated(4,4,0.2);
		glScaled(BOARD_WIDTH,BOARD_HEIGHT,1);
		glRotated(90.0,1,0,0);
		materialA->apply();
		boardA->draw(1, 1,0);
	glPopMatrix();
	
	//Board B
	glPushMatrix();
		glTranslated(10.5,4,0.2);
		glScaled(BOARD_WIDTH,BOARD_HEIGHT,1);
		glRotated(90.0,1,0,0);
		materialB->apply();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		boardB->draw(1, 1.3f, -0.12f);
	glPopMatrix();
		
	//  Clock Hand
	glPushMatrix();
		glTranslated(7.3,7.5,0.175);
		glRotated(-90,0,1,0);
		clock->draw();
	glPopMatrix();




	// ---- END Primitive drawing section
	

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}

void LightingScene::update(unsigned long ms) {
	if (!_last_time_ms)
		_last_time_ms = ms;

	long elapsed = ms - _last_time_ms;

	_last_time_ms = ms;

	clock->update(elapsed);
	//std::cout << "Tempo: " << elapsed << ", " << ms << std::endl;
    
}

void LightingScene::toggleSomething(){
}
LightingScene::~LightingScene() 
{
	delete(light0);
	delete(light1);
	delete(light2);
	delete(light3);

	delete(table);
	delete(chair);
	delete(wall);
	delete(boardA);
	delete(boardB);
	delete(clock);
	delete(robot);
	delete(impostor);
	delete(materialA);
	delete(materialB);
	delete(materialFW);
	delete(tableAppearance);
	delete(windowAppearance);
	delete(floorAppearance);
	delete(backgroundAppearance);
	delete(Robot1Appearance);
	delete(Robot2Appearance);
	delete(Robot3Appearance);

}

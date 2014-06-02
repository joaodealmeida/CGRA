#include "Chair.h"

#include "Cube.h"

#include <time.h>
#include <stdlib.h>

#define RGB(r,g,b) {r / 255.0f, g / 255.0f, b / 255.0f}

//  Coefficients for table top
float ambC[3] = RGB(68.0f, 111.0f, 222.0f);
float difC[3] = RGB(68.0f, 111.0f, 222.0f);
float specC[3] = RGB(68.0f, 111.0f, 222.0f);
float shininessC = 40.f;

Chair::Chair() {    
    angle = rand()%40 - 20;
    
    material = new CGFappearance(ambC, difC, specC, shininessC);
}

void Chair::draw() {
    Cube cube;
    
    material->apply();
    
    glPushMatrix();
    
    glRotated(angle, 0, 1, 0);
    
    //  Top-Left Leg
    
    glPushMatrix();
    
    glScaled(0.3, 2, 0.3);
    
    cube.draw();
    
    glPopMatrix();
    
    //  Top-Right Leg
    
    glPushMatrix();
    
    glTranslated(2 - 0.3, 0, 0);
    
    glScaled(0.3, 2, 0.3);
    
    cube.draw();
    
    glPopMatrix();
    
    //  Bottom-Right Leg
    
    glPushMatrix();
    
    glTranslated(2 - 0.3, 0, 1.7f);
    
    glScaled(0.3, 2, 0.3);
    
    cube.draw();
    
    glPopMatrix();
    
    //  Bottom-Left Leg
    
    glPushMatrix();
    
    glTranslated(0, 0, 1.7f);
    
    glScaled(0.3, 2, 0.3);
    
    cube.draw();
    
    glPopMatrix();
    
    //  Chair Sit Down
    
    glPushMatrix();
    
    glTranslated(0, 2, 0);
    
    glScaled(2, 0.3, 2);
    
    cube.draw();
    
    glPopMatrix();
    
    //  Chair Encosto
    
    glPushMatrix();
    
    glTranslated(0, 4 + 0.3f, 0);
    
    glRotated(90, 1, 0, 0);
    
    glScaled(2, 0.3, 2);
    
    cube.draw();
    
    glPopMatrix();
    
    glPopMatrix();
}
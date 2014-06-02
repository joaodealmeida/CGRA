#include "Table.h"

#include "Cube.h"

#include "CGFappearance.h"

#include <time.h>
#include <stdlib.h>

#define RGB(r,g,b) {r / 255.0f, g / 255.0f, b / 255.0f}

//  Coefficients for table top
float ambT[3] = RGB(102.0f, 51.0f, 0.0f);
float difT[3] = RGB(102.0f, 51.0f, 0.0f);
float specT[3] = RGB(0.01f, 0.01f, 0.01f);
float shininessT = 10.f;

//  Coefficients for table legs
float ambL[3] = RGB(25.0f, 17.5f, 25.0f);
float difL[3] = RGB(224.0f, 223.0f, 219.0f);
float specL[3] = RGB(255.0f, 255.0f, 255.0f);
float shininessL = 20.f;

Table::Table() {
    angle = rand()%30 - 20;
    
    materialT = new CGFappearance(ambT, difT, specT, shininessT);
    materialL = new CGFappearance(ambL, difL, specL, shininessL);
    
    tableAppearance = new CGFappearance(ambT, difT, specT, shininessT);
    tableAppearance->setTexture("table.png");
}

void Table::draw() {
    Cube cube;
    
    glPushMatrix();
    
    materialL->apply();
    
    glRotated(angle, 0, 1, 0);
    
    //  Top-Left Leg
    
    glPushMatrix();
    
    glScaled(0.3, 3.5, 0.3);
    
    cube.draw();
    
    glPopMatrix();
    
    //  Top-Right Leg
    
    glPushMatrix();
    
    glTranslated(5 - 0.3, 0, 0);
    
    glScaled(0.3, 3.5, 0.3);
    
    cube.draw();
    
    glPopMatrix();
    
    //  Bottom-Right Leg
    
    glPushMatrix();
    
    glTranslated(5 - 0.3, 0, 2.7f);
    
    glScaled(0.3, 3.5, 0.3);
    
    cube.draw();
    
    glPopMatrix();
    
    //  Bottom-Left Leg
    
    glPushMatrix();
    
    glTranslated(0, 0, 2.7f);
    
    glScaled(0.3, 3.5, 0.3);
    
    cube.draw();
    
    glPopMatrix();
    
    //  Table Head
    
    glPushMatrix();
    
    glTranslated(0, 3.5, 0);
    
    glScaled(5, 0.3, 3);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    tableAppearance -> apply();
    
    cube.draw();
    
    glPopMatrix();
    
    glPopMatrix();
}
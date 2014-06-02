#include "Cube.h"

void Cube::drawRect() {
    glNormal3f(0, 0, 1);
    
    glBegin(GL_QUADS);
    
    glTexCoord2d(0,0);
    glVertex2d(0, 0);
    
    glTexCoord2d(1, 0);
    glVertex2d(1, 0);
    
    glTexCoord2d(1, 1);
    glVertex2d(1, 1);
    
    glTexCoord2d(0, 1);
    glVertex2d(0, 1);
    
    glEnd();
}

void Cube::draw() {
    glPushMatrix();
    
    glPushMatrix();
    
    glTranslated(0, 0, 1);
    
    drawRect();
    
    glPopMatrix();
    
    glPushMatrix();
    
    glRotated(180, 1, 0, 0);
    
    glTranslated(0, -1, 0);
    
    drawRect();
    
    glPopMatrix();
    
    glPushMatrix();
    
    glRotated(90, 1, 0, 0);
    
    drawRect();
    
    glPopMatrix();
    
    glPushMatrix();
    
    glRotated(90 + 180, 1, 0, 0);
    
    glTranslated(0, -1, 1);
    
    drawRect();
    
    glPopMatrix();
    
    glPushMatrix();
    
    glRotated(90 + 180, 0, 1, 0);
    
    drawRect();
    
    glPopMatrix();
    
    glPushMatrix();
    
    glRotated(90, 0, 1, 0);
    
    glTranslated(-1, 0, 1);
    
    drawRect();
    
    glPopMatrix();
    
    glPopMatrix();
}

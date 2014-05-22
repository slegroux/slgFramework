#include "slgGFX.h"

slgGFX::slgGFX(){

}

slgGFX::~slgGFX(){

}

void slgGFX::drawAxis()
{
    // save the current transformation
    glPushMatrix();

        glBegin( GL_LINES );

            // x axis - red
            glColor4f( 1, 0, 0, 1 );
            glVertex3f( 0, 0, 0 );
            glVertex3f( 1, 0, 0 );

            // y axis - green
            glColor4f( 0, 1, 0, 1 );
            glVertex3f( 0, 0, 0 );
            glVertex3f( 0, 1, 0 );

            // z axis - blue
            glColor4f( 0, 0, 1, 1 );
            glVertex3f( 0, 0, 0 );
            glVertex3f( 0, 0, 1 );

        glEnd();

    // restore state
    glPopMatrix();   
}

void slgGFX::drawSnowMan() {
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
    glTranslatef(0.0f ,0.75f, 0.0f);
    glutSolidSphere(0.75f,20,20);

// Draw Head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f,20,20);

// Draw Eyes
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f,10,10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f,10,10);
    glPopMatrix();

// Draw Nose
    glColor3f(1.0f, 0.5f , 0.5f);
    glRotatef(0.0f,1.0f, 0.0f, 0.0f);
    glutSolidCone(0.08f,0.5f,10,2);
    glPopMatrix();
}

// Draw Ground
void slgGFX::drawGround(){
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();
    glPopMatrix();
}
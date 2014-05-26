/*
 *  test.cpp
 *
 *  Created by Sylvain Le Groux 
 *  slegroux@stanford.edu
 *  Copyright 2013. All rights reserved.
 *
 */
 
#include <iostream>
#include <string>
#include <math.h>


#include "slgGL.h"
#include "slgGFX.h"

using namespace std;

void displayFunc( );
void idleFunc();
void keyboardFunc(unsigned char, int, int);
void setup();
void mouseFunc(int button, int state, int x, int y);
void motionFunc(int x, int y);
void specialFunc(int key, int x, int y);

int g_eyeX = 400, g_eyeY = 300, g_eyeZ = 500;
int g_centerX = 400, g_centerY = 300, g_centerZ = 0;
float rtri = 0.0;
float theta = 0.0;
float rotX,rotY,rotZ;
float trZ;

//-----------------------------------------------
// name: main
// desc: entry point
//-----------------------------------------------
int main ( int argc, char *argv[] )
{    
    // declare OpenGL context//
    slgGL myGL;

    // SETUP OPENGL WINDOW
    myGL.initWindow(800,600, 100,100," Open GL/GLU boiler plate");
    
    // background, draw, light, etc //
    myGL.initGraphics( );
    myGL.setup(*setup);

    // reshape
    myGL.reshapeFunc();

    // UPDATE
    myGL.idleFunc(*idleFunc);

    //DRAW
    myGL.displayFunc(*displayFunc);

    //KEY PRESSED
    myGL.keyboardFunc(*keyboardFunc);
    
    //KEY RELEASED

    // MOUSE 
    myGL.mouseFunc(*mouseFunc);
    myGL.motionFunc(*motionFunc);
    myGL.specialFunc(*specialFunc);
    // SEED RANDOM GENERATOR
    srand(time(NULL));

    // Let GLUT handle the current thread from here
    myGL.glutLoop();
    
    return 0;
}

// SETUP STUFF
void setup(){
    // Look from
    g_eyeX = g_requestedWidth/2.0;
    g_eyeY = g_requestedHeight/2.0;
    g_eyeZ = 50;
    // look to
    g_centerX = g_requestedWidth/2.0;
    g_centerY = g_requestedHeight/2.0;
    g_centerZ = 0;
    glClearColor(0.9,0.9,0.9,0.9);
}

// UPDATE
void idleFunc( )
{
    rtri += 0.2;
    /*rotX += 0.1;
    rotY += 0.1;
    rotY += 0.1;*/
    theta +=0.001;
    // render the scene
    glutPostRedisplay( );
}

//DRAW
void displayFunc(){
    
    // setup screen 
    slgGL::setupScreen();

    slgGFX myGFX;

    float radius = 100;
    float viewAngle = 20;

    glTranslatef(g_requestedWidth/2,g_requestedHeight/2,0);
    
    //gluLookAt(radius*(sin(theta)),radius*(sin(viewAngle*M_PI/180)),radius*(cos(viewAngle*M_PI/180)),0,0,0,0,1,0);

    glRotatef(rotX,1.0,0.0,0.0);
    glRotatef(rotY,0.0,1.0,0.0);
    glRotatef(rotZ,0.0,0.0,1.0);
    glTranslatef(0,0,trZ);

    // draw axis
    myGFX.drawAxis(100);
    // draw stuff
    //glColor4f(0.9,0.9,0.9,0.9);
    //glutSolidSphere(50, 30, 30);
    glPushMatrix();
    glColor4f(0.9,0.9,0.9,0.7);
    myGFX.drawGround(500.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-400);
    //myGFX.drawSnowMan();
    glutSolidCube(100);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,100,0);
    glRotatef(rtri,0,1,0);
    glTranslatef(0,-50,0);
    glColor4f(0.4,0.4,0.4,0.7);
    glTranslatef(100,0,0);
    glutSolidSphere(50,30,30);
    glTranslatef(-200,0,0);
    glutSolidSphere(50,30,30);
    glTranslatef(100,100,0);
    glutSolidSphere(50,30,30);
    glPopMatrix();
    
    /*glTranslatef(20,20,0);
    glPushMatrix();
    glColor4f(0.6,0,0,0.9);
    glRotatef(rtri,0,0,1);
    glBegin(GL_TRIANGLES);
    glVertex3f(-100,0.0f, 0.0f);
    glVertex3f( 100.0f, 0.0f, 0.0);
    glVertex3f( 0.0f, 100.0f, 0.0);
    glEnd();
    glPopMatrix();*/

    // flush!
    glFlush( );
    // swap the double buffer
    glutSwapBuffers( );
     
}

void keyboardFunc( unsigned char key, int x, int y )
{
    switch( key ){
        case 27:
        exit(0);
        break;
        case 'w':
        trZ += 10;
        break;
        case 's':
        trZ -= 10;
        break;
    }
}


void specialFunc(int key, int x, int y){
    float fraction = 0.1;

    switch(key)
    {
    case GLUT_KEY_LEFT : // Rotate on x axis
    rotY -= 0.5f;
    break;
    case GLUT_KEY_RIGHT : // Rotate on x axis (opposite)
    rotY += 0.5f;
    break;
    case GLUT_KEY_UP : // Rotate on y axis 
    rotX += 0.5f;
    break;
    case GLUT_KEY_DOWN : // Rotate on y axis (opposite)
    rotX -= 0.5f;
    break; 
    // fn arrow
    case GLUT_KEY_PAGE_UP: // Rotate on z axis
    rotZ -= 0.5f;
    break;
    case GLUT_KEY_PAGE_DOWN:// Rotate on z axis (opposite)
    rotZ += 0.5f;
    break;
    }

}

void mouseFunc(int button, int state, int x, int y){

    if( state == GLUT_DOWN )
        cout<<"down"<<endl;
    else if ( state == GLUT_UP)
        cout<<"up"<<endl;

    cout<<"x: "<<x<<" y: "<<y<<" button: "<<button<<endl;


//    glutPostRedisplay( );

}

void motionFunc(int x, int y){

    cout<<"x: "<<x<<" y: "<<y<<endl;
    g_eyeX = g_requestedWidth/2. -x;
    g_eyeY = g_requestedHeight/2. -y;
}

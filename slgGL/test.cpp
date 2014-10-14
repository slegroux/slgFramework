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

// rotations and translations
float rtri = 0.0;
float theta = 0.0;
float rotX,rotY,rotZ;
float trZ;
float rotCube = 0.0;

// 
struct point {
        GLfloat x;
        GLfloat y;
    };
point graph;
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

    GLfloat g_light0_pos[4] = { 2.0f, 8.2f, 4.0f, 1.0f };
    myGL.initLight0(g_light0_pos,4);

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
    /*// Look from
    g_eyeX = g_requestedWidth/2.0;
    g_eyeY = g_requestedHeight/2.0;
    g_eyeZ = 50;
    // look to
    g_centerX = g_requestedWidth/2.0;
    g_centerY = g_requestedHeight/2.0;
    g_centerZ = 0;
    glClearColor(0.9,0.9,0.9,0.9);*/
    
    point graph[2000];
 
    for(int i = 0; i < 2000; i++) {
        float x = (i - 1000.0) / 100.0;
        graph[i].x = x;
        graph[i].y = sin(x * 10.0) / (1.0 + x * x);
    }
}

// UPDATE
void idleFunc( )
{
    rtri += 0.05;
    theta += 0.001;
    rotCube += 0.1;
    // render the scene
    glutPostRedisplay( );
}

//DRAW
void displayFunc(){
    //clear screen and depth buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity(); //reset current model view matrix
    
    // setup screen 
    slgGL::setupScreen();
 
    // init view
    glTranslatef(g_requestedWidth/2,g_requestedHeight/2,0);
    gluLookAt(0,0.1,0.5,0,0,0,0,1,0);

    // lighting
    GLfloat g_light0_pos[] = { 400,600, 500, 1.0f };
    glLightfv( GL_LIGHT0, GL_POSITION, g_light0_pos );
    
    // graphics objects
    slgGFX myGFX;

    float radius = 100;
    float viewAngle = 20;
    

    // control rotation and translation from keyboard inputs
    glRotatef(rotX,1.0,0.0,0.0);
    glRotatef(rotY,0.0,1.0,0.0);
    glRotatef(rotZ,0.0,0.0,1.0);
    glTranslatef(0,0,trZ);

    // draw axis
    glPushMatrix();
    myGFX.drawAxis(100);
    glPopMatrix();
    /*glBegin( GL_LINES );
    // x axis - red
    glColor4f( 0, 0, 0, 1 );
    glVertex3f( 0, 0, 0 );
    glVertex3f( 0, 0, -1 );
    glEnd();*/


    // draw grid
    //myGFX.drawGrid(10, 10, 10, 10);

    // draw rotating cube
    glPushMatrix();
    glTranslatef(0, 100,0);
    glRotatef(rotCube,0,1,0);
    glRotatef(rotCube,1,1,1);
    glutWireCube(50);
    glPopMatrix();

    
    // ground
    glPushMatrix();
    glColor4f(0.9,0.9,0.9,1);
    myGFX.drawGround(500.0);
    glPopMatrix();

    
    // cubes
    glPushMatrix();
    glTranslatef(200,50,-200);
    glutSolidCube(100);
    glTranslatef(-400,0,0);
    glutSolidCube(100);
    glPopMatrix();

    // cones
    glPushMatrix();
    //glTranslatef(0,0,100);
    glRotatef(-90,1,0,0);
    glutSolidCone(20,100,30,30);
    glPopMatrix();
    
    // Spheres
    glPushMatrix();
    glRotatef(rtri,0,1,0);
    glTranslatef(0,100,0);
    glTranslatef(100,0,0);
    glutSolidSphere(10,30,30);
    glBegin(GL_LINES);
    glVertex3f( 0, 0, 0 );
    glVertex3f( -200, 0, 0 );
    glEnd();
    glTranslatef(-200,0,0);
    glutSolidSphere(10,30,30);
    glPopMatrix();

    //
    glTranslatef(-100,0,-100);
    myGFX.drawSnowMan(30);

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

    glutPostRedisplay( );
}


void specialFunc(int key, int x, int y){
    float fraction = 1.0;

    switch(key)
    {
    case GLUT_KEY_LEFT : // Rotate on x axis
    rotY -= fraction;
    break;
    case GLUT_KEY_RIGHT : // Rotate on x axis (opposite)
    rotY += fraction;
    break;
    case GLUT_KEY_UP : // Rotate on y axis 
    rotX += fraction;
    break;
    case GLUT_KEY_DOWN : // Rotate on y axis (opposite)
    rotX -= fraction;
    break; 
    // fn arrow
    case GLUT_KEY_PAGE_UP: // Rotate on z axis
    rotZ -= fraction;
    break;
    case GLUT_KEY_PAGE_DOWN:// Rotate on z axis (opposite)
    rotZ += fraction;
    break;
    }

    glutPostRedisplay( );

}

void mouseFunc(int button, int state, int x, int y){

    if( state == GLUT_DOWN )
        cout<<"down"<<endl;
    else if ( state == GLUT_UP)
        cout<<"up"<<endl;

    cout<<"x: "<<x<<" y: "<<y<<" button: "<<button<<endl;


    glutPostRedisplay( );

}

void motionFunc(int x, int y){

    cout<<"x: "<<x<<" y: "<<y<<endl;
    g_eyeX = g_requestedWidth/2. -x;
    g_eyeY = g_requestedHeight/2. -y;
    glutPostRedisplay( );
}

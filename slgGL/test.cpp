#include <iostream>
#include <string>
#include <math.h>

#include "slgGL.h"
#include "slgGFX.h"

using namespace std;

void displayFunc( );
void my_func();

float g_angle = 0.0;
pt3d g_from( 0.0, 0.0, 10.0);
pt3d g_to( 0.0, 0.0, 0.0 );
pt3d g_up( 0.0, 1.0, 0.0 );

//-----------------------------------------------
// name: main
// desc: entry point
//-----------------------------------------------
int main ( int argc, char *argv[] )
{    
    // INIT //


    slgGL myGL;

    // OPENGL //
    
    myGL.initWindow(argc, argv, 800,600, 100,100);
    myGL.initGraphics( );
    myGL.initUi();
    
    //display
    myGL.displayFunc(*displayFunc);
    
    // let GLUT handle the current thread from here
    myGL.glutLoop();
    
    
    return 0;
}

void my_func(){
    cout<<"toto"<<endl;
}

void displayFunc(){
    slgGFX myGFX;

    // white background
    glClearColor(1,1,1,1);
    // clear the color and depth buffers
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    gluLookAt(  0,0, 10,0.0f, 0.0f,  0.0f,0.0f, 1.0f,  0.0f);

    glRotatef(g_angle, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
    myGFX.drawAxis();
    myGFX.drawSnowMan();
    glColor3f(0,0,0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.0f,-2.0f, 0.0f);
    glVertex3f( 2.0f, 0.0f, 0.0);
    glVertex3f( 0.0f, 2.0f, 0.0);
    glEnd();
    glPopMatrix();

    g_angle+=0.1f;

    // flush!
    glFlush( );
    // swap the double buffer
    glutSwapBuffers( );
     
}
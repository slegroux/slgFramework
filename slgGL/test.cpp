#include <iostream>
#include <string>
#include <math.h>

#include "slgGL.h"

using namespace std;

void displayFunc( );
void my_func();

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

    static int count;
    // white background
    glClearColor(1,1,1,1);
    // clear the color and depth buffers
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    
    glPushMatrix();

    //count = count+1;
    glTranslatef(0,0, -5);
    
    /*glBegin(GL_QUADS);
    glColor3ub(255, 0, 0); 
    glVertex2f(0, 3);
    glVertex2f(6, 3);
    glColor3ub(255, 255, 0);
    glVertex2f(6, 0);
    glVertex2f(0, 0);
    glEnd();

    glPopMatrix();*/
    glColor3f(0,0,0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.6f, -0.5f);
    glVertex2f(0.1f, 0.8f);
    glVertex2f(0.9f, -0.1f);
    glEnd();

    glPopMatrix();

    // flush!
    glFlush( );
    // swap the double buffer
    glutSwapBuffers( );
     
}
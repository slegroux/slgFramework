#include <iostream>
#include <string>
#include <math.h>

#include "slgGL.h"

using namespace std;

void displayFunc( );

//-----------------------------------------------
// name: main
// desc: entry point
//-----------------------------------------------
int main ( int argc, char *argv[] )
{    
    // INIT //


    slgGL g_myGL;
    // OPENGL //
    g_myGL.initWindow(argc, argv);
    g_myGL.initGraphics( );
    g_myGL.initUi();
    //display
    glutDisplayFunc( displayFunc );

    // let GLUT handle the current thread from here
    glutMainLoop();
    
    return 0;
}

void displayFunc( ){
    glClearColor(1,1,1,1);
    // clear the color and depth buffers
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // line width
    glLineWidth( 2.0 );
    glColor3f(0.,0.,0.);

    glPushMatrix();
        //drawAxis();
        //glColor3f(0,0,0);
        //drawString(0,0,0,"Hola!",1);
        //line(0,0,1,1);
        //cout<<"x: "<<glutGet(GLUT_WINDOW_X);
        //cout<<"width: "<<glutGet(GLUT_SCREEN_WIDTH);

        //glColor4f(0.5,0.5,0.5,0.2);
        //rect(0,0,0.1,0.5);
        //glScalef(0.5,0.5,1);
        //renderPulse();
        
    glPopMatrix();
    //rotate(0.01,1,0,1);

    // flush!
    glFlush( );
    // swap the double buffer
    glutSwapBuffers( );
     
}
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
    //myGL.initGraphics( );
    myGL.setup(*setup);

    // reshape
    //myGL.reshapeFunc();

    // UPDATE
    myGL.idleFunc(*idleFunc);

    //DRAW
    myGL.displayFunc(*displayFunc);

    //KEY PRESSED
    myGL.keyboardFunc(*keyboardFunc);
    
    //KEY RELEASED

    // SEED RANDOM GENERATOR
    srand(time(NULL));

    // Let GLUT handle the current thread from here
    myGL.glutLoop();
    
    return 0;
}

// SETUP STUFF
void setup(){
    cout<<"Setup "<<endl;
}

// UPDATE
void idleFunc( )
{
    // render the scene
    glutPostRedisplay( );
}

//DRAW
void displayFunc(){
    
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);    
    // setup screen 
    slgGL::setupScreen();
    slgGFX myGFX;


    //myGFX.drawSnowMan();
    glTranslatef(400,300,0);
    //myGFX.drawGround();
    glColor3f(1,0,0);
    //myGFX.drawAxis();
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glVertex3f(-100,0.0f, 0.0f);
    glVertex3f( 100.0f, 0.0f, 0.0);
    glVertex3f( 0.0f, 100.0f, 0.0);
    glEnd();
    glPopMatrix();

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
    }
}

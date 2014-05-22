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
    cout<<"sdfasdfasdf "<<endl;
}

// UPDATE
void idleFunc( )
{
    // render the scene
    glutPostRedisplay( );
}

//DRAW
void displayFunc(){
    

    // SETUP SCREEN
    int w, h;

    w = glutGet(GLUT_WINDOW_WIDTH);
    h = glutGet(GLUT_WINDOW_HEIGHT);

    glViewport( 0, 0, w, h);

    // black background
    glClearColor(0,0,0,1);
    // clear the color and depth buffers of screen
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // define field of vision (http://www.eng.utah.edu/~cs5600/slides/Wk%205%20Lec09%20perspective%20II.pdf)
    float halfFov, theTan, screenFov, aspect;
    screenFov       = 60.0f;

    float eyeX      = (float)w / 2.0;
    float eyeY      = (float)h / 2.0;
    halfFov         = M_PI * screenFov / 360.0;
    theTan          = tanf(halfFov);
    float dist      = eyeY / theTan;
    float nearDist  = dist / 10.0;  // near / far clip plane
    float farDist   = dist * 10.0;
    aspect          = (float)w/(float)h;

    // SET UP PROJECTION
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(screenFov, aspect, nearDist, farDist);

    // SETUP CAMERA VIEW
    gluLookAt(eyeX, eyeY, dist, eyeX, eyeY, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(1, -1, 1);           // invert Y axis so increasing Y goes down.
    glTranslatef(0, -h, 0);       // shift origin up to upper-left corner.
    
    slgGFX myGFX;
    //glPushMatrix();
    //glColor3f(0,0,0);
    //myGFX.drawAxis();
    
    //myGFX.drawSnowMan();
    glTranslatef(400,300,0);
    myGFX.drawGround();
    glColor3f(1,0,0);
    myGFX.drawAxis();
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glVertex3f(-20,0.0f, 0.0f);
    glVertex3f( 20.0f, 0.0f, 0.0);
    glVertex3f( 0.0f, 20.0f, 0.0);
    glEnd();
    glPopMatrix();

    //slgGL::_angle+=0.05f;

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

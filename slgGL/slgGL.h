#ifndef __SLGGL_H__
#define __SLGGL_H__

#ifdef __MACOSX_CORE__
  #include <GLUT/glut.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
  #include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <cstdlib>
#include <time.h>

#define INC_VAL 1.0f
#define TRUE 1
#define FALSE 0

using namespace std;


struct pt3d
{
    pt3d( GLfloat x, GLfloat y, GLfloat z ) : x(x), y(y), z(z) {};
    float x;
    float y;
    float z;
};

class slgGL{

public:
    slgGL();
    ~slgGL();

public:
	// probably better to just have those as plain helper functions outside a class
	// just wanted to try this as a practice exercise
	static void changeLookAt( pt3d look_from, pt3d look_to, pt3d head_up );
	static void idleFunc( );
	static void displayFunc( void(*myFunc)());
	static void reshapeFunc( int width, int height );
	static void keyboardFunc( unsigned char, int, int );
	static void mouseFunc( int button, int state, int x, int y );
	static void glutLoop();
	void initGraphics( );
	void initWindow(int argc, char *argv[],int width=800, int height=600, int x=100,int y=100);
	void initUi();
	

private:
    
	// light 0 position
	static GLfloat g_light0_pos[4];// = { 2.0f, 1.2f, 4.0f, 1.0f };

	// light 1 parameters
	GLfloat g_light1_ambient[4];// = { .2f, .2f, .2f, 1.0f };
	GLfloat g_light1_diffuse[4];// = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat g_light1_specular[4];// = { 1.0f, 1.0f, 1.0f, 1.0f };
	static GLfloat g_light1_pos[4];// = { -2.0f, 0.0f, -4.0f, 1.0f };

	// modelview stuff
	GLfloat g_angle_y;// = 0.0f;
	static GLfloat g_inc;// = 0.0f;
	static GLfloat g_eye_y;// = 0;

	// WINDOW
	static GLsizei g_width;// = 800; 
	static GLsizei g_height;// = 600;

	// fullscreen
	static GLboolean g_fullscreen;// = FALSE;

	static float g_z;// = 0.0f;
	static float g_space;// = .15f;

	static float g_factor;// = 1.0f;
	static int g_phase_fix;// = TRUE;
	static float g_factor2;// = 1.0f;
	static int g_freeze;// = 0;

	static pt3d g_look_from;//( 0, 0, 1);
	static pt3d g_look_to;//( 0, 0, 0 );
	static pt3d g_head_up;//( 0, 1, 0 );*/

	
};

#endif
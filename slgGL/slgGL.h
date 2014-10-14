/*
 *  slgGL.h
 *
 *  Created by Sylvain Le Groux 
 *  slegroux@stanford.edu
 *  Copyright 2013. All rights reserved.
 *
 */
 
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
// window size
extern int g_requestedWidth;
extern int g_requestedHeight;
// light 0 position
extern GLfloat g_light0_pos[4];
// light 1 parameters
extern GLfloat g_light1_ambient[4];
extern GLfloat g_light1_diffuse[4];
extern GLfloat g_light1_specular[4];
extern GLfloat g_light1_pos[4];

struct pt3d
{
	// structure constructor with default values x,y,z
    pt3d( GLfloat x, GLfloat y, GLfloat z ) : x(x), y(y), z(z) {};
    void print(){cout<<"x: "<<x<<" y: "<<y<<" z: "<<z<<endl;};
    float x;
    float y;
    float z;
};

class slgGL{

public:
    slgGL();
    ~slgGL();

public:
	// GLUT callbacks need a static function
	static void changeLookAt( pt3d look_from, pt3d look_to, pt3d head_up );
	static void idleFunc(void(*myFunc)());
	static void displayFunc( void(*myFunc)());
	static void reshapeFunc();
	//static void keyboardFunc( unsigned char, int, int );
	static void keyboardFunc(void(*myFunc)(unsigned char, int, int));
	static void specialFunc(void(*myFunc)(int key, int x, int y));
	static void mouseFunc( void(*myFunc)(int button, int state, int x, int y ));
	static void motionFunc(void (*myMotionFunc)(int x, int y));
	static void setup(void(*mySetupFunc)());
	static void setupScreen();
	void glutLoop();
	void initGraphics( );
	void initLight0(GLfloat ligth0_pos[],int size);
	void initWindow(int width=800, int height=600, int x=100,int y=100, string title="slg window");

	static void printCoordinates();	

private:
	// core of reshape func callback
	static void myReshapeFunc( int w =800, int h=600 );

    
	// modelview stuff
	//GLfloat g_angle_y;// = 0.0f;
	static GLfloat g_inc;// = 0.0f;
	//static GLfloat g_eye_y;// = 0;

	// fullscreen
	static GLboolean g_fullscreen;// = FALSE;
	
	static pt3d g_look_from;//( 0, 0, 1);
	static pt3d g_look_to;//( 0, 0, 0 );
	static pt3d g_head_up;//( 0, 1, 0 );

	
};

#endif
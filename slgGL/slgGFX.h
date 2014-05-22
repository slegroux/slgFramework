#ifndef __SLGGFX_H__
#define __SLGGFX_H__

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

class slgGFX{

public:
	slgGFX();
	~slgGFX();
public:
	void drawAxis();
	void drawSnowMan();
	void drawGround();
};

#endif
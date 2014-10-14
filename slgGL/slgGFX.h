/*
 *  slgGFX.h
 *
 *  Created by Sylvain Le Groux 
 *  slegroux@stanford.edu
 *  Copyright 2013. All rights reserved.
 *
 */
 
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
	void drawAxis(float size);
	void drawSnowMan(float size=1);
	void drawGround(float size = 1000.0);
	void drawGrid(int xPointCount, int yPointCount, double xSpacing, double ySpacing);
};

#endif
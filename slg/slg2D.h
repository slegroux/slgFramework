#ifndef __SLG2D_H__
#define __SLG2D_H__

#ifdef __MACOSX_CORE__
  #include <GLUT/glut.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
  #include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
#include "Definitions.h"

enum drawMode{
    kOutline= 0,
    kFilled = 1
};

extern drawMode g_drawMode ;//= kOutline;

enum rectMode{
    kCorner = 1,
    kCenter = 0
};

extern rectMode g_rectMode;// = kCenter;

void renderBitmapString(float x,float y,float z,void *font,char *string);
//template <class TBuffer> void drawBuffer(TBuffer *buffer, int size,TBuffer maxHeight,float translateY=0.0f);
template <class TBuffer> void drawBuffer(TBuffer *buffer, int size);
template <class TBuffer> void drawBuffer(TBuffer *buffer, int size, TBuffer min, TBuffer max);
void drawAxis(float size);
void drawSnowMan(float size=1);
void drawGround(float size = 1000.0);
void drawGrid(int xPointCount, int yPointCount, double xSpacing, double ySpacing);
void drawString( GLfloat x, GLfloat y, GLfloat z, const char * str, GLfloat scale);
void circle(float x,float y, float radius);
void line(float x1,float y1,float x2,float y2);
void rect(float x,float y,float w,float h);
void renderPulse();



#endif

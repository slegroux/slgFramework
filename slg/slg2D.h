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

void renderBitmapString(float x,float y,float z,void *font,char *string);
//template <class TBuffer> void drawBuffer(TBuffer *buffer, int size,TBuffer maxHeight,float translateY=0.0f);
template <class TBuffer> void drawBuffer(TBuffer *buffer, int size);
template <class TBuffer> void drawBuffer(TBuffer *buffer, int size, TBuffer min, TBuffer max); 

#endif

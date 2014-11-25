#ifndef __SLGGRAPHICS_H__
#define __SLGGRAPHICS_H__

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
#include "glm/vec3.hpp"// glm::vec3

enum drawMode{
    kOutline= 0,
    kFilled = 1,
};

enum LineMode{
    kLine,
    kStem,
    kPoints
};

extern drawMode g_drawMode ;//= kOutline;

enum rectMode{
    kCorner = 1,
    kCenter = 0
};
extern rectMode g_rectMode;// = kCenter;

//for 2D/3D overlay
void go2D();
void go3D();

//glm::vec3 GetOGLPos(int x, int y);

//2D
void BitmapString( GLfloat x, GLfloat y, GLfloat z, const char * str, GLfloat scale);
void Circle(float x,float y, float radius);
void Ellipse(float x,float y, float width, float height);
void Line(float x1,float y1,float x2,float y2);
void Rectangle(float x,float y,float w,float h);
void Triangle(float x1, float y1, float x2, float y2, float x3, float y3);
void Pulse();
void renderBitmapString(float x,float y,float z,void *font,char *string);
void GridPoints(int xPointCount, int yPointCount, double xSpacing, double ySpacing);
void Grid(const float x, const float y, const float width, const float height, const unsigned int num_rows, const unsigned int num_columns);
//template <class TBuffer> void Buffer(TBuffer *buffer, int size,TBuffer maxHeight,float translateY=0.0f);
//template <class TBuffer> void Buffer(TBuffer *buffer, const int size);
//template <class TBuffer> void Buffer(TBuffer *buffer, const int size, const TBuffer min, const TBuffer max, const LineMode line_mode = kLine);
void Buffer1D(SAMPLE *buffer, const int size, const float min, const float max, const LineMode line_mode = kLine);
void Buffer2D(SAMPLE **buffer, const int n_rows, const int n_cols, const float min, const float max);

//3D
void Axis(float size=1.0);
void SnowMan(float size=1);
void Ground(float size = 1000.0);




#endif
#ifndef __SLGGUI_H__
#define __SLGGUI_H__

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


class Slider{
public:
	Slider(int x, int y, int w, int h);
   	void Draw();
   	bool Touched();
   	void Touch(int x, int y);
   	void UnTouch();
	void SetValue(float val);
   	float Value();
   	bool Hit(int x, int y);
   
private:
	float fVal;
	bool fTouched;
};


class ToggleButton{

public:
	ToggleButton(int x, int y, int w, int h);
	void Draw();
   	void Toggle();
   	bool Toggled();
   	bool Hit(int x, int y);
   
private:
   bool fToggled;
};

#endif
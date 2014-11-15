#ifndef __SLGTOGGLEBUTTON_H__
#define __SLGTOGGLEBUTTON_H__

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
#include "slgGraphics.h"


class slgToggleButton{

public:
  slgToggleButton(const float x, const float y, const float w,const float h, void (*callbackon)(void),void (*callbackoff)(void));
  ~slgToggleButton();
	void Draw();
  void Toggle();
  bool Toggled();
  bool Hit(float x,float y);
  
  float get_x();
  float get_y();
  float get_h();
  float get_w();
  


private:
  bool _toggled;
  float _x, _y,_w,_h;
  void (*_CallbackON)();
  void (*_CallbackOFF)(); 

};

#endif
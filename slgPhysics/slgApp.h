#ifndef _SLG_APP_H
#define _SLG_APP_H

#include "slgGraphics.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <glm/glm.hpp>
#include "slgPhysics.h"
//#include "glm/ext.hpp"
#include "slgGLUT.h"


class slgApp{

public:
   void setup();
   void displayFunc();
   void reshapeFunc(int w, int h);
   void idleFunc(); //update
   void keyboardFunc(unsigned char key, int x, int y);
   void specialFunc(int key, int x, int y);
   void passiveMotionFunc(int x, int y);
   void mouseFunc(int button, int state, int x, int y);
   void cleanup();

   // frame rate and timing
   int g_frame_rate = 20; // refresh in Hz
   int g_previous_time = 0;

   //screen
   bool g_fullScreen = false;
   int g_height, g_width;

   //mouse
   glm::vec2 g_mouse;

   //Forces
   glm::vec2 g_wind;
   glm::vec2 g_gravity;
   glm::vec2 g_helium;

   //Entities
   static const int num_movers = 10;
   slgMover mover[num_movers];

};

#endif
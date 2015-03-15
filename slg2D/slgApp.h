#ifndef _SLG_APP_H
#define _SLG_APP_H

#include "slgGraphics.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <glm/glm.hpp>
#include "glm/ext.hpp"

class slgApp{

public:
   /* INIT */
   void setup();
   /* DRAW */
   void displayFunc();
   /* RESIZE */
   void reshapeFunc(int w, int h);
   //void update(int value);
   void idleFunc();
   /* KEY PRESSED */
   void keyboardFunc(unsigned char key, int x, int y);
   void specialFunc(int key, int x, int y);
   /* KEY RELEASED */
   void keyboardUpFunc(unsigned char key, int x, int y);
   void specialUpFunc(int key, int x, int y);

   void cleanup();
   int g_frame_rate = 30; // refresh interval in milliseconds
   int g_previous_time = 0;
   float g_counter;
   float g_x,g_y;
};

#endif
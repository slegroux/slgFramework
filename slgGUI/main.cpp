#include "slgGraphics.h"
#include "slgToggleButton.h"
#include "slgGen.h"
#include "realFFTW.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//to print out vectors directly
#include <glm/gtx/string_cast.hpp>

using namespace std;
 
#define N 100

// global variables
int g_refreshRateMs = 30; // refresh interval in milliseconds
slgToggleButton *g_toggle;

struct Mouse 
{
  int x;    /*  the x coordinate of the mouse cursor  */
  int y;    /*  the y coordinate of the mouse cursor  */
  int lmb;  /*  is the left button pressed?   */
  int mmb;  /*  is the middle button pressed? */
  int rmb;  /*  is the right button pressed?  */
  glm::vec3 position_gl;

  /*
   *  These two variables are a bit odd. Basically I have added these to help replicate
   *  the way that most user interface systems work. When a button press occurs, if no
   *  other button is held down then the co-ordinates of where that click occured are stored.
   *  If other buttons are pressed when another button is pressed it will not update these
   *  values. 
   *
   *  This allows us to "Set the Focus" to a specific portion of the screen. For example,
   *  in maya, clicking the Alt+LMB in a view allows you to move the mouse about and alter
   *  just that view. Essentually that viewport takes control of the mouse, therefore it is
   *  useful to know where the first click occured.... 
   */
  int xpress; /*  stores the x-coord of when the first button press occurred  */
  int ypress; /*  stores the y-coord of when the first button press occurred  */
};

/*
 *  rename the structure from "struct Mouse" to just "Mouse"
 */
typedef struct Mouse Mouse;

/*
 *  Create a global mouse structure to hold the mouse information.
 */
Mouse TheMouse = {0,0,0,0,0};

//void idleFunc();
void setupGL();
void init();
void displayFunc();
void reshapeFunc(int w, int h);
void Timer(int value);
void keyboardFunc(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);
void MouseFunc( int button, int state, int x, int y );
void CallbackToggleOn();
void CallbackToggleOff();


/* Called back when timer expired */
void Timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(g_refreshRateMs, Timer, 0); // next Timer call milliseconds later
}

void setupGL(){
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
  //lighting
  glEnable(GL_LIGHT0);
  // transparency
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void init(){
  //gToggle.Toggle();
}

void CallbackToggleOn(){
  cout<<"Callback ON called!"<<endl;
}

void CallbackToggleOff(){
  cout<<"Callback OFF called"<<endl;
}

void displayFunc() {
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  go2D();
  glColor4f(1,1,1,0.5);
  g_drawMode = kOutline;
  Circle(0,0,0.2);
  glRectf(0,0,0.1,0.1);
  //gToggle.Toggle();
  g_toggle->Draw();
  if (g_toggle->Toggled()){
    glTranslatef(0.5,0.5,0);
    glutSolidSphere(0.2,16,16);
  }

  go3D();

  glutSwapBuffers(); //equivalent to glFlush for double buffering
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

  glutInit(&argc, argv);                 // Initialize GLUT
  //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA ); // double buffer, use rgb color, enable depth buffer and alpha
  //No depth in 2D
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA ); // double buffer, use rgb color, enable depth buffer and alpha
  glutInitWindowSize(640, 480);   // Set the window's initial width & height
  glutInitWindowPosition(50, 50); // Position the window's initial top-left corner   
  glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
  setupGL();
  init();
  glutDisplayFunc(displayFunc); // Register display callback handler for window re-paint
  glutReshapeFunc(reshapeFunc); 
  glutMouseFunc(MouseFunc);
//  glutMotionFunc(MouseMotion);
//  glutPassiveMotionFunc(MousePassiveMotion);
  g_toggle = new slgToggleButton(-0.5, -0.5, 0.1,0.1, CallbackToggleOn, CallbackToggleOff);

  glutTimerFunc(0, Timer, 0);
  glutKeyboardFunc(keyboardFunc);
  //glutSpecialFunc(specialFunc);
  
  //Start the glut loop! 
  glutMainLoop();
  return 0;
}

void MouseFunc(int button,int state,int x, int y)
{
  /*
   *  has the button been pressed or released?
   */
  if (state == GLUT_DOWN) 
  {
    /*
     *  Which button was pressed?
     */
    switch(button) 
    {
    case GLUT_LEFT_BUTTON:
      printf("left button");
      //work with 2D coordinates (-1,1)
      go2D();
      //glm::vec3 mouse_position_gl_coordinates(3);
      TheMouse.position_gl = GetOGLPos(x,y);
      std::cout<<glm::to_string(TheMouse.position_gl)<<std::endl;
       
      if (g_toggle->Hit(TheMouse.position_gl[0],TheMouse.position_gl[1]))
      {
         g_toggle->Toggle();
      }
      //go back to 3D coordinates
      go3D();
      break;

    case GLUT_MIDDLE_BUTTON:
      printf("middle ");
      break;

    case GLUT_RIGHT_BUTTON:
      printf("right ");
      break;
    }
    printf("button pressed at (%d,%d)\n",x,y);
  }
  else 
  {
    /*
     *  Which button was released?
     */
    switch(button) 
    {
    case GLUT_LEFT_BUTTON:
      printf("left ");
      break;
    case GLUT_MIDDLE_BUTTON:
      printf("middle ");
      break;
    case GLUT_RIGHT_BUTTON:
      printf("right ");
      break;
    }
    printf("button released at (%d,%d)\n",x,y);
  }

  /*
   *  Force a redraw of the screen
   */
  glutPostRedisplay();
}

void reshapeFunc(int w, int h) {

   // Prevent a divide by zero, when window is too short
   // (you cant make a window of zero width).
   if(h == 0)
      h = 1;

   // aspect ratio (keep proportions when resize)
   float aspect = (float)w/(float)h;
   //float aspect = 1.0;

   // Set the viewport to be the entire window
   glViewport(0, 0, w, h);

   // Use the Projection Matrix
   glMatrixMode(GL_PROJECTION);

   // Reset Matrix
   glLoadIdentity();

   // Set clipping area's left, right, bottom, top (default -1,1,-1,1)
   if (w>h)
      gluOrtho2D(-1.0*aspect, 1.0*aspect, -1.0, 1.0);
   else
      gluOrtho2D(-1.0, 1.0, -1.0/aspect, 1.0/aspect);
   
   //gluPerspective(0.0f,(GLfloat)w/(GLfloat)h,1.0f,1000.0f); 
   // no depth in 2D
   glDisable(GL_DEPTH_TEST);
 
   // Get Back to the Modelview matrix
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

}

void keyboardFunc(unsigned char key, int x, int y) {

   switch (key) {
   case 'w':

      break;
   case 'a':

      break;
   case 's':

      break;
   case 'd':

      break;
   case 'q':

      break;
   case 'e':

      break;
   case 27:
      exit(0);
      break;
   }
}

void specialFunc(int key, int x, int y) {

   switch(key) {
      case GLUT_KEY_F1 :
            /*red = 1.0;
            green = 0.0;
            blue = 0.0;*/
            break;
      case GLUT_KEY_F2 :
            /*red = 0.0;
            green = 1.0;
            blue = 0.0; */
            break;
      case GLUT_KEY_F3 :
            /*red = 0.0;
            green = 0.0;
            blue = 1.0;*/
            break;
      case GLUT_KEY_UP:
         break;

   }
}
#include "slg2D.h"
#include "slgGen.h"
#include "realFFTW.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
 
#define N 100
// global variable
float g_angle=0.0;
float g_phase=0.0;
float g_frequency=2000.0;
int g_refreshRateMs = 30; // refresh interval in milliseconds

//float *g_array;
float g_array[N];
float g_up=0.0;


//void idleFunc();
void setup();
void displayFunc();
void reshapeFunc(int w, int h);
void Timer(int value);
void keyboardFunc(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);

/* Called back when timer expired */
void Timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(g_refreshRateMs, Timer, 0); // next Timer call milliseconds later
   g_angle = 2.0;
   g_phase-=0.05;
   g_frequency+=5;
   g_up=0;

}

void setup(){
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   /*g_array= new float[N];
   memset(g_array,0,sizeof(float)*N);*/
}

void displayFunc() {

   // 2D
   //no depth in 2D!
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
   glMatrixMode(GL_MODELVIEW); 


   //glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);         // Clear the color buffer
   glColor3f(255,255,255);

   for (int i=0;i<N;i++){
      g_array[i] = (float) -0.5+sin(2*M_PI*5*(float)i/N);
   }   

   //drawBuffer(g_array,N);
   line(0,0,1,1);
   glPushMatrix();
      glTranslatef(0.5,0.5,0);
      void drawSnowMan();
   glPopMatrix();

   drawString(0.5,0.5,0,"toto", 1);
   g_drawMode = kOutline;

   circle(0,0,1);
   glColor3f(255,0,0);
   renderPulse();
   glColor3f(0,200,0);
   rect(-0.5,0.5,0.25,0.25);
   g_drawMode = kFilled;
   drawGrid(20,10,0.1,0.1);

   // need to specicy float type to template func
   //drawBuffer(g_array,N);
   
   glutSwapBuffers(); //equivalent to glFlush for double buffering

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
   //Displacement trick for exact pixelization
   //glTranslatef(0.375, 0.375, 0);

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
 
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

   glutInit(&argc, argv);                 // Initialize GLUT
   //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA ); // double buffer, use rgb color, enable depth buffer and alpha
   //No depth in 2D
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA ); // double buffer, use rgb color, enable depth buffer and alpha
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner   
   glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
   setup();
   glutDisplayFunc(displayFunc); // Register display callback handler for window re-paint
   glutReshapeFunc(reshapeFunc); 
   //glutReshapeWindow(320,320);
   //glutIdleFunc(idleFunc); //replaced by timer
   
   //First timer call immediately
   glutTimerFunc(0, Timer, 0);
   glutKeyboardFunc(keyboardFunc);
   //glutSpecialFunc(specialFunc);
  
   //Start the glut loop! 
   glutMainLoop();           // Enter the infinitely event-processing loop
   return 0;
}
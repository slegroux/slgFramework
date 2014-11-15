#include "slgGraphics.h"
#include "slgGen.h"
#include "realFFTW.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

using namespace std;
 
#define N 100
// global variable
float g_angle=0.0;
float g_phase=0.0;
float g_frequency=2000.0;
int g_refreshRateMs = 30; // refresh interval in milliseconds

//float *g_array;
SAMPLE g_array[N];
float g_up=0.0;



const int g_size_buffer=5,g_size_spectrum=2;


//void idleFunc();
void setup();
void displayFunc();
void reshapeFunc(int w, int h);
void Timer(int value);
void keyboardFunc(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);
void cleanup();

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
   // transparency
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void cleanup(){
   //free deallocate double pointer
   /*for(int i=0;i<g_size_buffer;i++)
      delete[] g_array2D[i];
   delete[] g_array2D;*/
}

void displayFunc() {

   // 2D
   //no depth in 2D!
   glClear(GL_COLOR_BUFFER_BIT);

   //glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);         // Clear the color buffer
   glColor3f(255,255,255);

   for (int i=0;i<N;i++){
      g_array[i] = sin(2*M_PI*5*(float)i/N);
   }   
   
   /*g_drawMode = kOutline;
   Axis();
   Line(0,0,0.5,0.5);
   glColor3f(1.0,0.0,0.0);
   BitmapString(0.5,0.5,0,"toto", 1);
   glColor3f(1.0,1.0,1.0);
   Circle(0,0,1);
   //g_rectMode = kCenter; check the centered/bottom difference for rectangles
   glColor3f(0,0,1.0);
   Triangle(-0.0, -1.0, -1,1,1,1);
   glColor3f(0.0,1.0,0.0);
   g_drawMode = kFilled;
   Rectangle(-0.5,0.5,0.5,0.25);
   g_drawMode = kOutline;
   //GridPoints(0,5,0.1,0.1);
   glColor3f(1.0,1.0,1.0);
   glLineWidth(1);
   Grid(0, 0, 1,1,5,5);
   Ellipse(0,0,0.5,0.25);*/

   //glPushAttrib(GL_ALL_ATTRIB_BITS); save all current rendering attributes
   //glPushAttrib(GL_CURRENT_BIT);   /* Save current drawing color, etc */
   // draw gridaf
   glPushAttrib(GL_ENABLE_BIT|GL_CURRENT_BIT);
      glLineWidth(1);
      glLineStipple(4, 0xAAAA);
      glEnable(GL_LINE_STIPPLE);
      glColor4f(1,1,1,0.3);
      Grid(-1,-1.0,2,2,10,10);
   glPopAttrib();
   glLineWidth(5);
   
   // struct of spectrum
   struct Spectrum{
      SAMPLE pts[2];
   };
   // succession of those create spectrogram
   Spectrum *buf = new Spectrum[5];
   // assign values to specific points of spectrogram
   buf[0].pts[1] = 10;
   buf[3].pts[0] = 0;
   //delete[] buff


   SAMPLE **g_array2D;

   g_array2D = new SAMPLE*[g_size_buffer];

   for (int i = 0;i<g_size_buffer;i++){
      g_array2D[i] = new SAMPLE[g_size_spectrum];
      //memset(g_array2D[i],0,sizeof(SAMPLE)*g_size_spectrum);
   }
   
   cout<<g_array2D[0][0]<<' '<<g_array2D[0][1]<<endl;
   cout<<g_array2D[1][0]<<' '<<g_array2D[1][1]<<endl;
   cout<<g_array2D[2][0]<<' '<<g_array2D[2][1]<<endl;
   cout<<g_array2D[3][0]<<' '<<g_array2D[3][1]<<endl;
   cout<<g_array2D[4][0]<<' '<<g_array2D[4][1]<<endl;
   cout<<"-----"<<endl;

   SAMPLE my_array[g_size_buffer][g_size_spectrum];
   for (int i=0;i<g_size_buffer;i++){
      for (int j=0;j<g_size_spectrum;j++){
         my_array[i][j] = 0;
      }
   }

   /*my_array[0][0] = 1;
   my_array[0][1] = 0;
   my_array[1][0] = 1;
   my_array[1][1] = 0;
   my_array[2][0] = 1;
   my_array[2][1] = 0;
   my_array[3][0] = 1;
   my_array[3][1] = 0;
   my_array[4][0] = 1;
   my_array[4][1] = 0;*/

   g_array2D[0][0] = 1;
   g_array2D[0][1] = 1;
   g_array2D[1][0] = 0;
   g_array2D[1][1] = 1;
   g_array2D[2][0] = 0;
   g_array2D[2][1] = 1;
   g_array2D[3][0] = 1;
   g_array2D[3][1] = 0;
   g_array2D[4][0] = 0;
   g_array2D[4][1] = 0;


   // first index is time second index is frequency
   SAMPLE **rows= new SAMPLE*[g_size_buffer];
   for (int i=0;i<g_size_buffer;i++){
      rows[i] = g_array2D[i];
   }

   // nrow,ncols,height min, height max
   Buffer2D(rows,2,5,-2,2);
   //Buffer1D(g_array,N, -1.0f,1.0f);
   
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
      case 'q':
         exit(0);
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
   cleanup();
   return 0;
}
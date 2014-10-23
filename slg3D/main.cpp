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
void init();
void go2D();
void go3D();
void displayFunc();
void reshapeFunc(int w, int h);
void Timer(int value);
void keyboardFunc(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);


void go2D(){
   glClear(GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   float aspect = 1.0;
   int w = glutGet(GLUT_WINDOW_WIDTH);
   int h = glutGet(GLUT_WINDOW_HEIGHT);
   // Set clipping area's left, right, bottom, top (default -1,1,-1,1)
   if (w>h)
      gluOrtho2D(-1.0*aspect, -1.0*aspect, -1.0, 1.0);
   else
      gluOrtho2D(-1.0, 1.0, -1.0/aspect, 1.0/aspect);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void go3D(){
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   int w = glutGet(GLUT_WINDOW_WIDTH);
   int h = glutGet(GLUT_WINDOW_HEIGHT);
   gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,1.0f,1000.0f); 
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void init(){

   //init GL
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
   glEnable ( GL_CULL_FACE );
   //glCullFace(GL_FRONT_AND_BACK); 
   //glCullFace(GL_FRONT); 
   glCullFace(GL_BACK); 

   /*// set the fog attributes
   // the colour of the fog and the clear colour.
   float  fog_colour[] = {0.6f,0.58f,0.79f,0.0f};

   /// the density of the fog
   float  fog_density  = 0.03f;

   /// The fog mode, either GL_LINEAR, GL_EXP or GL_EXP2
   GLenum fog_mode     = GL_EXP;

   /// the far distance of the fog & camera
   float far_distance  = 100.0f;

   /// the near distance of the fog & camera
   float near_distance = 0.1f;

   glFogf (GL_FOG_START,  near_distance);
   glFogf (GL_FOG_END,    far_distance);
   glFogfv(GL_FOG_COLOR,  fog_colour);      
   glFogi (GL_FOG_MODE,   fog_mode);
   glFogf (GL_FOG_DENSITY,fog_density);

   // enable the fog
   glEnable(GL_FOG);*/

   // enable colors otherwise everything is grey
   glEnable(GL_COLOR_MATERIAL);
   glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
   const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
   const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
   const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
   //const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f }; 
   const GLfloat light_position[] = { 1.0f, 1.0f, 10.0f, 0.0f }; 

   const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
   const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
   const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
   const GLfloat high_shininess[] = { 100.0f }; 
   
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_NORMALIZE);
   glEnable(GL_COLOR_MATERIAL);
   
 
   glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position); 
 
   /*glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess); */

}

/* Called back when timer expired */
void Timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(g_refreshRateMs, Timer, 0); // next Timer call milliseconds later
   g_angle += 2.0;
   g_phase += 0.1;
   g_frequency += 5;
   g_up += sin(2*M_PI*1/5.*g_phase);


}

void displayFunc() {

   glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);         // Clear the color buffer

   drawAxis(1.0);

   go2D();
   glPushMatrix();
      g_drawMode = kOutline;
      glColor3f(255,0,0);
      circle(0,0,1);
   glPopMatrix();


   /*glPushMatrix();
        glTranslated(0.0,0,0);
        glRotatef(-g_angle,1,1,1);
        drawAxis(1.0);
        glColor3f(0,0,200);
        glutSolidSphere(0.5,50,50);
   glPopMatrix(); 
 
   glPushMatrix();
        glTranslated(0,0,0);
        glRotatef(-g_angle,1,0,0);
        drawAxis(1.0);
        glColor3f(0,0,100);
        glutSolidTorus(0.2, 1, 10, 50);
    glPopMatrix();*/
   glPushMatrix();
      glRotatef(30,0,1,1);
      glutSolidSphere(0.5,20,20);
   glPopMatrix();
   
   
   glutSwapBuffers(); //equivalent to glFlush for double buffering

}

void reshapeFunc(int w, int h) {

   // Prevent a divide by zero, when window is too short
   // (you cant make a window of zero width).
   if(h == 0)
      h = 1;

   // aspect ratio
   float aspect = (float)w/(float)h;
   //float aspect = 1.0;

   // Set the viewport to be the entire window
   glViewport(0, 0, w, h);

   // Use the Projection Matrix
   glMatrixMode(GL_PROJECTION);

   // Reset Matrix
   glLoadIdentity();

   // define field of vision (http://www.eng.utah.edu/~cs5600/slides/Wk%205%20Lec09%20perspective%20II.pdf)
    float halfFov, theTan, screenFov;
    screenFov       = 45.0f;

    float eyeX      = (float)w / 2.0;
    float eyeY      = (float)h / 2.0;
    halfFov         = M_PI * screenFov / 360.0;
    theTan          = tanf(halfFov);
    float dist      = eyeY / theTan;
    float nearDist  = dist / 10.0;  // near / far clip plane
    float farDist   = dist * 10.0;
    //cout<<"near: "<<nearDist<<"far: "<<farDist<<endl;
    //gluPerspective(screenFov, aspect, nearDist, farDist);
   
   gluPerspective(45.0,(GLfloat)w/(GLfloat)h,0.1f,100.0f); 
 
   // Get Back to the Modelview matrix
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0, 0, 5, 0,0,0,0.0f,1.0f,0.0f);

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
   glutInitDisplayMode(GLUT_DOUBLE); // double buffer, use rgb color, enable depth buffer and alpha
   //No depth in 2D
   //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA ); // double buffer, use rgb color, enable depth buffer and alpha
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner   
   glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
   init();
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
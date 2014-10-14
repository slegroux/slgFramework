#ifdef __MACOSX_CORE__
  #include <GLUT/glut.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
  #include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
#include "camera.h"
using namespace std;
 
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */

float g_angle=0.0;
Camera camera;

void passiveFunc(int x, int y) {}
//Used when person clicks mouse
void mouseFunc(int button, int state, int x, int y) {
   camera.SetPos(button, state, x, y);
}
//Used when person drags mouse around
void motionFunc(int x, int y) {
   camera.Move2D(x, y);
}

void displayFunc() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);         // Clear the color buffer
   


   //Camera
   glm::mat4 model, view, projection;
   camera.Update();
   camera.GetMatrices(projection,view,model);
   glm::mat4 mvp = projection* view * model; //Compute the mvp matrix
   glLoadMatrixf(glm::value_ptr(mvp));

   // Reset transformations
   //glLoadIdentity();

   // Set the camera
   /*gluLookAt(  0.0f, 1.0f, 15.0f,
            0.0f, 0.0f,  0.0f,
            0.0f, 1.0f,  0.0f);*/

   

   
   // draw ground

   GLfloat extent      = 50.0f; // How far on the Z-Axis and X-Axis the ground extends
   GLfloat stepSize    = 1.0f;  // The size of the separation between points
   GLfloat groundLevel = -0.0f;   // Where on the Y-Axis the ground is drawn
  
   // Set colour to white
   glColor3ub(255, 255, 255);


   glPushMatrix();
   // Draw our ground grid
   glBegin(GL_LINES);
   for (GLint loop = -extent; loop < extent; loop += stepSize)
   {
         // Draw lines along Z-Axis
         glVertex3f(loop, groundLevel,  extent);
         glVertex3f(loop, groundLevel, -extent);
  
         // Draw lines across X-Axis
         glVertex3f(-extent, groundLevel, loop);
         glVertex3f(extent,  groundLevel, loop);
   }
   glEnd();
   glPopMatrix();

   /*glBegin(GL_TRIANGLES);
      glVertex3f(-2,-2,-10);
      glVertex3f(2,0.0,-10);
      glVertex3f(0.0,2,-10);
   glEnd();*/
   
   
   //glFlush();  // Render now

   //glRotatef(g_angle, 0, 1.0f, 0);
   // Draw a Red 1x1 Square centered at origin
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      //glColor3f(1.0f, 0.0f, 0.0f); // Red
      glColor3ub(255,0,0);
      glVertex3f(-2, -2,-5);
      glColor3ub(0,255,0);
      glVertex3f( 2, -2,-5);
      glColor3ub(0,0,255);
      glVertex3f( 2,  2,-5);
      glVertex3f(-2,  2,-5);
      glColor3ub(100,200,200);
      glVertex3f(0,0,-20);
   glEnd();



   g_angle += 0.05;

   glutSwapBuffers(); //equivalent to glFlush for double buffering
   
}

void reshapeFunc(int w, int h) {

   // Prevent a divide by zero, when window is too short
   // (you cant make a window of zero width).
   if(h == 0)
      h = 1;

   // define field of vision (http://www.eng.utah.edu/~cs5600/slides/Wk%205%20Lec09%20perspective%20II.pdf)
   /*float halfFov, theTan, g_screenFov, g_aspect;
   g_screenFov       = 60.0f;

   float eyeX      = (float)w / 2.0;
   float eyeY      = (float)h / 2.0;
   halfFov         = M_PI * g_screenFov / 360.0;
   theTan          = tanf(halfFov);
   float dist      = eyeY / theTan;
   float g_nearDist  = dist / 10.0;  // near / far clip plane
   cout<<"Near clipping plane: "<<g_nearDist<<endl;
   float g_farDist   = dist * 10.0;
   cout<<"Far clipping plane: "<<g_farDist<<endl;
   g_aspect          = (float)w/(float)h;*/

   // Use the Projection Matrix
   glMatrixMode(GL_PROJECTION);

   // Reset Matrix
   glLoadIdentity();

   // Set the viewport to be the entire window
   //glViewport(0, 0, w, h);
   camera.SetViewport(0,0,w,h);

   // Set the correct perspective view angle, ratio, near and far clipping planes
   //gluPerspective(0,g_aspect,g_nearDist,g_farDist);
   //gluPerspective(45,(float)w/(float)h,0.1,100);

   // Get Back to the Modelview matrix
   //glMatrixMode(GL_MODELVIEW);
}

void keyboardFunc(unsigned char key, int x, int y) {

   /*if (key == 27)
      exit(0);
   if (key=='a')
      cout<<"left"<<endl;
   if (key=='d')
      cout<<"right"<<endl;*/

   switch (key) {
   case 'w':
      camera.Move(FORWARD);
      break;
   case 'a':
      camera.Move(LEFT);
      break;
   case 's':
      camera.Move(BACK);
      break;
   case 'd':
      camera.Move(RIGHT);
      break;
   case 'q':
      camera.Move(DOWN);
      break;
   case 'e':
      camera.Move(UP);
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
   }
}

 
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // Initialize GLUT
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA ); // double buffer, use rgb color, enable depth buffer and alpha
   glutInitWindowSize(320, 320);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner   
   glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
   glutDisplayFunc(displayFunc); // Register display callback handler for window re-paint
   glutReshapeFunc(reshapeFunc); 
   glutIdleFunc(displayFunc);
   glutKeyboardFunc(keyboardFunc);
   glutSpecialFunc(specialFunc);
   glutMouseFunc(mouseFunc);
   glutMotionFunc(motionFunc);
   glutPassiveMotionFunc(passiveFunc);
   //glutTimerFunc(window.interval, TimerFunc, 0);
   //Setup camera
   camera.SetMode(FREE);
   camera.SetPosition(glm::vec3(0, 10, 10));
   camera.SetLookAt(glm::vec3(0, 0, 0));
   camera.SetClipping(.1, 1000);
   camera.SetFOV(45);
   //Start the glut loop!
   
   glutMainLoop();           // Enter the infinitely event-processing loop
   return 0;
}
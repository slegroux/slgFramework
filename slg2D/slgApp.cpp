#include "slgApp.h"
#include <unistd.h>

void slgApp::setup(){

   /* OPEN GL */
   //Color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearColor(0.5,0.5,0.5, 1.0f); // Set background color to grey
   //Transparency
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   /* INIT */
   g_counter = 0.0;
   g_x = 0;
   g_y = 0;

}

void slgApp::idleFunc(){
   float time_step = 1.0f / (float)g_frame_rate;
   int time_step_ms = (int)(1000.0f * time_step);
   int time_difference = glutGet(GLUT_ELAPSED_TIME) - g_previous_time;
   // wait for duration = at least time_step
   if (time_difference > time_step_ms){
      ; // we do nothing, we are already slower than target frame
   } else {
      int waiting_time = time_step_ms - time_difference;
      usleep(waiting_time * 1000); //mac sleep in microseconds - cooler :)
   }

   /* UPDATE VARIABLES */
   g_counter += 1;

   glutPostRedisplay();
   g_previous_time = glutGet(GLUT_ELAPSED_TIME);
}

void slgApp::displayFunc(){
   /* INIT */
   // each time displayFunc is called it adds to the current OpenGL state machine
   // 2D no depth
   glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
   // 3D with depth
   //glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT); // Clear the color buffer
   // drawing starts at the same location than previous call
   glLoadIdentity();
   
   //Drawing
   g_drawMode = kOutline;
   
   Axis();
   glColor4f(1,0.7,0.7,0.8);
   glPointSize(20.0f);
   Point(g_x,g_y);
   
   glColor4f(0.8,0.8,1,0.8);
   glLineWidth(2.0);
   // save state
   glPushMatrix();
   glRotatef((g_counter), 1,0,0);
   Rectangle(-0.5,-0.5,1,1);
   // retrieve state
   glPopMatrix();

   g_drawMode = kFilled;
   glColor4f(1,1,1,0.5);
   Triangle(0,0,-1,-0.5,1,-0.5);
   
   glColor4f(0.8,1,0.8,0.5);
   glPushMatrix();
   glTranslatef(-0.5,0.5,0.0);
   glRotatef(-g_counter,0,1,0);
   Circle(0,0,0.2);
   glPopMatrix();

   glColor4f(0.8,0.8,0.8,0.5);
   glRotatef((g_counter), 1,1,1);
   glutWireCube(0.5f); 
   
   glutSwapBuffers(); //equivalent to glFlush for double buffering
}

void slgApp::cleanup(){

}

void slgApp::reshapeFunc(int w, int h) {

   // Prevent a divide by zero, when window is too short
   // (you cant make a window of zero width).
   if(h == 0)
      h = 1;

   // aspect ratio (keep proportions when resize)
   float aspect = (float)w/(float)h;
   //float aspect = 1.0;

   // Set the 2D plane viewport to be the entire window
   glViewport(0, 0, w, h); //0,0 is bottom left

   // swithch to projection Matrix
   glMatrixMode(GL_PROJECTION);

   // Reset projection matrix to default
   glLoadIdentity();

   // Set clipping area's left, right, bottom, top (default -1,1,-1,1)
   if (w>h)
      gluOrtho2D(-1.0*aspect, 1.0*aspect, -1.0, 1.0);
   else
      gluOrtho2D(-1.0, 1.0, -1.0/aspect, 1.0/aspect);
   
   //gluPerspective(0.0f,(GLfloat)w/(GLfloat)h,1.0f,1000.0f); 
   //gluPerspective(90, (GLfloat)w/ (GLfloat)h, 0.0, 100.0);
 
   // Switch back to Modelview matrix
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void slgApp::keyboardFunc(unsigned char key, int x, int y) {

   switch (key) {
      case 'w':
         std::cout<<"w"<<std::endl;
         break;
      case 'a':
         std::cout<<"a"<<std::endl;
         break;
      case 'd':
         std::cout<<"d"<<std::endl;
         break;
      case 's':
         std::cout<<"s"<<std::endl;
         break;
      case 'q':
         exit(0);
         break;
      case 27:
         exit(0);
         break;
   }
}

void slgApp::keyboardUpFunc(unsigned char key, int x, int y){
   switch (key) {
      case 'w':
         std::cout<<"w released"<<std::endl;
         break;
      case 'a':
         std::cout<<"a released"<<std::endl;
         break;
      case 'd':
         std::cout<<"d released"<<std::endl;
         break;
      case 's':
         std::cout<<"s released"<<std::endl;
         break;
   }

}

void slgApp::specialFunc(int key, int x, int y) {

   switch(key) {
      case GLUT_KEY_F1 :
         break;
      case GLUT_KEY_F2 :
         break;
      case GLUT_KEY_F3 :
         break;
      case GLUT_KEY_UP:
         std::cout<<"UP"<<std::endl;
         g_y += 0.1;
         break;
      case GLUT_KEY_DOWN:
         std::cout<<"DOWN"<<std::endl;
         g_y -= 0.1;
         break;
      case GLUT_KEY_LEFT:
         std::cout<<"LEFT"<<std::endl;
         g_x -=0.1;
         break;
      case GLUT_KEY_RIGHT:
         std::cout<<"RIGHT"<<std::endl;
         g_x +=0.1;
         break;
   }
}

void slgApp::specialUpFunc(int key, int x, int y) {

   switch(key) {
      case GLUT_KEY_F1 :
         break;
      case GLUT_KEY_F2 :
         break;
      case GLUT_KEY_F3 :
         break;
      case GLUT_KEY_UP:
         std::cout<<"UP released"<<std::endl;
         break;
      case GLUT_KEY_DOWN:
         std::cout<<"DOWN released"<<std::endl;
         break;
      case GLUT_KEY_LEFT:
         std::cout<<"LEFT released"<<std::endl;
         break;
      case GLUT_KEY_RIGHT:
         std::cout<<"RIGHT released"<<std::endl;
         break;
   }
}
 
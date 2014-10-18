#include "slg2D.h"
#include "slgGen.h"
#include "slgAudio.h"
#include "realFFTW.h"
#include "Thread.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

#define BUFFER_SIZE 512
// global variables
int g_refreshRateMs = 30; // refresh interval in milliseconds
float g_phase = 0.0;
float g_freq = 440.0;
SAMPLE g_t = 0;

// 1 channel buffer
SAMPLE * g_buffer = NULL;
int g_bufferSize = (int)BUFFER_SIZE/NUM_CHANNS;
// fft of one channel
SAMPLE *g_fftBuff = NULL;
int g_fftSize = (g_bufferSize/2)+1;

slgAudio *audio = NULL;

Mutex g_mutex;

//function definitions
//void idleFunc();
void setup();
void displayFunc();
void reshapeFunc(int w, int h);
void Timer(int value);
void keyboardFunc(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);

void setup(){
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   //bufferBytes = bufferFrames * MY_CHANNELS * sizeof(SAMPLE);
   // allocate global buffer
   g_buffer = new SAMPLE[g_bufferSize];
   memset( g_buffer, 0, sizeof(SAMPLE)*g_bufferSize);
   g_fftBuff = new SAMPLE[g_fftSize];
   memset(g_fftBuff,0,sizeof(SAMPLE)*g_fftSize);
}

/* Called back when timer expired */
void Timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(g_refreshRateMs, Timer, 0); // next Timer call milliseconds later
   //g_phase-=0.05;
   //g_freq += 10.0;
}

int audioCallback( void * outputBuffer, void * inputBuffer, 
                   unsigned int nFrames, double streamTime,
                   RtAudioStreamStatus status, void * userData )
{
   SAMPLE * out = (SAMPLE *)outputBuffer;
   SAMPLE * in = (SAMPLE *)inputBuffer;
   //memset(in,0,nFrames*sizeof(SAMPLE));
   memset(out,0,nFrames*sizeof(SAMPLE));
   
   g_mutex.lock();
   
   //memcpy(out,in, nFrames*sizeof(SAMPLE));
   // fill
   for( int i = 0; i < nFrames; i++ )
   {
      //out[i*NUM_CHANNS] = ::sin( 2 * M_PI * g_freq * g_t / SAMPLE_RATE);
      out[i*NUM_CHANNS] = in[i*NUM_CHANNS];

      g_buffer[i] = in[i*NUM_CHANNS];
      //makeSine(out,440,nBufferFrames/SAMPLE_RATE);

      // copy into other channels
      for( int j = 1; j < NUM_CHANNS; j++ )
         out[i*NUM_CHANNS+j] = out[i*NUM_CHANNS];
      g_t += 1.0;
   }
   g_mutex.unlock();
   return 0;
}

void displayFunc() {

   //glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);         // Clear the color buffer
   //but no depth in 2D so:
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
   
   g_mutex.lock();

   realFFTW myfft(g_bufferSize);
   myfft.setInput(g_buffer, g_bufferSize);
   myfft.forwardTransform();

   //drawBuffer(g_buffer,g_bufferSize,-1.0,1.0);
   myfft.getMagnitudeDB(g_fftBuff,g_fftSize);
   drawBuffer(g_fftBuff,g_fftSize);
   g_mutex.unlock();
   
   glutSwapBuffers(); //equivalent to glFlush for double buffering

}


 
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

   
   glutInit(&argc, argv); // Initialize GLUT
   //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA ); // double buffer, use rgb color, enable depth buffer and alpha
   //No depth in 2D
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA ); // double buffer, use rgb color, enable depth buffer and alpha
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner   
   glutCreateWindow("SonoScope"); // Create a window with the given title

   setup();

   glutDisplayFunc(displayFunc); // Register display callback handler for window re-paint
   glutReshapeFunc(reshapeFunc); 
   //glutReshapeWindow(320,320);
   //glutIdleFunc(idleFunc); //replaced by timer
   
   //First timer call immediately
   glutTimerFunc(0, Timer, 0);
   glutKeyboardFunc(keyboardFunc);
   //glutSpecialFunc(specialFunc);

   audio = new slgAudio( NUM_CHANNS, SAMPLE_RATE, BUFFER_SIZE );
   //slgAudio audio( NUM_CHANNS, SAMPLE_RATE, BUFFER_SIZE );
   // open audio stream
   audio->openStream( &audioCallback);
    
   // info about default input/output devices
   audio->info();

   audio->startStream();
   //Start the glut loop! 
   glutMainLoop();
   audio->stopStream();
   //clean up
   audio->closeStream();
   delete audio;

   delete [] g_buffer;
   g_buffer = NULL;

   delete [] g_fftBuff;
   g_fftBuff = NULL;
   
   return 0;
}

void reshapeFunc(int w, int h) {

   // Prevent a divide by zero, when window is too short
   // (you cant make a window of zero width).
   if(h == 0)
      h = 1;

   // aspect ratio
   //float aspect = (float)w/(float)h;
   float aspect = 1.0;

   // Set the viewport to be the entire window
   glViewport(0, 0, w, h);

   // Use the Projection Matrix
   glMatrixMode(GL_PROJECTION);

   // Reset Matrix
   glLoadIdentity();

   // Set clipping area's left, right, bottom, top (default -1,1,-1,1)
   if (w>h)
      gluOrtho2D(-1.0*aspect, -1.0*aspect, -1.0, 1.0);
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
      cout<<"w"<<endl;
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
      //clean up
      delete [] g_buffer;
      g_buffer = NULL;
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
         cout<<"up!"<<endl;
         break;
   }
}
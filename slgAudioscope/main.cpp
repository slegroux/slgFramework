#include "slgGraphics.h"
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

// size of AUDIO BUFFER (including n channels)
#define BUFFER_SIZE 1024
// global variables
int g_refreshRateMs = 30; // refresh interval in milliseconds
float g_phase = 0.0;
int g_freq = 11025;
SAMPLE g_t = 0;

// UI
int g_key = 1;
enum displayMode {kAmplitude = 1, kSpectrum, kSpectrumDB};
enum InputMode {kSine,kInput};
InputMode g_inputSignal = kInput;
enum DisplayDim {k2d,k3d};
DisplayDim g_dimension = k2d;

// Global buffers 1 channel
SAMPLE * g_buffer = NULL;
int g_bufferSize = (int)BUFFER_SIZE/NUM_CHANNS; //n samples for 1 channel of audio
// fft of one channel
SAMPLE *g_fftBuff = NULL;
int g_fftSize = (g_bufferSize/2)+1; //n fft bins
// window (e.g. hanning)
SAMPLE *g_window = NULL;

//Global classes 
slgAudio *audio = NULL;
realFFTW *g_Myfft = NULL;

Mutex g_mutex;

//function definitions
//void idleFunc();
void help();
void setup();
void cleanup();
void displayFunc();
void reshapeFunc(int w, int h);
void Timer(int value);
void keyboardFunc(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);
void menu(int item);

void setup(){
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   //bufferBytes = bufferFrames * MY_CHANNELS * sizeof(SAMPLE);
   // allocate global buffer
   
}

/* Called back when timer expired */
void Timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(g_refreshRateMs, Timer, 0); // next Timer call milliseconds later
   //g_phase-=0.05;
   g_freq += 10;
   //g_freq = (int)g_freq % 30;
   

}

struct AudioCallbackData{
   int n_channels = 2;
   SAMPLE *audio_buffer;
   unsigned int audio_buffer_size;
   realFFTW *fft_class;
};

int audioCallback( void * outputBuffer, void * inputBuffer, 
                   unsigned int nFrames, double streamTime,
                   RtAudioStreamStatus status, void * userData )
{
   SAMPLE * out = (SAMPLE *)outputBuffer;
   SAMPLE * in = (SAMPLE *)inputBuffer;
   memset(g_buffer,0,g_bufferSize*sizeof(SAMPLE));
   memset(out,0,nFrames*sizeof(SAMPLE));

   g_mutex.lock();
   
   switch (g_inputSignal){
      case kSine:
         for (int i=0;i<g_bufferSize;i++){
            g_buffer[i] = ::sin( 2 * M_PI * g_freq * g_t / SAMPLE_RATE);
         }
         g_t += 1.0;
         break;

      case kInput:
         for (int i=0;i<g_bufferSize;i++){
            g_buffer[i] = in[i*NUM_CHANNS];
         }
         break;
   }
   
   g_Myfft->setInput(g_buffer, g_bufferSize);
   g_Myfft->forwardTransform();
         
   g_mutex.unlock();
   
   //memcpy(out,in, nFrames*sizeof(SAMPLE));
   // fill
   /*for( int i = 0; i < nFrames; i++ )
   {
      switch (g_inputSignal){
         
         case kSine:
            out[i*NUM_CHANNS] = ::sin( 2 * M_PI * g_freq * g_t / SAMPLE_RATE);
            break;

         case kInput:
            out[i*NUM_CHANNS] = in[i*NUM_CHANNS];
            break;
      }
      
      g_buffer[i] = out[i*NUM_CHANNS];
      //makeSine(out,440,nBufferFrames/SAMPLE_RATE);

      // copy into other channels
      for( int j = 1; j < NUM_CHANNS; j++ )
         out[i*NUM_CHANNS+j] = out[i*NUM_CHANNS];
      g_t += 1.0;
   }*/
  
   return 0;
}

void displayFunc() {

   //glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);         // Clear the color buffer
   //but no depth in 2D so:
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();

   // draw background dashed grid
   glPushAttrib(GL_ENABLE_BIT|GL_CURRENT_BIT);
      glLineWidth(1);
      glLineStipple(4, 0xAAAA);
      glEnable(GL_LINE_STIPPLE);
      glColor4f(1,1,1,0.3);
      Grid(-1,-1.0,2,2,10,10);
   glPopAttrib();

   //g_mutex.lock();
   
   switch (g_key){
      case kAmplitude:
         g_mutex.lock();
         Buffer(g_buffer,g_bufferSize,-1.0,1.0,kLine);
         g_mutex.unlock();
         break;
      
      case kSpectrum:
         g_mutex.lock();
         g_Myfft->getMagnitude(g_fftBuff,g_fftSize);
         Buffer(g_fftBuff,g_fftSize, 0.0,1.0,kStem);
         g_mutex.unlock();
         break;
      
      case kSpectrumDB:
         g_mutex.lock();
         g_Myfft->getMagnitudeDB(g_fftBuff,g_fftSize);
         Buffer(g_fftBuff,g_fftSize, -120.0, 0.0,kLine);
         g_mutex.unlock();
         break;
   }

   glFlush();
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
   glutCreateMenu(menu);
   glutAddMenuEntry("Waveform", 1);
   //glutAddMenuEntry("", -1);
   glutAddMenuEntry("Magnitude Spectrum", 2);
   glutAddMenuEntry("Magnitude Spectrum DB", 3);
   glutAddMenuEntry("Exit", 0);
   glutAttachMenu(GLUT_RIGHT_BUTTON);

   g_buffer = new SAMPLE[g_bufferSize];
   memset( g_buffer, 0, sizeof(SAMPLE)*g_bufferSize);
   
   g_fftBuff = new SAMPLE[g_fftSize];
   memset(g_fftBuff,0,sizeof(SAMPLE)*g_fftSize);
   
   /*g_window = new SAMPLE[g_bufferSize];
   memset(g_window,0,sizeof(SAMPLE)*g_bufferSize);
   hanning(g_window, g_bufferSize);*/

   g_Myfft = new realFFTW(g_bufferSize);
   //applyWindow(g_buffer,window, g_bufferSize);

   audio = new slgAudio( NUM_CHANNS, SAMPLE_RATE, BUFFER_SIZE );
   cout<<"create audio class"<<endl;
   // open audio stream
   audio->openStream( &audioCallback);
   cout<<"open audio stream"<<endl;
    
   // info about default input/output devices
   audio->info();

   // print help after audio info so we see it last
   help();

   audio->startStream();
   cout<<"start audio stream"<<endl;
   //Start the glut loop! 
   glutMainLoop();
   
   audio->stopStream();
   cout<<"stop audio stream"<<endl;
   
   audio->closeStream();
   cout<<"close audio stream"<<endl;
   
   cleanup();
   cout<<"cleanup"<<endl;
   

   return 0;
}

void cleanup(){
   if (g_buffer != NULL){
      delete [] g_buffer;
      g_buffer = NULL;
   }
   
   if (g_fftBuff != NULL){
      delete [] g_fftBuff;
      g_fftBuff = NULL;
   }

   if (g_window != NULL){
      delete [] g_window;
      g_window = NULL;
   }

   if (g_Myfft != NULL)
      delete g_Myfft;

   if (audio != NULL)
      delete audio;
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

   /*switch (g_dimension){
      case k2d:
         cout<<"switching to 2D"<<endl;
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
         break;

      case k3d:
         cout<<"switching to 3D"<<endl;
         // Use the Projection Matrix
         glMatrixMode(GL_PROJECTION);
         // Reset Matrix
         glLoadIdentity();
         gluPerspective( 45.0, (GLfloat) w / (GLfloat) h, 1.0, 300.0 );
         //gluPerspective( 90,1, .01, 300.0 );
         
         break;
   }*/

   // Use the Projection Matrix
   glMatrixMode(GL_PROJECTION);
   // Reset Matrix
   glLoadIdentity();
   //glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1, 1);
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
   //gluLookAt(0.0f, 3.5f * sin( gEyeY ), 3.5f * cos( gEyeY ), 
   //          0.0f, 0.0f, 0.0f, 0.0f, ( cos( gEyeY ) < 0 ? -1.0f : 1.0f ), 0.0f );
   gluLookAt(0.0f, 0, 1, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0.0f );
   //gluLookAt(10, 1000, 10, 0,0, 0, 0, 1, 0);

}

void keyboardFunc(unsigned char key, int x, int y) {

   switch (key) {
   case 'w':
      cout<<"w"<<endl;
      break;
   
   case 'a':
      g_dimension = k2d;
      break;
   
   case 'd':
      g_dimension = k3d;
      break;
   
   case 's':
      g_inputSignal = kSine;
      break;

   case 'i':
      g_inputSignal = kInput;
      break;

   case 'h':
      help();
      break;

   case 'q':
      //clean up
      cleanup();
      exit(0);
      break;

   case 'e':
      break;

   case '1':
      g_key = kAmplitude;
      break;

   case '2':
      g_key = kSpectrum;
      break;

   case '3':
      g_key = kSpectrumDB;
      break;

   case 27:
      //clean up
      cleanup();
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

void menu(int item)
{
   switch(item)
   {
   case 0:
       exit(0);
      
   case 1:
      g_key = kAmplitude;
      break;

   case 2:
      g_key = kSpectrum;
      break;

   case 3:
      g_key = kSpectrumDB;
      break;

   }
}

void help()
{
    fprintf( stderr, "----------------------------------------------------\n" );
    fprintf( stderr, "Sonoscope v0.0\n");
    fprintf( stderr, "Sylvain Le Groux\n");
    fprintf( stderr, "http://ccrma.stanford.edu/~slegroux\n");
    fprintf( stderr, "----------------------------------------------------\n" );
    fprintf( stderr, "'h' - print this help message\n" );
    fprintf( stderr, "'i' - mic audio input \n" );
    fprintf( stderr, "'s' - sine audio input\n" );
    fprintf( stderr, "'1' - toggle waveform\n" );
    fprintf( stderr, "'2' - toggle spectrum\n" );
    fprintf( stderr, "'3' - toggle spectrum DB display\n" );
   fprintf( stderr, "'esc' - quit\n" );
    fprintf( stderr, "----------------------------------------------------\n" );
    fprintf( stderr, "\n" );
}


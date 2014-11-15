/**
 *  @file       main.cpp
 *
 *  @author     Sylvain Le Groux <slegroux [at] stanford.edu>
 *  
 *              Copyright (c) 2013 Sylvain Le Groux
 *
 **/
#include "slgGraphics.h"
#include "slgGen.h"
#include "slgAudio.h"
#include "realFFTW.h"
#include "slgCircularBuffer.h"
#include "slgCircularBuffer2D.h"
#include "Thread.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <boost/circular_buffer.hpp>


using namespace std;

// global constants
#define BUFFER_SIZE 8
const unsigned int g_ring_size = BUFFER_SIZE*2;
const int g_refreshRateMs = 100; // refresh interval in milliseconds

// global variables
float g_phase = 0.0;
int g_freq = 11025;
SAMPLE g_t = 0;

// UI
int g_key = 1;
enum displayMode {kAmplitude = 1, kSpectrum, kSpectrumDB, kScrollingWaveform,kSpectrogram};
enum InputMode {kSine,kInput};
InputMode g_inputSignal = kInput;
enum DisplayDim {k2d,k3d};
DisplayDim g_dimension = k2d;

Mutex g_mutex;

// data that is passed around audio and gfx
struct AudioCallbackData{
   // data
   unsigned int n_channels;
   SAMPLE *audio_buffer;
   unsigned int audio_buffer_size;
   realFFTW *fft_class;
   SAMPLE *fft_buffer;
   unsigned int fft_buffer_size;
   SAMPLE *analysis_window;
   slgCircularBuffer <SAMPLE> ring_buffer;
   unsigned int ring_buffer_size;
   slgCircularBuffer<SAMPLE*> ring_spectrum;
   boost::circular_buffer<SAMPLE*> boost_ring;


   //constructor
   AudioCallbackData(){
      n_channels=2;
      // Global buffers 1 channel
      audio_buffer = NULL;
      audio_buffer_size = (int)BUFFER_SIZE/NUM_CHANNS; //n samples for 1 channel of audio
      audio_buffer = new SAMPLE[audio_buffer_size];
      memset( audio_buffer, 0, sizeof(SAMPLE)*audio_buffer_size);
      
      // fft of one channel
      fft_buffer = NULL;
      fft_buffer_size = (audio_buffer_size/2); //n fft bins
      fft_buffer = new SAMPLE[fft_buffer_size];
      memset(fft_buffer,0,sizeof(SAMPLE)*fft_buffer_size);
      
      // window (e.g. hanning)
      analysis_window = NULL;
      /*
      g_window = new SAMPLE[g_bufferSize];
      memset(g_window,0,sizeof(SAMPLE)*g_bufferSize);
      hanning(g_window, g_bufferSize);*/
      fft_class = NULL;
      fft_class = new realFFTW(audio_buffer_size);
      //applyWindow(g_buffer,window, g_bufferSize);
      ring_buffer_size = g_ring_size;
      ring_buffer.set_size(ring_buffer_size);
      ring_spectrum.set_size(ring_buffer_size);
      boost_ring.set_capacity(ring_buffer_size);
   }

   //destructor
   ~AudioCallbackData(){
      if (audio_buffer != NULL){
         delete [] audio_buffer;
         audio_buffer = NULL;
      }
      
      if (fft_buffer != NULL){
         delete [] fft_buffer;
         fft_buffer = NULL;
      }

      if (analysis_window != NULL){
         delete [] analysis_window;
         analysis_window = NULL;
      }

      if (fft_class != NULL)
         delete fft_class;

      /*if (ring_buffer != NULL)
         delete ring_buffer;*/
   }  
};
AudioCallbackData g_callback_data;


//function definitions
//void idleFunc();
static void Help();
static void SetupGL();
static void SetupGLUT(int argc, char** argv);
static void SetupLight();
static void Cleanup();
static void displayFunc();
static void reshapeFunc(int w, int h);
static void Timer(int value);
static void keyboardFunc(unsigned char key, int x, int y);
static void specialFunc(int key, int x, int y);
static void menu(int item);


/* Called back when timer expired */
static void Timer(int value) {

   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(g_refreshRateMs, Timer, 0); // next Timer call milliseconds later
   //g_phase-=0.05;
   g_freq += 10;
   //g_freq = (int)g_freq % 30;
}


int AudioCallback( void * outputBuffer, void * inputBuffer, 
                   unsigned int nFrames, double streamTime,
                   RtAudioStreamStatus status, void * userData )
{
   SAMPLE * out = (SAMPLE *)outputBuffer;
   SAMPLE * in = (SAMPLE *)inputBuffer;
   AudioCallbackData *data = (AudioCallbackData*) userData;
   
   //memset(g_buffer,0,g_bufferSize*sizeof(SAMPLE));
   memset(data->audio_buffer,0,data->audio_buffer_size*sizeof(SAMPLE));
   memset(out,0,nFrames*sizeof(SAMPLE));

   g_mutex.lock();

   switch (g_inputSignal){
      case kSine:
         g_t = streamTime;
         for (int i=0;i<data->audio_buffer_size;i++){
            data->audio_buffer[i] = 0.7*::sin( 2 * M_PI * g_freq * g_t / SAMPLE_RATE);
            g_t += 1.0;   
         }
         break;

      case kInput:
         for (int i=0;i<data->audio_buffer_size;i++){
            data->audio_buffer[i] = in[i*NUM_CHANNS];
         }
         break;
   }
   
   data->fft_class->setInput(data->audio_buffer, data->audio_buffer_size);
   data->fft_class->forwardTransform();
   g_callback_data.fft_class->getMagnitude(g_callback_data.fft_buffer,g_callback_data.fft_buffer_size);
   
   // push data in ring buffer spectrum by spectrum
   g_callback_data.boost_ring.push_back(g_callback_data.fft_buffer);


   //fft is over all audio buffer write the whole buffer at once
   //g_callback_data.ring_spectrum.Write(g_callback_data.fft_buffer);

   /*cout<<"data.fftbuff"<<endl;
   for (int i =0;i<g_callback_data.fft_buffer_size;++i){
      cout<<g_callback_data.fft_buffer[i]<<endl;
   }
   cout<<"-----------"<<endl;
   cout<<"num elements: "<<g_callback_data.ring_spectrum.get_num_elements()<<endl;

   SAMPLE* spectrum = new SAMPLE[g_callback_data.fft_buffer_size];
   //spectrum = g_callback_data.ring_spectrum.Read();
   cout<<"spectrum"<<endl;
   for (int i=0;i<g_callback_data.fft_buffer_size;++i){
      cout<<spectrum[i]<<endl;
   }

   //write sample by sample
   for (int i=0;i<nFrames;i++){
      g_callback_data.ring_buffer.Write(in[i*NUM_CHANNS]);
   }*/

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

static void displayFunc() {

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

   switch (g_key){
      case kAmplitude:
         g_mutex.lock();
         Buffer1D(g_callback_data.audio_buffer,g_callback_data.audio_buffer_size,-1.0,1.0,kLine);
         g_mutex.unlock();
         break;
      
      case kSpectrum:
         g_mutex.lock();
         g_callback_data.fft_class->getMagnitude(g_callback_data.fft_buffer,g_callback_data.fft_buffer_size);
         //cout<<g_callback_data.fft_buffer[0]<<endl;
         Buffer1D(g_callback_data.fft_buffer,g_callback_data.fft_buffer_size, 0,1, kStem);
         g_mutex.unlock();
         break;
      
      case kSpectrumDB:
         g_mutex.lock();
         g_callback_data.fft_class->getMagnitudeDB(g_callback_data.fft_buffer,g_callback_data.fft_buffer_size);
         Buffer1D(g_callback_data.fft_buffer,g_callback_data.fft_buffer_size, -120.0, 0.0,kLine);
         g_mutex.unlock();
         break;

      case kScrollingWaveform:
      {
         g_mutex.lock();
         SAMPLE *data = new SAMPLE[g_ring_size];
         memset(data,0,g_ring_size*sizeof(SAMPLE));
         glColor4f(1,0,0,0.4);
         for (int i=0;i<g_ring_size;++i){
            data[i]=g_callback_data.ring_buffer.Read();
            //cout<<data[i]<<endl;
         }
         Buffer1D(data,g_ring_size, -1.0,1.0,kLine);
         g_mutex.unlock();
         break;
      }

      case kSpectrogram:
      {

         g_mutex.lock();

       

         cout<<"fft buffer size: "<<g_callback_data.fft_buffer_size<<endl;
         boost::circular_buffer<SAMPLE*>::iterator ring_iterator;
         for(ring_iterator = g_callback_data.boost_ring.begin(); ring_iterator != g_callback_data.boost_ring.end();ring_iterator++){
            cout<<"it: "<<ring_iterator- g_callback_data.boost_ring.begin()<<endl;

            cout<<(*ring_iterator)<<endl;
         }

         // 1 spectral frame
         SAMPLE *spectrum= new SAMPLE[g_callback_data.fft_buffer_size];
         memset(spectrum,0,(g_callback_data.fft_buffer_size)*sizeof(SAMPLE));
         spectrum = g_callback_data.ring_spectrum.Read();
         for (int i=0;i<g_callback_data.fft_buffer_size;i++){
            cout<<spectrum[i]<<endl;
         }

         //spectrum = g_callback_data.ring_spectrum.Read();
         //spectrum = g_callback_data.boost_ring.pop_front();

         //2D spectrogram
         SAMPLE **spectrogram = new SAMPLE*[g_callback_data.ring_buffer_size];
         
         for (int i =0;i<g_callback_data.ring_buffer_size;i++){
           
            spectrogram[i] = spectrum;
         }
         //Buffer2D(g_callback_data.boost_ring,g_callback_data.fft_buffer_size-1,g_callback_data.ring_buffer_size,0,g_callback_data.fft_buffer_size);
         
         
         g_mutex.unlock();
         break;
      }
   }

   glFlush();
   glutSwapBuffers(); //equivalent to glFlush for double buffering

}


/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
   
   // GFX
   SetupGLUT(argc, argv);
   SetupGL();
   //SetupLight();
   
   // Audio
   slgAudio *audio = NULL;
   audio = new slgAudio( NUM_CHANNS, SAMPLE_RATE, BUFFER_SIZE );
   cout<<"create audio class"<<endl;
   // open audio stream
   audio->openStream( &AudioCallback, &g_callback_data);
   cout<<"open audio stream"<<endl;
    
   // info about default input/output devices
   audio->info();

   // print help after audio info so we see it last
   Help();

   audio->startStream();
   cout<<"start audio stream"<<endl;

   //Start the glut loop! 
   glutMainLoop();
   
   audio->stopStream();
   cout<<"stop audio stream"<<endl;
   
   audio->closeStream();
   cout<<"close audio stream"<<endl;
   
   Cleanup();
   delete audio;
   //delete g_callback_data;
   cout<<"cleanup"<<endl;
   

   return 0;
}

static void SetupGL(){
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   // Turn on alpha blending for textures
   glEnable(GL_ALPHA_TEST);
   glAlphaFunc(GL_GREATER, 0.01f);
   // enable z-buffering
   glEnable(GL_DEPTH_TEST);
}

static void SetupLight(){
     GLfloat light0_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
     GLfloat light0_diffuse[] =  {.6f, .6f, 1.0f, 1.0f};
     GLfloat light0_position[] = {1.0f, 1.0f, 1.0f, 0.0f};

     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
     glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
}

static void SetupGLUT(int argc, char** argv){
   glutInit(&argc, argv);
   cout<<"Initialize GLUT"<<endl;
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA ); // double buffer, use rgb color, enable depth buffer and alpha
   cout<<"Display mode"<<endl;
   //No depth in 2D
   int SystemResWidth = glutGet(GLUT_SCREEN_WIDTH);
   int SystemResHeight = glutGet(GLUT_SCREEN_HEIGHT);

   //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA ); // double buffer, use rgb color, enable depth buffer and alpha
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner   
   glutCreateWindow("Test");

   glutDisplayFunc(displayFunc); // Register display callback handler for window re-paint
   cout<<"display func"<<endl;
   glutReshapeFunc(reshapeFunc); 
   cout<<"reshape func"<<endl;
   //glutReshapeWindow(320,320);
   //glutIdleFunc(idleFunc); //replaced by timer
   
   //First timer call immediately
   glutTimerFunc(0, Timer, 0);
   cout<<"Timer"<<endl;
   glutKeyboardFunc(keyboardFunc);
   //glutSpecialFunc(specialFunc);
   glutCreateMenu(menu);
   glutAddMenuEntry("Waveform", 1);
   //glutAddMenuEntry("", -1);
   glutAddMenuEntry("Magnitude Spectrum", 2);
   glutAddMenuEntry("Magnitude Spectrum DB", 3);
   glutAddMenuEntry("Exit", 0);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
}

static void Cleanup(){
   //TO DO check if delete explicitely needed
   //delete g_callback_data;

   /*if (audio != NULL)
      delete audio;
      audio = NULL;*/
}

static void reshapeFunc(int w, int h) {

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

static void keyboardFunc(unsigned char key, int x, int y) {

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
      Help();
      break;

   case 'q':
      //clean up
      Cleanup();
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

   case '4':
      g_key = kScrollingWaveform;
      break;

   case '5':
      g_key = kSpectrogram;
      break;

   case 27:
      //clean up
      Cleanup();
      exit(0);
      break;
   }
}

static void specialFunc(int key, int x, int y) {

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

static void menu(int item)
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

static void Help()
{
    fprintf( stderr, "----------------------------------------------------\n" );
    fprintf( stderr, "Sonoscope v0.0\n");
    fprintf( stderr, "Sylvain Le Groux\n");
    fprintf( stderr, "http://ccrma.stanford.edu/~slegroux\n");
    fprintf( stderr, "----------------------------------------------------\n" );
    fprintf( stderr, "'h' - print this help message\n" );
    fprintf( stderr, "'i' - mic audio input \n" );
    fprintf( stderr, "'s' - sine audio input\n" );
    fprintf( stderr, "'1' - toggle audio buffer\n" );
    fprintf( stderr, "'2' - toggle spectrum\n" );
    fprintf( stderr, "'3' - toggle spectrum in Decibels\n" );
    fprintf( stderr, "'4' - toggle scrolling waveform\n" );
    fprintf( stderr, "'esc' - quit\n" );
    fprintf( stderr, "----------------------------------------------------\n" );
    fprintf( stderr, "\n" );
}


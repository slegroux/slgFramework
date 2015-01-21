#ifndef _SLG_APP_H
#define _SLG_APP_H

#include "slgGraphics.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <glm/glm.hpp>
#include "slgPhysics.h"
#include "slgGLUT.h"
#include "slgAudio.h"
#include "slgOscillator.h"
#include "JCRev.h"
#include "slgOsc.h"
#include "Thread.h"
#include "Mutex.h"


class slgApp : public osc::OscPacketListener{

public:
   void setup();
   void displayFunc(); //draw
   void reshapeFunc(int w, int h);
   void idleFunc(); //update
   void keyboardFunc(unsigned char key, int x, int y);
   void specialFunc(int key, int x, int y);
   void passiveMotionFunc(int x, int y); //coordinates
   void mouseFunc(int button, int state, int x, int y); //mouse pressed/released
   int audioCallback( void * outputBuffer, void * inputBuffer, unsigned int nFrames, double streamTime,RtAudioStreamStatus status);
   void ProcessMessage( const osc::ReceivedMessage & m, const IpEndpointName & remoteEndpoint );
   //void * cb_osc_listener( void * );
   //void ProcessMessage( const osc::ReceivedMessage & m, const IpEndpointName & remoteEndpoint );
    
 

   // static wrapper to be able to use a member function callback
   static int cb_audioWrapper(void * outputBuffer, void * inputBuffer, unsigned int nFrames, double streamTime,RtAudioStreamStatus status, void * userData);

   void cleanup();

   //Threads
   stk::Thread g_osc_listener_thread;
   stk::Mutex g_mutex;
   //OSC
   //slgOscListener osc_listener;

   //Audio
   slgAudio audio;
   slgOscillator oscillator;
   stk::JCRev reverb;

   // frame rate and timing
   int g_frame_rate;// = 20; // refresh in Hz
   int g_previous_time = 0;

   //screen
   bool g_fullScreen = false;
   int g_height, g_width;

   //Font
   float volatile g_font_scale;

   //mouse
   glm::vec2 g_mouse;

   //Forces
   glm::vec2 g_wind;
   glm::vec2 g_gravity;
   glm::vec2 g_helium;

   //Entities
   static const int num_movers = 100;
   slgMover mover[num_movers];

};

#endif
#include "slgApp.h"
#include <unistd.h>
using namespace std;


// need a wrapper to call non-static member function
int slgApp::cb_audioWrapper(void * outputBuffer, void * inputBuffer, unsigned int nFrames, double streamTime,RtAudioStreamStatus status, void * userData){
      slgApp *self = static_cast<slgApp*>(userData);
      return self->audioCallback(outputBuffer, inputBuffer, nFrames, streamTime,status);
}

int slgApp::audioCallback( void * outputBuffer, void * inputBuffer, unsigned int nFrames, double streamTime, RtAudioStreamStatus status){

   if ( status ) std::cout << "Stream over/underflow detected." << std::endl;
   SAMPLE * out = (SAMPLE *)outputBuffer;
   SAMPLE * in = (SAMPLE *)inputBuffer;
   //slgOsc* data = (slgOsc*) userData;
   
   // fill
   for( int i = 0; i < nFrames; ++i ){
       
       // generate signal
       out[i*kNumChannels] = oscillator.render();
       
       // copy into other channels
       for( int j = 1; j < kNumChannels; ++j )
           out[i*kNumChannels+j] = out[i*kNumChannels];
   }

   return 0;

}

void slgApp::setup(){

   std::cout<<"--- setup"<<std::endl;
   g_height = glutGet(GLUT_WINDOW_HEIGHT);
   g_width = glutGet(GLUT_WINDOW_WIDTH);   
   std::cout<<"Window Width: "<<g_width<<std::endl;
   std::cout<<"Window Height: "<<g_height<<std::endl;
   
   // OPEN GL //
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glEnable (GL_BLEND); // transparency
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   // AUDIO //
   //audio(kNumChannels,kSampleRate,kFrameSize);
   audio.info();
   // call instance of class "this" via userData for wrapper
   audio.openStream(&slgApp::cb_audioWrapper, this);
   audio.getBufferSize();
   audio.startStream();
   // Audio objects
   oscillator.set_frequency(440.0);
   oscillator.set_mode(kSin);
   
   //seed randomizer
   srand(time(NULL));

   // PHYSICS //
   g_wind = glm::vec2(0.0,0);
   g_gravity = glm::vec2(0.0,-0.2);
   g_helium = glm::vec2(0);//glm::vec2(0.0,+0.07);

   // ENTITIES //
   for (int i=0;i<num_movers;i++){
      mover[i] = slgMover(g_width,g_height);
      //mover[i].printState();
   }
}

void slgApp::idleFunc(){
   // TIMER
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

   // BODY of the FUNCTION
   /*------------------*/
   for (int i=0;i<num_movers;i++){
      //mover[i].applyForce(g_wind);
      mover[i].applyForce(g_gravity);
      mover[i].applyForce(g_helium);
      //mover[i].bounce(g_width,g_height);
      mover[i].checkEdges(g_width,g_height);
      //mover[i].checkTop(g_width,g_height);
      mover[i].update(g_mouse);
      
   }
   //std::cout<<g_width<<std::endl;


   //END  
   /*------------------*/
   //std::cout<<"--- idle Function"<<std::endl;
   glutPostRedisplay();
   g_previous_time = glutGet(GLUT_ELAPSED_TIME);
}

void slgApp::displayFunc(){
   // 2D
   //no depth in 2D!
   glClear(GL_COLOR_BUFFER_BIT);
   //glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);         // Clear the color buffer
   glLoadIdentity();
   
   //glTranslatef(glutGet(GLUT_WINDOW_WIDTH)/2.0,glutGet(GLUT_WINDOW_HEIGHT)/2.0,0);
   Axis(50);
   //glColor4f(200,200,200,0.4);
   for (int i=0;i<num_movers;i++){
      //mover[i].checkEdges(g_width,g_height);
      mover[i].draw();
   }
   //std::cout<<"--- display Func"<<std::endl;
   //glFlush();
   glutSwapBuffers(); //equivalent to glFlush for double buffering
}


void slgApp::cleanup(){
   audio.stopStream();
   audio.closeStream();
}

void slgApp::reshapeFunc(int w, int h) {

   // Prevent a divide by zero, when window is too short
   // (you cant make a window of zero width).
   g_height = glutGet(GLUT_WINDOW_HEIGHT);
   g_width = glutGet(GLUT_WINDOW_WIDTH);   
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

   gluOrtho2D(0,w,0,h);
   // Set clipping area's left, right, bottom, top (default -1,1,-1,1)
   /*if (w>h)
      gluOrtho2D(-1.0*aspect, 1.0*aspect, -1.0, 1.0);
   else
      gluOrtho2D(-1.0, 1.0, -1.0/aspect, 1.0/aspect);
   */
   //gluPerspective(0.0f,(GLfloat)w/(GLfloat)h,1.0f,1000.0f); 
   // no depth in 2D
   glDisable(GL_DEPTH_TEST);
 
   // Get Back to the Modelview matrix
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   //Displacement trick for exact pixelization
   //glTranslatef(0.375, 0.375, 0);
   //std::cout<<"--- reshape Function"<<std::endl;
}

void slgApp::keyboardFunc(unsigned char key, int x, int y) {

   switch (key) {
      case 'q':
         exit(0);
         break;
      case 27:
         exit(0);
         break;
      case 'r':
         for (int i=0;i<num_movers;i++){
            mover[i].resetAcceleration();
         }
         break;
   }
}

void slgApp::specialFunc(int key, int x, int y) {

   switch(key) {
      case GLUT_KEY_F1 :
         g_fullScreen = !g_fullScreen;   
         if (g_fullScreen) {                     // Full-screen mode
            glutFullScreen();                      // Switch into full screen
         } else {                                         // Windowed mode
            glutReshapeWindow(g_windowWidth, g_windowHeight); // Switch into windowed mode
            glutPositionWindow(g_windowPosX, g_windowPosX);   // Position top-left corner
         }
         break;
      case GLUT_KEY_F2 :
            break;
      case GLUT_KEY_F3 :
            break;
      case GLUT_KEY_UP:
         for (int i = 0;i<num_movers;i++){
            mover[i].increaseAcceleration();
         }
         break;
      case GLUT_KEY_DOWN:
         for (int i = 0;i<num_movers;i++){
            mover[i].decreaseAcceleration();
         }
         break;
   }
}

void slgApp::passiveMotionFunc(int x, int y){
   g_mouse.x = x;
   g_mouse.y = g_height-y;
}

void slgApp::mouseFunc(int button, int state, int x, int y){
   if( state == GLUT_DOWN )
      g_wind = glm::vec2(0.5,0);
   else if ( state == GLUT_UP)
      g_wind = glm::vec2(0.0);

}

 
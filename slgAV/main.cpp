#include "slgGraphics.h"
#include "slgApp.h"
#include "slgAudio.h"

using namespace std;
 
#define N 100

//slgApp *myApp = new slgApp;
slgApp g_App;
//static slgAudio audio;
//trampolines from c++ member function to c callback!
extern "C" void cb_displayFunc() { g_App.displayFunc(); }
extern "C" void cb_reshapeFunc(int w, int h) { g_App.reshapeFunc(w,h); }
extern "C" void cb_idleFunc() { g_App.idleFunc(); }
extern "C" void cb_keyboardFunc(unsigned char key, int x, int y) { g_App.keyboardFunc(key, x, y); }
extern "C" void cb_specialFunc(int key, int x, int y) { g_App.specialFunc(key, x, y); }
extern "C" void cb_passiveMotionFunc(int x, int y) { g_App.passiveMotionFunc(x,y); }
extern "C" void cb_mouseFunc(int button, int state, int x, int y) { g_App.mouseFunc(button,state,x,y); }
/*extern "C" void cb_audio(void * outputBuffer, void * inputBuffer, 
                   unsigned int nFrames, double streamTime,
                   RtAudioStreamStatus status, void * userData ){g_App.audioCallback( outputBuffer, inputBuffer, 
                   nFrames, streamTime,status, userData );}*/
                   
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv){
   glutInit(&argc, argv);                 // Initialize GLUT
   //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA ); // double buffer, use rgb color, enable depth buffer and alpha
   //No depth in 2D
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA ); // double buffer, use rgb color, enable depth buffer and alpha
   glutInitWindowSize(kWindowWidth,kWindowHeight);   // Set the window's initial width & height
   glutInitWindowPosition(kInitWindowPosX, kInitWindowPosY); // Position the window's initial top-left corner   
   glutCreateWindow(argv[0]); // Create a window with the given title
   g_App.setup();
   //audio.info();
   glutDisplayFunc(cb_displayFunc); // Register display callback handler for window re-paint
   glutReshapeFunc(cb_reshapeFunc); 
   //glutReshapeWindow(320,320);
   glutIdleFunc(cb_idleFunc); //replaced by timer
   
   //glutTimerFunc(0, cb_update, 0);
   glutKeyboardFunc(cb_keyboardFunc);
   glutSpecialFunc(cb_specialFunc);
   glutMouseFunc(cb_mouseFunc);
   glutPassiveMotionFunc(cb_passiveMotionFunc);
  
   //Start the glut loop! 
   glutMainLoop();           // Enter the infinitely event-processing loop
   g_App.cleanup();
   return 0;
}
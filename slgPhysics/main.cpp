#include "slgGraphics.h"
#include "slgApp.h"

using namespace std;
 
#define N 100

slgApp *myApp = new slgApp;
 
//trampolines from c++ member function to c callback!
extern "C" void cb_displayFunc() { myApp->displayFunc(); }
extern "C" void cb_reshapeFunc(int w, int h) { myApp->reshapeFunc(w,h); }
// had to declare this one static as it is calling itself... maybe do that for other cb functions too
//extern "C" void cb_update(int value) { myApp->update(value); }
extern "C" void cb_idleFunc() { myApp->idleFunc(); }
extern "C" void cb_keyboardFunc(unsigned char key, int x, int y) { myApp->keyboardFunc(key, x, y); }
extern "C" void cb_specialFunc(int key, int x, int y) { myApp->specialFunc(key, x, y); }
extern "C" void cb_passiveMotionFunc(int x, int y) { myApp->passiveMotionFunc(x,y); }
extern "C" void cb_mouseFunc(int button, int state, int x, int y) { myApp->mouseFunc(button,state,x,y); }

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv){
   glutInit(&argc, argv);                 // Initialize GLUT
   //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA ); // double buffer, use rgb color, enable depth buffer and alpha
   //No depth in 2D
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA ); // double buffer, use rgb color, enable depth buffer and alpha
   glutInitWindowSize(kWindowWidth,kWindowHeight);   // Set the window's initial width & height
   glutInitWindowPosition(kInitWindowPosX, kInitWindowPosY); // Position the window's initial top-left corner   
   glutCreateWindow(argv[0]); // Create a window with the given title
   myApp->setup();
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
   myApp->cleanup();
   return 0;
}
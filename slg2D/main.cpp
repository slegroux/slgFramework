#include "slgGraphics.h"
#include "slgApp.h"

using namespace std;
 
slgApp *myApp = new slgApp;
// TRAMPOLINES from c++ member function to c callback
extern "C" void cb_displayFunc() { myApp->displayFunc(); }
extern "C" void cb_reshapeFunc(int w, int h) { myApp->reshapeFunc(w,h); }
// had to declare this one static as it is calling itself... maybe do that for other cb functions too
//extern "C" void cb_update(int value) { myApp->update(value); }
extern "C" void cb_idleFunc() { myApp->idleFunc(); }
extern "C" void cb_keyboardFunc(unsigned char key, int x, int y) { myApp->keyboardFunc(key, x, y); }
extern "C" void cb_keyboardUpFunc(unsigned char key, int x, int y) { myApp->keyboardUpFunc(key, x, y); }
extern "C" void cb_specialFunc(int key, int x, int y) { myApp->specialFunc(key, x, y); }
extern "C" void cb_specialUpFunc(int key, int x, int y) { myApp->specialUpFunc(key, x, y); }

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv){
   
   /* INIT */
   glutInit(&argc, argv);
   // 3D with depth
   //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA ); // double buffer, use rgb color, enable depth buffer and alpha
   // 2D no depth
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA ); // double buffer, use rgb color, disable depth buffer and alpha

   /* WINDOWING */
   glutInitWindowSize(640, 640);   // Set the window's initial width & height
   glutInitWindowPosition(100, 100); // Position the window's initial top-left corner   
   glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
   // setup opengl properties once
   myApp->setup();
   // drawing loop
   glutDisplayFunc(cb_displayFunc);
   // reshape when resizing window
   glutReshapeFunc(cb_reshapeFunc); 
   //glutReshapeWindow(320,320);
   glutIdleFunc(cb_idleFunc); //replaced by timer?
   //glutTimerFunc(0, cb_update, 0);

   /* KEYBOARD */
   // key pressed
   glutKeyboardFunc(cb_keyboardFunc);
   glutSpecialFunc(cb_specialFunc);
   // key up
   glutKeyboardUpFunc(cb_keyboardUpFunc);
   glutSpecialUpFunc(cb_specialUpFunc);
   
   /* GLUT LOOP */ 
   glutMainLoop(); // Enter the infinitely event-processing loop

   /* CLEANUP */
   myApp->cleanup();

   return 0;
}
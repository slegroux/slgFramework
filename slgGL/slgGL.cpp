/*
 *  slgGL.cpp
 *
 *  Created by Sylvain Le Groux 
 *  slegroux@stanford.edu
 *  Copyright 2013. All rights reserved.
 *
 */
 
#include "slgGL.h"
#include <typeinfo>

// window
int g_requestedWidth = 800;
int g_requestedHeight = 600;
float X = 0, Y = 0, Z = 0;
float g_screenFov =0, g_aspect=0, g_nearDist=0, g_farDist=0; 


// light 0 position
GLfloat g_light0_pos[] = { 2.0f, 1.2f, 4.0f, 1.0f };
//GLfloat g_light0_pos[] = { 0, 1000, 0, 1.0f };
// light 1 parameter
//GLfloat g_light1_pos[] = { -2.0f, 0.0f, -4.0f, 1.0f };
GLfloat g_light1_pos[] = { 0.0f, 10000.0f, 0.0f, 1.0f };
GLfloat g_light1_ambient[] = { .2f, .2f, .2f, 1.0f };
GLfloat g_light1_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat g_light1_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };


GLfloat slgGL::g_inc;


// eye, center, up vector
pt3d slgGL::g_look_from( 0.0, 0.0, 10.0);
pt3d slgGL::g_look_to( 0.0, 0.0, 0.0 );
pt3d slgGL::g_head_up( 0.0, 1.0, 0.0 );
//cout<<typid(g_head_up).name()<<endl;
//void myreshapeFunc( int w, int h );

slgGL::slgGL(){
    cout<<"create openGL object"<<endl;
    // all global variables are initialized at the top
	// fullscreen
	//g_fullscreen = FALSE;
   
}

slgGL::~slgGL(){
    cout<<"clean slgGL Object"<<endl;
}

void slgGL::printCoordinates(){
    /*cout<<"------------ Coordinates--------------"<<endl;
    cout<< "X: "<<X<<" Y: "<<Y<<" Z: "<<Z<<endl;
    cout<< "rotX: "<<rotX<<" rotY: "<<rotY<<" rotZ: "<<rotZ<<endl;
    cout<< "rotlX: "<<rotLx<<" rotLY: "<<rotLy<<" rotLZ: "<<rotLz<<endl;*/
}

//void slgGL::initWindow(int argc, char *argv[], int width, int height, int x,int y){
void slgGL::initWindow(int width, int height, int x,int y, string title){
    //TODO: put size as agrument
    cout<<"Initialize window"<<endl;
    int argc = 1;
    char *argv = "slg";
    char **vptr = &argv;
    // initialize GLUT
    glutInit( &argc, vptr);

    // initialize the window size
    glutInitWindowSize(width,height);
    // set the window postion
    //glutInitWindowPosition( x, y);
    // create the window
    glutCreateWindow( "" );
    glutSetWindowTitle(title.c_str());
    g_requestedWidth  = glutGet(GLUT_WINDOW_WIDTH);
    g_requestedHeight = glutGet(GLUT_WINDOW_HEIGHT);
    cout<<"------------ init Window--------------"<<endl;
    printCoordinates();

}

//-----------------------------------------------------------------------------
// Name: initialize_graphics( )
// Desc: sets initial OpenGL states and initializes any application data
//-----------------------------------------------------------------------------
void slgGL::initGraphics()
{
    cout<<"initialize graphics settings"<<endl;

    // double buffer, use rgb color, enable depth buffer and alpha
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA );
    
    // set the GL clear color - use when the color buffer is cleared
    glClearColor(0.9,0.9,0.9,0.9);
    glClearDepth(1.0);

    // set the shading model to 'smooth'
    glShadeModel( GL_SMOOTH );
    // for texture to be applied well
    // enable depth
    glEnable( GL_DEPTH_TEST );
    // The Type Of Depth Test To Do
    //glDepthFunc(GL_LESS);                       
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    // set the front faces of polygons
    glFrontFace( GL_CCW );
    // set fill mode
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    // enable lighting
    glEnable( GL_LIGHTING );
    // enable lighting for front
    //glLightModeli( GL_FRONT, GL_TRUE );
    glLightModeli( GL_FRONT_AND_BACK, GL_TRUE );
    // material have diffuse and ambient lighting
    //glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    // enable color
    glEnable( GL_COLOR_MATERIAL );
    // transparency
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    
    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,g_requestedWidth/g_requestedHeight,0.1f,100.0f); // Calculate The Aspect Ratio Of The Window
    
    glMatrixMode(GL_MODELVIEW);*/
}

void slgGL::initLight0(GLfloat light0_pos[],int size){
    GLfloat _light0_pos[4];
    // enable light 0
    glEnable( GL_LIGHT0 );
    if (size!=4){
        cout<<"Size error: need 4 values"<<endl;
        cout<<"Default light at 0,0,0,0"<<endl;
        for (int i=0;i<4;i++)
            _light0_pos[i]=0;
        glLightfv( GL_LIGHT0, GL_POSITION, _light0_pos );

    }
    else{
        for (int i=0;i<4;i++)
            _light0_pos[i] = light0_pos[i];
    }

}

void slgGL::setupScreen(){
   
    // SETUP SCREEN
    int w, h;

    w = glutGet(GLUT_WINDOW_WIDTH);
    h = glutGet(GLUT_WINDOW_HEIGHT);

    //glutReshapeWindow(g_requestedWidth, g_requestedHeight); 
    glutReshapeWindow(w, h); 

    glViewport( 0, 0, w, h );
    // black background
    glClearColor(0,0,0,1);
    // clear the color and depth buffers of screen
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    // define field of vision (http://www.eng.utah.edu/~cs5600/slides/Wk%205%20Lec09%20perspective%20II.pdf)
    float halfFov, theTan, g_screenFov, g_aspect;
    g_screenFov       = 60.0f;

    float eyeX      = (float)w / 2.0;
    float eyeY      = (float)h / 2.0;
    halfFov         = M_PI * g_screenFov / 360.0;
    theTan          = tanf(halfFov);
    float dist      = eyeY / theTan;
    float g_nearDist  = dist / 10.0;  // near / far clip plane
    float g_farDist   = dist * 10.0;
    g_aspect          = (float)w/(float)h;

    // SET UP PROJECTION (how the camera sees the world)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(g_screenFov, g_aspect, g_nearDist, g_farDist);
    //gluPerspective(45.0f,g_requestedWidth/g_requestedHeight,0.1f,100.0f); // Calculate The Aspect Ratio Of The Window

    // SETUP CAMERA VIEW

    gluLookAt(eyeX, eyeY, dist, eyeX, eyeY, 0.0, 0.0, 1.0, 0.0);
    
    // SET UP  POSITION AND ORIENTATION of CAMERA+WORLD
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // setup and enable light 1
    //glLightfv( GL_LIGHT1, GL_AMBIENT, g_light1_ambient );
    //glLightfv( GL_LIGHT1, GL_DIFFUSE, g_light1_diffuse );
    //glLightfv( GL_LIGHT1, GL_SPECULAR, g_light1_specular );
    //glEnable( GL_LIGHT1 );

    // set the position of the lights
    //glLightfv( GL_LIGHT0, GL_POSITION, g_light0_pos );
    //glLightfv( GL_LIGHT1, GL_POSITION, g_light1_pos );

    //glScalef(1, -1, 1);           // invert Y axis so increasing Y goes down.
    //glTranslatef(0, -h, 0);     // shift origin up to upper-left corner.

}

//-----------------------------------------------------------------------------
// Name: reshapeFunc( )
// Desc: called when window size changes
//-----------------------------------------------------------------------------
void slgGL::myReshapeFunc( int w, int h )
{
    // map the view port to be the entire window
    glViewport( 0, 0, w, h );
    // set the matrix mode to project
    glMatrixMode( GL_PROJECTION );
    // load the identity matrix
    glLoadIdentity( );
    // create the viewing frustum
    //gluPerspective(g_screenFov, g_aspect, g_nearDist, g_farDist);
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
    // set the matrix mode to modelview
    glMatrixMode( GL_MODELVIEW );
    // load the identity matrix
    glLoadIdentity( );
    gluLookAt(10, 1000, 10, 0,0, 0, 0, 1, 0);
    
    cout<<"--------REShape------"<<endl;
    slgGL::printCoordinates();
    //glutPostRedisplay();
}




//-----------------------------------------------------------------------------
// Name: mouseFunc( )
// Desc: handles mouse stuff
//-----------------------------------------------------------------------------
/*void slgGL::mouseFunc( int button, int state, int x, int y )
{
    if( button == GLUT_LEFT_BUTTON )
    {
        // rotate
        if( state == GLUT_DOWN )
            g_inc -= INC_VAL;
        else
            g_inc += INC_VAL;
    }
    else if ( button == GLUT_RIGHT_BUTTON )
    {
        if( state == GLUT_DOWN )
            g_inc += INC_VAL;
        else
            g_inc -= INC_VAL;
    }
    else
        g_inc = 0.0f;

    glutPostRedisplay( );
}*/


//-----------------------------------------------------------------------------
// name: changeLookAt()
// desc: changes the point of view
//-----------------------------------------------------------------------------
void slgGL::changeLookAt( pt3d look_from, pt3d look_to, pt3d head_up )
{
    // eye, center, up vector
   gluLookAt(  look_from.x, look_from.y, look_from.z, 
                look_to.x, look_to.y, look_to.z, 
                head_up.x, head_up.y, head_up.z );    
}

void slgGL::displayFunc(void (*myDisplayFunc)()){
    glutDisplayFunc( myDisplayFunc );
}

void slgGL::idleFunc(void (*myIdleFunc)()){
    glutIdleFunc( myIdleFunc );
}

void slgGL::setup(void (*mySetupFunc)()){
    mySetupFunc();
}

void slgGL::keyboardFunc(void(*myKeyboardFunc)(unsigned char, int, int)){
    glutKeyboardFunc(myKeyboardFunc);
}

void slgGL::specialFunc(void(*mySpecialFunc)(int key, int x, int y)){
    glutSpecialFunc(mySpecialFunc);
}

void slgGL::mouseFunc(void (*myMouseFunc)(int button, int state, int x, int y)){
    glutMouseFunc(myMouseFunc);
}

void slgGL::motionFunc(void (*myMotionFunc)(int x, int y)){
    glutMotionFunc(myMotionFunc);
}

void slgGL::glutLoop(){
    glutMainLoop();
}

void slgGL::reshapeFunc(){
    // set the reshape function - called when client area changes
    glutReshapeFunc( myReshapeFunc);
}

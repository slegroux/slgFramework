#include "slgGL.h"
#include <typeinfo>

// Declare static member variables (so that static member function can use them...)
GLfloat slgGL::g_eye_y = 0;
GLsizei slgGL::g_width = 800; 
GLsizei slgGL::g_height = 600;
GLboolean slgGL::g_fullscreen = FALSE;
GLfloat slgGL::g_light0_pos[4];
GLfloat slgGL::g_light1_pos[4];
float slgGL::g_z = 0.0f;
float slgGL::g_space = .15f;
float slgGL::g_factor = 1.0f;
int slgGL::g_phase_fix = TRUE;
float slgGL::g_factor2 = 1.0f;
int slgGL::g_freeze = 0;
GLfloat slgGL::g_inc;

// eye, center, up vector
pt3d slgGL::g_look_from( 0.0, 0.0, 10.0);
pt3d slgGL::g_look_to( 0.0, 0.0, 0.0 );
pt3d slgGL::g_head_up( 0.0, 1.0, 0.0 );
//cout<<typid(g_head_up).name()<<endl;

slgGL::slgGL(){
    cout<<"create openGL object"<<endl;
	// light 0 position
	GLfloat g_light0_pos_[] = { 2.0f, 1.2f, 4.0f, 1.0f };
    //hack to initialize arrays because i'm too lazy to go index by index
	memcpy(g_light0_pos,g_light0_pos_,4*sizeof(GLfloat));
	// light 1 parameter
	GLfloat g_light1_ambient_[] = { .2f, .2f, .2f, 1.0f };
    memcpy(g_light1_ambient,g_light1_ambient_,4*sizeof(GLfloat));
	GLfloat g_light1_diffuse_[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    memcpy(g_light1_diffuse,g_light1_diffuse_,4*sizeof(GLfloat));
	GLfloat g_light1_specular_[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    memcpy(g_light1_specular,g_light1_specular_,4*sizeof(GLfloat));
	GLfloat g_light1_pos_[] = { -2.0f, 0.0f, -4.0f, 1.0f };
    memcpy(g_light1_pos,g_light1_pos_,4*sizeof(GLfloat));

	// modelview stuff
	g_angle_y = 0.0f;
	g_inc = 0.0f;
	g_eye_y = 0;

	// WINDOW
	g_width = 800; 
	g_height = 600;

	// fullscreen
	g_fullscreen = FALSE;

	g_z = 0.0f;
	g_space = .15f;

	g_factor = 1.0f;
	g_phase_fix = TRUE;
	g_factor2 = 1.0f;
	g_freeze = 0;
}

slgGL::~slgGL(){
    cout<<"clean slgGL Object"<<endl;
}

void slgGL::initWindow(int argc, char *argv[], int width, int height, int x,int y){
    //TODO: put size as agrument
    cout<<"Initialize window"<<endl;
    // initialize GLUT
    glutInit( &argc, argv );
    // double buffer, use rgb color, enable depth buffer and alpha
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA );
    // initialize the window size
    glutInitWindowSize(width,height );
    // set the window postion
    glutInitWindowPosition( x, y);
    // create the window
    glutCreateWindow( "OpenGL Window" );
}

//-----------------------------------------------------------------------------
// Name: initialize_graphics( )
// Desc: sets initial OpenGL states and initializes any application data
//-----------------------------------------------------------------------------
void slgGL::initGraphics()
{
    cout<<"initialize graphics"<<endl;
    // set the GL clear color - use when the color buffer is cleared
    glClearColor( 0.0f, 0.0f,0.0f, 1.0f );
    // set the shading model to 'smooth'
    glShadeModel( GL_SMOOTH );
    // enable depth
    glEnable( GL_DEPTH_TEST );
    // set the front faces of polygons
    glFrontFace( GL_CCW );
    // set fill mode
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    // enable lighting
    glEnable( GL_LIGHTING );
    // enable lighting for front
    glLightModeli( GL_FRONT, GL_TRUE );
    // material have diffuse and ambient lighting 
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    // enable color
    glEnable( GL_COLOR_MATERIAL );
    // enable light 0
    glEnable( GL_LIGHT0 );

    // setup and enable light 1
    glLightfv( GL_LIGHT1, GL_AMBIENT, g_light1_ambient );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, g_light1_diffuse );
    glLightfv( GL_LIGHT1, GL_SPECULAR, g_light1_specular );
    glEnable( GL_LIGHT1 );
}

void slgGL::initUi(){
    // set the idle function - called when idle
    glutIdleFunc(slgGL::idleFunc);
    // set the display function - called when redrawing
    //glutDisplayFunc( slgGL::displayFunc );
    // set the reshape function - called when client area changes
    glutReshapeFunc( slgGL::reshapeFunc);
    // set the keyboard function - called on keyboard events
    glutKeyboardFunc( slgGL::keyboardFunc );
    // glut special keys
    glutSpecialFunc(slgGL::specialFunc);
    // set the mouse function - called on mouse stuff
    glutMouseFunc( slgGL::mouseFunc ); 
    
}

void slgGL::displayFunc(void (*myDisplayFunc)()){

    glutDisplayFunc( myDisplayFunc );
}

void slgGL::glutLoop(){
    glutMainLoop();
}
//-----------------------------------------------------------------------------
// Name: reshapeFunc( )
// Desc: called when window size changes
//-----------------------------------------------------------------------------
void slgGL::reshapeFunc( int w, int h )
{
    // map the view port to be the entire window
    glViewport( 0, 0, w, h );
    // set the matrix mode to project
    glMatrixMode( GL_PROJECTION );
    // load the identity matrix
    glLoadIdentity( );
    // create the viewing frustum
    //gluPerspective( 45.0, (GLfloat) w / (GLfloat) h, 1.0, 300.0 );
    gluPerspective( 45.0, (GLfloat) w / (GLfloat) h, .1, 100.0 );
    // set the matrix mode to modelview
    glMatrixMode( GL_MODELVIEW );
    // load the identity matrix
    glLoadIdentity( );

    changeLookAt(g_look_from,g_look_to, g_head_up );
    // position the view point
    /*gluLookAt( 0.0f, 3.5f * sin( g_eye_y ), 3.5f * cos( g_eye_y ), 
               0.0f, 0.0f, 0.0f, 
               0.0f, ( cos( g_eye_y ) < 0 ? -1.0f : 1.0f ), 0.0f );*/


    // set the position of the lights
    glLightfv( GL_LIGHT0, GL_POSITION, g_light0_pos );
    glLightfv( GL_LIGHT1, GL_POSITION, g_light1_pos );
}

void slgGL::specialFunc(int key, int x, int y){
    switch(key)
    {
        case GLUT_KEY_LEFT:
        cout<<"left"<<endl;
        break;
        case GLUT_KEY_RIGHT:
        cout<<"right"<<endl;
        break;
        case GLUT_KEY_UP:
        cout<<"up"<<endl;
        break;
        case GLUT_KEY_DOWN:
        cout<<"down"<<endl;
        break;
    }
}
//-----------------------------------------------------------------------------
// Name: keyboardFunc( )
// Desc: key event
//-----------------------------------------------------------------------------
void slgGL::keyboardFunc( unsigned char key, int x, int y )
{
    switch( key )
    {
    case 27:
    exit(0);
    break;

    
   /* case '[':
        g_eye_y -= .01f;
    break;
    case ']':
        g_eye_y += .01f;
    break;
    case 'h':
        //help();
    break;
    case '.':
        g_z += .1f;
        break;
    case ',':
        g_z -= .1f;
        break;
    case 'e':
        g_space *= 1.02f;
        break;
    case 'i':
        g_space *= .98f;
        break;
    case 'w':
        //g_wutrfall = !g_wutrfall;
        break;
    case 'd':
       // g_usedb = !g_usedb;
        break;
    case 'q':
        exit( 0 );
        break;
    case 'L':
    case 'l':
        g_look_from = pt3d( -1, 0, 0 );
        cerr << "Looking from the left" << endl;
        break;
    case 'R':
    case 'r':
        g_look_from = pt3d( 1, 0, 0 );
        cerr << "Looking from the right" << endl;
        break;
    case 'f':
        g_look_from = pt3d( 0, 0, 1 );
        cerr << "Looking from the front" << endl;
        break;
    case 'O':
    case 'o':
        g_look_from = pt3d( 1, 1, 1 );
        cerr << "Looking from the somewhere else" << endl;
        break;
    case 'p':
        g_phase_fix = !g_phase_fix;
        cerr << "phase fix: " << ( g_phase_fix ? "ON" : "OFF" ) << endl;
        break;
    case '_':
        g_factor -= .05f;
        if( g_factor < .1f )
            g_factor = .1f;
        break;
    case '-':
        g_factor2 -= .05f;
        if( g_factor2 < .1f )
            g_factor2 = .1f;
        break;
    case '+':
        g_factor += .05f;
        break;
    case '=':
        g_factor2 += .05f;
        break;
    case '1':
        g_factor = 1.0f;
        cerr << "time expansion factor RESET to 1.0" << endl;
        break;
    case '(':
        
        break;
    case ')':
        
        break;
    case '<':
        
        
        break;
    case '>':

    
        
        break;*/
    case 's':
    {
        static GLuint w, h;

        if( !g_fullscreen )
        {
            w = g_width;
            h = g_height;
            glutFullScreen();
        }
        else
            glutReshapeWindow( w, h );

        g_fullscreen = !g_fullscreen;
    }
    break;
    /*case 'g':
        g_freeze = !g_freeze;*/
    break;
    }

    // do a reshape since g_eye_y might have changed
    reshapeFunc( g_width, g_height );
    glutPostRedisplay( );
}


//-----------------------------------------------------------------------------
// Name: mouseFunc( )
// Desc: handles mouse stuff
//-----------------------------------------------------------------------------
void slgGL::mouseFunc( int button, int state, int x, int y )
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
}


//-----------------------------------------------------------------------------
// Name: idleFunc( )
// Desc: callback from GLUT
//-----------------------------------------------------------------------------
void slgGL::idleFunc( )
{
    // render the scene
    glutPostRedisplay( );
}

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

#include "slgGraphics.h"
#include <iterator>
using namespace std;

drawMode g_drawMode = kFilled;
rectMode g_rectMode = kCorner;

void renderBitmapString(
      float x,
      float y,
      float z,
      void *font,
      char *string) {

  char *c;
  glRasterPos3f(x, y,z);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

/*template <class TBuffer>
//void drawBuffer(TBuffer *buffer, int size, TBuffer maxHeight, float translateY){   
void Buffer(TBuffer *buffer, int size){   
   // default font
   void *font = GLUT_BITMAP_HELVETICA_12;
   glPushMatrix();
      TBuffer min, max, range;
      //cout<<sizeof(_buffer)<<" "<<sizeof(TBuffer)<<endl;

      min = *std::min_element(buffer,buffer+size);
      int minIdx = std::distance(buffer,std::min_element(buffer,buffer+size));
      max = *std::max_element(buffer,buffer+size);
      int maxIdx = std::distance(buffer,std::max_element(buffer,buffer+size));

      range = max-min;
      float scale = (float) 2./range;
      float scaleX = (float) 2./size;
      //std::cout<<"max scaled: "<<max*scale<<endl;
      //std::cout<<"max idx scaled: "<<maxIdx*scaleX<<endl;

      glTranslatef(0.0,1.0-max*scale,0.0);
      glTranslatef(-1.0,0,0);
      glScalef(2.,1,1);

      // draw grid
      //Grid(0,min,size,range,5,5);
      // draw axes
      glBegin(GL_LINES);
         glVertex2f(0,0);
         glVertex2f(1,0);
         glVertex2f(0,0);
         glVertex2f(0,1);
      glEnd();

      // draw function
      glColor3f(1,0,0);
      glPointSize(2);


      glBegin(GL_LINE_STRIP);
      //glBegin(GL_POINTS);
      for (int i=0;i<size;i++){         
        glVertex2f((float)i/size,buffer[i]*scale);
        //glVertex2f((float)i/size,(float)i/size);
      }
      glEnd();

      string message="buffer plot";
      glColor3f(1,1,1);
      renderBitmapString(0.9, 0.9f, 0.0f, (void *)font ,(char*)message.c_str());

      // print reference values
      glRasterPos2f(0.01,0);
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0');
      glRasterPos2f(0.01,0.93);
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '1');
      string minusone="-1";
      renderBitmapString(0.01f, -1.0, 0, GLUT_BITMAP_HELVETICA_18 ,(char*)minusone.c_str());
      string xmax=std::to_string(size);
      renderBitmapString(0.92, 0, 0, GLUT_BITMAP_HELVETICA_18 ,(char*)xmax.c_str());
      string xmax2=std::to_string(size/2);
      renderBitmapString(0.5, 0, 0, GLUT_BITMAP_HELVETICA_18 ,(char*)xmax2.c_str());

      string ymax="max:"+std::to_string(max);
      renderBitmapString(maxIdx*scaleX, max*scale-0.075, 0, GLUT_BITMAP_HELVETICA_12 ,(char*)ymax.c_str());
      string ymin="min:"+std::to_string(min);
      renderBitmapString(minIdx*scaleX, min*scale, 0, GLUT_BITMAP_HELVETICA_12 ,(char*)ymin.c_str());
      
      //ticks
      glPointSize(6);
      glBegin(GL_POINTS);
        glVertex2f(0,1);
        glVertex2f(0,-1);
        glVertex2f(0.5,0);
        glVertex2f(1,0);
      glEnd();

      glPointSize(5);
      glBegin(GL_POINTS);
        glVertex2f(maxIdx*scaleX,max*scale);
      glEnd();
      

   glPopMatrix();
}
// template declarations to please compiler
//template void drawBuffer(float *buffer, int size, float maxHeight, float translateY);
//template void drawBuffer(double *buffer, int size, double maxHeight, float translateY);
template void Buffer(float *buffer, int size);
template void Buffer(double *buffer, int size);*/

void Buffer1D(SAMPLE *buffer, const int size, const float min, const float max, const LineMode line_mode){
  glPushMatrix();
    float range;
    //min = *std::min_element(buffer,buffer+size);
    int minIdx = std::distance(buffer,std::min_element(buffer,buffer+size));
    //max = *std::max_element(buffer,buffer+size);
    int maxIdx = std::distance(buffer,std::max_element(buffer,buffer+size));
    range = max-min;

    // scale y axis
    float scale = (float) 2./range;

    // scale x axis
    float scaleX = (float) 2./size;

    glTranslatef(0.0,1.0-max*scale,0.0);
    glTranslatef(-1.0,0,0);
    glScalef(2.,1,1);

    // draw axes
    glLineWidth(1.0);
    glBegin(GL_LINES);
      glVertex2f(0,0);
      glVertex2f(1,0);
      glVertex2f(0.00,-1);
      glVertex2f(0.00,1.0);
    glEnd();

    // draw function
    glColor3f(1,0,0);
    glPointSize(2);

    switch(line_mode){
      case 0:
        glBegin(GL_LINE_STRIP);
        for (int i=0;i<size;i++){
          glVertex2f((float)i/size,buffer[i]*scale);
         //glVertex2f((float)i/size,(float)i/size);
        }
        glEnd();
        break;

      case 1:
        glBegin(GL_LINES);
        for (int i=0;i<size;i++){
          glVertex2f((float)i/size,0);
          glVertex2f((float)i/size,buffer[i]*scale);
         //glVertex2f((float)i/size,(float)i/size);
        }
        glEnd();

      case 2:
        glBegin(GL_POINTS);
        for (int i=0;i<size;i++){
          glVertex2f((float)i/size,buffer[i]*scale);
         //glVertex2f((float)i/size,(float)i/size);
        }
        glEnd();
        break;
    }

    // default font
    void *font = GLUT_BITMAP_HELVETICA_12;
  
    string message="buffer plot";
    glColor3f(1,1,1);
    renderBitmapString(0.9, 0.9f, 0.0f, (void *)font ,(char*)message.c_str());

    // print reference values
    glRasterPos2f(0.01,0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0');
    glRasterPos2f(0.01,1*scale);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '1');
    string minusone="-1";
    renderBitmapString(0.01f, -1.0*scale, 0, GLUT_BITMAP_HELVETICA_18 ,(char*)minusone.c_str());
    string xmax=std::to_string(size);
    renderBitmapString(0.92, 0, 0, GLUT_BITMAP_HELVETICA_18 ,(char*)xmax.c_str());
    string xmax2=std::to_string(size/2);
    renderBitmapString(0.5, 0, 0, GLUT_BITMAP_HELVETICA_18 ,(char*)xmax2.c_str());
    /*
    string ymax="max:"+std::to_string(max);
    renderBitmapString(maxIdx*scaleX, max-0.05, 0, GLUT_BITMAP_HELVETICA_12 ,(char*)ymax.c_str());
    string ymin="min:"+std::to_string(min);
    renderBitmapString(minIdx*scaleX, min, 0, GLUT_BITMAP_HELVETICA_12 ,(char*)ymin.c_str());*/

    //ticks
    glPointSize(6);
    glBegin(GL_POINTS);
      glVertex2f(0,1);
      glVertex2f(0,-1);
      glVertex2f(0.5,0);
      glVertex2f(1,0);
    glEnd();
    
  glPopMatrix(); 
}

void Buffer2D(SAMPLE **buffer, const int n_rows, const int n_cols, const float min, const float max){
  glPushMatrix();
    float range;
    //min = *std::min_element(buffer,buffer+size);
    int minIdx = std::distance(buffer,std::min_element(buffer,buffer+n_cols));
    //max = *std::max_element(buffer,buffer+size);
    int maxIdx = std::distance(buffer,std::max_element(buffer,buffer+n_cols));
    range = max-min;

    // scale y axis
    float scale = (float) 2./range;

    // scale x axis
    float scaleX = (float) 2./n_cols;

    glTranslatef(0.0,1.0-max*scale,0.0);
    glTranslatef(-1.0,0,0);
    glScalef(2.,1,1);

    // draw axes
    glLineWidth(1.0);
    glBegin(GL_LINES);
      glVertex2f(0,0);
      glVertex2f(1,0);
      glVertex2f(0.00,-1);
      glVertex2f(0.00,1.0);
    glEnd();

    // draw function
    glColor3f(1,0,0);
    glPointSize(5);

    glBegin(GL_POINTS);
      for (int i=0;i<n_rows;i++){
        for (int j =0;j<n_cols;j++){
          glColor4f(1,0,0,buffer[j][i]);
          // xscale has be glscaled to 1 so don't use scaleX
          glVertex2f((float)j/n_cols,i*scale);
        }
      }
    glEnd();

    //ticks
    glPointSize(6);
    glBegin(GL_POINTS);
      glVertex2f(0,1);
      glVertex2f(0,-1);
      glVertex2f(0.5,0);
      glVertex2f(1,0);
    glEnd();
    
  glPopMatrix(); 
}

//-----------------------
void Axis(float size)
{
    // save the current transformation
    glPushMatrix();
    glLineWidth(2);
      glBegin( GL_LINES );
      // x axis - red
      glColor4f( 1, 0, 0, 1 );
      glVertex3f( 0, 0, 0 );
      glVertex3f( size, 0, 0 );

      // y axis - green
      glColor4f( 0, 1, 0, 1 );
      glVertex3f( 0, 0, 0 );
      glVertex3f( 0, size, 0 );

      // z axis - blue
      glColor4f( 0, 0, 1, 1 );
      glVertex3f( 0, 0, 0 );
      glVertex3f( 0, 0, size );   

    glEnd();

    // restore state
    glPopMatrix();

    //back to white color
    glColor4f(1.0f,1.0f,1.0f,1.0f);
}

//--------------------------
void SnowMan(float size) {
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
    glTranslatef(0.0f ,size*0.75f, size*0.0f);
    glutSolidSphere(size*0.75f,20,20);


// Draw Head
    glTranslatef(0.0f, size*1.0f, 0.0f);
    glutSolidSphere(size*0.25f,20,20);

// Draw Eyes
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(size*0.05f, size*0.10f, size*0.18f);
    glutSolidSphere(size*0.05f,10,10);
    glTranslatef(-size*0.1f, 0.0f, 0.0f);
    glutSolidSphere(size*0.05f,10,10);
    glPopMatrix();

// Draw Nose
    glColor3f(1.0f, 0.5f , 0.5f);
    glRotatef(0.0f,1.0f, 0.0f, 0.0f);
    glutSolidCone(size*0.08f,size*0.5f,10,2);
    glPopMatrix();
}

// Draw Ground
void Ground(float size){
    glPushMatrix();
    //glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(-size, 0.0f, -size);
        glVertex3f(-size, 0.0f, size);
        glVertex3f( size, 0.0f,  size);
        glVertex3f( size, 0.0f, -size);
    glEnd();
    glPopMatrix();
}

void GridPoints(int xPointCount, int yPointCount, double xSpacing, double ySpacing)
{
    glPushMatrix();
    //glLineWidth(5);
    double width = xSpacing * (xPointCount-1); double height = ySpacing * (yPointCount-1); double minX = -width/2;
    double minY = -height/2;
    glBegin(GL_POINTS);
    for(int i=0; i<xPointCount; i++) {
        for(int j=0; j<yPointCount; j++) {
            double x = minX + i*xSpacing;
            double y = minY + j*ySpacing;
            double z = 0;
            glVertex3f(x, y, z);
        }
    }
    glEnd();
    glPopMatrix();
}

void Grid(const float x, const float y, const float width, const float height, const unsigned int num_rows, const unsigned int num_columns){
  
  // row settings
//  unsigned int num_rows = 5; 
  float y_increment = (float) height/num_rows;
  float y_current = y;
  // column settings
  //unsigned int num_columns = 4;
  float x_increment = (float) width/num_columns, x_current = x;

  glPushMatrix();
  glBegin(GL_LINES);
    for (int i =0;i<num_rows+1;i++){
        glVertex2f(x,y_current);
        glVertex2f(x+width,y_current);
        y_current += y_increment;
    }
    for (int i = 0;i<num_columns+1;i++){
      glVertex2f(x_current,y);
      glVertex2f(x_current,y+height);
      x_current += x_increment;

    }
  glEnd();
  glPopMatrix();
}

void BitmapString( GLfloat x, GLfloat y, GLfloat z, const char * str, GLfloat scale = 1.0f )
{
    GLint len = strlen( str ), i;

    glPushMatrix();
    glTranslatef( x, y, z );
    glScalef( .001f * scale, .001f * scale, .001f * scale );

    for( i = 0; i < len; i++ )
        glutStrokeCharacter( GLUT_STROKE_ROMAN, str[i] );
    
    glPopMatrix();
}

void Circle(float x,float y, float radius){
    // draw:
    
    glPushMatrix();
        glTranslatef(x, y, 0);
        glScalef(radius, radius, 1);
        glBegin( (g_drawMode == kFilled) ? GL_POLYGON : GL_LINE_LOOP);
        //glBegin(GL_POLYGON);
        float angle = 0.0f;
        float angleAdder = 2 * M_PI / (float)CIRC_RESOLUTION;
        for (float i = 0; i < CIRC_RESOLUTION; i++){
            glVertex2f( cos(angle), sin(angle));
            angle += angleAdder;
        }
        glEnd();
    glPopMatrix();

    // back to normal, if smoothness is on
}

void Ellipse(float x,float y, float width, float height){
    // draw:
    
    glPushMatrix();
        glTranslatef(x, y, 0);
        glScalef(width, height, 1);
        glBegin( (g_drawMode == kFilled) ? GL_POLYGON : GL_LINE_LOOP);
        //glBegin(GL_POLYGON);
        float angle = 0.0f;
        float angleAdder = 2 * M_PI / (float)CIRC_RESOLUTION;
        for (float i = 0; i < CIRC_RESOLUTION; i++){
            glVertex2f( cos(angle), sin(angle));
            angle += angleAdder;
        }
        glEnd();
    glPopMatrix();

    // back to normal, if smoothness is on
}

void Line(float x1,float y1,float x2,float y2){
// draw:
    glPushMatrix();
    glBegin( GL_LINES );
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
    glEnd();
    glPopMatrix();
}

void Rectangle(float x,float y,float w,float h){
    glPushMatrix();
    // define center of rectangle
    if (g_rectMode == kCenter){
        glBegin( (g_drawMode == kFilled) ? GL_QUADS : GL_LINE_LOOP);
            glVertex2f(x-w/2,y-h/2);
            glVertex2f(x+w/2,y-h/2);
            glVertex2f(x+w/2,y+h/2);
            glVertex2f(x-w/2,y+h/2);
        glEnd();
    } else {
      // define bottom left
        glBegin( (g_drawMode == kFilled) ? GL_QUADS : GL_LINE_LOOP);
        glVertex2f(x,y);
        glVertex2f(x+w,y);
        glVertex2f(x+w,y+h);
        glVertex2f(x,y+h);
        glEnd();
    }
    glPopMatrix();
}

void Triangle(float x1, float y1, float x2, float y2, float x3, float y3){
  glPushMatrix();
    glBegin((g_drawMode == kFilled) ? GL_TRIANGLES : GL_LINE_LOOP);
      glVertex2f(x1,y1);
      glVertex2f(x2,y2);
      glVertex2f(x3,y3);
    glEnd();
  glPopMatrix();

}

void Pulse(){
    // animation parameters
    static float angle = 0;
    angle = angle + 0.1;
    if ( angle > 360) angle -= 360;
    //g_counter = g_counter + 0.1;
     glPushMatrix();
        float osc_radius = 1/4.+ 0.1*sin(angle/100.);
        g_drawMode = kOutline;
        Circle(0,0,osc_radius*2);
        Circle(0,0,osc_radius*1.5);
        g_drawMode = kFilled;
        Circle(0,0,1/4.);
    glPopMatrix();
    
}

void go2D(){
  /*
   *  Disable depth test and lighting for 2D elements
   */
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  int w = glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  // Prevent a divide by zero, when window is too short
  // (you cant make a window of zero width).
  if(h == 0)
    h = 1;
  
  // aspect ratio (keep proportions when resize)
  float aspect = (float)w/(float)h;
  //float aspect = 1.0;
  // Set clipping area's left, right, bottom, top (default -1,1,-1,1)
  if (w>h)
    gluOrtho2D(-1.0*aspect, -1.0*aspect, -1.0, 1.0);
  else
    gluOrtho2D(-1.0, 1.0, -1.0/aspect, 1.0/aspect);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void go3D(){
  /*
   *  Enable lighting and the z-buffer
   */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  int w = glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,1.0f,1000.0f); 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

glm::vec3 GetOGLPos(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
 
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
 
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
 
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
 
    return glm::vec3(posX, posY, posZ);
}

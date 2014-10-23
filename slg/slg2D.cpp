#include "slg2D.h"
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

template <class TBuffer>
//void drawBuffer(TBuffer *buffer, int size, TBuffer maxHeight, float translateY){   
void drawBuffer(TBuffer *buffer, int size){   
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

      // draw axes
      glLineWidth(1.0);
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
template void drawBuffer(float *buffer, int size);
template void drawBuffer(double *buffer, int size);

template <class TBuffer> void drawBuffer(TBuffer *buffer, int size, TBuffer min, TBuffer max){
  glPushMatrix();
    TBuffer range;
    //cout<<sizeof(_buffer)<<" "<<sizeof(TBuffer)<<endl;

    //min = *std::min_element(buffer,buffer+size);
    int minIdx = std::distance(buffer,std::min_element(buffer,buffer+size));
    //max = *std::max_element(buffer,buffer+size);
    int maxIdx = std::distance(buffer,std::max_element(buffer,buffer+size));

    range = max-min;
    float scale = (float) 2./range;
    float scaleX = (float) 2./size;

    glTranslatef(0.0,1.0-max*scale,0.0);
    glTranslatef(-1.0,0,0);
    glScalef(2.,1,1);

    // draw axes
    glLineWidth(1.0);
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

    // default font
    void *font = GLUT_BITMAP_HELVETICA_12;
  
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
template void drawBuffer(float *buffer, int size, float min, float max);
template void drawBuffer(double *buffer, int size, double min, double max);

void drawAxis(float size)
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

    //back to color
    glColor4f(1.0f,1.0f,1.0f,1.0f);
}

void drawSnowMan(float size) {
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
void drawGround(float size){
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

void drawGrid(int xPointCount, int yPointCount, double xSpacing, double ySpacing)
{
    glPushMatrix();
    //glLineWidth(5);
    double width = xSpacing * (xPointCount-1); double height = ySpacing * (yPointCount-1); double minX = -width/2;
    double minY = -height/2;
    glBegin(GL_LINES);
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

void drawString( GLfloat x, GLfloat y, GLfloat z, const char * str, GLfloat scale = 1.0f )
{
    GLint len = strlen( str ), i;

    glPushMatrix();
    glTranslatef( x, y, z );
    glScalef( .001f * scale, .001f * scale, .001f * scale );

    for( i = 0; i < len; i++ )
        glutStrokeCharacter( GLUT_STROKE_ROMAN, str[i] );
    
    glPopMatrix();
}

void circle(float x,float y, float radius){
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

void line(float x1,float y1,float x2,float y2){
// draw:
    glPushMatrix();
    glBegin( GL_LINES );
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
    glEnd();
    glPopMatrix();
}

void rect(float x,float y,float w,float h){
    glPushMatrix();
    if (g_rectMode == kCenter){
        glBegin( (g_drawMode == kFilled) ? GL_QUADS : GL_LINE_LOOP);
            glVertex2f(x-w/2,y-h/2);
            glVertex2f(x+w/2,y-h/2);
            glVertex2f(x+w/2,y+h/2);
            glVertex2f(x-w/2,y+h/2);
        glEnd();
    } else {
        glBegin( (g_drawMode == kFilled) ? GL_QUADS : GL_LINE_LOOP);
        glVertex2f(x,y);
        glVertex2f(x+w,y);
        glVertex2f(x+w,y+h);
        glVertex2f(x,y+h);
        glEnd();
    }
    glPopMatrix();
}


void renderPulse(){
    // animation parameters
    static float angle = 0;
    angle = angle + 0.1;
    if ( angle > 360) angle -= 360;
    //g_counter = g_counter + 0.1;
     glPushMatrix();
        // Draw axis centered at the origin
        //drawAxis();
        //circle(0,0,1);
        //drawAxis();
        //float counter=0;
        //float radius = sin(g_counter);
        float osc_radius = 1/4.+ 0.1*sin(angle/100.);
        //glColor4f( 0, 0, 1, 0.6);
        g_drawMode = kOutline;
        //glRotatef( angle, 1, 0, 0 );
        circle(0,0,osc_radius*2);
        //glRotatef( angle, 0, 1, 0 );
        circle(0,0,osc_radius*1.5);
        g_drawMode = kFilled;
        //glRotatef( angle, 1, 0, 0 );
        //glRotatef( angle, 0, 1, 0 );
        circle(0,0,1/4.);
        //rect(0,0,0.5,0.5);
        //line(0,0,-1,0);
    glPopMatrix();
    
}




#include "slg2D.h"
#include <iterator>
using namespace std;

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
      renderBitmapString(maxIdx*scaleX, max-0.05, 0, GLUT_BITMAP_HELVETICA_12 ,(char*)ymax.c_str());
      string ymin="min:"+std::to_string(min);
      renderBitmapString(minIdx*scaleX, min, 0, GLUT_BITMAP_HELVETICA_12 ,(char*)ymin.c_str());
      
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

    string ymax="max:"+std::to_string(max);
    renderBitmapString(maxIdx*scaleX, max-0.05, 0, GLUT_BITMAP_HELVETICA_12 ,(char*)ymax.c_str());
    string ymin="min:"+std::to_string(min);
    renderBitmapString(minIdx*scaleX, min, 0, GLUT_BITMAP_HELVETICA_12 ,(char*)ymin.c_str());

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




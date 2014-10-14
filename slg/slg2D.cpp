#include "slg2D.h"

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
void drawBuffer(TBuffer *buffer, int size, TBuffer maxHeight, float translateY){   
   // default font
   void *font = GLUT_BITMAP_HELVETICA_12;
   glPushMatrix();
      string message="buffer plot";
      glColor3f(1,1,1);
      renderBitmapString(0.5, 0.9f, 0.0f, (void *)font ,(char*)message.c_str());

      //glTranslatef(-1.0,0,0);
      //glScalef(2.0,1./height,1.);
      
      /*glRasterPos2f(0.01,0);
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '0');
      glRasterPos2f(0.01,1);
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '-1');
      string unity="-1";
      renderBitmapString(0.0f, 1.0, 0, GLUT_BITMAP_HELVETICA_12 ,(char*)unity.c_str());
      string stringHeight = to_string(height);
      renderBitmapString(0.0f, height-0.2, 0, GLUT_BITMAP_HELVETICA_12 ,(char*)stringHeight.c_str());
      string stringHeight2 = "-";
      renderBitmapString(0.0f, height-0.05, 0, GLUT_BITMAP_HELVETICA_12 ,(char*)stringHeight2.c_str());*/
      TBuffer range;
      range = 2*maxHeight;
      
      float scale = (float) 2./range;

      glTranslatef(-1.0,0.0,0.0);
      glTranslatef(0.0,translateY*scale,0.0);
      glScalef(2.,1,1);
      // draw axes
      glLineWidth(1);
      glBegin(GL_LINES);
         glVertex2f(0,0);
         glVertex2f(1,0);
         glVertex2f(0,0);
         glVertex2f(0,1*scale);
      glEnd();

      glPointSize(5);
      glBegin(GL_POINTS);
        glVertex2f(0,maxHeight*scale);
        glVertex2f(0,maxHeight*scale);
        glVertex2f(0,1);
        glVertex2f(0,0);
        glVertex2f(1,0);
      glEnd();



      // draw function
      glColor3f(1,0,0);
      glPointSize(2);

      for (int i=0;i<size;i++){
         //glBegin(GL_LINE_STRIP);
         glBegin(GL_POINTS);
            glVertex2f((float)i/size,buffer[i]*scale);
         glEnd();
      }
   glPopMatrix();
}
// template declarations to please compiler
template void drawBuffer(float *buffer, int size, float maxHeight, float translateY);
template void drawBuffer(double *buffer, int size, double maxHeight, float translateY);



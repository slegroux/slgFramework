#include "slgGUI.h"

class Widget
{
public:
   Widget(int x, int y, int w, int h)
   : fX(x)
   , fY(y)
   , fW(w)
   , fH(h)
   {
   }
   
   bool Hit(int x, int y)
   {
      
      if ((x >= fX && x <= fX + fW) && (gHeight - y >= fY && gHeight - y <= fY + fH))
      {  
         return true;
      }
      else
      {
         return false;
      }
      
   }
   
   int X() const { return fX; }
   int Y() const { return fY; }
   int W() const { return fW; }
   int H() const { return fH; }
   
protected:
   int fX, fY, fW, fH;
};

class Slider : public Widget
{
public:
   Slider(int x, int y, int w, int h)
   : Widget(x,y,w,h)
   {
      fTouched = false;
      fVal = 0.f;
   }
   
   void Draw()
   {
      go2d();
      
      glPushMatrix();
      glLineWidth(2);
      glColor4f(1,1,1,1);
      glBegin(GL_LINE_STRIP);
      glVertex2f(fX + fVal * fW,  fY + 2);
      glVertex2f(fX + fVal * fW, fY + fH - 2);
      glEnd();
      glPopMatrix();
      
      glColor4f(0,0,0,1);
      glRecti(fX+2, fY+2, fX + fW - 2, fY + fH - 2);
      glColor4f(1,0,0,1);
      glRecti(fX, fY, fX + fW, fY + fH);
      
      
      
      //glScalef(1, fW/fH,1);
      
      //glPushMatrix();
      //glTranslatef(gMouseOriginX/(float)gWidth, 0, 0);
      //glutWireSphere(fH, 5, 3);
      //glPopMatrix();
      
      go3d();
   }
   

   
   bool Touched() const { return fTouched; }
   
   void Touch(int x, int y)
   {
      fTouched = true;
      
      int localX = std::max(x - fX, 0);
      
      fVal = std::min(localX, fW) / (float)fW;
   }
   
   void UnTouch()
   {
      fTouched = false;
   }
   
   void SetValue(float val)
   {
      fVal = val;
      if (fVal < 0) val = 0;
      if (fVal > 1) val = 1;
   }
   
   float Value() const { return fVal; }
   
private:
   float fVal;
   bool fTouched;
};


class ToggleButton : public Widget
{
public:
   ToggleButton(int x, int y, int w, int h)
   : Widget(x,y,w,h)
   , fToggled(false)
   {
   }
   
   void Draw()
   {
      go2d();

      if (fToggled)
      {
         glPushMatrix();
         glColor4f(1,1,1,1);
         glBegin(GL_LINES);
         glVertex2f(fX+2,  fY+2);
         glVertex2f(fX + fW - 2,  fY + fH - 2);
         glVertex2f(fX+2,  fY + fH-2);
         glVertex2f(fX + fW - 2,  fY + 2);
         glEnd();
         glPopMatrix();
      }

      glColor4f(0,0,0,1);
      glRecti(fX+2, fY+2, fX + fW - 2, fY + fH - 2);
      glColor4f(1,0,0,1);
      glRecti(fX, fY, fX + fW, fY + fH);

      go3d();
   }
   
   void Toggle()
   {
      fToggled = !fToggled;
   }
   
   bool Toggled() const { return fToggled; }
   
private:
   bool fToggled;
};
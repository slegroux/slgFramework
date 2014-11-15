#include "slgToggleButton.h"


slgToggleButton::slgToggleButton(const float x, const float y, const float w,const float h,void (*CallbackOn)(void),void (*CallbackOff)(void)){
   _x = x;
   _y = y;
   _w = w;
   _h = h;
   _toggled = false;
   _CallbackON = CallbackOn;
   _CallbackOFF = CallbackOff;

}

slgToggleButton::~slgToggleButton(){

}

bool slgToggleButton::Hit(float x, float y){
   // if mouse in the toggle area
   std::cout<<"x: "<<x<<" y: "<<y<<std::endl;
   if ((x >= _x && x <= _x + _w)&&(y >= _y && y <= _y +_h)){
      return(true);
   }
   else
      return(false);
}

void slgToggleButton::Draw(){

   if (_toggled)
   {
      glPushMatrix();
      glColor4f(1,1,1,1);
      //draw cross
      glBegin(GL_LINES);
         glVertex2f(_x,  _y);
         glVertex2f(_x + _w, _y + _h);
         glVertex2f(_x,  _y + _h);
         glVertex2f(_x + _w, _y);
      glEnd();
      glPopMatrix();
   }

   glColor4f(1,1,1,1);
   g_drawMode = kOutline;
   Rectangle(_x, _y, _w,_h);

}

void slgToggleButton::Toggle()
{

   _toggled = !_toggled;
   if (_toggled == false)
      _CallbackOFF();
   if (_toggled == true)
      _CallbackON();
}

bool slgToggleButton::Toggled(){ 
   return _toggled; 
}

float slgToggleButton::get_x(){return _x;}
float slgToggleButton::get_y(){return _y;}
float slgToggleButton::get_h(){return _h;}
float slgToggleButton::get_w(){return _w;}

   
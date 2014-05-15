/* Copyright 2001,2002 Matt Flax <flatmax@ieee.org>
   This file is part of the MFFM FFTw Wrapper library.

   MFFM MFFM FFTw Wrapper library is free software; you can 
   redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   MFFM FFTw Wrapper library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You have received a copy of the GNU General Public License
   along with the MFFM FFTw Wrapper library
*/
#include "realFFT.h"

#include <iostream>
#include <math.h>

realFFT::
realFFT(void) {
  //  cout <<"realFFT init:"<<this<<std::endl;
  data=NULL;
  createPlan();
}

realFFT::
realFFT(realFFTData *d) {
  //  cout <<"realFFT init:"<<this<<std::endl;
  data=d;
  createPlan();
}

realFFT::
~realFFT(){
  destroyPlan();
}

void realFFT::
destroyPlan(void){
  if (data){
    fftw_destroy_plan(fwdPlan);
    fftw_destroy_plan(invPlan);
  }
}

void realFFT::
createPlan(void){
  if (data){
    //fftw3
    fwdPlan=fftw_plan_r2r_1d(data->getSize(), data->in, data->out, FFTW_R2HC, PLANTYPE);
    invPlan=fftw_plan_r2r_1d(data->getSize(), data->in, data->out, FFTW_HC2R, PLANTYPE);
  }
}

void realFFT::
switchData(realFFTData *d){
  destroyPlan();
  data=d;
  createPlan();
}

void realFFT::
fwdTransform(){
  if (!data)
    std::cerr<<"realFFT::fwdTransform : data not present, please switch data"<<std::endl;
  else
    fftw_execute(fwdPlan);
}

void realFFT::
invTransform(){
  if (!data)
    std::cerr<<"realFFT::invTransform : data not present, please switch data"<<std::endl;
  else
    fftw_execute(invPlan);
}

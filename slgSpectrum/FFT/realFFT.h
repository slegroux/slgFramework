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
#ifndef REALFFT_H_
#define REALFFT_H_

#include "realFFTData.h"
#include <fftw3.h>

#include <iostream>
using namespace std;

class realFFTData;

#define PLANTYPE FFTW_ESTIMATE

///class realFFT controls fftw plans and executes fwd/inv transforms
class realFFT {
  /// The fwd/inv plans
  fftw_plan fwdPlan, invPlan;

  /// Method to create the plans
  void createPlan(void);
  /// Method to destroy the plans
  void destroyPlan(void);
protected:
  /// The pointer to the relevant data
  realFFTData *data;
public:
  /// fft init ... don't forget to associate data using switchData
  realFFT(void);
  /// fft init ... data pointed to by 'd'
  realFFT(realFFTData *d);
  /// fft deconstructor
  ~realFFT(void);

  /// Use this to change associated fft data (for fft'ing)
  void switchData(realFFTData *d);

  /// Forward transform the data (in to out)
  void fwdTransform(); // Forward fft
  /// Inverse transform the data (out to in)
  void invTransform(); // Inverse fft
};
/** \example realFFTExample.cc
 * This is an example of how to use the class.
 * It transforms a sine tone stored in the .dat file and saves the
 * in, out, and power_spectrum results of using the class
 */
#endif // REALFFT_H_

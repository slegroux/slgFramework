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
#ifndef REALFFTDATA_H_
#define REALFFTDATA_H_

#include "realFFT.h"
#include <fftw3.h>

#include <iostream>
using namespace std;

#ifndef fftw_real
#define fftw_real double
#endif

/// class realFFTData controls and manipulates fft data
class realFFTData {
  /// Var used to specify if the memory was allocated by the realFFTData class
  int deleteInOutMemory;
public:
  /// Specifies the size of the data array
  int size;
  /// Specifies the minimum and maximum power bins as used in the methods findMaxMinPowerBins and compPowerSpec
  int minPowerBin, maxPowerBin;
  /// the input, output and power_spectrum arrays
  fftw_real *in, *out, *power_spectrum; //, *powerDeriv; power deriv. removed for now
  /// The total power (summed) of the power spectrum as used in the method compPowerSpec
  double totalPower;

  /// All memory to be allocated internally
  realFFTData(int sz);
  /// input and output data arrays are to be allocated by another process
  realFFTData(int sz, fftw_real*inp, fftw_real*outp);
  /// Deconstructor
  ~realFFTData(void);

  /// Limits the maximum to 'lim' and returns the last fft bin with max
  int limitHalfPowerSpec(double lim); 

  /// Returns the number of elements in the input and output arrays
  int getSize(void){return size;}
  /// Returns the number of elements in the power spectrum array
  int getHalfSize(void){ if (!(size%2)) return size/2; else return size/2+1;}

  /// Returns the maximum input variable
  fftw_real findMaxIn(void);
  /// Fills the max and min power spectrum bins
  void findMaxMinPowerBins(void);

  /// This function computes the power spectrum and returns the max bin
  int compPowerSpec();
  /// This function computes the square root of the power spectrum and returns the max bin
  int sqrtPowerSpec();

  //  int powerSpecDeriv(); // Find the derivative of the power spectrum

  /// This function zeros the output data array (out)
  void zeroFFTData(void);
};
#endif // REALFFTDATA_H_

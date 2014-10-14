from numpy import fft
import pylab

#fundamental frequency
f = 2000
#sampling frequency
fs = 8000.0
Ts = 1/fs
# 1 sec of signal
t = arange(0,1,Ts)

#vectorized sin
fx = sin(2*pi*f*t)

#iterative sin
ffx=[]
for i in range(0,8000):
	ffx.append(sin(2*pi*f*i/fs))

# normalize by 2/Nsamples (real only has half of samples hence the 2)
#myFFt = (2/8000.)*abs(fft.rfft(fx))
#iterative sin
myFFT= (2/8000.)*abs(fft.rfft(ffx))
plot(myFFT)

savetxt('function.out',ffx)
savetxt('fft.out',myFFT)
myFFt=loadtxt('fft.out')
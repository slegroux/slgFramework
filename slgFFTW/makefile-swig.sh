g++ -O2 -fPIC -c realFFTW.cpp
g++ -O2 -fPIC -c realFFTW_wrap.cxx -I/usr/local/Cellar/python/2.7.8_1/Frameworks/Python.framework/Versions/Current/include/python2.7/
#g++ -lpython -shared -dynamiclib realFFTW.o realFFTW_wrap.o -o _realFFTW.dylib
g++ -lpython -shared realFFTW.o -L/usr/local/lib/ realFFTW_wrap.o -o _realFFTW.dylib -lfftw3
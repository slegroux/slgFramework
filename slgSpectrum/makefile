
CXX=g++
INCLUDES=

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
FLAGS=-D__LINUX_ALSASEQ__ -D__UNIX_JACK__ -c
LIBS=-lasound -lpthread -ljack -lstdc++ -lm
endif
ifeq ($(UNAME), Darwin)
FLAGS=-D__MACOSX_CORE__ -c
LIBS=-framework CoreAudio -framework CoreMIDI -framework CoreFoundation \
	-framework IOKit -framework Carbon -lstdc++ -lm -lfftw3
endif


OBJS= RtAudio.o slgAudio.o chuck_fft.o realFFTData.o realFFT.o slgSpectrum.o test.o


test: $(OBJS)
	$(CXX) -o test $(OBJS) $(LIBS)

test.o: test.cpp
	$(CXX) $(FLAGS) test.cpp

RtAudio.o: RtAudio/RtAudio.h RtAudio/RtAudio.cpp RtAudio/RtError.h
	$(CXX) $(FLAGS) RtAudio/RtAudio.cpp

slgAudio.o: slgAudio.h slgAudio.cpp
	$(CXX) $(FLAGS) slgAudio.cpp

slgSpectrum.o: slgSpectrum.h slgSpectrum.cpp
	$(CXX) $(FLAGS) slgSpectrum.cpp

chuck_fft.o: FFT/chuck_fft.h FFT/chuck_fft.c
	$(CXX) $(FLAGS) $(INC_PATH) FFT/chuck_fft.c

realFFT.o: FFT/realFFT.h FFT/realFFT.cpp
	$(CXX) $(FLAGS) FFT/realFFT.cpp

realFFTData.o: FFT/realFFTData.h FFT/realFFTData.cpp
	$(CXX) $(FLAGS) FFT/realFFTData.cpp


clean:
	rm -f *~ *# *.o test

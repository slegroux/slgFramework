CXX=g++
INCLUDES=

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
FLAGS=-D__LINUX_ALSASEQ__ -D__UNIX_JACK__ -c
LIBS=-lasound -lpthread -ljack -lstdc++ -lm -lstk
endif
ifeq ($(UNAME), Darwin)
FLAGS=-D__MACOSX_CORE__ -c -w
LIBS=-framework CoreAudio -framework CoreMIDI -framework CoreFoundation \
	-framework OpenGL -framework GLUT \
	-framework IOKit -framework Carbon \
	-framework Foundation -framework AppKit \
	-lstdc++ -lm #-lgsl
endif

# this is needed by some oscpack sources
INC_PATH = -I./
#INC_PATH += -I libs
#INC_PATH += -I/usr/local/include/xtract

#LIB_PATH = -L libs
# executable

#OBJS= RtAudio.o MyAudio.o chuck_fft.o Utilities.o Math.o ofVec2f.o ofVec4f.o MyGraphics.o Waveform.o Spectrum.o Waterfall.o ScrollingWaveform.o Thread.o Stk.o MyOpenGL.o letsPlay.o
OBJS= slgGL.o slgGFX.o test.o

test: $(OBJS)
	$(CXX) -o test $(OBJS) $(LIB_PATH) $(LIBS)

test.o: test.cpp
	$(CXX) $(FLAGS) test.cpp

slgGL.o: slgGL.h slgGL.cpp
	$(CXX) $(FLAGS) slgGL.cpp

slgGFX.o: slgGFX.h slgGFX.cpp
	$(CXX) $(FLAGS) slgGFX.cpp

clean:
	rm -f *~ *# *.o test

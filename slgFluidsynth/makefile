CXX=g++
INCLUDES=

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
FLAGS=-D__UNIX_JACK__ -c
LIBS=-lasound -lpthread -ljack -lstdc++ -lm
endif
ifeq ($(UNAME), Darwin)
FLAGS=-D__MACOSX_CORE__ -c -g
LIBS=-framework CoreAudio -framework CoreMIDI -framework CoreFoundation \
	-framework IOKit -framework Carbon -lstdc++ -lm -lfluidsynth
endif

SLG_DIR = ../slg/
INC_PATH = -I../slg/ -I../RtAudio/ -I../RtMidi/ -I/usr/local/include/
RTA_DIR = ../RtAudio/
RTM_DIR = ../RtMidi/
LIB_PATH = -L/usr/local/lib/


OBJS=   RtAudio.o RtMidi.o slgFluidSynth.o slgAudio.o slgMidi.o test.o

test: $(OBJS)
	$(CXX) -o test $(OBJS) $(LIB_PATH) $(LIBS)

test.o: 
	$(CXX) $(FLAGS) $(INC_PATH) test.cpp

RtMidi.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(RTM_DIR)RtMidi.cpp

RtAudio.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(RTA_DIR)RtAudio.cpp

slgMidi.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgMidi.cpp

slgAudio.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgAudio.cpp

slgFluidSynth.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgFluidSynth.cpp

clean:
	rm -f *~ *# *.o test

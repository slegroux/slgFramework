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
	-framework IOKit -framework Carbon -lstdc++ -lm
endif

SLG_DIR = ../slg/
INC_PATH = -I../slg/ -I../RtAudio/ -I../RtMidi/ 
RTA_DIR = ../RtAudio/
RTM_DIR = ../RtMidi/


OBJS=   RtMidi.o slgMidi.o test.o

test: $(OBJS)
	$(CXX) -o test $(OBJS) $(LIBS)

test.o: 
	$(CXX) $(FLAGS) $(INC_PATH) test.cpp

RtMidi.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(RTM_DIR)RtMidi.cpp

slgMidi.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgMidi.cpp

clean:
	rm -f *~ *# *.o test

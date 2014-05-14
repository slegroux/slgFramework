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

OBJS=   RtMidi.o slgMidi.o test.o

test: $(OBJS)
	$(CXX) -o test $(OBJS) $(LIBS)

test.o: test.cpp slgMidi.h
	$(CXX) $(FLAGS) test.cpp

RtMidi.o: RtMidi/RtMidi.h RtMidi/RtMidi.cpp
	$(CXX) $(FLAGS) RtMidi/RtMidi.cpp

slgMidi.o: slgMidi.h slgMidi.cpp
	$(CXX) $(FLAGS) slgMidi.cpp

clean:
	rm -f *~ *# *.o test

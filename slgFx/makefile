
CXX=g++
INCLUDES=

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
FLAGS=-D__LINUX_ALSASEQ__ -D__UNIX_JACK__ -c
LIBS=-lasound -lpthread -ljack -lstdc++ -lm -lstk
endif
ifeq ($(UNAME), Darwin)
FLAGS=-D__MACOSX_CORE__ -c
LIBS=-framework CoreAudio -framework CoreMIDI -framework CoreFoundation \
	-framework IOKit -framework Carbon -lstdc++ -lm
endif


OBJS=   RtAudio.o slgAudio.o slgFilter.o slgOnePole.o test.o
#OBJS=   RtAudio.o slgAudio.o test.o


test: $(OBJS)
	$(CXX) -o test $(OBJS) $(LIBS)

test.o: test.cpp
	$(CXX) $(FLAGS) test.cpp

RtAudio.o: RtAudio/RtAudio.h RtAudio/RtAudio.cpp RtAudio/RtError.h
	$(CXX) $(FLAGS) RtAudio/RtAudio.cpp

slgAudio.o: slgAudio.h slgAudio.cpp
	$(CXX) $(FLAGS) slgAudio.cpp

slgFilter.o: slgFilter.h slgFilter.cpp
	$(CXX) $(FLAGS) slgFilter.cpp

slgOnePole.o: slgOnePole.h slgOnePole.cpp
	$(CXX) $(FLAGS) slgOnePole.cpp

#slgDelay.o: slgDelay.h slgDelay.cpp
#	$(CXX) $(FLAGS) slgDelay.cpp

clean:
	rm -f *~ *# *.o test

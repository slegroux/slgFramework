CXX=g++
INCLUDES=

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
FLAGS=-D__LINUX_ALSASEQ__ -D__UNIX_JACK__ -c -g
LIBS=-lasound -lpthread -ljack -lstdc++ -lm -lstk
endif
ifeq ($(UNAME), Darwin)
FLAGS=-D__MACOSX_CORE__ -c -w -g -Wall -Wextra -Werror -pedantic
LIBS=-framework CoreAudio -framework CoreMIDI -framework CoreFoundation \
	-framework OpenGL -framework GLUT \
	-framework IOKit -framework Carbon \
	-framework Foundation -framework AppKit \
	-lstdc++ -lm -lfftw3 #-lglui#-lgsl
endif

# include slg classes
INC_PATH = -I../slg/ -I/usr/local/include/
SLG_DIR = ../slg/
INC_PATH += -I../RtAudio/
RTA_DIR = ../RtAudio/


# LIBS
#INC_PATH += -I libs
#INC_PATH += -I/usr/local/include/xtract
LIB_PATH = -L/usr/local/lib/

# executable
TARGET = test

OBJS = Stk.o Thread.o RtAudio.o slgAudio.o slgCircularBuffer.o ScrollingWaveform.o slgGen.o realFFTW.o slgGraphics.o main.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIB_PATH) $(LIBS)

main.o:
	$(CXX) $(FLAGS) $(INC_PATH) main.cpp

slgGraphics.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgGraphics.cpp

realFFTW.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)realFFTW.cpp

slgGen.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgGen.cpp

slgCircularBuffer.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgCircularBuffer.cpp

ScrollingWaveform.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)ScrollingWaveform.cpp

slgAudio.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgAudio.cpp

RtAudio.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(RTA_DIR)RtAudio.cpp

Thread.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)Thread.cpp

Stk.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)Stk.cpp


#slgGFX.o: slgGFX.h slgGFX.cpp
#	$(CXX) $(FLAGS) slgGFX.cpp

clean:
	rm -f *~ *# *.o test

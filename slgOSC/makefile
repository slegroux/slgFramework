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
	-lstdc++ -lm -loscpack#-lstk #-lfftw3 #-lstk#-lgsl
endif

SLG_DIR = ../slg/
RTA_DIR = ../RtAudio/
STK_DIR = ../stk/
OSC_DIR = ../oscpack/
INC_PATH = -I$(SLG_DIR) -I$(RTA_DIR) -I$(STK_DIR) -I$(OSC_DIR) -I/usr/local/include/glm -I/usr/local/include

# LIBS
LIB_PATH = -L/usr/local/lib

# executable
TARGET = test

OBJS = Mutex.o Thread.o RtAudio.o slgAudio.o slgOscillator.o slgApp.o slgMath.o slgPhysics.o slgGraphics.o main.o Stk.o JCRev.o Delay.o OnePole.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIB_PATH) $(LIBS)

main.o:
	$(CXX) $(FLAGS) $(INC_PATH) main.cpp

slgApp.o:
	$(CXX) $(FLAGS) $(INC_PATH) slgApp.cpp

slgGraphics.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgGraphics.cpp

slgPhysics.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgPhysics.cpp

slgMath.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgMath.cpp

slgOscillator.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgOscillator.cpp

slgAudio.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgAudio.cpp

RtAudio.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(RTA_DIR)RtAudio.cpp

JCRev.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(STK_DIR)JCRev.cpp

Stk.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(STK_DIR)Stk.cpp

Delay.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(STK_DIR)Delay.cpp

OnePole.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(STK_DIR)OnePole.cpp

Thread.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(STK_DIR)Thread.cpp	

Mutex.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(STK_DIR)Mutex.cpp

clean:
	rm -f *~ *# *.o test

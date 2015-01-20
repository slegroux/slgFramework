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
	-lstdc++ -lm -lfftw3 #-lgsl
endif

# include slg classes
SLG_DIR = ../slg/
STK_DIR = ../stk/
INC_PATH = -I$(SLG_DIR) -I$(STK_DIR) -I/usr/local/include/glm

# LIBS
#INC_PATH += -I libs
#INC_PATH += -I/usr/local/include/xtract
LIB_PATH = -L/usr/local/lib

# executable
TARGET = test

OBJS = slgApp.o Stk.o Thread.o slgMath.o slgOscillator.o slgPhysics.o slgGraphics.o main.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIB_PATH) $(LIBS)

main.o:
	$(CXX) $(FLAGS) $(INC_PATH) main.cpp

slgApp.o:
	$(CXX) $(FLAGS) $(INC_PATH) slgApp.cpp

slgOscillator.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgOscillator.cpp

slgGraphics.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgGraphics.cpp

slgPhysics.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgPhysics.cpp

slgMath.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgMath.cpp

Thread.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(STK_DIR)Thread.cpp

Stk.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(STK_DIR)Stk.cpp

clean:
	rm -f *~ *# *.o test

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
INC_PATH = -I../slg/ -I/usr/local/include
SLG_DIR = ../slg/

# LIBS
#INC_PATH += -I libs
#INC_PATH += -I/usr/local/include/xtract
LIB_PATH = -L/usr/local/lib

# executable
TARGET = test

OBJS = slgGen.o realFFTW.o slg2D.o main.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIB_PATH) $(LIBS)

main.o:
	$(CXX) $(FLAGS) $(INC_PATH) main.cpp

slg2D.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slg2D.cpp

realFFTW.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)realFFTW.cpp

slgGen.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgGen.cpp

#slgGFX.o: slgGFX.h slgGFX.cpp
#	$(CXX) $(FLAGS) slgGFX.cpp

clean:
	rm -f *~ *# *.o test

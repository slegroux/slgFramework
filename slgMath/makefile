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
	-framework OpenGL -framework GLUT \
	-framework IOKit -framework Carbon -lstdc++ -lm #-lfftw3
endif

# include headers
INC_PATH = -I../slg/
SLG_DIR = ../slg/

# executable
TARGET = test

OBJS= slgMath.o main.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIB_PATH) $(LIBS)

main.o:
	$(CXX) $(FLAGS) $(INC_PATH) main.cpp

slgMath.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgMath.cpp

clean:
	rm -f *~ *# *.o test

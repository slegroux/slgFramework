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

# include headers
INC_PATH = -I../slg/
SLG_DIR = ../slg/

# executable
TARGET = test

OBJS = camera.o main.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIB_PATH) $(LIBS)

main.o:
	$(CXX) $(FLAGS) $(INC_PATH) main.cpp

camera.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)camera.cpp

clean:
	rm -f *~ *# *.o $(TARGET)

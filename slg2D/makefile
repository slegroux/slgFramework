CXX=g++
INCLUDES=

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
#FLAGS=-D__LINUX_ALSASEQ__ -D__UNIX_JACK__ -c
#LIBS=-lasound -lpthread -ljack -lstdc++ -lm -lstk
FLAGS=-D__LINUX_PULSE__ -D__USE_GLUT__ -c
LIB_PATH = -L/usr/X11R6/lib
LIBS=-Wall -lpthread -lpulse-simple -lpulse -lstdc++ -lm -lglut -lGL -lGLU -lXmu -lX11 -lXext -lXi

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
INC_PATH = -I../slg/ -I/usr/local/include -I../glm/
SLG_DIR = ../slg/

# executable
TARGET = test

OBJS = slgApp.o slgGraphics.o main.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIB_PATH) $(LIBS)

main.o:
	$(CXX) $(FLAGS) $(INC_PATH) main.cpp

slgApp.o:
	$(CXX) $(FLAGS) $(INC_PATH) slgApp.cpp

slgGraphics.o:
	$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgGraphics.cpp

clean:
	rm -f *~ *.o test

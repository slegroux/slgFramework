
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
	-framework IOKit -framework Carbon -lstdc++ -lm
endif

# include slg classes
INC_PATH = -I../slg/
INC_PATH += -I../RtAudio/
SLG_DIR = ../slg/
RTA_DIR += ../RtAudio/

# LIBS
#INC_PATH += -I libs
#INC_PATH += -I/usr/local/include/xtract
#LIB_PATH = -L libs

# executable
TARGET = test

OBJS = RtAudio.o slgAudio.o main.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIB_PATH) $(LIBS)

main.o:
	$(CXX) $(FLAGS) $(INC_PATH) main.cpp

slgAudio.o:
		$(CXX) $(FLAGS) $(INC_PATH) $(SLG_DIR)slgAudio.cpp

RtAudio.o:
		$(CXX) $(FLAGS) $(INC_PATH) $(RTA_DIR)RtAudio.cpp

clean:
	rm -f *~ *# *.o $(TARGET)

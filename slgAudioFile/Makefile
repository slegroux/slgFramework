CXX=g++

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	# FLAGS=-D__LINUX_ALSASEQ__ -D__UNIX_JACK__ -c
	# LIBS=-lasound -lpthread -ljack -lstdc++ -lm
	CFLAGS=-D__LINUX_PULSE__ -c
	LDFLAGS=-Wall -lpthread -lpulse-simple -lpulse -lstdc++ -lm
endif
ifeq ($(UNAME), Darwin)
	CFLAGS=-D__MACOSX_CORE__ -Wall -c -Wextra
	LDFLAGS=-lsndfile
endif

INC_PATH += -I../slg/
LIB_PATH =

# executable
TARGET = test
OBJS = test.o slgAudioFile.o

#library
TARGET_LIB = libslgaudiofile.a
SRCS_LIB = slgAudioFile.cpp
OBJS_LIB = $(SRCS_LIB:.cpp=.o)

.PHONY: all
all: ${TARGET}

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIB_PATH) $(LDFLAGS)

test.o:
	$(CXX) $(CFLAGS) $(INC_PATH) test.cpp

slgAudioFile.o:
	$(CXX) $(CFLAGS) $(INC_PATH) slgAudioFile.cpp

.PHONY: staticlib
staticlib: ${TARGET_LIB}
$(TARGET_LIB): $(OBJS_LIB)
	ar -rv ${TARGET_LIB} slgAudioFile.o

.PHONY: test
test: ${TARGET}
test: test.o
	$(CXX) -o ${TARGET} test.cpp $(LIB_PATH) $(LDFLAGS) -lslgaudiofile

install:
	cp ${TARGET_LIB} /usr/local/lib
	cp slgAudioFile.h /usr/local/include

.PHONY: clean
clean:
	rm -f *~ *# *.a $(OBJS) $(TARGET)

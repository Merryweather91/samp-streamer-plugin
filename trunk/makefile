CXX = g++

INCLUDES = -I./include
LIBS = -lboost_system -lsampgdk -lrt

CXXFLAGS = -O3 -ffast-math -fno-strict-aliasing -fmerge-all-constants -fvisibility=hidden -fvisibility-inlines-hidden -Wall
LDFLAGS = -s -shared -m32 -L./lib/linux/boost/ -L./lib/linux/sampgdk/

BINDIR = ./bin/linux
OBJDIR = ./obj/linux
SRCDIR = ./src

TARGET = $(BINDIR)/streamer.so

all:
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)
	$(CXX) -c $(SRCDIR)/*.cpp $(CXXFLAGS) $(INCLUDES)
	mv *.o $(OBJDIR)
	$(CXX) -o $(TARGET) $(OBJDIR)/*.o $(LDFLAGS) $(LIBS)

clean:
	rm -f ./*.o
	rm -rf ./bin
	rm -rf ./obj

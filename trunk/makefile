CXX = g++
CXXFLAGS = -O3 -ffast-math -fno-strict-aliasing -fmerge-all-constants -fvisibility=hidden -fvisibility-inlines-hidden -Wall -I./include/
LDFLAGS = -s -shared -L./lib/linux/boost/ -L./lib/linux/sampgdk/ -lboost_system -lsampgdk -lrt

OUT = ./streamer.so
SRC = ./src/*.cpp

all:
	$(CXX) -c $(SRC) $(CXXFLAGS)
	$(CXX) -o $(OUT) *.o $(LDFLAGS)
	-rm -f *.o

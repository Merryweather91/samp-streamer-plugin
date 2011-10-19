CXX = g++
CXXFLAGS = -O3 -ffast-math -fno-strict-aliasing -fmerge-all-constants -fvisibility=hidden -fvisibility-inlines-hidden -Wall -I./Libraries/
LDFLAGS = -s -shared -L./Libraries/boost/ -lboost_system -lrt

OUT = ./streamer.so
SRC = ./Libraries/sampgdk/*.cpp ./Source/*.cpp ./*.cpp

all:
	$(CXX) -c $(SRC) $(CXXFLAGS)
	$(CXX) -o $(OUT) *.o $(LDFLAGS)
	-rm -f *.o

CXX = g++
CXXFLAGS = -O3 -fno-strict-aliasing -fmerge-all-constants -fvisibility=hidden -ffunction-sections -fdata-sections -Wall -I./
LDFLAGS = -Wl,--gc-sections -s -shared

OUT = ./streamer.so
SRC = ./SDK/*.cpp ./Source/*.cpp ./*.cpp

all:
	$(CXX) -c $(SRC) $(CXXFLAGS)
	$(CXX) $(LDFLAGS) -o $(OUT) *.o
	-rm -f *.o

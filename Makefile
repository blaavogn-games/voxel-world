LFLAGS = -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl
OFLAGS = -std=c++11 -Wall -O3
CPP_FILES := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)


all:
	g++-4.9 $(OFLAGS) -o bin/$(file) $(file).cpp $(HELPERS) $(CPP_FILES) $(LFLAGS) -fmax-errors=3

debug:
	g++-4.9 $(OFLAGS) -g -o bin/$(file) $(file).cpp $(HELPERS) $(CPP_FILES) $(LFLAGS) -fmax-errors=3

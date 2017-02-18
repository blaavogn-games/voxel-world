LFLAGS = -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl
OFLAGS = -std=c++11 -Wall -O3 

all: 
	g++-4.9 $(OFLAGS) -o bin/$(file) Shader.cpp Window.cpp $(file).cpp $(LFLAGS) 

debug: 
	g++-4.9 $(OFLAGS) -g -o bin/$(file) Shader.cpp Window.cpp $(file).cpp $(LFLAGS) 

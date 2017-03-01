#ifndef WINDOW_H
#define WINDOW_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <stdio.h>

class Window
{
	public:
  	static GLFWwindow* Init(GLuint WIDTH, 
  												  GLuint HEIGHT, 
  												  void (*keyCallback) (GLFWwindow*, int, int, int, int),
  												  void (*mouseClickCallback) (GLFWwindow*, int, int, int),
  												  void (*cursorPosCallback) (GLFWwindow*, double, double));
};
  
#endif
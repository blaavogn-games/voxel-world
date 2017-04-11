#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <stdio.h>
#include "Window.h"

void error(int i, const char* str){
  printf("GLFW-error:\n %s\n", str);
}

GLFWwindow* Window::Init(GLuint WIDTH,
                         GLuint HEIGHT,
                         void (*keyCallBack) (GLFWwindow*, int, int, int, int),
                         void (*mouseClickCallback) (GLFWwindow*, int, int, int),
                         void (*cursorPosCallback) (GLFWwindow*, double, double))
{
  if (!glfwInit())
  {
    printf("Init error\n");
    return NULL;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  glfwSetErrorCallback(error);
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Exercises", NULL, NULL);

  if (!window)
  {
    printf("Winod error\n");
    glfwTerminate();
    return NULL;
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, keyCallBack);
  glfwSetMouseButtonCallback(window, mouseClickCallback);
  glfwSetCursorPosCallback(window, cursorPosCallback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  glewExperimental = GL_TRUE;
  glewInit();
  glViewport(0, 0, WIDTH, HEIGHT);

  glEnable(GL_POINT_SPRITE);
  glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
  // glEnable(GL_BLEND);
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  return window;
}

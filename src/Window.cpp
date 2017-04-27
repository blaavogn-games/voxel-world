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
  // GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Exercises", glfwGetPrimaryMonitor(), NULL);
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
  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glewExperimental = GL_TRUE;
  glewInit();
  glViewport(0, 0, WIDTH, HEIGHT);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  const unsigned char * version ;
  version = (const unsigned char *)glGetString(GL_VENDOR);
  printf ("Vendor: %s\n", version);

  return window;
}

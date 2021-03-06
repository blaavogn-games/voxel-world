#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "src/Timer.h"
#include "src/Shader.h"
#include "src/draw3d/Box.h"
#include "src/Window.h"

const GLuint WIDTH = 600, HEIGHT = 600;
Timer timer;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void cursorCallback(GLFWwindow* window, double xPos, double yPos);
void mouseClickCallback(GLFWwindow* window, int button, int action, int mode);
void DrawCircle(float cx, float cy, float r, int num_segments);

using namespace glm;

int main() {
  GLFWwindow* window = Window::Init(WIDTH, HEIGHT, &keyCallback, &mouseClickCallback, &cursorCallback);
  if(!window){
    printf("Something went wrong with window initialization\n");
    exit(-1);
  }

  Box box1;
  box1.transform.Scale(vec3(1.3f,1,1));
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    if(timer.IsPaused())
      continue;
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    box1.Draw(timer.GetMs());
    glfwSwapBuffers(window);
  }
  glfwTerminate();
  return 0;
}

double tCord(double v, double max){
  return v * 2 / max - 1;
}

void cursorCallback(GLFWwindow* window, double xPos, double yPos)
{
  if(timer.IsPaused())
    return;
}

void mouseClickCallback(GLFWwindow* window, int button, int action, int mode)
{
  // double xpos, ypos;
  // glfwGetCursorPos(window, &xpos, &ypos);
  // int i = particleInfo * curParticle;
  // vertices[i] = tCord(xpos, WIDTH);
  // vertices[i + 1] = tCord(HEIGHT - ypos, HEIGHT);
  // curParticle = (curParticle + 1) % particleNum;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if(action == GLFW_PRESS){
    if(timer.IsPaused())
      timer.Resume();
    else
      timer.Pause();
  }
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

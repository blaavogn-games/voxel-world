#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <vector>
#include "src/Timer.h"
#include "src/shader/Shader.h"
#include "src/draw3d/Box.h"
#include "src/Window.h"

const GLuint WIDTH = 600, HEIGHT = 600;
Timer timer;
Camera camera;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void cursorCallback(GLFWwindow* window, double xPos, double yPos);
void mouseClickCallback(GLFWwindow* window, int button, int action, int mode);
void DrawCircle(float cx, float cy, float r, int num_segments);

using namespace glm;

std::vector<Box*> voxels;

int main() {
  GLFWwindow* window = Window::Init(WIDTH, HEIGHT, &keyCallback, &mouseClickCallback, &cursorCallback);
  if (!window){
    printf("Something went wrong with window initialization\n");
    exit(-1);
  }

  for (int x = 0; x < 200; x++){
    for (int z = 0; z < 200; z++){
      Box *box = new Box();
      box->transform.Translate(glm::vec3(x * 2, 0, z * 2));
      voxels.push_back(box);
    }
  }

  camera.Translate(glm::vec3(0,14.0f,-1.0f));
  camera.LookAt(glm::vec3(0.0f,0.01f,0.01f), glm::vec3(0,1,0));

  float lastTime = timer.GetMs();
  while (!glfwWindowShouldClose(window))
  {
    float time = timer.GetMs();
    float deltaTime = time-lastTime;
    glfwPollEvents();
    if (timer.IsPaused())
      continue;

    camera.Translate(glm::vec3(0.0005f * deltaTime,0.000f,0.00045f * deltaTime));
    ShaderManager::SetCamera(camera);

    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render
    printf("FPS: %f\n", 1000.0f/(time-lastTime));
    for(auto &box : voxels){
      box->Draw(time);
    }
    lastTime = time;
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

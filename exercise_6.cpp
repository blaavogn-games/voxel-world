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
#include "src/draw3d/VoxelRenderer.h"
#include "src/Window.h"
#include "src/world/VoxelByteNote.h"

const GLuint WIDTH = 600, HEIGHT = 600;
Timer timer;
Camera camera;
VoxelByteNote voxelByteNote(0,0,0);

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void cursorCallback(GLFWwindow* window, double xPos, double yPos);
void mouseClickCallback(GLFWwindow* window, int button, int action, int mode);
void DrawCircle(float cx, float cy, float r, int num_segments);

using namespace glm;

int main() {
  GLFWwindow* window = Window::Init(WIDTH, HEIGHT, &keyCallback, &mouseClickCallback, &cursorCallback);
  if (!window){
    printf("Something went wrong with window initialization\n");
    exit(-1);
  }

  VoxelRenderer *voxelRenderer = new VoxelRenderer();

  camera.Translate(glm::vec3(-15f,34.0f,-15f));
  camera.LookAt(glm::vec3(17f,0.01f,17f), glm::vec3(0,1,0));

  float lastTime = timer.GetMs();
  while (!glfwWindowShouldClose(window))
  {
    float time = timer.GetMs();
    float deltaTime = time-lastTime;
    glfwPollEvents();
    if (timer.IsPaused())
      continue;

    camera.Translate(glm::vec3(-0.005f * deltaTime,0.000f,-0.005f * deltaTime));
    ShaderManager::SetCamera(camera);

    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render
    // printf("FPS: %f\n", 1000.0f/(time-lastTime));
    int camX = (int) -camera.position.x;
    int camZ = (int) -camera.position.z;
    // voxelByteNote.Traverse(7, 0, 0, 44, 31, 1, voxelRenderer);
    voxelByteNote.Traverse(std::max(0, camX - 10), 0, std::max(0, camZ - 10), camX + 10, 31, camZ + 10, voxelRenderer);

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

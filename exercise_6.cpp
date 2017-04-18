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
#include "src/io/Input.h"
#include "src/Window.h"
#include "src/world/VoxelByteNote.h"

// const GLuint WIDTH = 1366, HEIGHT = 768;
const GLuint WIDTH = 800, HEIGHT = 800;
Timer timer;
Camera camera;
VoxelByteNote voxelByteNote(0,0,0);

void cursorCallback(GLFWwindow* window, double xPos, double yPos);
void mouseClickCallback(GLFWwindow* window, int button, int action, int mode);
void DrawCircle(float cx, float cy, float r, int num_segments);

using namespace glm;

int main() {
  GLFWwindow* window = Window::Init(WIDTH, HEIGHT, &Input::KeyCallback, &mouseClickCallback, &cursorCallback);
  if (!window){
    printf("Something went wrong with window initialization\n");
    exit(-1);
  }

  VoxelRenderer::StaticInit();

  camera.Translate(glm::vec3(-16.0f,0.0f,-16.0f));
  camera.LookHorizontal(45);

  float lastTime = timer.GetMs();
  while (!glfwWindowShouldClose(window))
  {
    float time = timer.GetMs();
    float deltaTime = time-lastTime;
    glfwPollEvents();
    if (timer.IsPaused())
      continue;

    Input::Reset();
    ShaderManager::SetCamera(&camera);
    glClearColor(0.8f,0.8f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render
    printf("FPS: %f, voxels: %d\n", 1000.0f/(time-lastTime), VoxelRenderer::c);
    VoxelRenderer::c = 0;
    camera.Update();
    voxelByteNote.Traverse(camera);
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


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

// const GLuint WIDTH = 1366, HEIGHT = 768;
const GLuint WIDTH = 800, HEIGHT = 800;
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

  camera.Translate(glm::vec3(16.0f,32.0f,16.0f));
  camera.Translate(glm::vec3(100.0f,0.0f,100.0f));
  camera.Print();

  float lastTime = timer.GetMs();
  while (!glfwWindowShouldClose(window))
  {
    float time = timer.GetMs();
    float deltaTime = time-lastTime;
    glfwPollEvents();
    if (timer.IsPaused())
      continue;

    ShaderManager::SetCamera(camera);

    glClearColor(0.8f,0.8f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render
    // printf("FPS: %f\n", 1000.0f/(time-lastTime));
    int camX = (int) camera.position.x;
    int camY = (int) camera.position.y;
    int camZ = (int) camera.position.z;
    // camera.Print();
    // float pp = 60.0f;
    float pp = 60.0f;
    int minX = std::max(camX - pp * (2.0f-(camera.front.x + 1.0f)) * (2.0f-(camera.front.x + 1.0f)), 0.0f);
    int maxX = std::max(camX + pp * (camera.front.x + 1.0f), 0.0f);
    printf("%d, %d\n", minX, maxX);
    voxelByteNote.Traverse(minX,
                           0,
                           std::max(0,(int) (camZ - pp * (2.0f-(camera.front.z + 1.0f)) * (2.0f-(camera.front.z + 1.0f)))),
                           maxX,
                           31,
                           camZ + pp * (camera.front.z + 1.0f),
                           voxelRenderer);

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
  if(key == GLFW_KEY_W)
    camera.Translate(camera.front * 0.1f);
  if(key == GLFW_KEY_S)
    camera.Translate(camera.front * -0.1f);
  if(key == GLFW_KEY_D)
    camera.Translate(glm::normalize(glm::cross(camera.up,camera.front)) * -0.1f);
  if(key == GLFW_KEY_A)
    camera.Translate(glm::normalize(glm::cross(camera.up,camera.front)) * 0.1f);
  if(key == GLFW_KEY_UP)
    camera.LookVertical(1);
  if(key == GLFW_KEY_DOWN)
    camera.LookVertical(-1);
  if(key == GLFW_KEY_RIGHT)
    camera.LookHorizontal(1);
  if(key == GLFW_KEY_LEFT)
    camera.LookHorizontal(-1);
  if(key == GLFW_KEY_Q && action == GLFW_PRESS){
    if(timer.IsPaused()){
      timer.Resume();
    }
    else{
      timer.Pause();
    }
  }

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

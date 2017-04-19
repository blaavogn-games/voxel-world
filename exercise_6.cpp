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

  while (!glfwWindowShouldClose(window))
  {
    //Handling event and time in "static classes"
    glfwPollEvents();
    Timer::Tick();
    if (Timer::IsPaused())
      continue;
    Input::Reset();

    ShaderManager::SetCamera(&camera);
    glClearColor(0.8f,0.8f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render
    printf("FPS: %f, voxels: %d\n", 1.0f/Timer::DeltaTime, VoxelRenderer::c);
    VoxelRenderer::c = 0;
    camera.Update();
    voxelByteNote.Traverse(camera);
    glfwSwapBuffers(window);
  }
  glfwTerminate();
  return 0;
}

//These should be moved to Input.h
void cursorCallback(GLFWwindow* window, double xPos, double yPos)
{
}

void mouseClickCallback(GLFWwindow* window, int button, int action, int mode)
{
}


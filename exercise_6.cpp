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
#include "src/world/VoxelTypes.h"
#include "src/obj/CameraHandler.h"

// const GLuint WIDTH = 1366, HEIGHT = 768;
const GLuint WIDTH = 600, HEIGHT = 600;
Camera camera;
VoxelByteNote* VoxelByteNote::Root = new VoxelByteNote(0,0,0);

void mouseClickCallback(GLFWwindow* window, int button, int action, int mode);

using namespace glm;

int main() {
  GLFWwindow* window = Window::Init(WIDTH, HEIGHT, &Input::KeyCallback, &mouseClickCallback, &Input::CursorCallback);
  if (!window){
    printf("Something went wrong with window initialization\n");
    exit(-1);
  }

  //Initialising static data
  for(int i = 0; i < 1024; i++){
    Input::Key[i] = false;
    Input::KeyUp[i] = false;
    Input::KeyDown[i] = false;
  }
  VoxelRenderer::StaticInit();
  VoxelTypes::StaticInit();

  CameraHandler cameraHandler(&camera);

  while (!glfwWindowShouldClose(window))
  {
    //Handling event and time in "static classes"
    Input::Reset();
    glfwPollEvents();
    Timer::Tick();
    if (Timer::IsPaused())
      continue;

    // glClearColor(0.24f,0.2f,0.8f,1.0f);
    glClearColor(0.2f,0.2f,0.7f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render
    // printf("FPS: %f, voxels: %d\n", 1.0f/Timer::DeltaTime, VoxelRenderer::c);
    VoxelRenderer::c = 0;
    cameraHandler.Update();

    glm::vec3 lightPosition(camera.position.x + cos(Timer::Time * .5f) * (1000 + sin(Timer::Time * .5f) * 1000),
                             camera.position.y + sin(Timer::Time * .5f) * 2000,
                             camera.position.z + sin(Timer::Time * .5f) * 500);
    ShaderManager::SetCamera(&camera, &lightPosition);

    //Skybox
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    VoxelRenderer::Draw(camera.position.x + cos(Timer::Time * .5f) * (10 + sin(Timer::Time * .5f) * 10),
                        camera.position.y + sin(Timer::Time * .5f) * 20,
                        camera.position.z + sin(Timer::Time * .5f) * 5, 0);
    glEnable(GL_DEPTH_TEST);
    VoxelByteNote::Root->Traverse(camera, false);
    glEnable(GL_BLEND);
    VoxelByteNote::Root->Traverse(camera, true);
    glfwSwapBuffers(window);
  }
  glfwTerminate();
  return 0;
}

void mouseClickCallback(GLFWwindow* window, int button, int action, int mode)
{
}

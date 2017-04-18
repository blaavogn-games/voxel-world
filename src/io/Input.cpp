#include "Input.h"

bool* Input::Key = new bool[1024];
bool* Input::KeyUp = new bool[1024];
bool* Input::KeyDown = new bool[1024];

void Input::Reset(){
  for(int i = 0; i < 1024; i++){
    KeyDown[i] = false;
    KeyUp[i] = false;
  }
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode){
  if(action == GLFW_PRESS)
  {
    Key[key] = true;
    KeyDown[key] = true;
  }
  else if(action == GLFW_RELEASE)
  {
    Key[key] = false;
    KeyUp[key] = true;
  }

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

#include "Input.h"

bool*  Input::Key = new bool[1024];
bool*  Input::KeyUp = new bool[1024];
bool*  Input::KeyDown = new bool[1024];
double Input::lastX = 0;
double Input::lastY = 0;
double Input::DeltaX = 0;
double Input::DeltaY = 0;

void Input::Reset(){
  for(int i = 0; i < 1024; i++){
    KeyDown[i] = false;
    KeyUp[i] = false;
  }
  DeltaX = 0;
  DeltaY = 0;
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode){
  if (action == GLFW_PRESS)
  {
    Key[key] = true;
    KeyDown[key] = true;
  }
  else if (action == GLFW_RELEASE)
  {
    Key[key] = false;
    KeyUp[key] = true;
  }
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void Input::CursorCallback(GLFWwindow* window, double xPos, double yPos){
  DeltaX = lastX - xPos;
  DeltaY = yPos - lastY;
  lastY = yPos;
  lastX = xPos;
}

#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../geom/Transform.h"

class Input
{
  private:

  public:
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void Reset();
    static bool *Key;
    static bool *KeyDown;
    static bool *KeyUp;
};

#endif

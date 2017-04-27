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
    static double lastX, lastY;
  public:
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void CursorCallback(GLFWwindow* window, double xPos, double yPos);
    static void Reset();
    static bool *Key;
    static bool *KeyDown;
    static bool *KeyUp;
    static double DeltaX;
    static double DeltaY;
};

#endif
